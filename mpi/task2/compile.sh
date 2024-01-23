#!/bin/bash
#module add mpi/openmpi-local
module add openmpi
module load gcc/9
mpicxx task2.cpp -o runfile
