Readme:

1) The input file name should be "input.txt".

2) and the inputs in that "input.txt" should be N and K which are two integers seperated by a space.

and the rest of the instructions are followed according to the given instructions in the question . 

The main program will read the numbers N and K from an input file. The main process
will create a set of K processes. And then set up shared memory buffers with each of
the child processes. The child processes will in turn, will also create shared memory
buffers to communicate with the main process.
The numbers from 1 to N will be partitioned among these processes so that two
processes do not work on the name number. Thus each process Pi will be responsible
for a set of numbers. For each number in its set, the process Pi will determine if the
number is a perfect number or not. If it is, Pi will store it in a local array. After
completion, Pi will share the set of numbers it identified with the main process.
The main process will wait till all the processes are complete. It will then consolidate all
the perfect numbers identified and communicated by child processes in a single output
file.
Input File:- As mentioned above, the input will consist of two parameters N and K.
Output File:- For ease of understanding, each process Pi will also create a log file,
OutFilei onto which it will store all the details of its execution. It will log each number it
tests and the output it generates. Suppose Pi tests the number 1 to 10, then a sample
output can be as follows:
1: Not a perfect number
2: Not a perfect number
.
.
.
6: Is a perfect number

.
.
.

On similar lines, the main process will create a log file OutMain which will consist of all
the perfect numbers less than N and the process that identified it. A possible output
format for two processes is as follows:
P1: num1 num2 ....
P2: num5 num6 ....

