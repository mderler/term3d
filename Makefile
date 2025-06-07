bin:
	mkdir -p bin
	cc -o bin/main -lm main.c

.PHONY: run
run: bin
	./bin/main
