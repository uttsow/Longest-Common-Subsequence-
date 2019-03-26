/*
    a program that solves the Longest Common Subsequence (LCS) problem by the bottom-up dynamic programming approach.
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;
using namespace chrono;


//Main function. This will open the input files and then write the result to the output file. Argv will have 4 inputs
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

    //checks if the two input files are open. if its open, it writes the content of the files to each input holder string. if the files not open, it prints the error message.
    if(fileOne.is_open() && fileTwo.is_open()){
        fileOne >> first;
        fileTwo >> second;
    }else{
        perror("Error Opening files. Check files and try again");
        exit(EXIT_FAILURE);
    }


    int rowX = strlen(first.c_str()) + 1; //length row
    int colmY = strlen(second.c_str()) + 1; //length colm

    //Checks for valid input
    if(rowX < 0 || colmY < 0){
        perror("Length of input is less than 0. Something is deffinetly wrong");
        exit(EXIT_FAILURE);
    }

    //Creating two vector matrix tables, one for values, the other for direction
    vector<vector<int>> values(rowX, vector<int>(colmY));
    vector<vector<string>> arrow(rowX, vector<string>(colmY));


    //Timing of the algorithm. Got this from geeksforgeek.org
    auto start = high_resolution_clock::now(); //start timer
    ios_base::sync_with_stdio(false); //doesnt sync with stdio (I/O);

    //init the tables
    for(int i = 0; i < rowX; i++){

        values[i][0] = 0;
        arrow[i][0] = "BLANK";
    }
    for(int i = 0; i < colmY; i++){

        values[0][i] = 0;
        arrow[0][i] = "BLANK";
    }

    //Algorithm for LCS
    for(int i = 1; i < rowX; i++){
        for(int j = 1; j < colmY; j++){
            if(first[i-1] == second[j-1]){
                values[i][j] = values[i-1][j-1] + 1;
                arrow[i][j] = "DIAGONAL";
            }else if(values[i-1][j] >= values[i][j-1]){
                values[i][j] = values[i-1][j];
                arrow[i][j] = "UP";
            }else{
                values[i][j] = values[i][j-1];
                arrow[i][j] = "LEFT";
            }
        }
    }

    auto stop = high_resolution_clock::now();   //end of timer


    //If String is less than or equal to 10
    if(first.size() <= 10 && second.size() <= 10){

        //Writing the matrix into the file
        for(int i =0; i < rowX; i++){
            for(int j = 0; j < colmY; j++){
                outputFile << values[i][j] << " ";
            }
            outputFile << "\n";
        }

        //Longest common subsequence. Output is in reverse order
        string sequene = "";
        int i = first.size();
        int j = second.size();
        while(i > 0 && j > 0){
            if(arrow[i][j] =="DIAGONAL"){
                sequene = first[i-1] + sequene;
                i--;
                j--;
            }else if(arrow[i][j] == "LEFT"){
                j--;
            }else if(arrow[i][j] == "UP"){
                i--;
            }else{ //you hit "BLANK"
                break;
            }
        }
        //Write sequene to output file
        outputFile << sequene << endl;

    }else{  //inputs not less than or equal to 10 so just write the length;
        outputFile << values[rowX-1][colmY-1] << endl;
    }

    //Cast it to microseconds and store it in duration
    double duration = duration_cast<nanoseconds>(stop-start).count();
    duration *= 1e-9;
    outputFile << fixed << duration << setprecision(9) << " seconds" << endl;


    //Close all the files;
    fileOne.close();
    fileTwo.close();
    outputFile.close();

    return 0;

}
