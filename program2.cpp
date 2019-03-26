/*
solves the LCS problem by recursively computing the length of a longest common subsequence (without memoization). The input as before are the files filex and filey.
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;


/*
    LCS Recursive function. string frist and second are nonempty and int i,j holds the length of these strings. the function will recursively go through the two strings and find the longest common subsequence.
    Returns the length of the subsequence.
*/
int lcsRecursive(string first, string second, int i , int j){
    if(i == 0 || j == 0){
        return 0;
    }
    if(first[i] == second[j]){
        return lcsRecursive(first, second, i-1, j-1) + 1;
    }else{
        return max(lcsRecursive(first, second, i-1, j), lcsRecursive(first, second, i, j-1));
    }
}


//Main function. This will open the input files and then write the result to the output file
int main(int argc, char const *argv[]) {

    //Checks if proper usage. needs to be length of 4, else prints error
    if(argc != 4){
        perror("Invalid usage.\n Format: ./program2 <filex.txt> <filey.txt> <output.txt>");
        exit(EXIT_FAILURE);
    }

    //2 input file and 1 output file
    ifstream fileOne(argv[1]);
    ifstream fileTwo(argv[2]);
    ofstream outputFile(argv[3]);

    //String variable to hold the first, second input from file;
    string first, second;

    //Inital length is 0. This will hold the result of the LCS recursive algorithm
    int length = 0;


    //checks if the two input files are open. if its open, it writes the content of the files to each input holder string. if the files not open, it prints the error message.
    if(fileOne.is_open() && fileTwo.is_open()){
        fileOne >> first;
        fileTwo >> second;
    }else{
        perror("Error Opening files. Check files and try again");
        exit(EXIT_FAILURE);
    }


    int i = strlen(first.c_str()); //length of frist input
    int j = strlen(second.c_str()); //length of second input

    // checks for valid input
    if(i < 0 || j < 0){
        perror("Length of input is less than 0. Something is deffinetly wrong");
        exit(EXIT_FAILURE);
    }

    //Timing of the algorithm. Got this from geeksforgeek.org
    auto start = high_resolution_clock::now(); //start timer
    ios_base::sync_with_stdio(false); //doesnt sync with stdio (I/O);

    length = lcsRecursive(first, second , i, j);    //Call the function

    auto stop = high_resolution_clock::now();   //end of timer
    //Cast it to microseconds and store it in duration
    double duration = duration_cast<nanoseconds>(stop-start).count();
    duration *= 1e-9;

    //write length and time to file;
    outputFile << length << endl;
    outputFile << fixed << duration << setprecision(9) << " seconds" << endl;

    //Close the opened files
    fileOne.close();
    fileTwo.close();
    outputFile.close();


    return 0;
}
