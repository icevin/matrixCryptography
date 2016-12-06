#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "filetransfer.h"
#include "inputOutput.h"
#include "matrixMath.h"
#include "filetransfer.h"
using namespace std;

vector<long double> encrypt(vector<int> input, vector<vector<int>> key) {
	//Input into vector num, round to to nearest group of 3 and fill extra with whitespace
	int roundedLength = roundToThree(input.size());
	input.resize(roundedLength, 32);

	//Encrypt num into vector encrypted
	vector<long double> out = multiplyArray(input, key, roundedLength);
	return out;
}

void encryptToFile(string filename, vector<int> input) {
	vector<vector<int>> key = generateKey();
	vector<long double> encrypted = encrypt(input, key);
	outputToFile(filename, encrypted, key);
	return;
}

