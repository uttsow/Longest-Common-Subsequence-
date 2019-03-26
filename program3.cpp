/*
program that solves the LCS problem by the top-down dynamic programming approach - recursively computing the length of a longest common subsequence with memoization
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;
using namespace chrono;


/*
    The recurisve Top-Down LCS Memonized function. The parameters are the 2D array, a const char array of the input datas (first and second), and the starting index i,j. i, j are default to 0,0 because its top down. The array keeps track of the calculated values and does the recurisve function call only when the value of array[i][j] < 0, which is different than the Inital value of -1.
    This return the length of subsequence
*/
int lcsMemonized(int **array, const char *first, const char *second, int i, int j){
    if(array[i][j] < 0){
        if(first[i] == '\0' || second[j] == '\0'){
            array[i][j] = 0;
        }else if(first[i] == second[j]){
            array[i][j] = 1+ lcsMemonized(array, first, second, i+1, j+1);
        }else{
            array[i][j] = max(lcsMemonized(array, first, second, i+1, j), lcsMemonized(array, first, second, i, j+1));
        }
    }
    return array[i][j];

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
    string *first = new string("");
    string *second = new string("");

    //Inital length is 0. This will hold the result of the LCS recursive algorithm
    int length = 0;


    //checks if the two input files are open. if its open, it writes the content of the files to each input holder string. if the files not open, it prints the error message.
    if(fileOne.is_open() && fileTwo.is_open()){
        fileOne >> (*first);
        fileTwo >> (*second);
    }else{
        perror("Error Opening files. Check files and try again");
        exit(EXIT_FAILURE);
    }


    int rowX = strlen((*first).c_str())+1; //length of frist input
    int colmY = strlen((*second).c_str())+1; //length of second input

    // checks for valid input
    if(rowX < 0 || colmY < 0){
        perror("Length of input is less than 0. Something is deffinetly wrong");
        exit(EXIT_FAILURE);
    }

    //Will hold the answers to the subproblems so it can see if the solution has already been calulated


    //Timing of the algorithm. Got this from geeksforgeek.org
    auto start = high_resolution_clock::now(); //start timer
    ios_base::sync_with_stdio(false); //doesnt sync with stdio (I/O);

    //Setting up the Array. This will keep track of the recurisve function and see if the index has already been calulated.
    int **array = new int*[rowX];
    for(int i =0; i < rowX;i++){
        array[i] = new int[colmY];
    }

    for(int i =0; i < rowX; i++){
        for(int j = 0; j < colmY; j++){
            array[i][j] = -1;
        }
    }

    length = lcsMemonized(array, first->data(), second->data(), 0, 0);    //Call the function

    auto stop = high_resolution_clock::now();   //end of timer
    //Cast it to microseconds and store it in duration
    double duration = duration_cast<nanoseconds>(stop-start).count();
    duration *= 1e-9;

    //write length and time to file;
    outputFile << length << endl;
    outputFile << fixed << duration << setprecision(9) << " seconds" << endl;

    //Managing memory. Deletes dynamic arrays and strings;
    delete first;
    delete second;
    for(int i =0; i < rowX; i++){
        delete array[i];
    }
    delete[] array;

    //Close the opened files
    fileOne.close();
    fileTwo.close();
    outputFile.close();

    return 0;
}
