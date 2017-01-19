PROG=		tests

SRCS=		tests.cc

OBJS=		${SRCS:N*.h:R:S/$/.o/g}
NENETOBJS=	../network.o  \
		../neuron.o   \
		../synapse.o  \
		../softsign.o \


CC?=		cc
CFLAGS+=	-g -Wall
CXXFLAGS+=	-g -Wall -std=c++11
CPPFLAGS+=	-I..
LDADD=		-lstdc++

all:		${PROG}

${PROG}:	${OBJS}
	${CC} ${CXXFLAGS} ${LDFLAGS} -o ${.TARGET} ${OBJS} ${NENETOBJS} ${LDADD}

.cc.o:
	${CC} ${CXXFLAGS} ${CPPFLAGS} ${DEFS} -c ${.IMPSRC}

clean:
	rm -f ${PROG} ${OBJS}

test:	${PROG}
	@./${PROG}
