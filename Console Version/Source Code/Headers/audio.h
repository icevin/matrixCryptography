#pragma once
#include "library.h"

void playSong(string filename) {
	if (audioStat == "ON") {
		const char * a = filename.c_str();
		PlaySoundA(a, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	else {
		cout << "Error: Audio is muted" << endl;
		hangUntilContinue();
	}
}

PWSTR openWavDialog() {
	PWSTR filename = L"null1";
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);

		IFileOpenDialog *pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			hr = pFileOpen->SetOptions(FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST | FOS_FILEMUSTEXIST);

				// Set the file types to display only. 
				// Notice that this is a 1-based array.
				COMDLG_FILTERSPEC rgSpec[] =
				{
					{ L"WAV Files", L"*.wav" },
				};
				hr = pFileOpen->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);


					// Set the default extension to be ".txt" file.
					pFileOpen->SetTitle(L"Open Song...");
					hr = pFileOpen->SetDefaultExtension(L"txt");
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
								filename = pszFilePath;
								CoTaskMemFree(pszFilePath);
								pItem->Release();
							}
							else 
								filename = L"null";
						}
						else if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED)) {
							filename = L"null";
						}
						pFileOpen->Release();

		CoUninitialize();
		if (filename == L"null1")
			filename = L"null";
	return filename;
}

void unused(string filename) {
	//string filename = pFilename(openFileDialog());
	const char * a = filename.c_str();
	if (filename != "null") {
		PlaySoundA(a, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}