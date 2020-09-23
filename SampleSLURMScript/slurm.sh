#!/bin/sh

#SBATCH --job-name=myproject
#SBATCH --ntasks=30         # will run with -n 30 tasks
#SBATCH --mem=2gb
#SBATCH --tim-00:05:00      # Time limit in the form hh:mm::ss
#SBATCH --output=out/%j.log

module load mpi/mpich-x86_64

mpirun (PATH)/outputfile num # note: don't need the -n argument, etc, reads from above
