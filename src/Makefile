
CC = gcc 
CCFLAGS = -g -Wall

OBJECTS = main.o funcs.o tokenizer.o tabs.o Memory.o rows.o display.o pager.o B_Tree.o

prog: $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -o prog

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
	del -f core *.o prog




##################