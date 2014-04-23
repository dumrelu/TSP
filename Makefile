compile: bin bin/main.o bin/word.o bin/component.o bin/list.o bin/search.o bin/common.o bin/master.o bin/slave.o
	mpicc bin/main.o bin/word.o bin/component.o bin/list.o bin/search.o bin/common.o bin/master.o bin/slave.o -otsp

bin:
	mkdir bin/

bin/main.o: src/main.c
	mpicc -c -o bin/main.o src/main.c

bin/word.o: src/word.c
	mpicc -c -o bin/word.o src/word.c

bin/component.o: src/component.c
	mpicc -c -o bin/component.o src/component.c

bin/list.o: src/list.c
	mpicc -c -o bin/list.o src/list.c

bin/search.o: src/search.c
	mpicc -c -o bin/search.o src/search.c

bin/common.o: src/common.c
	mpicc -c -o bin/common.o src/common.c

bin/master.o: src/master.c
	mpicc -c -o bin/master.o src/master.c

bin/slave.o: src/slave.c
	mpicc -c -o bin/slave.o src/slave.c

exec: compile
	mpiexec -n 3 ./tsp

	
