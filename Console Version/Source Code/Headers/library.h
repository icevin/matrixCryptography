#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <shobjidl.h> 
#include <ShlObj.h>
#include <shtypes.h>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>	
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32")
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   ________  ___  ___      ________       ________      _________    ___      ________      ________                             //
//  |\  _____\|\  \|\  \    |\   ___  \    |\   ____\    |\___   ___\ |\  \    |\   __  \    |\   ___  \                           //
//  \ \  \__/ \ \  \\\  \   \ \  \\ \  \   \ \  \___|    \|___ \  \_| \ \  \   \ \  \|\  \   \ \  \\ \  \                          //
//   \ \   __\ \ \  \\\  \   \ \  \\ \  \   \ \  \            \ \  \   \ \  \   \ \  \\\  \   \ \  \\ \  \                         //
//    \ \  \_|  \ \  \\\  \   \ \  \\ \  \   \ \  \____        \ \  \   \ \  \   \ \  \\\  \   \ \  \\ \  \                        //
//     \ \__\    \ \_______\   \ \__\\ \__\   \ \_______\       \ \__\   \ \__\   \ \_______\   \ \__\\ \__\                       //
//      \|__|     \|_______|    \|__| \|__|    \|_______|        \|__|    \|__|    \|_______|    \|__| \|__|                       //
//   ________      ___      ___  _______       ________      ___      ___  ___      _______       ___       __                     //
//  |\   __  \    |\  \    /  /||\  ___ \     |\   __  \    |\  \    /  /||\  \    |\  ___ \     |\  \     |\  \                   //
//  \ \  \|\  \   \ \  \  /  / /\ \   __/|    \ \  \|\  \   \ \  \  /  / /\ \  \   \ \   __/|    \ \  \    \ \  \                  //
//   \ \  \\\  \   \ \  \/  / /  \ \  \_|/__   \ \   _  _\   \ \  \/  / /  \ \  \   \ \  \_|/__   \ \  \  __\ \  \                 //
//    \ \  \\\  \   \ \    / /    \ \  \_|\ \   \ \  \\  \|   \ \    / /    \ \  \   \ \  \_|\ \   \ \  \|\__\_\  \                //
//     \ \_______\   \ \__/ /      \ \_______\   \ \__\\ _\    \ \__/ /      \ \__\   \ \_______\   \ \____________\               //
//      \|_______|    \|__|/        \|_______|    \|__|\|__|    \|__|/        \|__|    \|_______|    \|____________|               //
//                                                                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// matrixMath.h//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int roundToThree(int textLength); // Rounds an integer to the next highest multiple of three.

void clearMatrix(vector<vector<long double>> clear); // Fills a 3x3 matrix with 0's.

int calculateDeterminant(vector<vector<int>> key); // Calculates the determinant of a 3x3 matrix.

vector <vector <int> > generateKey(); // Generates a random 3x3 matrix, that has an inverse

vector<vector<long double>> inverseOfKey(vector<vector<int>> key); //Finds the inverse of a 3x3 matrix

vector<long double> multiplyArray(vector<int> num, vector<vector<int>> key, int roundedLength); //Multiples a 1-dimensional vector of length roundedLength by a key.

//Unused:
vector<vector<long double>> multiply3by3(vector<vector<long double>> array1, vector<vector<int>> array2); //Multiples two 3x3 matricies. Unused
// end matrixMath.h//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------------------------------------//

// filetransfer.h////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getLength(string filename); //Returns the first integer from the file at path filename

vector<vector<int>> getKey(string filename); //Returns 9 integers from the file at path filename

vector<long double> getText(string filename); //Returns ciphertext from the file at path filename
int clear(string filename); //Clears/creates a file at path filename.

void errorHandler(int errorCode); //Handles errors from file-IO errors.

int putLength(int length, string filename); //Outputs an integer into the file at path filename

int putKey(vector<vector<int>> key, string filename); //Outputs a key into the file at path filename

int putText(vector<long double> text, string filename); //Outputs a one-dimensional vector into the file at path filename

void outputToFile(string outputFilename, vector<long double> encrypted, vector<vector<int>> key); //Outputs ciphertext and key into file at path filename

vector<int> getTextFromFile(string filename); //Returns contents of file into a vector

int putChar(vector<char> input, string filename); //Outputs a vector of chars into file at path filename

// end filetransfer.h////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------------------------------------//

// decrypt.h/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<char> decrypt(vector<long double> input, vector<vector<int>> key); //Decrypts input with a key

vector<char> decryptFromFile(string filename); //Reads all info from file at path filename, and decrypts
// end decrypt.h

// encrypt.h
vector<long double> encrypt(vector<int> input, vector<vector<int>> key); //Encrypts input with key

void encryptToFile(string filename, vector<int> input); //Encrypts input, then puts all relevant information into file filename. Automatically generates key.
//end encrypt.h

//inputOutput.h
PWSTR saveFileDialog(); //Opens pop-up window, asking for location to save a file.

PWSTR openFileDialog(); //Opens pop-up window, to open an existing file.

string pFilename(PWSTR oFilename); //Parses Pointer-To-Wide-String into string

vector<int> inputString(); //Stores input into a vector until enter is pressed twice

vector<char> characterize(vector<long double> input); //Rounds ASCII values of decrypted text, and turns them back into characters

void outputVector(vector<int> input); //Outputs a vector. Debugging purposes

vector<vector<int>> outputMatrix(vector<vector<int>> output); //Outputs a two dimensional vector. Debugging purposes
//end inputOutput.h

//audio.h
void playSong(string filename); //Plays the .wav file at path filename

PWSTR openWavDialog(); //Opens dialog to open only .wav files
//end audio.h

//graphics.h
void getScreenSize(int& columns, int& rows); //Gets console window size in columns and rows.

void line(); //Separator. Uses size of console window found in getScreenSize to output a full-width line.

void outputSpace(int spaceLength); //Outputs spaceLength amount of spaces. Used in centering text.

void displayTitle(); //Displays ASCII art title and author credits. Centered using outputSpace and getScreenSize.

void prepScreen(); //Clears screen and displays title. Used to clear screen between menus.

void updateColor(char arr[2]); //Updates text/background color.

char chooseColor(string prompt); //Prompts user for color choice

void intro(); //Run before main body, resizes window and sets title
//end graphics.h

// menu.h //
void hangUntilContinue(); //Similar to system("pause").

int askFor(string prompt); //Prompts user string prompt, returns yes = 1/no = 0.

int askForExit(); //Asks user if they are sure they want to exit.

int menu(); //Start point of menu system. Returns 0 when user chooses to exit.
// end menu.h //

string titleStat = "ON";
string audioStat = "OFF";

#include "matrixMath.h"
#include "inputOutput.h"
#include "encrypt.h"
#include "decrypt.h"
#include "menu.h"
#include "filetransfer.h"
#include "graphics.h"
#include "audio.h"