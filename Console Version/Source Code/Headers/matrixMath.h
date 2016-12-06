#pragma once
#include "library.h"
using namespace std;

extern int encryptLvl = 16;

int roundToThree(int textLength) {
	int roundedLength = 3 * ((textLength / 3) + 1);
	if ((textLength % 3) == 0)
		roundedLength = textLength;
	return roundedLength;
}

void clearMatrix(vector<vector<long double>> clear) {
	for (int row312934 = 0; row312934 < 3; row312934++)
		for (int colum3124 = 0; colum3124 < 3; colum3124++)
			clear[row312934][colum3124] = 0;
}

vector<vector<long double>> multiply3by3(vector<vector<long double>> array1, vector<vector<int>> array2) {
	vector<vector<long double>> decrypt;
	decrypt.resize(3);
	for (int resize = 0; resize < 3; resize++)
		decrypt[resize].resize(3);
	
	clearMatrix(decrypt);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++) {
				decrypt[i][j] += double(array1[i][k]) * double(array2[k][j]);
				cout << decrypt[i][j] << endl << endl;
			}
	return decrypt;
}

int calculateDeterminant(vector<vector<int>> key) {
	int deter1 = 0, deter2 = 0, deter3 = 0, deter4 = 0, deter5 = 0, deter6 = 0;
	int determinant = 0;

	deter1 = key[0][0] * key[1][1] * key[2][2];
	deter2 = key[0][1] * key[1][2] * key[2][0];
	deter3 = key[0][2] * key[1][0] * key[2][1];

	deter4 = key[2][0] * key[1][1] * key[0][2];
	deter5 = key[2][1] * key[1][2] * key[0][0];
	deter6 = key[2][2] * key[1][0] * key[0][1];

	determinant = (deter1 + deter2 + deter3) - (deter4 + deter5 + deter6);

	return determinant;
}

vector <vector <int> > generateKey() {
	// uses clock time as seed
	vector<vector<int>> key;
	key.resize(3);
	for (int resize = 0; resize < 3; resize++)
		key[resize].resize(3);

	int determinant = 0;
	do {
		srand(time(0) + rand());
		int checkCounts = 0;
		for (int row = 0; row < 3; row++)
			for (int column = 0; column < 3; column++)
				key[row][column] = (rand() % encryptLvl + 1) * pow(-1, rand() % 10);
		
		determinant = calculateDeterminant(key);
	} while (determinant == 0 || abs(determinant) > 20);

	return key;
}

vector<vector<long double>> inverseOfKey(vector<vector<int>> key) {
	vector<vector<long double>> out;
	out.resize(3);
	for (int resize = 0; resize < 3; resize++)
		out[resize].resize(3);
	int cofactor[3][3];
	int minorMatrix[4];
	int numberNumber = 0, determinant;
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++) {
			numberNumber = 0;
			for (int rowCheck = 0; rowCheck < 3; rowCheck++)
				for (int columnCheck = 0; columnCheck < 3; columnCheck++)
					if (row != rowCheck && column != columnCheck) {
						minorMatrix[numberNumber] = key[rowCheck][columnCheck];
						numberNumber++;
					}
			cofactor[row][column] = ((minorMatrix[0] * minorMatrix[3]) - (minorMatrix[1] * minorMatrix[2])) *  pow(-1.0, row + column);
		}
	determinant = calculateDeterminant(key);
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			out[row][column] = double(cofactor[column][row]) / determinant;

	return out;
}

vector<long double> multiplyArray(vector<int> num, vector<vector<int>> key, int roundedLength) {
	num.resize(roundedLength, 32);
	vector<long double> output(roundedLength,0);
	for (int threeLocation = 0; threeLocation < roundedLength; threeLocation = threeLocation + 3)
		for (int outRow = 0; outRow < 3; outRow++)
			for (int aRow = 0; aRow < 3; aRow++)
				output[threeLocation + outRow] += (key[outRow][aRow] * num[threeLocation + aRow]);
	return output;
	}

vector<long double> multiplyArray(vector<long double> num, vector<vector<long double>> key, int roundedLength) {
	num.resize(roundedLength, 32);
	vector<long double> output(roundedLength, 0);
	for (int threeLocation = 0; threeLocation < roundedLength; threeLocation = threeLocation + 3)
		for (int outRow = 0; outRow < 3; outRow++)
			for (int aRow = 0; aRow < 3; aRow++)
				output[threeLocation + outRow] += (key[outRow][aRow] * num[threeLocation + aRow]);
	return output;
}