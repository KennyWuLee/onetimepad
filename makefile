CC = gcc
EXEC = onetimepad

${EXEC}: onetimepad.c
	${CC} -Wall onetimepad.c -o ${EXEC}
	
clean:
	rm -f ${EXEC}
