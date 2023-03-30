# ParallelHW2AndrewChemaly
Source1.c sequential
Source2.c pthreads
Source3.c omp
to compile
gcc -o myprogram Source1.c 1024

gcc -o myprogram Source2.c -pthread

gcc -fopenmp Source3.c -o myprogram

to run:
./myprogram
