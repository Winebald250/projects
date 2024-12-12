#include <iostream>
#include <windows.h>

using namespace std;

void hideFolder(const string& folderName) {
    string hiddenPath = "C:\\hidden_folders\\" + folderName; // Specify a hidden directory

    // Create the hidden directory if it doesn't exist
    CreateDirectory("C:\\hidden_folders", NULL);

    // Move the folder to the hidden location
    if (MoveFile(folderName.c_str(), hiddenPath.c_str())) {
        cout << "Folder hidden: " << folderName << endl;
    } else {
        cout << "Failed to hide folder. Please check if it exists." << endl;
    }
}

int main() {
    string folderName = "me"; // Specify the folder to hide
    hideFolder(folderName); // Call the function to hide the folder
    return 0;
}
