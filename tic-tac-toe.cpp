#include <iostream>

using namespace std;

// Function to display the current game board
void showboard(const char board[9]) {
    cout << "Board:\n"; // Print the board title
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " "; // Show each cell in the board
        if ((i + 1) % 3 == 0) cout << endl; // New line after every 3 cells
    }
}

// Function to check if a player has won
int checkWin(const char board[9], char player) {
    // Winning combinations for Tic-Tac-Toe
    const int winningcombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };

    // Check each winning combination
    for (int i = 0; i < 8; i++) {
        // If player has all three in a row
        if (board[winningcombinations[i][0]] == player &&
            board[winningcombinations[i][1]] == player &&
            board[winningcombinations[i][2]] == player) {
            return 1; // Player wins
        }
    }
    return 0; // No winner yet
}

int main() {
    char playagain; // Variable to ask if the player wants to play again
    do {
        // Initialize the board with numbers
        char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char currentplayer = 'X'; // Start with player X
        int move; // Variable for player's move

        while (true) {
            showboard(board); // Show the current board
            cout << "Player " << currentplayer << ", enter a move (1-9): ";
            cin >> move; // Get the player's move
            move--; // Adjust for zero-based index

            // Check if the move is valid
            if (move < 0 || move >= 9 || board[move] == 'X' || board[move] == 'O') {
                cout << "Invalid move. Try again.\n"; // Warn the player
                continue; // Ask for the move again
            }

            board[move] = currentplayer; // Place the player's mark on the board
            // Check if the current player has won
            if (checkWin(board, currentplayer) == 1) {
                showboard(board); // Show the final board
                cout << "Player " << currentplayer << " wins!\n"; // Announce the winner
                break; // End the game
            }

            // Switch to the other player
            currentplayer = (currentplayer == 'X') ? 'O' : 'X';
        }

        // Ask if the player wants to play again
        cout << "Do you want to play again? (y/n): ";
        cin >> playagain;

    }
    while (playagain == 'y' || playagain == 'Y'); // Repeat if yes

    cout << "Thank you for playing!\n"; // End message
    return 0; // End of the program
}
