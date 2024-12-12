#include <iostream>
#include <windows.h>

using namespace std;

void unhideFolder(const string& folderName) {
    string hiddenPath = "C:\\hidden_folders\\" + folderName; // Specify the hidden directory

    // Move the folder back to the original location
    if (MoveFile(hiddenPath.c_str(), folderName.c_str())) {
        // Remove the hidden attribute
        DWORD attributes = GetFileAttributes(folderName.c_str());
        if (attributes != INVALID_FILE_ATTRIBUTES) {
            // Remove the hidden attribute
            SetFileAttributes(folderName.c_str(), attributes & ~FILE_ATTRIBUTE_HIDDEN);
            cout << "Folder unhidden: " << folderName << endl;
        } else {
            cout << "Failed to retrieve folder attributes." << endl;
        }
    } else {
        cout << "Failed to unhide folder. Please check if it exists." << endl;
    }
}

int main() {
    string folderName = "me"; // Specify the folder to unhide
    unhideFolder(folderName); // Call the function to unhide the folder
    return 0;
}
