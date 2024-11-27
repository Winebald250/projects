#include <iostream>
#include <cstdio> // For std::rename

using namespace std; // Use the standard namespace

int main() {
    // Specify the hidden file name
    string hiddenPath = ".hidden_stl.cpp"; // Name of the hidden file
    string originalPath = "stl.cpp"; // Name to restore the file to

    // Attempt to rename the hidden file back to its original name
    if (rename(hiddenPath.c_str(), originalPath.c_str()) == 0) {
        // If renaming is successful, notify the user
        cout << "File unhidden successfully: " << originalPath << endl;
    } else {
        // If renaming fails, notify the user of the failure
        cout << "Failed to unhide the file. Please check if it exists." << endl;
    }

    return 0; // Return success
}
