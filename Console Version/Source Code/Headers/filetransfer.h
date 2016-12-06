#pragma once
#include "library.h"
using namespace std;

int getLength(string filename) {
	ifstream file;
	file.open(filename);
	int x;
	string y;
	file >> y;
	istringstream buffer(y);
	buffer >> x;
	return x;
}

vector<vector<int>> getKey(string filename) {
	ifstream file;
	file.open(filename);
	int x;
	file >> x;
	vector<vector<int>> key;
	key.resize(3);
	for (int resize = 0; resize < 3; resize++)
		key[resize].resize(3);

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			string z;
			file >> z;
			istringstream buffer(z);
			buffer >> key[x][y];
		}
	}
	return key;
}

vector<long double> getText(string filename) {
	ifstream file;
	file.open(filename);
	int x;
	file >> x;
	vector<vector<int>> key;
	key.resize(3);
	for (int resize = 0; resize < 3; resize++)
		key[resize].resize(3);
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			file >> key[x][y];
		}
	}
	vector<long double> num;
	num.resize(x, -1);
	for (int i = 1; i <= x; i++) {
		file >> num[i - 1];
	}
	return num;
}

int clear(string filename) {
	ofstream file;
	file.open(filename);
	try {
		if (file.fail()) {
			throw 1;
		}
	}
	catch (int x) {
		return x;
	}

	file << "";
	return 0;
}

void errorHandler(int errorCode) {
	if (errorCode == 1) {
		cout << "Error finding or overwritting text file!" << endl;
	}

	if (errorCode == 2) {
		cout << "Error with inputting text length!" << endl;
	}

	if (errorCode == 3) {
		cout << "Error with inputting key!" << endl;
	}

	if (errorCode == 4) {
		cout << "Error with inputting cipher text!" << endl;
	}
}


int putLength(int length, string filename) {
	ofstream file;
	file.open(filename, ios::app);
	try {
		if (file.fail())
			throw 2;
	}
	catch (int x) {
		return x;
	}

	file << length << " ";
	return 0;
}

int putKey(vector<vector<int>> key, string filename) {
	ofstream file;
	file.open(filename, ios::app);

	try {
		if (file.fail()) {
			throw 3;
		}
	}
	catch (int x) {
		return x;
	}

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			file << key[x][y] << " ";
		}
	}

	return 0;
}

int putText(vector<long double> text, string filename) {
	ofstream file;
	file.open(filename, ios::app);

	try {
		if (file.fail()) {
			throw 4;
		}
	}
	catch (int x) {
		return x;
	}

	for (int x = text.size(), y = 0; y < x; y++) {
		file << text[y] << " ";
	}

	return 0;
}

void outputToFile(string outputFilename, vector<long double> encrypted, vector<vector<int>> key) {
	clear(outputFilename);
	putLength(encrypted.size(), outputFilename);
	putKey(key, outputFilename);
	putText(encrypted, outputFilename);
}

vector<int> getTextFromFile(string filename) {
	ifstream in(filename);
	string contentsInString((istreambuf_iterator<char>(in)),
	istreambuf_iterator<char>());
	vector<int> num;
	for (int i = 0; i < contentsInString.size(); i++)
		num.push_back(int(contentsInString[i]));
	return num;
}

int putChar(vector<char> input, string filename) {
	clear(filename);
	ofstream file;
	file.open(filename);
	try {
		if (file.fail()) {
			throw 4;
		}
	}
	catch (int x) {
		return x;
	}

	for (int x = input.size(), y = 0; y < x; y++) {
		file << input[y];
	}
	file.close();
	return 0;
}