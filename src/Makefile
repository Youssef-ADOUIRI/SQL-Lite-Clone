prog: main.o funcs.o tokenizer.o tabs.o display.o
	gcc main.o funcs.o tokenizer.o tabs.o display.o -o prog

main.o: main.c
	gcc -c main.c

funcs.o: funcs.c
	gcc -c funcs.c

tokenizer.o: tokenizer.c
	gcc -c tokenizer.c

tabs.o: tabs.c
	gcc -c tabs.c

display.o: display.c
	gcc -c display.c


clean:
	del -f main.o funcs.o tokenizer.o tabs.o display.o prog