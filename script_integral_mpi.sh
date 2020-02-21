#!/bin/sh
module add intel/v2018.1.163-9
mpiicc integral_mpi.c -o res1.out

sq=cpu

#SBATCH -p $sq
#SBATCH -n 1
#SBATCH -t 60
mpirun -np 1 ./res1.out

#SBATCH -p $sq
#SBATCH -n 2
#SBATCH -t 60
mpirun -np 2 ./res1.out

#SBATCH -p $sq
#SBATCH -n 3
#SBATCH -t 60
mpirun -np 3 ./res1.out

#SBATCH -p $sq
#SBATCH -n 4
#SBATCH -t 60
mpirun -np 4 ./res1.out

#SBATCH -p $sq
#SBATCH -n 5
#SBATCH -t 60
mpirun -np 5 ./res1.out

#SBATCH -p $sq
#SBATCH -n 6
#SBATCH -t 60
mpirun -np 6 ./res1.out

#SBATCH -p $sq
#SBATCH -n 7
#SBATCH -t 60
mpirun -np 7 ./res1.out

#SBATCH -p $sq
#SBATCH -n 8
#SBATCH -t 60
mpirun -np 8 ./res1.out
