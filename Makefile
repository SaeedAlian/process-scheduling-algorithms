build: mkbin
	@g++ -o ./bin/psa src/main.c src/util.c src/args.c src/proc.c src/queue.c src/algorithms.c

run: build
	@./bin/psa

build-debug: mkbin
	@g++ -g -o ./bin/psa_debug src/main.c src/util.c src/args.c src/proc.c src/queue.c src/algorithms.c

debug: build-debug
	@gdb ./bin/psa_debug

valgrind: build-debug
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/psa_debug

mkbin:
	@mkdir -p ./bin
