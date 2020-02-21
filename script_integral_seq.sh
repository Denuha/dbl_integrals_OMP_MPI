#!/bin/sh

module add intel/v2018.1.163-9
icc -qopenmp integral_seq.c -mkl -o res3.out
./res3.out