include config.mk
SRC = $(wildcard *.c)
OBJ = ${SRC:.c=.o}

.c.o:
	${CC} -c ${CFLAGS} $<

all: ${NAME} .gitignore
	@echo "CFLAGS: ${CFLAGS}"
	@echo "LDFLAGS: ${LDFLAGS}"

.gitignore: config.mk .gitignore_static
	@cat .gitignore_static > .gitignore
	@echo ${NAME} >> .gitignore

${OBJ}: config.mk

run: ${NAME}
	./${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} ${OBJ} -o ${NAME}

clean:
	rm ${OBJ}

install: all
	cp ${NAME} ${PREFIX}/bin/${NAME}

uninstall:
	rm ${PREFIX}/bin/${NAME}
