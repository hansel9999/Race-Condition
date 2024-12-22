PROG = racecond
AUX1 = draw
AUX2 = utils
CC = gcc
LIBS = `pkg-config --libs gtk+-3.0`
CFLAGS = `pkg-config --cflags gtk+-3.0` -export-dynamic -w -lm
SRC = ${PROG}.c ${AUX1}.c ${AUX2}.c
OBJ = ${SRC:.c=.o}

${PROG}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${LIBS} -o ${PROG}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${PROG} ${OBJ}

