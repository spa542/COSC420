#!/bin/sh

#SBATCH --job-name=GrantPro
#SBATCH --nodes=31
#SBATCH --ntasks-per-node=1
##SBATCH --ntasks=100
#SBATCH --mem=8gb
#SBATCH --time=05:05:00
#SBATCH --output=out/%j.log

module load mpi/mpich-3.2-x86_64

##mpicc ~/Ryan/COSC420/

mpirun ~/Ryan/COSC420/Lab3/driver


