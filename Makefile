.PHONY: bin
bin:
	mkdir -p bin
	cc -o bin/main -lm main.c render.c drawing.c vmath.c

.PHONY: run
run: bin
	./bin/main
