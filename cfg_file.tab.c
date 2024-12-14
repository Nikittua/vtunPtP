/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20220114

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "cfg_file.y"
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
 * cfg_file.y,v 1.1.1.2.2.11 2001/12/29 17:01:01 bergolth Exp
 */ 

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <syslog.h>

#include "compat.h"
#include "vtun.h"

int lineno = 1;

struct vtun_host *parse_host;
extern struct vtun_host default_host;

llist  *parse_cmds;
struct vtun_cmd parse_cmd;

llist host_list;

int  cfg_error(const char *fmt, ...);
int  add_cmd(llist *cmds, char *prog, char *args, int flags);
void *cp_cmd(void *d, void *u);
int  free_cmd(void *d, void *u);

void copy_addr(struct vtun_host *to, struct vtun_host *from);
int  free_host(void *d, void *u);
void free_addr(struct vtun_host *h);
void free_host_list(void);

int  parse_syslog(char *facility);

int yyparse(void);
int yylex(void);	
int yyerror(char *s); 

#define YYERROR_VERBOSE 1

#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 66 "cfg_file.y"
typedef union YYSTYPE {
   char *str;
   int  num;
   struct { int num1; int num2; } dnum;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 100 "cfg_file.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

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
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    1,    1,    3,    1,    5,    1,    1,    2,
    2,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    7,    7,    7,    4,    4,    8,    8,    8,
    8,    8,    8,    8,   10,    8,    8,   12,    8,    8,
    8,    8,    8,    8,   14,    8,   16,    8,    8,    9,
    9,    9,   11,   11,   11,   13,   13,   13,   17,   17,
   17,   17,   17,   15,   15,   15,   18,   20,   18,   18,
   18,   18,   18,   18,   18,   19,   19,   21,   21,   21,
};
static const YYINT yylen[] = {                            2,
    0,    2,    1,    4,    0,    5,    0,    5,    1,    1,
    2,    1,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    1,    1,    1,    1,    1,    2,    1,    2,    2,
    2,    2,    2,    2,    0,    3,    2,    0,    3,    2,
    2,    2,    2,    4,    0,    5,    0,    5,    1,    1,
    1,    1,    1,    1,    1,    0,    1,    2,    2,    2,
    2,    2,    1,    0,    1,    2,    1,    0,    3,    2,
    2,    2,    2,    2,    1,    1,    2,    1,    1,    1,
};
static const YYINT yydefred[] = {                         1,
    0,    0,    5,    7,    9,    3,    2,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   22,
   12,    0,   10,    0,    0,   13,   15,   16,   17,   19,
   18,   14,   25,   24,   23,   21,   20,    4,   11,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   35,    0,
   38,    0,   45,   47,   49,   28,    0,   26,    0,   41,
   32,   29,   33,   34,   30,   31,    0,   42,   43,    0,
   37,    0,   40,    0,    0,    6,   27,    8,    0,    0,
    0,   63,    0,   57,   52,   50,   51,   36,   55,   53,
   54,   39,    0,    0,   62,   60,   61,   59,   44,   58,
   68,    0,    0,    0,    0,    0,   75,   67,    0,   65,
    0,    0,   70,   71,   73,   72,   74,   46,   66,   48,
   78,   79,   80,    0,   76,   77,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  292,  257,  258,  284,  285,   10,  293,  123,  295,  297,
  259,  261,  264,  266,  267,  268,  274,  282,  283,  285,
   10,  294,  298,  123,  123,  289,  289,  287,  287,  287,
  287,  289,  285,  286,  289,  299,  287,  125,  298,  260,
  261,  262,  265,  269,  270,  271,  274,  275,  276,  277,
  278,  279,  280,  281,  285,   10,  296,  300,  296,  289,
  289,  286,  289,  290,  286,  289,  123,  289,  289,  302,
  289,  304,  289,  306,  308,  125,  300,  125,  259,  272,
  273,  285,  305,  309,  285,  289,  290,  301,  285,  289,
  290,  303,  123,  123,  289,  286,  288,  286,  125,  309,
  263,  264,  266,  267,  268,  283,  285,   10,  307,  310,
  307,  312,  288,  288,  288,  288,  288,  125,  310,  125,
  287,  288,  289,  311,  313,  313,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          1,
    7,   22,    9,   57,   10,   23,   36,   58,   88,   70,
   92,   72,   83,   74,  109,   75,   84,  110,  124,  112,
  125,
};
static const YYINT yysindex[] = {                         0,
   22,  -98,    0,    0,    0,    0,    0,   69,  -96,  -94,
 -259, -258, -254, -253, -252, -251, -250, -272, -249,    0,
    0,   57,    0,   34,   34,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -248,
 -247, -246, -278, -243, -244,  -86, -242, -241,    0, -240,
    0, -239,    0,    0,    0,    0,  -10,    0,   12,    0,
    0,    0,    0,    0,    0,    0, -257,    0,    0, -282,
    0, -280,    0,  -77,  -72,    0,    0,    0, -237, -265,
 -233,    0, -124,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  115,  115,    0,    0,    0,    0,    0,    0,
    0, -234, -232, -231, -230, -229,    0,    0,   81,    0,
   92, -269,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -269,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -70,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -65,  -65,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  104,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
    0,    0,    0,   36,    0,   40,    0,  -53,    0,    0,
    0,    0,    0,    0,  -31,    0,  -19,  -85,    0,    0,
  -59,
};
#define YYTABLESIZE 400
static const YYINT yytable[] = {                         56,
   99,   79,   85,   77,   89,   77,   86,   87,   90,   91,
   63,   64,   33,   34,   80,   81,   35,  121,  122,  123,
   96,   56,   97,  119,    8,  119,   24,   82,   25,   26,
   27,    6,   28,   29,   30,   31,   67,   37,   32,   62,
   60,   61,   65,   56,   66,   93,   68,   69,   71,   73,
   94,   95,   98,  113,   56,  114,  115,  116,  117,   64,
   59,   39,  111,  100,  126,    0,   21,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   21,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  108,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  108,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   69,   76,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  108,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   79,    0,   78,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   80,   81,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   82,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   38,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  118,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  120,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   69,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   40,
   41,   42,    0,    0,   43,    0,    0,    0,   44,   45,
   46,    0,    0,   47,   48,   49,   50,   51,   52,   53,
   54,   40,   41,   42,   55,    0,   43,    0,    2,    3,
   44,   45,   46,    0,    0,   47,   48,   49,   50,   51,
   52,   53,   54,   40,   41,   42,   55,    0,   43,    0,
    0,    0,   44,   45,   46,    4,    5,   47,   48,   49,
   50,   51,   52,   53,   54,   11,    0,   12,   55,    0,
   13,    0,   14,   15,   16,    0,    0,   11,    0,   12,
   17,    0,   13,    0,   14,   15,   16,    0,   18,   19,
    0,   20,   17,  101,  102,    0,  103,  104,  105,    0,
   18,   19,    0,   20,  101,  102,    0,  103,  104,  105,
    0,    0,    0,  106,    0,  107,   69,   69,    0,   69,
   69,   69,    0,    0,  106,    0,  107,  101,  102,    0,
  103,  104,  105,    0,    0,    0,   69,    0,   69,    0,
    0,    0,    0,    0,    0,    0,    0,  106,    0,  107,
};
static const YYINT yycheck[] = {                         10,
  125,  259,  285,   57,  285,   59,  289,  290,  289,  290,
  289,  290,  285,  286,  272,  273,  289,  287,  288,  289,
  286,   10,  288,  109,  123,  111,  123,  285,  123,  289,
  289,   10,  287,  287,  287,  287,  123,  287,  289,  286,
  289,  289,  286,   10,  289,  123,  289,  289,  289,  289,
  123,  289,  286,  288,  125,  288,  288,  288,  288,  125,
   25,   22,   94,   83,  124,   -1,   10,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   10,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   10,  125,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   10,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  259,   -1,  125,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  272,  273,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  285,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  125,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  125,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  125,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  260,
  261,  262,   -1,   -1,  265,   -1,   -1,   -1,  269,  270,
  271,   -1,   -1,  274,  275,  276,  277,  278,  279,  280,
  281,  260,  261,  262,  285,   -1,  265,   -1,  257,  258,
  269,  270,  271,   -1,   -1,  274,  275,  276,  277,  278,
  279,  280,  281,  260,  261,  262,  285,   -1,  265,   -1,
   -1,   -1,  269,  270,  271,  284,  285,  274,  275,  276,
  277,  278,  279,  280,  281,  259,   -1,  261,  285,   -1,
  264,   -1,  266,  267,  268,   -1,   -1,  259,   -1,  261,
  274,   -1,  264,   -1,  266,  267,  268,   -1,  282,  283,
   -1,  285,  274,  263,  264,   -1,  266,  267,  268,   -1,
  282,  283,   -1,  285,  263,  264,   -1,  266,  267,  268,
   -1,   -1,   -1,  283,   -1,  285,  263,  264,   -1,  266,
  267,  268,   -1,   -1,  283,   -1,  285,  263,  264,   -1,
  266,  267,  268,   -1,   -1,   -1,  283,   -1,  285,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  283,   -1,  285,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 314
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"error","K_OPTIONS",
"K_DEFAULT","K_PORT","K_PERSIST","K_TIMEOUT","K_PASSWD","K_PROG","K_PPP",
"K_SPEED","K_IFCFG","K_FWALL","K_ROUTE","K_DEVICE","K_MULTI","K_SRCADDR",
"K_IFACE","K_ADDR","K_TYPE","K_PROT","K_COMPRESS","K_ENCRYPT","K_KALIVE",
"K_STAT","K_UP","K_DOWN","K_SYSLOG","K_IPROUTE","K_HOST","K_ERROR","WORD",
"PATH","STRING","NUM","DNUM","$accept","config","statement","options","$$1",
"host_options","$$2","option","syslog_opt","host_option","compress","$$3",
"keepalive","$$4","srcaddr_options","$$5","command_options","$$6",
"srcaddr_option","command_option","prog_options","$$7","prog_option",
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : config",
"config :",
"config : config statement",
"statement : '\\n'",
"statement : K_OPTIONS '{' options '}'",
"$$1 :",
"statement : K_DEFAULT $$1 '{' host_options '}'",
"$$2 :",
"statement : K_HOST $$2 '{' host_options '}'",
"statement : K_ERROR",
"options : option",
"options : options option",
"option : '\\n'",
"option : K_PORT NUM",
"option : K_TYPE NUM",
"option : K_TIMEOUT NUM",
"option : K_PPP PATH",
"option : K_IFCFG PATH",
"option : K_ROUTE PATH",
"option : K_FWALL PATH",
"option : K_IPROUTE PATH",
"option : K_SYSLOG syslog_opt",
"option : K_ERROR",
"syslog_opt : NUM",
"syslog_opt : WORD",
"syslog_opt : K_ERROR",
"host_options : host_option",
"host_options : host_options host_option",
"host_option : '\\n'",
"host_option : K_PASSWD WORD",
"host_option : K_DEVICE WORD",
"host_option : K_MULTI NUM",
"host_option : K_TIMEOUT NUM",
"host_option : K_SPEED NUM",
"host_option : K_SPEED DNUM",
"$$3 :",
"host_option : K_COMPRESS $$3 compress",
"host_option : K_ENCRYPT NUM",
"$$4 :",
"host_option : K_KALIVE $$4 keepalive",
"host_option : K_STAT NUM",
"host_option : K_PERSIST NUM",
"host_option : K_TYPE NUM",
"host_option : K_PROT NUM",
"host_option : K_SRCADDR '{' srcaddr_options '}'",
"$$5 :",
"host_option : K_UP $$5 '{' command_options '}'",
"$$6 :",
"host_option : K_DOWN $$6 '{' command_options '}'",
"host_option : K_ERROR",
"compress : NUM",
"compress : DNUM",
"compress : K_ERROR",
"keepalive : NUM",
"keepalive : DNUM",
"keepalive : K_ERROR",
"srcaddr_options :",
"srcaddr_options : srcaddr_option",
"srcaddr_options : srcaddr_options srcaddr_option",
"srcaddr_option : K_ADDR WORD",
"srcaddr_option : K_IFACE WORD",
"srcaddr_option : K_IFACE STRING",
"srcaddr_option : K_PORT NUM",
"srcaddr_option : K_ERROR",
"command_options :",
"command_options : command_option",
"command_options : command_options command_option",
"command_option : '\\n'",
"$$7 :",
"command_option : K_PROG $$7 prog_options",
"command_option : K_PPP STRING",
"command_option : K_IFCFG STRING",
"command_option : K_ROUTE STRING",
"command_option : K_FWALL STRING",
"command_option : K_IPROUTE STRING",
"command_option : K_ERROR",
"prog_options : prog_option",
"prog_options : prog_options prog_option",
"prog_option : PATH",
"prog_option : STRING",
"prog_option : NUM",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 448 "cfg_file.y"

int yyerror(char *s) 
{
   syslog(LOG_ERR, "%s line %d\n", s, lineno);
   return 0;
}

int cfg_error(const char *fmt, ...)
{
   char buf[255];
   va_list ap;

   /* print the argument string */
   va_start(ap, fmt);
   vsnprintf(buf,sizeof(buf),fmt,ap);
   va_end(ap);

   yyerror(buf);
   return 0;
}

int add_cmd(llist *cmds, char *prog, char *args, int flags)
{
   struct vtun_cmd *cmd;
   if( !(cmd = malloc(sizeof(struct vtun_cmd))) ){
      yyerror("No memory for the command");
      return -1;
   }
   memset(cmd, 0, sizeof(struct vtun_cmd)); 		   			

   cmd->prog = prog;
   cmd->args = args;
   cmd->flags = flags;
   llist_add(cmds, cmd);

   return 0;
}		

void *cp_cmd(void *d, void *u)
{
   struct vtun_cmd *cmd = d, *cmd_copy; 

   if( !(cmd_copy = malloc(sizeof(struct vtun_cmd))) ){
      yyerror("No memory to copy the command");
      return NULL;
   }
 
   cmd_copy->prog = strdup(cmd->prog);
   cmd_copy->args = strdup(cmd->args);
   cmd_copy->flags = cmd->flags;
   return cmd_copy;
}

int free_cmd(void *d, void *u)
{
   struct vtun_cmd *cmd = d; 
   free(cmd->prog);
   free(cmd->args);
   free(cmd);
   return 0;
}

void copy_addr(struct vtun_host *to, struct vtun_host *from)
{  
   if( from->src_addr.type ){
      to->src_addr.type = from->src_addr.type;
      to->src_addr.name = strdup(from->src_addr.name);
   }
   to->src_addr.port = from->src_addr.port;
}

void free_addr(struct vtun_host *h)
{  
   if( h->src_addr.type ){
      h->src_addr.type = 0;
      free(h->src_addr.name);
   }
}

int free_host(void *d, void *u)
{
   struct vtun_host *h = d;

   if (u && !strcmp(h->host, u))
      return 1;

   free(h->host);   
   free(h->passwd);   
   
   llist_free(&h->up, free_cmd, NULL);   
   llist_free(&h->down, free_cmd, NULL);

   free_addr(h);
 
   return 0;   
}

/* Find host in the hosts list.
 * NOTE: This function can be called only once since it deallocates hosts list.
 */ 
inline struct vtun_host* find_host(char *host)
{
   return (struct vtun_host *)llist_free(&host_list, free_host, host);
}

inline void free_host_list(void)
{
   llist_free(&host_list, free_host, NULL);
}

static struct {
   char *c_name;
   int  c_val;
} syslog_names[] = {
    { "auth",   LOG_AUTH },
    { "cron",   LOG_CRON },
    { "daemon", LOG_DAEMON },
    { "kern",   LOG_KERN },
    { "lpr",    LOG_LPR },
    { "mail",   LOG_MAIL },
    { "news",   LOG_NEWS },
    { "syslog", LOG_SYSLOG },
    { "user",   LOG_USER },
    { "uucp",   LOG_UUCP },
    { "local0", LOG_LOCAL0 },
    { "local1", LOG_LOCAL1 },
    { "local2", LOG_LOCAL2 },
    { "local3", LOG_LOCAL3 },
    { "local4", LOG_LOCAL4 },
    { "local5", LOG_LOCAL5 },
    { "local6", LOG_LOCAL6 },
    { "local7", LOG_LOCAL7 },
    { NULL, -1 }
};

int parse_syslog(char *facility)
{
   int i;

   for (i=0; syslog_names[i].c_name;i++) {
      if (!strcmp(syslog_names[i].c_name, facility)) {
         vtun.syslog = syslog_names[i].c_val;
         return(0);
      }
   }
}

/* 
 * Read config file. 
 */ 
int read_config(char *file) 
{
   static int cfg_loaded = 0;
   extern FILE *yyin;

   if( cfg_loaded ){
      free_host_list();
      syslog(LOG_INFO,"Reloading configuration file");
   }	 
   cfg_loaded = 1;

   llist_init(&host_list);

   if( !(yyin = fopen(file,"r")) ){
      syslog(LOG_ERR,"Can not open %s", file);
      return -1;      
   }

   yyparse();

   free_host(&default_host, NULL);

   fclose(yyin);
  
   return !llist_empty(&host_list);     
}
#line 828 "cfg_file.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 5:
#line 92 "cfg_file.y"
	{ 
		  parse_host = &default_host; 
                }
#line 1503 "cfg_file.tab.c"
break;
case 7:
#line 97 "cfg_file.y"
	{ 
		  if( !(parse_host = malloc(sizeof(struct vtun_host))) ){
		     yyerror("No memory for the host");
		     YYABORT;
		  }

		  /* Fill new host struct with default values.
		   * MUST dup strings to be able to reread config.
		   */
	  	  memcpy(parse_host, &default_host, sizeof(struct vtun_host));
		  parse_host->host = strdup(yystack.l_mark[0].str);
		  parse_host->passwd = NULL;

		  /* Copy local address */
		  copy_addr(parse_host, &default_host);

		  llist_copy(&default_host.up,&parse_host->up,cp_cmd,NULL);
		  llist_copy(&default_host.down,&parse_host->down,cp_cmd,NULL);

		}
#line 1527 "cfg_file.tab.c"
break;
case 8:
#line 118 "cfg_file.y"
	{
		  /* Check if session definition is complete */ 
		  if (!parse_host->passwd) {
		  	cfg_error("Ignored incomplete session definition '%s'", parse_host->host);
			free_host(parse_host, NULL);			
			free(parse_host);
		  } else {
		  	/* Add host to the list */
		  	llist_add(&host_list, (void *)parse_host);
		  }
		}
#line 1542 "cfg_file.tab.c"
break;
case 9:
#line 130 "cfg_file.y"
	{
		  cfg_error("Invalid clause '%s'",yystack.l_mark[0].str);
		  YYABORT;
		}
#line 1550 "cfg_file.tab.c"
break;
case 13:
#line 143 "cfg_file.y"
	{ 
			  if(vtun.svr_port == -1)
			     vtun.svr_port = yystack.l_mark[0].num;
			}
#line 1558 "cfg_file.tab.c"
break;
case 14:
#line 148 "cfg_file.y"
	{ 
			  if(vtun.svr_type == -1)
			     vtun.svr_type = yystack.l_mark[0].num;
			}
#line 1566 "cfg_file.tab.c"
break;
case 15:
#line 153 "cfg_file.y"
	{  
			  if(vtun.timeout == -1)
			     vtun.timeout = yystack.l_mark[0].num; 	
			}
#line 1574 "cfg_file.tab.c"
break;
case 16:
#line 158 "cfg_file.y"
	{
			  free(vtun.ppp);
			  vtun.ppp = strdup(yystack.l_mark[0].str);
			}
#line 1582 "cfg_file.tab.c"
break;
case 17:
#line 163 "cfg_file.y"
	{
			  free(vtun.ifcfg);
			  vtun.ifcfg = strdup(yystack.l_mark[0].str);
			}
#line 1590 "cfg_file.tab.c"
break;
case 18:
#line 168 "cfg_file.y"
	{   
			  free(vtun.route);  
			  vtun.route = strdup(yystack.l_mark[0].str); 	
			}
#line 1598 "cfg_file.tab.c"
break;
case 19:
#line 173 "cfg_file.y"
	{   
			  free(vtun.fwall);  
			  vtun.fwall = strdup(yystack.l_mark[0].str); 	
			}
#line 1606 "cfg_file.tab.c"
break;
case 20:
#line 178 "cfg_file.y"
	{   
			  free(vtun.iproute);  
			  vtun.iproute = strdup(yystack.l_mark[0].str); 	
			}
#line 1614 "cfg_file.tab.c"
break;
case 22:
#line 185 "cfg_file.y"
	{
			  cfg_error("Unknown option '%s'",yystack.l_mark[0].str);
			  YYABORT;
			}
#line 1622 "cfg_file.tab.c"
break;
case 23:
#line 192 "cfg_file.y"
	{
                          vtun.syslog = yystack.l_mark[0].num;
  			}
#line 1629 "cfg_file.tab.c"
break;
case 24:
#line 196 "cfg_file.y"
	{
                          if (parse_syslog(yystack.l_mark[0].str)) {
                            cfg_error("Unknown syslog facility '%s'", yystack.l_mark[0].str);
                            YYABORT;
                          }
                        }
#line 1639 "cfg_file.tab.c"
break;
case 25:
#line 203 "cfg_file.y"
	{
   			  cfg_error("Unknown syslog option '%s'",yystack.l_mark[0].str);
  			  YYABORT;
			}
#line 1647 "cfg_file.tab.c"
break;
case 29:
#line 217 "cfg_file.y"
	{
			  free(parse_host->passwd);
			  parse_host->passwd = strdup(yystack.l_mark[0].str);
			}
#line 1655 "cfg_file.tab.c"
break;
case 30:
#line 222 "cfg_file.y"
	{
			  free(parse_host->dev);
			  parse_host->dev = strdup(yystack.l_mark[0].str);
			}
#line 1663 "cfg_file.tab.c"
break;
case 31:
#line 227 "cfg_file.y"
	{ 
			  parse_host->multi = yystack.l_mark[0].num;
			}
#line 1670 "cfg_file.tab.c"
break;
case 32:
#line 231 "cfg_file.y"
	{ 
			  parse_host->timeout = yystack.l_mark[0].num;
			}
#line 1677 "cfg_file.tab.c"
break;
case 33:
#line 235 "cfg_file.y"
	{ 
			  if( yystack.l_mark[0].num ){ 
			     parse_host->spd_in = parse_host->spd_out = yystack.l_mark[0].num;
			     parse_host->flags |= VTUN_SHAPE;
			  } else 
			     parse_host->flags &= ~VTUN_SHAPE;
			}
#line 1688 "cfg_file.tab.c"
break;
case 34:
#line 243 "cfg_file.y"
	{ 
			  if( yylval.dnum.num1 || yylval.dnum.num2 ){ 
			     parse_host->spd_out = yylval.dnum.num1;
		             parse_host->spd_in = yylval.dnum.num2; 	
			     parse_host->flags |= VTUN_SHAPE;
			  } else 
			     parse_host->flags &= ~VTUN_SHAPE;
			}
#line 1700 "cfg_file.tab.c"
break;
case 35:
#line 252 "cfg_file.y"
	{
			  parse_host->flags &= ~(VTUN_ZLIB | VTUN_LZO); 
			}
#line 1707 "cfg_file.tab.c"
break;
case 37:
#line 257 "cfg_file.y"
	{  
			  if( yystack.l_mark[0].num )
			     parse_host->flags |= VTUN_ENCRYPT;
			  else
			     parse_host->flags &= ~VTUN_ENCRYPT;
			}
#line 1717 "cfg_file.tab.c"
break;
case 38:
#line 264 "cfg_file.y"
	{
			  parse_host->flags &= ~VTUN_KEEP_ALIVE; 
			}
#line 1724 "cfg_file.tab.c"
break;
case 40:
#line 269 "cfg_file.y"
	{
			  if( yystack.l_mark[0].num )
			     parse_host->flags |= VTUN_STAT;
			  else
			     parse_host->flags &= ~VTUN_STAT;
			}
#line 1734 "cfg_file.tab.c"
break;
case 41:
#line 276 "cfg_file.y"
	{ 
	      		  parse_host->persist = yystack.l_mark[0].num;

			  if(vtun.persist == -1) 
			     vtun.persist = yystack.l_mark[0].num; 	
			}
#line 1744 "cfg_file.tab.c"
break;
case 42:
#line 283 "cfg_file.y"
	{  
			  parse_host->flags &= ~VTUN_TYPE_MASK;
			  parse_host->flags |= yystack.l_mark[0].num;
			}
#line 1752 "cfg_file.tab.c"
break;
case 43:
#line 288 "cfg_file.y"
	{  
			  parse_host->flags &= ~VTUN_PROT_MASK;
			  parse_host->flags |= yystack.l_mark[0].num;
			}
#line 1760 "cfg_file.tab.c"
break;
case 45:
#line 295 "cfg_file.y"
	{ 
			  parse_cmds = &parse_host->up; 
   			  llist_free(parse_cmds, free_cmd, NULL);   
			}
#line 1768 "cfg_file.tab.c"
break;
case 47:
#line 300 "cfg_file.y"
	{ 
			  parse_cmds = &parse_host->down; 
   			  llist_free(parse_cmds, free_cmd, NULL);   
			}
#line 1776 "cfg_file.tab.c"
break;
case 49:
#line 305 "cfg_file.y"
	{
			  cfg_error("Unknown option '%s'",yystack.l_mark[0].str);
			  YYABORT;
			}
#line 1784 "cfg_file.tab.c"
break;
case 50:
#line 312 "cfg_file.y"
	{ 
			  if( yystack.l_mark[0].num ){  
      			     parse_host->flags |= VTUN_ZLIB; 
			     parse_host->zlevel = yystack.l_mark[0].num;
			  }
			}
#line 1794 "cfg_file.tab.c"
break;
case 51:
#line 319 "cfg_file.y"
	{
			  parse_host->flags |= yylval.dnum.num1;
		          parse_host->zlevel = yylval.dnum.num2;
  			}
#line 1802 "cfg_file.tab.c"
break;
case 52:
#line 324 "cfg_file.y"
	{
			  cfg_error("Unknown compression '%s'",yystack.l_mark[0].str);
			  YYABORT;
			}
#line 1810 "cfg_file.tab.c"
break;
case 53:
#line 331 "cfg_file.y"
	{ 
			  if( yystack.l_mark[0].num )
			     parse_host->flags |= VTUN_KEEP_ALIVE;
			}
#line 1818 "cfg_file.tab.c"
break;
case 54:
#line 336 "cfg_file.y"
	{
			  if( yylval.dnum.num1 ){
			     parse_host->flags |= VTUN_KEEP_ALIVE;
			     parse_host->ka_interval = yylval.dnum.num1;
		             parse_host->ka_failure  = yylval.dnum.num2;
			  }
  			}
#line 1829 "cfg_file.tab.c"
break;
case 55:
#line 344 "cfg_file.y"
	{
			  cfg_error("Unknown keepalive option '%s'",yystack.l_mark[0].str);
			  YYABORT;
			}
#line 1837 "cfg_file.tab.c"
break;
case 59:
#line 356 "cfg_file.y"
	{
			  free_addr(parse_host);
			  parse_host->src_addr.name = strdup(yystack.l_mark[0].str);
			  parse_host->src_addr.type = VTUN_ADDR_NAME;
			}
#line 1846 "cfg_file.tab.c"
break;
case 60:
#line 362 "cfg_file.y"
	{
			  free_addr(parse_host);
			  parse_host->src_addr.name = strdup(yystack.l_mark[0].str);
			  parse_host->src_addr.type = VTUN_ADDR_IFACE;
			}
#line 1855 "cfg_file.tab.c"
break;
case 61:
#line 368 "cfg_file.y"
	{
			  free_addr(parse_host);
			  parse_host->src_addr.name = strdup(yystack.l_mark[0].str);
			  parse_host->src_addr.type = VTUN_ADDR_IFACE;
			}
#line 1864 "cfg_file.tab.c"
break;
case 62:
#line 374 "cfg_file.y"
	{
			  parse_host->src_addr.port = yystack.l_mark[0].num;
			}
#line 1871 "cfg_file.tab.c"
break;
case 63:
#line 378 "cfg_file.y"
	{
			  cfg_error("Unknown option '%s'",yystack.l_mark[0].str);
			  YYABORT;
			}
#line 1879 "cfg_file.tab.c"
break;
case 68:
#line 390 "cfg_file.y"
	{
			  memset(&parse_cmd, 0, sizeof(struct vtun_cmd));
			}
#line 1886 "cfg_file.tab.c"
break;
case 69:
#line 393 "cfg_file.y"
	{
			  add_cmd(parse_cmds, parse_cmd.prog, 
				  parse_cmd.args, parse_cmd.flags);
			}
#line 1894 "cfg_file.tab.c"
break;
case 70:
#line 398 "cfg_file.y"
	{   
			  add_cmd(parse_cmds, strdup(vtun.ppp), strdup(yystack.l_mark[0].str), 
					VTUN_CMD_DELAY);
			}
#line 1902 "cfg_file.tab.c"
break;
case 71:
#line 403 "cfg_file.y"
	{   
			  add_cmd(parse_cmds, strdup(vtun.ifcfg),strdup(yystack.l_mark[0].str),
					VTUN_CMD_WAIT);
			}
#line 1910 "cfg_file.tab.c"
break;
case 72:
#line 408 "cfg_file.y"
	{   
			  add_cmd(parse_cmds, strdup(vtun.route),strdup(yystack.l_mark[0].str),
					VTUN_CMD_WAIT);
			}
#line 1918 "cfg_file.tab.c"
break;
case 73:
#line 413 "cfg_file.y"
	{   
			  add_cmd(parse_cmds, strdup(vtun.fwall),strdup(yystack.l_mark[0].str),
					VTUN_CMD_WAIT);
			}
#line 1926 "cfg_file.tab.c"
break;
case 74:
#line 418 "cfg_file.y"
	{   
			  add_cmd(parse_cmds, strdup(vtun.iproute),strdup(yystack.l_mark[0].str),
					VTUN_CMD_WAIT);
			}
#line 1934 "cfg_file.tab.c"
break;
case 75:
#line 423 "cfg_file.y"
	{
			  cfg_error("Unknown cmd '%s'",yystack.l_mark[0].str);
			  YYABORT;
			}
#line 1942 "cfg_file.tab.c"
break;
case 78:
#line 435 "cfg_file.y"
	{
			  parse_cmd.prog = strdup(yystack.l_mark[0].str);
			}
#line 1949 "cfg_file.tab.c"
break;
case 79:
#line 439 "cfg_file.y"
	{
			  parse_cmd.args = strdup(yystack.l_mark[0].str);
			}
#line 1956 "cfg_file.tab.c"
break;
case 80:
#line 443 "cfg_file.y"
	{
			  parse_cmd.flags = yystack.l_mark[0].num;
			}
#line 1963 "cfg_file.tab.c"
break;
#line 1965 "cfg_file.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
