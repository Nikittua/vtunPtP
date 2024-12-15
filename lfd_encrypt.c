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
#include <libakrypt.h>


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

#include <stdio.h>
#include <string.h>
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
#include <syslog.h>
#include <libakrypt.h>

#define ENC_BUF_SIZE (VTUN_FRAME_SIZE + 16)
#define SALT_SIZE 4  // "rand", 4 bytes

typedef struct {
    struct bckey bkey;  // bckey structure, not a pointer
    char *enc_buf;      // Encryption buffer
} encrypt_context;

static encrypt_context ctx = {0};

int alloc_encrypt(struct vtun_host *host)
{
    int error = ak_error_ok;
    const char salt[SALT_SIZE] = "rand";  // fixed salt
     
    ctx.enc_buf = lfd_alloc(ENC_BUF_SIZE);
    if (ctx.enc_buf == NULL) {
        syslog(LOG_ERR, "Can't allocate buffer for encryptor");
        return -1;
    }

    if (ak_libakrypt_create(NULL) != ak_true) {
        syslog(LOG_ERR, "Failed to initialize libakrypt");
        lfd_free(ctx.enc_buf);
        ctx.enc_buf = NULL;
        return -1;
    }

    error = ak_bckey_create_oid(&ctx.bkey, ak_oid_find_by_name("kuznechik"));
    if (error != ak_error_ok) {
        ak_error_message(error, __func__, "Failed to create block cipher key context");
        ak_libakrypt_destroy();
        lfd_free(ctx.enc_buf);
        ctx.enc_buf = NULL;
        return -1;
    }

    error = ak_bckey_set_key_from_password(&ctx.bkey,
                                           host->passwd, strlen(host->passwd),
                                           salt, SALT_SIZE);
    if (error != ak_error_ok) {
        ak_error_message(error, __func__, "Failed to set key from password");
        ak_bckey_destroy(&ctx.bkey);
        ak_libakrypt_destroy();
        lfd_free(ctx.enc_buf);
        ctx.enc_buf = NULL;
        return -1;
    }

    syslog(LOG_INFO, "libakrypt encryption initialized with Kuznechik cipher");
    return 0;
}

int free_encrypt()
{
    if (ctx.enc_buf) {
        lfd_free(ctx.enc_buf);
        ctx.enc_buf = NULL;
    }
    ak_bckey_destroy(&ctx.bkey);
    ak_libakrypt_destroy();
    return 0;
}

int encrypt_buf(int len, char *in, char **out)
{
    int pad;
    size_t total_len;
    char *out_ptr = ctx.enc_buf;
    int error;

    pad = ctx.bkey.bsize - (len % ctx.bkey.bsize);
    if (pad == 0) pad = ctx.bkey.bsize;

    total_len = len + pad;
    if (total_len > ENC_BUF_SIZE) {
        syslog(LOG_ERR, "Encrypted buffer size is insufficient");
        return -1;
    }

    memset(out_ptr, pad, pad);
    memcpy(out_ptr + pad, in, len);

    error = ak_bckey_encrypt_ecb(&ctx.bkey,
                                 (const ak_pointer)out_ptr,
                                 (ak_pointer)out_ptr,
                                 total_len);
    if (error != ak_error_ok) {
        ak_error_message(error, __func__, "Encryption failed");
        return -1;
    }

    *out = ctx.enc_buf;
    return total_len;
}

int decrypt_buf(int len, char *in, char **out)
{
    int pad;
    int error;

    error = ak_bckey_decrypt_ecb(&ctx.bkey,
                                 (const ak_pointer)in,
                                 (ak_pointer)in,
                                 len);
    if (error != ak_error_ok) {
        ak_error_message(error, __func__, "Decryption failed");
        return -1;
    }

    pad = (unsigned char)*in;
    if (pad < 1 || pad > ctx.bkey.bsize) {
        syslog(LOG_INFO, "decrypt_buf: bad pad length");
        return 0;
    }

    *out = in + pad;
    return len - pad;
}

struct lfd_mod lfd_encrypt = {
     "libakrypt Encryptor",
     alloc_encrypt,
     encrypt_buf,
     NULL,          // No additional initialization
     decrypt_buf,
     NULL,          // No additional processing
     free_encrypt,
     NULL,          // No additional cleanup
     NULL           // No additional functions
};

#endif /* HAVE_SSL */


