Compile & Run:
1. Unzip the source file
2. on the command line, type "make";
3. to run all 3 programs at once, on the command line type "make fullRun"
4. to run individually, type: "./program1 <filex.txt> <filey.txt> <output1.txt>"

Data Structures:

This program only used a 2D vector of integers. The rows of the vector was set to input file 1  + sizeof input string and the column is 1 + size of second input string.

if input string size is less or equal 10, the ouputfile will have the matrix and the subsequence and time. If size is more than 10, it will have just the length of the subsequence and time.


Time complexity:
Timing begins after the creation of the vector and ends after the algorithm. the writing of output is not included in timing, nor is any other I/O calls
Theta(nm)  were n and m are the lengths of the input strings;

classes used:
program1.cpp
 - contains source code
