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

    // Track game state
    bool guessedLetters[10] = {false}; // Assume max word length of 10
    int incorrectGuesses = 0;
    int maxGuesses = 6;

    cout << "Welcome to Hangman!" << endl;

    while (incorrectGuesses < maxGuesses) {
        // Display current game status
        cout << "\nWord: ";
        screenword(word, guessedLetters);

        cout << "Wrong! Lives left: " << maxGuesses - incorrectGuesses << endl;

        // Get player's guess
        char guess;
        cout << "Guess a letter: ";
        cin >> guess;

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
            incorrectGuesses++;
            cout << "Incorrect guess!" << endl;
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
