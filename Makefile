make: select.c
	gcc -g -Wall -std=c99 -o select select.c
	./select

clean: 
	rm select	
