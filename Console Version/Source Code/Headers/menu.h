#pragma once
#include "library.h"

int firstrun = 1;

using namespace std;

int askFor(string prompt) {
	char option;
	do {
		cout << endl;
		line();
		cout << prompt << " (Y/N)" << endl;
		line();
		cout << ": ";
		option = _getch();
		option = char(toupper(option));
		cout << option << endl;
		if (option == 'Y')
			return 1;
		else if (option == 'N')
			return 0;
	} while (option != 'Y' && option != 'N');
}

void hangUntilContinue() {
	cout << "<Press any key to continue>";
	int get = _getch();
	return;
}

void consoleEncryptMenu() {
	prepScreen();
	cout << "Select output file: " << endl;
	line();
	string path = pFilename(saveFileDialog());
	if (path == "null")
		return;
	prepScreen();
	cout << "Generating key..." << endl;
	line();
	vector<vector<int>> key = generateKey();
	prepScreen();
	cout << "Text to encrypt: (Press enter twice to submit)" << endl;
	line();
	encryptToFile(path, inputString());
	prepScreen();
	cout << "Encryption finished. Text outputted to:" << endl;
	cout << "\"" << path << "\"" << endl;
	line();
	hangUntilContinue();
}

void fileEncryptMenu() {
	line();
	cout << "Select input file: " << endl;
	line();
	string path = pFilename(openFileDialog());
	if (path == "null")
		return;
	vector<int> input = getTextFromFile(path);
	prepScreen();
	cout << "Select output location:" << endl;
	line();
	string pout = pFilename(saveFileDialog());
	if (pout == "null")
		return;
	vector<vector<int>> key = generateKey();
	encryptToFile(pout, input);
	prepScreen();
	cout << "File \"" << path << "\" encrypted to file:" << endl;
	cout << "\"" << pout << "\"" << endl;
	line();
	hangUntilContinue();
}

void encryptMenu() {
	char option;
	do {
		prepScreen();
		cout << "Encrypt from:\n";
		cout << "1: Console\n";
		cout << "2: Existing file\n";
		cout << "ESC: Return to menu\n";
		line();
		cout << ": ";
		option = _getch();
		cout << option << endl;
	} while (int(option) != 27 && option != '1' && option != '2');
	if (int(option) == 27)
		return;
	else if (option == '1')
		consoleEncryptMenu();
	else if (option == '2')
		fileEncryptMenu();
}

void fileDecryptMenu() {
	int cont, save;
	do {
		cout << "Select file: " << endl;
		string path = pFilename(openFileDialog());
		if (path == "null")
			return;
		vector<char> decrypted = decryptFromFile(path);
		prepScreen();
		cout << "Decrypted text: " << endl;
		line();
		outputVector(decrypted);
		save = askFor("Do you want to save this output?");
		if (save) {
			string outPath = pFilename(saveFileDialog());
			if (outPath == "null")
				return;
			putChar(decrypted, outPath);
		}
		cont = askFor("Do you want to decrypt another file?");
	} while (cont == 1);
}

void decryptMenu() {
	char option;
		prepScreen();
		cout << "Choose the file to decrypt from:\n";
		cout << "<Press any key to continue>\n";
		cout << "ESC: Return to menu\n";
		line();
		cout << ": ";
		option = _getch();
		cout << option << endl;
		line();
	if (int(option) == 27)
		return;
	else
		fileDecryptMenu();
}

void graphicsSettings() {
	char optio2n;
	static char color[2] = { '7','9' };
	static char old[2] = { '7', '9' };
	titleStat = "ON";
	int keepGoing1, keepGoing2;
	do {
		prepScreen();
		cout << "Graphics Settings:\n";
		cout << "1. Text Color\n";
		cout << "2. Background Color\n";
		cout << "3. Toggle Title (Currently " << titleStat << ").\n";
		cout << "ESC: Return to menu\n";
		line();
		cout << ": ";
		optio2n = _getch();
		cout << optio2n << endl;
		if (int(optio2n) == 27)
			return;
		else if (optio2n == '1') {
			do {
				old[1] = color[1];
				old[0] = color[0];
				color[1] = chooseColor("Text color: ");
				if (color[1] == ' ')
					break;
				if (color[1] == color[0]) {
					cout << "Text and Background cannot be the same color.\n";
					keepGoing1 = 0;
					updateColor(old);
					color[1] = old[1];
					hangUntilContinue();
				}
				else {
					updateColor(color);
					keepGoing1 = askFor("Keep these colors?");
					if (keepGoing1 == 0) {
						color[1] = old[1];
						color[0] = old[0];
						updateColor(color);
					}
					else
					{
						old[1] = color[1];

					}
				}
			} while (keepGoing1 == 0);
		}
		else if (optio2n == '2') {
			do {
				old[0] = color[0];
				color[0] = chooseColor("Background color: ");
				if (color[0] == ' ')
					break;
				if (color[1] == color[0]) {
					cout << "Text and Background cannot be the same color.\n";
					keepGoing2 = 0;
					updateColor(old);
					color[0] = old[0];
					hangUntilContinue();
				}
				else {
					updateColor(color);
					keepGoing2 = askFor("Keep these colors?");
					if (keepGoing2 == 0) {
						updateColor(old);
						color[0] = old[0];
					}
					else
					{
						old[0] = color[0];
					}
				}
			} while (keepGoing2 == 0);
		}
		else if (optio2n = '3') {
			if (titleStat == "ON")
				titleStat = "OFF";
			else if (titleStat == "OFF")
				titleStat = "ON";
		}
	} while (int(optio2n) != 49 && int(optio2n) != 50 && int(optio2n) != 33);
}

