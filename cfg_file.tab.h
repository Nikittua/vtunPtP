#ifndef _yy_defines_h_
#define _yy_defines_h_

#define K_OPTIONS 257
#define K_DEFAULT 258
#define K_PORT 259
#define K_PERSIST 260
#define K_TIMEOUT 261
#define K_PASSWD 262
#define K_PROG 263
#define K_PPP 264
#define K_SPEED 265
#define K_IFCFG 266
#define K_FWALL 267
#define K_ROUTE 268
#define K_DEVICE 269
#define K_MULTI 270
#define K_SRCADDR 271
#define K_IFACE 272
#define K_ADDR 273
#define K_TYPE 274
#define K_PROT 275
#define K_COMPRESS 276
#define K_ENCRYPT 277
#define K_KALIVE 278
#define K_STAT 279
#define K_UP 280
#define K_DOWN 281
#define K_SYSLOG 282
#define K_IPROUTE 283
#define K_HOST 284
#define K_ERROR 285
#define WORD 286
#define PATH 287
#define STRING 288
#define NUM 289
#define DNUM 290
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE {
   char *str;
   int  num;
   struct { int num1; int num2; } dnum;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
