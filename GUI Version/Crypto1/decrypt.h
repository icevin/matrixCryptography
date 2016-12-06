#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "inputOutput.h"
#include "matrixMath.h"
#include "filetransfer.h"
using namespace std;

vector<char> decrypt(vector<long double> input, vector<vector<int>> key) {	
	//Input into vector num, round to to nearest group of 3 and fill extra with whitespace 
	int roundedLength = roundToThree(input.size());
	input.resize(roundedLength, 32);
	//Decrypt num into vector Decrypted
	vector<char> output = characterize(multiplyArray(input, inverseOfKey(key), roundedLength));
	return output;
}
