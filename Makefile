include config.mk
NAME=numcurses
SRC = $(wildcard *.c)
OBJ = ${SRC:.c=.o}

.c.o:
	${CC} -c ${CFLAGS} $<

all: ${NAME}
	@echo "CFLAGS: ${CFLAGS}"
	@echo "LDFLAGS: ${LDFLAGS}"

${OBJ}: config.mk

run: ${NAME}
	./${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} ${OBJ} -o ${NAME}

clean:
	rm ${OBJ}