void encryptionSettings() {
	char input;
	static int leftBar, rightBar;
	int tempEncrypt = int((float(float(encryptLvl) / 32.0) * 10.0) + 0.5);
	do
	{
		leftBar = tempEncrypt;
		rightBar = 10 - tempEncrypt;
		prepScreen();
		cout << "Encryption Strength:\n";
		cout << "Higher values take longer to encrypt\n";
		cout << "Min <";
		for (int i = 0; i < leftBar; i++)
			cout << "-";
		cout << "|";
		for (size_t i = 0; i < rightBar; i++)
			cout << "-";
		cout << "> Max\n";
		cout << "1. Increase level\n";
		cout << "2. Decrease level\n";
		cout << "3. Reset to default\n";
		cout << "ESC: Return to menu\n";
		line();
		cout << ": ";
		input = _getch();
		if (input == '1' && tempEncrypt<10) {
			tempEncrypt++;	
		}
		else if (input == '2') {
			if (tempEncrypt > 0) {
				tempEncrypt--;
			}
			else
				tempEncrypt = 0;
		}
		else if (input == '3') {
			tempEncrypt = 5;
		}
		else if (int(input == 27)) {
			break;
		}
	} while (int(input) != '27');
	encryptLvl = int(((float(tempEncrypt) / 10.0) * 32.0) + 0.5);
}

