.PHONY: bin
bin:
	mkdir -p bin
	gcc -std=c99 -o bin/main main.c render.c drawing.c vmath.c -lm

.PHONY: run
run: bin
	./bin/main
