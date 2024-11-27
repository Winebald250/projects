#include <iostream>
#include <cstdio> // For std::rename

using namespace std; // Use the standard namespace

int main() {
    // Specify the original file name
    string filePath = "stl.cpp"; // Original file to be hidden
    string hiddenPath = ".hidden_" + filePath; // New name for the hidden file

    // Attempt to rename the file to hide it
    if (rename(filePath.c_str(), hiddenPath.c_str()) == 0) {
        // If renaming is successful, notify the user
        cout << "File hidden successfully: " << hiddenPath << endl;
    } else {
        // If renaming fails, notify the user of the failure
        cout << "Failed to hide the file. Please check if it exists." << endl;
    }

    return 0; // Return success
}
