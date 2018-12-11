default:
#	gcc optimal.c -Wl,-rpath,/lusr/opt/gcc-5.2.0/lib64 -fopenmp -g -o bin/optimal
	pgcc -acc -Minfo optimal.c 
