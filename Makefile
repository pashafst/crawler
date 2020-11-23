CC = gcc
CCFLAGS = -std=c11 -pedantic -D_XOPEN_SOURCE=700 -Wall -Werror -g

main: 03g-lsdir.c
	${CC} ${CCFLAGS} -o main 03g-lsdir.c
