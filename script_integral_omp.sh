#!/bin/sh

module add intel/v2018.1.163-9
icc -qopenmp integral_omp.c -mkl -o res2.out

sq=cpu

#SBATCH -p $sq
#SBATCH -c 1
#SBATCH -t 60
export OMP_NUM_THREADS=1
export OMP_PLACES=cores
./res2.out

#SBATCH -p $sq
#SBATCH -c 2
#SBATCH -t 60
export OMP_NUM_THREADS=2
export OMP_PLACES=cores
./res2.out

#SBATCH -p $sq
#SBATCH -c 3
#SBATCH -t 60
export OMP_NUM_THREADS=3
export OMP_PLACES=cores
./res2.out

#SBATCH -p $sq
#SBATCH -c 4
#SBATCH -t 60
export OMP_NUM_THREADS=4
export OMP_PLACES=cores
./res2.out

#SBATCH -p $sq
#SBATCH -c 5
#SBATCH -t 60
export OMP_NUM_THREADS=5
export OMP_PLACES=cores
./res2.out

#SBATCH -p $sq
#SBATCH -c 6
#SBATCH -t 60
export OMP_NUM_THREADS=6
export OMP_PLACES=cores
./res2.out

#SBATCH -p $sq
#SBATCH -c 7
#SBATCH -t 60
export OMP_NUM_THREADS=7
export OMP_PLACES=cores
./res2.out

#SBATCH -p $sq
#SBATCH -c 8
#SBATCH -t 60
export OMP_NUM_THREADS=8
export OMP_PLACES=cores
./res2.out

