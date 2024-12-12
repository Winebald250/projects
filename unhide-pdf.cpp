#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void unhideFilesWithExtension(const string& extension) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    // Define the hidden directory
    string hiddenDir = "C:\\ProgramData\\hidden_files"; // This directory is usually hidden

    // Create the search pattern
    string searchPattern = hiddenDir + "\\*." + extension;

    // Find the first file in the hidden directory
    hFind = FindFirstFile(searchPattern.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "No hidden files found with extension: " << extension << endl;
        return;
    }

    do {
        string fileName = findFileData.cFileName;
        string sourcePath = hiddenDir + "\\" + fileName;
        string destPath = string(".\\") + fileName;

        // Move the file back to the original location
        MoveFile(sourcePath.c_str(), destPath.c_str());
        cout << "Unhidden file: " << fileName << endl;

        // Remove the hidden attribute
        DWORD attributes = GetFileAttributes(destPath.c_str());
        if (attributes != INVALID_FILE_ATTRIBUTES) {
            SetFileAttributes(destPath.c_str(), attributes & ~FILE_ATTRIBUTE_HIDDEN);
        }

    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main() {
    string extension = "pdf"; // Specify the extension to unhide
    unhideFilesWithExtension(extension); // Call the function to unhide files
    return 0;
}
