#pragma once
#include "library.h"
using namespace std;

void getScreenSize(int& columns, int& rows) {
	CONSOLE_SCREEN_BUFFER_INFO screensize;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screensize);
	columns = screensize.srWindow.Right - screensize.srWindow.Left + 1;
	rows = screensize.srWindow.Bottom - screensize.srWindow.Top + 1;
}

void line() {
	static int columns;
	static int rows;
	getScreenSize(columns, rows);
	for (int i = 0; i < columns - 1; i++)
		cout << "-";
	cout << endl;
	return;
}

void outputSpace(int spaceLength) {
	for (int i = 0; i < spaceLength; i++)
		cout << " ";
}

void displayTitle() {
	int columns, rows, spaceLength;
	getScreenSize(columns, rows);
	spaceLength = fabs((columns / 2) - 66);
	line();
	cout << endl;

	outputSpace(spaceLength);
	cout << "  ______                                                                                             __      __                     " << endl;
	outputSpace(spaceLength);
	cout << " /      \\                                                                                           /  |    /  |                    " << endl;
	outputSpace(spaceLength);
	cout << "/$$$$$$  | __    __  _____  ____   _____  ____    ______    _______   ______   __    __   ______   _$$ |_   $$/   ______   _______  " << endl;
	outputSpace(spaceLength);
	cout << "$$ \\__$$/ /  |  /  |/     \\/    \\ /     \\/    \\  /      \\  /       | /      \\ /  |  /  | /      \\ / $$   |  /  | /      \\ /       \\ " << endl;
	outputSpace(spaceLength);
	cout << "$$      \\ $$ |  $$ |$$$$$$ $$$$  |$$$$$$ $$$$  | $$$$$$  |/$$$$$$$/ /$$$$$$  |$$ |  $$ |/$$$$$$  |$$$$$$/   $$ |/$$$$$$  |$$$$$$$  |" << endl;
	outputSpace(spaceLength);
	cout << " $$$$$$  |$$ |  $$ |$$ | $$ | $$ |$$ | $$ | $$ | /    $$ |$$ |      $$ |  $$/ $$ |  $$ |$$ |  $$ |  $$ | __ $$ |$$ |  $$ |$$ |  $$ |" << endl;
	outputSpace(spaceLength);
	cout << "/  \\__$$ |$$ \\__$$ |$$ | $$ | $$ |$$ | $$ | $$ |/$$$$$$$ |$$ \\_____ $$ |      $$ \\__$$ |$$ |__$$ |  $$ |/  |$$ |$$ \\__$$ |$$ |  $$ |" << endl;
	outputSpace(spaceLength);
	cout << "$$    $$/ $$    $$ |$$ | $$ | $$ |$$ | $$ | $$ |$$    $$ |$$       |$$ |      $$    $$ |$$    $$/   $$  $$/ $$ |$$    $$/ $$ |  $$ |" << endl;
	outputSpace(spaceLength);
	cout << " $$$$$$/   $$$$$$$ |$$/  $$/  $$/ $$/  $$/  $$/  $$$$$$$/  $$$$$$$/ $$/        $$$$$$$ |$$$$$$$/     $$$$/  $$/  $$$$$$/  $$/   $$/ " << endl;
	outputSpace(spaceLength);
	cout << "          /  \\__$$ |                                                          /  \\__$$ |$$ |                                        " << endl;
	outputSpace(spaceLength);
	cout << "          $$    $$/                                                           $$    $$/ $$ |                                        " << endl;
	outputSpace(spaceLength);
	cout << "           $$$$$$/                                                             $$$$$$/  $$/                                         " << endl;
	cout << endl << endl;
	int secondSpaceLength = fabs((columns / 2) - 26);
	outputSpace(secondSpaceLength);
	cout << "by Kevin Tang, Amey Venkatanarayan, and Adrian Wiley" << endl;
}

void prepScreen() {
	system("cls");
	if (titleStat == "ON") {
		displayTitle();
	}
	line();
}

char chooseColor(string prompt) {
	char chosen, select;
	int isRight, size = 20;
	string selection, width;
	for (int i = 0; i < size; i++)
	{
		width += " ";
	}
	do {
		isRight = 1;
		prepScreen();
		cout << prompt << endl;
		cout << "1. Black " << width << left << "A. Grey" << endl;
		cout << "2. Blue  " << width << left << "B. Light Blue" << endl;
		cout << "3. Green " << width << left << "C. Light Green" << endl;
		cout << "4. Aqua  " << width << left << "D. Light Aqua" << endl;
		cout << "5. Red   " << width << left << "E. Light Red" << endl;
		cout << "6. Purple" << width << left << "F. Light Purple" << endl;
		cout << "7. Yellow" << width << left << "G. Light Yellow" << endl;
		cout << "8. White " << width << left << "H. Bright White" << endl;
		cout << "ESC: Return to menu\n";
		line();
		cout << ": ";
		select = _getch();
		cout << select << endl;
		line();
		select = char(toupper(select));
		if (int(select) == 27)
			return ' ';
		else if (select == '1') {
			selection = "Black";
			chosen = '0';
		}
		else if (select == '2') {
			selection = "Blue";
			chosen = '1';
		}
		else if (select == '3') {
			selection = "Green";
			chosen = '2';
		}
		else if (select == '4') {
			selection = "Aqua";
			chosen = '3';
		}
		else if (select == '5') {
			selection = "Red";
			chosen = '4';
		}
		else if (select == '6') {
			selection = "Purple";
			chosen = '5';
		}
		else if (select == '7') {
			selection = "Yellow";
			chosen = '6';
		}
		else if (select == '8') {
			selection = "White";
			chosen = '7';
		}
		else if (select == 'A') {
			selection = "Grey";
			chosen = '8';
		}
		else if (select == 'B') {
			selection = "Light Blue";
			chosen = '9';
		}
		else if (select == 'C') {
			selection = "Light Green";
			chosen = 'A';
		}
		else if (select == 'D') {
			selection = "Light Aqua";
			chosen = 'B';
		}
		else if (select == 'E') {
			selection = "Light Red";
			chosen = 'C';
		}
		else if (select == 'F') {
			selection = "Light Purple";
			chosen = 'D';
		}
		else if (select == 'G') {
			selection = "Light Yellow";
			chosen = 'E';
		}
		else if (select == 'H') {
			selection = "Bright White";
			chosen = 'F';
		}
		else {
			isRight = 0;
		}
	} while (isRight == 0);
	return chosen;
}

void updateColor(char arr[2]) {
	string command = "color ";
	command += arr[0];
	command += arr[1];
	const char * c = command.c_str();
	system(c);
}	

void intro() {
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csb;
	GetConsoleScreenBufferInfo(hd, &csb);
	csb.dwSize.X = 165;
	SetConsoleScreenBufferSize(hd, csb.dwSize);

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 1366, 768, TRUE); // 168 width, 100 height
	system("color 79");
	system("title Symmacryption");
	return;
}