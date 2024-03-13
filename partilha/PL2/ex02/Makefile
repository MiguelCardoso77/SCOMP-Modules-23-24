SOURCES = main.c
OBJFILES = main.o
EXEC = ex02

.SUFFIXES : .c .o

.c .o:
	gcc -Wall -Wextra -fanalyzer -c $<

${EXEC}: ${OBJFILES}
	gcc ${OBJFILES} -o ${EXEC} -z noexecstack

${OBJFILES}: ${SOURCES} ${INCLUDES}

run: ${EXEC}
	./${EXEC}

clean: 
	rm -f ${OBJFILES} ${EXEC}

debug: 
	gdb -tui ${EXEC}