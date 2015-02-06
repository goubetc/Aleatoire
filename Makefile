all: detecte_langue

detecte_langue: detecte_langue.o mot.o lettre.o
	gcc -o $@ $^

%.o: %.c 
	gcc -o $@ -c $<

clean:
	@rm *.o detecte_langue
