
CC = gcc 
CCFLAGS = -g -Wall


prog: main.o funcs.o tokenizer.o tabs.o Memory.o rows.o display.o
	$(CC) main.o funcs.o tokenizer.o tabs.o Memory.o rows.o display.o -Wall -o prog

# main.o: main.c
# 	$(CC) -c main.c

# funcs.o: funcs.c
# 	$(CC) -c funcs.c

# tokenizer.o: tokenizer.c
# 	$(CC) -c tokenizer.c

# tabs.o: tabs.c
# 	$(CC) -c tabs.c

# display.o: display.c
# $(CC) -c display.c

%.o: %.c
	$(CC) -c $(CCFLAGS) $<




clean:
	rm -f core *.o prog




##################