void audioSettings() {
	static vector<string> songs;
	static vector<string> filenames;
	if (firstrun == 1) {
		//MUSIC DEFAULTS
		songs.push_back("Jeopardy Music");
		filenames.push_back(".\\Music\\Jeopardy.wav");
		songs.push_back("Mission Impossible Theme");
		filenames.push_back(".\\Music\\Mission Impossible.wav");
		songs.push_back("The Matrix Theme");
		filenames.push_back(".\\Music\\The Matrix.wav");
		songs.push_back("James Bond Theme");
		filenames.push_back(".\\Music\\007 Theme.wav");
		firstrun = 0;
	}

	static int currentlyPlaying = 0;
	char entered;
	do
	{
		prepScreen();
		cout << "Audio Settings:\n";
		if (audioStat == "ON" && currentlyPlaying < songs.size()) {
			cout << "NOW PLAYING: " << songs[currentlyPlaying] << endl;
		}

		cout << "1. Audio (Currently " << audioStat << ")\n";
		cout << "2. View/Change Songs\n";
		cout << "ESC: Return to menu\n";
		line();
		cout << ": ";
		entered = _getch();
		if (int(entered == 27)) {
			break;
		}
		else if (entered == '1') {
			if (audioStat == "ON") {
				audioStat = "OFF";
				PlaySoundA(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (audioStat == "OFF") {
				audioStat = "ON";
				const char * nextSongName = filenames[currentlyPlaying].c_str();
				PlaySoundA(nextSongName, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
		}
		else if (entered == '2') {
			char secondInput;
			int selection;
			do
			{
				prepScreen();
				cout << "Song Library:\n";
				cout << "Select a song or press A to add a new song\n";
				line();	
				for (int i = 0; i < songs.size(); i++)
				{
					cout << i+1 << ". " << songs[i];
					if (i == currentlyPlaying)
						cout << " (SELECTED)";
					cout << endl;
				}
				cout << "ESC: Return to menu\n";
				line();
				cout << ": ";
				secondInput = _getch();
				secondInput = char(tolower(secondInput));
				if (int(secondInput == 27))
					break;
				else if (int(secondInput) >= 49 && int(secondInput) <= (48 + songs.size())) {
					selection = secondInput - 48;
					currentlyPlaying = selection - 1;
					playSong(filenames[currentlyPlaying]);
				}
				else {
					if (secondInput == 'a')
						{
							string nameBuff, fileBuff;
							nameBuff.clear();
							fileBuff.clear();
							prepScreen();
							cout << "Add new song to library:\n";
							cout << "Open file...\n";
							line();
							hangUntilContinue();
							cout << endl;
							fileBuff = pFilename(openWavDialog());
							if (fileBuff == "null") {
								goto endOfAudio;
							}
							cout << fileBuff << endl;
							filenames.push_back(fileBuff);
							line();
							cout << "Track Title:\n";
							line();
							cout << ": ";
							getline(cin, nameBuff);
							songs.push_back(nameBuff);
							endOfAudio:;
						}
				}
			} while (int(secondInput) != 27);
		}

	} while (int(entered) != '27');
}

void settingsMenu() {
	char optio1n;
	do {
		prepScreen();
		cout << "Settings:\n";
		cout << "1. Encryption Settings\n";
		cout << "2. Audio Settings\n";
		cout << "3. Graphics Settings\n";
		cout << "ESC: Return to menu\n";
		line();
		cout << ": ";
		optio1n = _getch();
		cout << optio1n << endl;
		line();
		if (int(optio1n) == 27)
			return;
		else if (optio1n == '1') {
			encryptionSettings();
		}
		else if (optio1n == '2') {
			audioSettings();
		}
		else if (optio1n = '3') {
			graphicsSettings();
		}
	} while (int(optio1n) != 49 && int(optio1n) != 50 && int(optio1n) != 51 && int(optio1n) != 33);
}

int askForExit() {
	char option;
	do {
		prepScreen();
		cout << "Are you sure you want to exit? (Y/N)" << endl;
		line();
		cout << ": ";
		option = _getch();
		option = char(toupper(option));
		cout << option << endl;
		if (option == 'Y')
			return 1;
		else if (option == 'N')
			return 0;
	} while (option != 'Y' && option != 'N');
}

int menu() {
	char option;
	do
	{
		prepScreen();
		cout << "Select an option:" << endl;
		cout << "1: Encrypt" << endl;
		cout << "2: Decrypt" << endl;
		cout << "3: Program Settings" << endl;
		cout << "or press ESC to exit" << endl;
		line();
		cout << ": ";
		option = _getch();
		cout << option << endl;
	} while ((int(option) < 49 || int(option) > 52) && int(option) != 27);
	if (option == 49)
		encryptMenu();
	else if (option == 50)
		decryptMenu();
	else if (option == 51)
		settingsMenu();
	else if (option == 27) {
		if (askForExit()) {
			cout << endl;
			return 0;
		}
	}
	return 1;
}

/*
void oldConsoleDecryptMenu() {
	int cont, save;
	vector<vector<int>> key;
	key.resize(3);
	for (int resize = 0; resize < 3; resize++)
		key[resize].resize(3);

	do {
		do {
			prepScreen();
			if (!calculateDeterminant(key)) {
				cout << "Invalid key." << endl;
				line();
			}
			cout << "Input Key: " << endl;
			cout << "Input 9 elements, 3 per row seperated by spaces. Example:\n";
			cout << "1 2 3\n-111 -222 -333\n5 5 5\n";
			line();
			vector<int> oneDimensionalKey;
			int temp;
			for (int i = 0; i < 9; i++) {
				cin >> temp;
				oneDimensionalKey.push_back(temp);
			}
			temp = 0;
			for (int row = 0; row < 3; row++)
				for (int column = 0; column < 3; column++)
				{
					key[row][column] = oneDimensionalKey[(row * 3) + column];
				}
		} while (calculateDeterminant(key) == 0);
		int length;
		prepScreen();
		cout << "Input length:" << endl;
		line();
		cout << ": ";
		cin >> length;
		line();
		prepScreen();
		int inBuff;
		vector<long double> input;
		for (int i = 0; i < length; i++) {
			cin >> inBuff;
			input.push_back(inBuff);
		}
		vector<char> decrypted = decrypt(input, key);
		prepScreen();
		cout << "Decrypted text: " << endl;
		line();
		outputVector(decrypted);
		save = askFor("Do you want to save this output?");
		if (save) {
			string path11 = pFilename(saveFileDialog());
			if (path11 == "null")
				return;
			putChar(decrypted, path11);
		}
		cont = askFor("Do you want to decrypt another file?");
	} while (cont == 1);
} */