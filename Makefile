build:
	@g++ -o main.out src/main.c src/util.c src/args.c src/proc.c src/queue.c

debug:
	@g++ -g -o main.out src/main.c src/util.c src/args.c src/proc.c src/queue.c && gdb ./main.out

run:
	@./main.out

valgrind: build
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main.out 

