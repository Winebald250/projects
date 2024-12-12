#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void hideFilesWithExtension(const string& extension) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    // Define a hidden directory in a temporary location
    string hiddenDir = "C:\\ProgramData\\hidden_files"; // This directory is usually hidden

    // Create the hidden directory if it doesn't exist
    CreateDirectory(hiddenDir.c_str(), NULL);

    // Set the directory attribute to hidden
    SetFileAttributes(hiddenDir.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_DIRECTORY);

    // Create the search pattern
    string searchPattern = string(".\\*.") + extension; // Current directory

    // Find the first file
    hFind = FindFirstFile(searchPattern.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "No files found with extension: " << extension << endl;
        return;
    }

    do {
        string fileName = findFileData.cFileName;
        string sourcePath = string(".\\") + fileName;
        string destPath = hiddenDir + "\\" + fileName;

        // Move the file to the hidden directory
        MoveFile(sourcePath.c_str(), destPath.c_str());
        cout << "Hidden file: " << fileName << endl;

    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main() {
    string extension = "pdf"; // Specify the extension to hide
    hideFilesWithExtension(extension); // Call the function to hide files
    return 0;
}
