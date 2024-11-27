#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Enum for genres
enum class Genre {
    fiction,
    nonfiction,
    periodical,
    biography,
    children
};

// Book class
class Book {
public:
    string ISBN;
    string title;
    string author;
    int copyrightDate;
    bool checkedOut;
    Genre genre;

    // Constructor
    Book(string isbn, string t, string a, int date, Genre g)
        : ISBN(isbn), title(t), author(a), copyrightDate(date), genre(g), checkedOut(false) {}

    // Functions to check out and check in a book
    void checkOut() { checkedOut = true; }
    void checkIn() { checkedOut = false; }

    // Overloaded operators
    bool operator==(const Book &other) const { return ISBN == other.ISBN; }
    bool operator!=(const Book &other) const { return !(*this == other); }

    friend ostream &operator<<(ostream &os, const Book &b) {
        os << "Title: " << b.title << "\n"
           << "Author: " << b.author << "\n"
           << "ISBN: " << b.ISBN << "\n"
           << "Genre: " << (b.genre == Genre::fiction ? "Fiction" :
                           b.genre == Genre::nonfiction ? "Nonfiction" :
                           b.genre == Genre::periodical ? "Periodical" :
                           b.genre == Genre::biography ? "Biography" : "Children");
        return os;
    }
};

// Patron class
class Patron {
public:
    string name;
    string cardNumber;
    int fees;

    // Constructor
    Patron(string n, string card, int f = 0)
        : name(n), cardNumber(card), fees(f) {}

    // Function to check if the patron owes fees
    bool owesFees() const { return fees > 0; }
};

// Transaction class
class Transaction {
public:
    Book book;
    Patron patron;
    string activity; // "Check Out" or "Check In"
    string date;

    // Constructor
    Transaction(Book b, Patron p, string act, string d)
        : book(b), patron(p), activity(act), date(d) {}

    // Display the transaction
    void display() const {
        cout << "Transaction: " << activity << "\n"
             << "Book: " << book.title << "\n"
             << "Patron: " << patron.name << "\n"
             << "Date: " << date << "\n";
    }
};

// Library class
class Library {
public:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

    // Add a book to the library
    void addBook(const Book &book) { books.push_back(book); }

    // Add a patron to the library
    void addPatron(const Patron &patron) { patrons.push_back(patron); }

    // Check out a book
    void checkOutBook(const string &isbn, const string &patronName, const string &date) {
        // Find the book
        auto bookIt = find_if(books.begin(), books.end(), [&isbn](const Book &b) { return b.ISBN == isbn; });
        if (bookIt == books.end()) {
            cout << "Error: Book not found in the library.\n";
            return;
        }

        // Check if the book is already checked out
        if (bookIt->checkedOut) {
            cout << "Error: Book '" << bookIt->title << "' is already checked out.\n";
            return;
        }

        // Find the patron
        auto patronIt = find_if(patrons.begin(), patrons.end(), [&patronName](const Patron &p) { return p.name == patronName; });
        if (patronIt == patrons.end()) {
            cout << "Error: Patron not found in the library.\n";
            return;
        }

        // Check if the patron owes fees
        if (patronIt->owesFees()) {
            cout << "Error: Patron owes fees and cannot check out a book.\n";
            return;
        }

        // Check out the book
        bookIt->checkOut();

        // Create a transaction
        transactions.emplace_back(*bookIt, *patronIt, "Check Out", date);
        cout << "Book checked out successfully: " << bookIt->title << "\n";
    }

    // List all patrons who owe fees
    vector<string> getPatronsWhoOweFees() const {
        vector<string> result;
        for (const auto &p : patrons) {
            if (p.owesFees()) {
                result.push_back(p.name);
            }
        }
        return result;
    }
};

// Main function
int main() {
    Library library;

    // Add books to the library
    library.addBook(Book("123", "C++ Basics", "Musime", 2020, Genre::nonfiction));
    library.addBook(Book("456", "Harry Potter", "Banituze", 1997, Genre::fiction));

    // Add patrons to the library
    library.addPatron(Patron("Winebald", "P001"));
    library.addPatron(Patron("Richard", "P002", 10)); // Richard owes fees

    // Check out a book
    library.checkOutBook("123", "Winebald", "2024-11-26");

    // Attempt to check out the same book again
    library.checkOutBook("456", "Richard", "2024-11-26"); // This should show an error message

    // List patrons who owe fees
    auto patronsWithFees = library.getPatronsWhoOweFees();
    cout << "Patrons who owe fees:\n";
    for (const auto &name : patronsWithFees) {
        cout << name << endl;
    }

    return 0;
}
