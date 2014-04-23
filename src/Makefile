compile:
	clear
	mpicc main.c word.c component.c list.c search.c common.c master.c slave.c -otsp

exec: \
compile
	mpiexec -n 3 ./tsp

