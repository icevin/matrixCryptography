#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <ShlObj.h>
#include <shtypes.h>
using namespace std;

PWSTR saveFileDialog() {
	PWSTR filename;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			hr = pFileOpen->SetOptions(FOS_FORCEFILESYSTEM); // | FOS_PATHMUSTEXIST | FOS_FILEMUSTEXIST
			if (SUCCEEDED(hr))
			{
				// Set the file types to display only. 
				// Notice that this is a 1-based array.
				COMDLG_FILTERSPEC rgSpec[] =
				{
					{ L"Text Files", L"*.txt" },
					{ L"All Files", L"*.*" },
				};
				hr = pFileOpen->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
				if (SUCCEEDED(hr))
				{

					// Set the default extension to be ".txt" file.
					pFileOpen->SetTitle(L"Save to...");
					hr = pFileOpen->SetDefaultExtension(L"txt");
					if (SUCCEEDED(hr))
					{

						hr = pFileOpen->SetOkButtonLabel(L"Select");
						if (SUCCEEDED(hr)) {
							// Show the Open dialog box.
							hr = pFileOpen->Show(NULL);

							// Get the file name from the dialog box.
							if (SUCCEEDED(hr))
							{
								IShellItem *pItem;
								hr = pFileOpen->GetResult(&pItem);
								if (SUCCEEDED(hr))
								{
									LPWSTR pszFilePath;
									hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

									// Display the file name to the user.
									if (SUCCEEDED(hr))
									{
										filename = pszFilePath;
										CoTaskMemFree(pszFilePath);
									}
									pItem->Release();
								}
							}
							pFileOpen->Release();
						}
					}
				}
			}
		}
		CoUninitialize();
	}
	else if (!SUCCEEDED(hr)) {
		filename = NULL;
	}

	return filename;
}


PWSTR openFileDialog() {
	PWSTR filename;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			hr = pFileOpen->SetOptions(FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST | FOS_FILEMUSTEXIST);
			if (SUCCEEDED(hr))
			{
				// Set the file types to display only. 
				// Notice that this is a 1-based array.
				COMDLG_FILTERSPEC rgSpec[] =
				{
					{ L"Text Files", L"*.txt" },
					{ L"All Files", L"*.*" },
				};
				hr = pFileOpen->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
				if (SUCCEEDED(hr))
				{

					// Set the default extension to be ".txt" file.
					pFileOpen->SetTitle(L"Open file...");
					hr = pFileOpen->SetDefaultExtension(L"txt");
					if (SUCCEEDED(hr))
					{
						// Show the Open dialog box.
						hr = pFileOpen->Show(NULL);

						// Get the file name from the dialog box.
						if (SUCCEEDED(hr))
						{
							IShellItem *pItem;
							hr = pFileOpen->GetResult(&pItem);
							if (SUCCEEDED(hr))
							{
								LPWSTR pszFilePath;
								hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

								// Display the file name to the user.
								if (SUCCEEDED(hr))
								{
									filename = pszFilePath;
									CoTaskMemFree(pszFilePath);
								}
								pItem->Release();
							}
						}
						pFileOpen->Release();
					}
				}
			}
		}
		CoUninitialize();
	}

	return filename;
}

vector<int> legacyInputLine() {
	//Defines char array for input
	char inputArray[256];

	//Clears arrays
	fill_n(inputArray, 256, 0);

	//Use Getline instead of just cin so that spaces are inputed as well
	cin.getline(inputArray, 256);

	//Find actual length of text input
	int textLength = strlen(inputArray);

	//Create vector of size textLength, filled with -1's
	vector<int> num(textLength, -1);

	//converts chars into equivalent ASCII values
	for (int conversionCount = 0; conversionCount < textLength; conversionCount++)
		num[conversionCount] = int(inputArray[conversionCount]);

	return num;
}

vector<int> inputString() {
	vector<int> input;
	char a;
	do {
		cin.get(a);
		if (a == '\n' && !(input.empty()))
			break;
		input.push_back(int(a));
	} while (input.size() < (input.max_size()-100));

	return input;
}

void outputVector(vector<int> input) {
	for (int i = 0; i < input.size(); i++)
		cout << input[i] << endl;
}

void outputVector(vector<long double> input) {
	for (int i = 0; i < input.size(); i++)
		cout << input[i] << endl;
}

void outputVector(vector<char> input) {
	for (int i = 0; i < input.size(); i++)
		cout << input[i];
	cout << endl;	
}

vector<vector<long double>> outputMatrix(vector<vector<long double>> output) {
	for (int outputRow = 0; outputRow < 3; outputRow++)
		for (int outputColumn = 0; outputColumn < 3; outputColumn++) {
			cout << setw(20) << setprecision(10) << output[outputRow][outputColumn];
			if (outputColumn == 2)
				cout << endl << endl;
		}
	return output;
}

vector<vector<int>> outputMatrix(vector<vector<int>> output) {
	for (int row312934 = 0; row312934 < 3; row312934++)
		for (int colum3124 = 0; colum3124 < 3; colum3124++) {
			cout << setw(10) << setprecision(5) << output[row312934][colum3124];
			if (colum3124 == 2)
				cout << endl << endl;
		}
	return output;
}

vector<char> characterize(vector<long double> input) {
	vector<char> out (input.size(), char(32));
	for (int i = 0; i < input.size(); i++)
		out[i] = char(input[i] + 0.5);;
	return out;
}

vector<char> characterize(vector<int> input) {
	vector<char> out(input.size(), char(32));
	for (int i = 0; i < input.size(); i++)
		out[i] = char(input[i] + 0.5);;
	return out;
}
