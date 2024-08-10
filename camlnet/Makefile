# Makefile for inet.
PROG=	inet
SRCS=	buf.c clock.c inet.c inet_config.c \
	mnx_eth.c mq.c qp.c sr.c \
	udp.c arp.c eth.c event.c \
	icmp.c io.c ip.c ip_ioctl.c \
	ip_lib.c ip_read.c ip_write.c \
	ipr.c rand256.c tcp.c tcp_lib.c \
	tcp_recv.c tcp_send.c ip_eth.c \
	ip_ps.c psip.c \
	queryparam.c version.c tcp_lib_help_shim.c

.PATH:	${.CURDIR}/generic

WARNS=

FILES=${PROG}.conf
FILESNAME=${PROG}
FILESDIR= /etc/system.conf.d

DPADD+=	${LIBCHARDRIVER} ${LIBSYS} ${LIBASMRUN} ${LIBM}
LDADD+=	-lchardriver -lsys -lasmrun -lm 

DPADD+= ${LIBC}
LDADD+= -lc

LDFLAGS+= -L/usr/pkg/lib/ocaml/ jooseBox.o

# OBJS+= joosebox.o

HEADER_PATH += -I/usr/pkg/lib/ocaml/

CPPFLAGS+=  -I${.CURDIR} -D'ARGS(a)=a' -I/usr/pkg/lib/ocaml/

MAN=

.include <minix.service.mk>
