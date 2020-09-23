#!/bin/sh

#SBATCH --job-name=GrantProject1Problem160
#SBATCH --ntasks = 100
#SBATCH --mem = 2gb
#SBATCH --time = 00::05:00
#SBATCH --output=out/%j.log

module load mpi/mpi-3.2-x86_64

mpirun ~/Ryan/COSC420/Project-1-ProjectEuler/Problem160/a.out


