/*  
    VTun - Virtual Tunnel over TCP/IP network.

    Copyright (C) 1998-2000  Maxim Krasnyansky <max_mk@yahoo.com>

    VTun has been derived from VPPP package by Maxim Krasnyansky. 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 */

/*
 * lfd_encrypt.c,v 1.2.2.5 2001/06/07 15:35:12 maxk Exp
 */ 

/*
   Encryption module uses software developed by the OpenSSL Project
   for use in the OpenSSL Toolkit. (http://www.openssl.org/)       
   Copyright (c) 1998-2000 The OpenSSL Project.  All rights reserved.
 */

/*
 * This lfd_encrypt module uses MD5 to create 128 bits encryption
 * keys and BlowFish for actual data encryption.
 * It is based on code written by Chris Todd<christ@insynq.com> with 
 * several improvements and modifications by me.  
 */

#include "config.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <strings.h>
#include <string.h>

#include "vtun.h"
#include "linkfd.h"
#include "lib.h"

#ifdef HAVE_SSL

#include <md5.h>
#include <blowfish.h>

#define ENC_BUF_SIZE VTUN_FRAME_SIZE + 16 
#define ENC_KEY_SIZE 16

BF_KEY key;
char * enc_buf;

int alloc_encrypt(struct vtun_host *host)
{
   if( !(enc_buf = lfd_alloc(ENC_BUF_SIZE)) ){
      syslog(LOG_ERR,"Can't allocate buffer for encryptor");
      return -1;
   }

   BF_set_key(&key, ENC_KEY_SIZE, MD5(host->passwd,strlen(host->passwd),NULL));

   syslog(LOG_INFO, "BlowFish encryption initialized");
   return 0;
}

int free_encrypt()
{
   lfd_free(enc_buf); enc_buf = NULL;
   return 0;
}

int encrypt_buf(int len, char *in, char **out)
{ 
   register int pad, p;
   register char *in_ptr = in, *out_ptr = enc_buf;

   /* 8 - ( len % 8 ) */
   pad = (~len & 0x07) + 1; p = 8 - pad;

   memset(out_ptr, 0, pad);
   *out_ptr = (char) pad;
   memcpy(out_ptr + pad, in_ptr, p);  
   BF_ecb_encrypt(out_ptr, out_ptr, &key, BF_ENCRYPT);
   out_ptr += 8; in_ptr += p; 
   len = len - p;

   for (p=0; p < len; p += 8)
      BF_ecb_encrypt(in_ptr + p,  out_ptr + p, &key, BF_ENCRYPT);

   *out = enc_buf;
   return len + 8;
}

int decrypt_buf(int len, char *in, char **out)
{
   register int p;

   for (p = 0; p < len; p += 8)
      BF_ecb_encrypt(in + p, in + p, &key, BF_DECRYPT);

   p = *in;
   if (p < 1 || p > 8) {
      syslog(LOG_INFO, "decrypt_buf: bad pad length");
      return 0;
   }

   *out = in + p;

   return len - p;
}

/* 
 * Module structure.
 */
struct lfd_mod lfd_encrypt = {
     "Encryptor",
     alloc_encrypt,
     encrypt_buf,
     NULL,
     decrypt_buf,
     NULL,
     free_encrypt,
     NULL,
     NULL
};

#else  /* HAVE_SSL */

#include <libakrypt.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <stdint.h>


#define ENC_BUF_SIZE (VTUN_FRAME_SIZE + 128)
#define KUZNECHIK_BLOCK_SIZE 128

static char *enc_buf = NULL;
static struct bckey kuznechik_key;
static uint8_t iv[KUZNECHIK_BLOCK_SIZE] = {0};

int alloc_encrypt(struct vtun_host *host)
{
    // Выделяем буфер для шифрования
    if (!(enc_buf = lfd_alloc(ENC_BUF_SIZE))) {
        syslog(LOG_ERR, "Can't allocate buffer for encryptor");
        return -1;
    }

    // Инициализация ключа "Кузнечик"
    if (ak_bckey_create_kuznechik(&kuznechik_key) != ak_error_ok) {
        syslog(LOG_ERR, "Failed to create Kuznechik key");
        lfd_free(enc_buf);
        return -1;
    }

    // Устанавливаем ключ (например, все байты равны 0x01 для теста)
    uint8_t key[32];
    memset(key, 0x01, sizeof(key));

    if (ak_bckey_set_key(&kuznechik_key, key, sizeof(key)) != ak_error_ok) {
        syslog(LOG_ERR, "Failed to set Kuznechik key");
        ak_bckey_destroy(&kuznechik_key);
        lfd_free(enc_buf);
        return -1;
    }

    syslog(LOG_INFO, "Kuznechik encryption initialized");
    return 0;
}

int free_encrypt()
{
    ak_bckey_destroy(&kuznechik_key);
    lfd_free(enc_buf);
    enc_buf = NULL;
    return 0;
}

int encrypt_buf(int len, char *in, char **out)
{
    // Шифрование с использованием режима CBC
    if (ak_bckey_encrypt_cbc(&kuznechik_key, in, enc_buf, len, iv, KUZNECHIK_BLOCK_SIZE) != ak_error_ok) {
        syslog(LOG_ERR, "Encryption failed");
        return -1;
    }

    *out = enc_buf;
    return len;
}

int decrypt_buf(int len, char *in, char **out)
{
    // Расшифровка с использованием режима CBC
    if (ak_bckey_decrypt_cbc(&kuznechik_key, in, enc_buf, len, iv, KUZNECHIK_BLOCK_SIZE) != ak_error_ok) {
        syslog(LOG_ERR, "Decryption failed");
        return -1;
    }

    *out = enc_buf;
    return len;
}

/* 
 * Структура модуля.
 */
struct lfd_mod lfd_encrypt = {
    "Encryptor",
    alloc_encrypt,
    encrypt_buf,
    NULL,
    decrypt_buf,
    NULL,
    free_encrypt,
    NULL,
    NULL
};

#endif /* HAVE_SSL */


