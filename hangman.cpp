#include <iostream>
#include <ctime>
using namespace std;

// Function to display the current state of the word
void screenword(const string& word, const bool guessedLetters[]) {
    for (int i = 0; i < word.length(); i++) {
        if (guessedLetters[i]) {
            cout << word[i] << " "; // Show guessed letters
        } else {
            cout << "_ "; // Hide unguessed letters
        }
    }
    cout << endl;
}

int main() {
    // Predefined list of words for the game
    string words[] = {"teacher", "program", "computer", "learning", "coding"};

    // Select a random word
    srand(time(0)); // Seed for random number generation
    string word = words[rand() % 5];

    // Ask the user to choose the difficulty level
    int maxGuesses;
    string level;
    cout << "Welcome to Hangman!\n";
    cout << "Choose a difficulty level (easy, medium, hard): ";
    cin >> level;

    // Set the number of lives based on difficulty level
    if (level == "easy") {
        maxGuesses = 10;
    } else if (level == "medium") {
        maxGuesses = 6;
    } else if (level == "hard") {
        maxGuesses = 3;
    } else {
        cout << "Invalid difficulty level. Defaulting to medium.\n";
        maxGuesses = 6;
    }

    // Track game state
    bool guessedLetters[10] = {false}; // Assume max word length of 10
    int incorrectGuesses = 0;

    while (incorrectGuesses < maxGuesses) {
        // Display current game status
        cout << "\nWord: ";
        screenword(word, guessedLetters);

        cout << "Lives left: " << maxGuesses - incorrectGuesses << endl;

        // Get player's guess
        string input;
        cout << "Guess a letter: ";
        cin >> input;

        // Validate input: must be a single letter
        if (input.length() != 1 || (input[0] < 'a' || input[0] > 'z') && (input[0] < 'A' || input[0] > 'Z')) {
            cout << "Invalid input! Please enter a single letter.\n";
            continue; // Skip to the next iteration without reducing lives
        }

        // Convert uppercase to lowercase manually
        char guess = (input[0] >= 'A' && input[0] <= 'Z') ? input[0] + 32 : input[0];

        // Check if letter is in the word
        bool found = false;
        for (int i = 0; i < word.length(); i++) {
            if (word[i] == guess && !guessedLetters[i]) {
                guessedLetters[i] = true;
                found = true;
            }
        }

        // Update game state
        if (!found) {
            cout << "Incorrect guess!" << endl;
            incorrectGuesses++;
        }

        // Check win condition
        bool wordGuessed = true;
        for (int i = 0; i < word.length(); i++) {
            if (!guessedLetters[i]) {
                wordGuessed = false;
                break;
            }
        }

        // Win or lose check
        if (wordGuessed) {
            cout << "\nCongratulations! You won! The word was " << word << endl;
            break;
        }

        if (incorrectGuesses == maxGuesses) {
            cout << "\nYou lost! The word was " << word << endl;
        }
    }

    return 0;
}
