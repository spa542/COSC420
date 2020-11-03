### Ryan Rosiak and Grant Dawson
COSC 420-001
10/17/20

# Lab-4: Eigen Value Decomposition and Partial HITS Algorithm Implementation
In this lab you will focus on the following objectives:
1. Develop familiarity with C programming language
2. Develop familiarity with parallel computing tools MPICH and OpenMPI
3. Develop familiarity with linear algebra and solving linear systems of equations.
4. Explore empirical tests for program efficiency in terms of parallel computation and resources
 

## Lab Description:
This lab demonstrates parallel eigenvalue decomposition functions. This function
is done in two ways. One way using normal MPI techniques including various 
MPI collectives and pooling. The other way using MPI file shared access
and shared memory. Both functions are analyzed for speed compared to one 
another.

## Files to pay attention to:

driver, main, filetest  - Output files that are run when the programs are executed

Makefile - File that allows the user to compile without having to input specific commands

## How to Run:

1. make main
        - This command compiles the main.c file. This file outputs specific test cases for each
        matrix function to show correct functionality

2. make driver
        - This command compiles the driver.c file. While using the time shell function, this 
        file outputs the amount of time that each matrix function will take on various test cases

3. make filetest
        - This command compiles the filtest.c file. This gives an example of file writing and reading
        using the given infile and outfile

3. make
        - This will compile all files, allowing you to run at your leisure

## Instructions for Program (manual):
Follow the Makefile instructions above to run the program without any manual work. If not
using Makefile, then you must compil the .c files using mpicc (mpicc main.c). After this,
each program can be run as such, (mpiexec -n (# of nodes) ./(output file)
*You must have a working library of openmpi3 or mpich that is already in your PATH


## Results: 


![Addition Time](https://github.com/spa542/COSC420/blob/master/Lab3/Img/Addition.png)
![Subtraction Time](https://github.com/spa542/COSC420/blob/master/Lab3/Img/Subtraction.png)
![Inner Product Time](https://github.com/spa542/COSC420/blob/master/Lab3/Img/Inner%20Product.png)
![Multiplication Time](https://github.com/spa542/COSC420/blob/master/Lab3/Img/Multiplication.png)
![Gauss Jordan Time](https://github.com/spa542/COSC420/blob/master/Lab3/Img/GaussJordan.png)

## Questions:

#### (a) What is the theoretical time complexity of your algorithms (best and worst case), in terms of the input size?
     


#### (b) According to the data, does adding more nodes perfectly divide the time taken by the program?


#### (c) What are some real-world software examples that would need the above routines? Why? Would they benefit greatly from using your distributed code?
        
        
#### (d) How could the code be improved in terms of usability, efficiency, and robustness?
        
        
        
