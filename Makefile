# Generated automatically from Makefile.in by configure.
#
#   VTun - Virtual Tunnel over TCP/IP network. 
#
#   Copyright (C) 1998-2000  Maxim Krasnyansky <max_mk@yahoo.com>
#
#   VTun has been derived from VPPP package by Maxim Krasnyansky. 
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   Makefile.in,v 1.6.2.1 2001/08/06 23:16:35 maxk Exp
#  
CC = gcc
CFLAGS = -g -O2 
LDFLAGS = 

LDFLAGS += -L/usr/local/lib
CFLAGS += -I/usr/local/include
LIBS += -lakrypt


LDFLAGS += -L/usr/local/lib -lakrypt
CFLAGS += -I/usr/local/include
LDFLAGS+= -Xlinker -rpath=/usr/local/include/
LIBS += -libakrypt


YACC = yacc
YACCFLAGS = -d

LEX = lex
LEXFLAGS = -t 

INSTALL = /usr/bin/install -c
INSTALL_OWNER = -o root -g 0

prefix = /usr/local
exec_prefix = ${prefix}

SBIN_DIR = ${exec_prefix}/sbin
MAN_DIR  = ${prefix}/man
ETC_DIR  = ${prefix}/etc
VAR_DIR  = ${prefix}/var

PID_FILE = ${VAR_DIR}/run/vtund.pid
CFG_FILE = ${ETC_DIR}/vtund.conf
STAT_DIR = ${VAR_DIR}/log/vtund
LOCK_DIR = ${VAR_DIR}/lock/vtund

DEFS = -DVTUN_CONFIG_FILE=\"$(CFG_FILE)\" -DVTUN_PID_FILE=\"$(PID_FILE)\" \
       -DVTUN_STAT_DIR=\"$(STAT_DIR)\" -DVTUN_LOCK_DIR=\"$(LOCK_DIR)\"

OBJS = main.o cfg_file.tab.o cfg_file.lex.o server.o client.o lib.o \
       llist.o auth.o tunnel.o lock.o netlib.o  \
       tun_dev.o tap_dev.o pty_dev.o pipe_dev.o \
       tcp_proto.o udp_proto.o \
       linkfd.o lfd_shaper.o lfd_zlib.o lfd_lzo.o lfd_encrypt.o 

CONFIGURE_FILES = Makefile config.status config.cache config.h config.log 

.c.o:
	$(CC) $(CFLAGS) $(DEFS) -c $<

vtund: $(OBJS)
	$(CC) $(CFLAGS) -o vtund $(OBJS) $(LFD_OBJS) $(LDFLAGS)

cfg_file.tab.c: cfg_file.y cfg_kwords.h config.h
	$(YACC) $(YACCFLAGS) -b cfg_file cfg_file.y

cfg_file.lex.c: cfg_file.l cfg_kwords.h config.h
	$(LEX) $(LEXFLAGS) cfg_file.l > cfg_file.lex.c 

depend:
	makedepend -- $(CFLAGS) -- *.c

clean:
	rm -f core cfg_file.tab.* cfg_file.lex.* *.o *~ *.bak vtund

distclean: clean
	rm -f $(CONFIGURE_FILES)
	rm -f `cat vtun.drivers`	

install_man: 
	$(INSTALL) -d -m 755 $(INSTALL_OWNER) $(MAN_DIR)/man8
	$(INSTALL) -m 644 $(INSTALL_OWNER) vtund.8 $(MAN_DIR)/man8
	$(INSTALL) -d -m 755 $(INSTALL_OWNER) $(MAN_DIR)/man5
	$(INSTALL) -m 644 $(INSTALL_OWNER) vtund.conf.5 $(MAN_DIR)/man5
	rm -f $(MAN_DIR)/man8/vtun.8 
	ln -s vtund.8 $(MAN_DIR)/man8/vtun.8 

install_config: 
	$(INSTALL) -d -m 755 $(INSTALL_OWNER) $(ETC_DIR)
	if [ ! -f $(ETC_DIR)/vtund.conf ]; then \
	  $(INSTALL) -m 600 $(INSTALL_OWNER) vtund.conf $(ETC_DIR); \
	fi

install: vtund install_config install_man
	$(INSTALL) -d -m 755 $(INSTALL_OWNER) $(VAR_DIR)/run
	$(INSTALL) -d -m 755 $(INSTALL_OWNER) $(STAT_DIR)
	$(INSTALL) -d -m 755 $(INSTALL_OWNER) $(LOCK_DIR)
	$(INSTALL) -d -m 755 $(INSTALL_OWNER) $(SBIN_DIR)
	$(INSTALL) -m 755 $(INSTALL_OWNER) vtund $(SBIN_DIR)

# DO NOT DELETE THIS LINE -- make depend depends on it.
