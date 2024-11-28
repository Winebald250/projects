#include <iostream>

using namespace std;

// Function to display the current game board
void showboard(const char board[9]) {
    cout << "Board:\n";
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
}

// Function to check if a player has won
int checkWin(const char board[9], char player) {
    const int winningcombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };

    for (int i = 0; i < 8; i++) {
        if (board[winningcombinations[i][0]] == player &&
            board[winningcombinations[i][1]] == player &&
            board[winningcombinations[i][2]] == player) {
            return 1; // Player wins
        }
    }
    return 0; // No winner yet
}

int main() {
    char playagain;
    do {
        char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char currentplayer = 'X';
        int move;

        while (true) {
            showboard(board);
            cout << "Player " << currentplayer << ", enter a move (1-9): ";
            cin >> move;

            // If input is invalid or out of range
            if (cin.fail() || move < 1 || move > 9 || board[move - 1] == 'X' || board[move - 1] == 'O') {
                cin.clear(); // Clear the input buffer
                cin.ignore(1000, '\n'); // Ignore invalid input
                cout << "Invalid move. Try again.\n";
                continue;
            }

            board[move - 1] = currentplayer; // Place the player's mark

            if (checkWin(board, currentplayer)) {
                showboard(board);
                cout << "Player " << currentplayer << " wins!\n";
                break;
            }

            currentplayer = (currentplayer == 'X') ? 'O' : 'X'; // Switch player
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playagain;

    } while (playagain == 'y' || playagain == 'Y');

    cout << "Thank you for playing!\n";
    return 0;
}
