Compile & Run:
1. Unzip the source file
2. on the command line, type "make";
3. to run all 3 programs at once, on the command line type "make fullRun"
4. to run individually, type: "./program3 <filex.txt> <filey.txt> <output3.txt>"


Data Structures:
2D dynamic array was created where the rows were the length of the first input plus one, and the columns were the length of the second input plus one. The array was initialized to -1 for all indexes because it will be used to keep track of the recursive function and if an index was already calculated. The input strings were also a pointer which was then converted to a char array and passed on to the lcsMemonized function. This function returns the length of the subsequence


time:
Timing is calculated strictly for the algorithm. No I/O is taken into account.

Time complexity: Theta(nm) where n and m are the lengths of the input strings

classes used:
program3.cpp
 - contains source code
