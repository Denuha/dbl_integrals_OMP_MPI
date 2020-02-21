#!/bin/sh
#SBATCH -p tut
#SBATCH -n 1
#SBATCH -c 1
./a.out
wait
