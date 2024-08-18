all: prog

prog: main.c
	gcc main.c -o prog

clean:
	rm prog

exec: ./prog
	./prog input.txt

exec2: ./prog
	./prog $(FILE)
