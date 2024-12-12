#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <limits> 
using namespace std;

// Genre Enumeration
enum Genre { Fiction, Nonfiction, Periodical, Biography, Children };

// Convert Genre to String
string genre_to_string(Genre genre) {
    switch (genre) {
        case Fiction: return "Fiction";
        case Nonfiction: return "Nonfiction";
        case Periodical: return "Periodical";
        case Biography: return "Biography";
        case Children: return "Children";
        default: return "Unknown";
    }
}

// Book Class
class Book {
private:
    string ISBN;
    string title;
    string author;
    int copyright_date;
    bool checked_out;
    Genre genre;

public:
    Book(string isbn, string t, string a, int date, Genre g)
        : ISBN(isbn), title(t), author(a), copyright_date(date), checked_out(false), genre(g) {}

    string get_ISBN() const { return ISBN; }
    string get_title() const { return title; }
    string get_author() const { return author; }
    int get_copyright_date() const { return copyright_date; }
    bool is_checked_out() const { return checked_out; }
    Genre get_genre() const { return genre; }

    void check_out() { checked_out = true; }
    void check_in() { checked_out = false; }

    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Title: " << book.title << "\n"
           << "Author: " << book.author << "\n"
           << "ISBN: " << book.ISBN << "\n"
           << "Genre: " << genre_to_string(book.genre) << "\n";
        return os;
    }
};

// Patron Class
class Patron {
private:
    string username;
    string card_number;
    int owed_fees;

public:
    Patron(string name, string card, int fees = 0)
        : username(name), card_number(card), owed_fees(fees) {}

    string get_username() const { return username; }
    string get_card_number() const { return card_number; }
    int get_owed_fees() const { return owed_fees; }

    bool owes_fees() const { return owed_fees > 0; }

    void set_fees(int fees) { owed_fees = fees; }
};

// Transaction Class
class Transaction {
private:
    Book book;
    Patron patron;
    string activity; // "Check Out" or "Check In"
    string date;

public:
    Transaction(Book b, Patron p, string act, string d)
        : book(b), patron(p), activity(act), date(d) {}

    void display() const {
        cout << "Transaction Details:\n"
             << "Book: " << book.get_title() << "\n"
             << "Patron: " << patron.get_username() << "\n"
             << "Activity: " << activity << "\n"
             << "Date: " << date << "\n";
    }
};

// Library Class
class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

public:
    void add_book(const Book& book) {
        books.push_back(book);
    }

    void add_patron(const Patron& patron) {
        patrons.push_back(patron);
    }

    void check_out_book(const string& isbn, const string& card_number, const string& date) {
        auto book_it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.get_ISBN() == isbn; });
        if (book_it == books.end()) throw runtime_error("Book not found in library.");
        if (book_it->is_checked_out()) throw runtime_error("Book is already checked out.");

        auto patron_it = find_if(patrons.begin(), patrons.end(), [&](const Patron& p) { return p.get_card_number() == card_number; });
        if (patron_it == patrons.end()) throw runtime_error("Patron not found in library.");
        if (patron_it->owes_fees()) throw runtime_error("Patron owes fees.");

        book_it->check_out();
        transactions.emplace_back(*book_it, *patron_it, "Check Out", date);
    }

    void check_in_book(const string& isbn, const string& card_number, const string& date) {
        auto book_it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.get_ISBN() == isbn; });
        if (book_it == books.end()) throw runtime_error("Book not found in library.");
        if (!book_it->is_checked_out()) throw runtime_error("Book is not currently checked out.");

        auto patron_it = find_if(patrons.begin(), patrons.end(), [&](const Patron& p) { return p.get_card_number() == card_number; });
        if (patron_it == patrons.end()) throw runtime_error("Patron not found in library.");

        book_it->check_in();
        transactions.emplace_back(*book_it, *patron_it, "Check In", date);
    }

    vector<string> patrons_with_fees() const {
        vector<string> names;
        for (const auto& patron : patrons) {
            if (patron.owes_fees()) names.push_back(patron.get_username());
        }
        return names;
    }

    void list_books() const {
        cout << "\nBooks in the Library:\n";
        for (const auto& book : books) {
            cout << book << "\n";
        }
    }
};

int get_valid_int(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer.\n";
        } else {
            return value;
        }
    }
}

string get_valid_string(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (value.empty()) {
            cout << "Invalid input. Please enter a valid string.\n";
        } else {
            return value;
        }
    }
}

void display_menu() {
    cout << "\n Welcome To Library Management System\n Menu:\n";
    cout << "1. Add a Book\n";
    cout << "2. Add a Patron\n";
    cout << "3. Check Out a Book\n";
    cout << "4. Check In a Book\n";
    cout << "5. View Patrons Owing Fees\n";
    cout << "6. List All Books\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

// Main Function
int main() {
    Library library;

    // Initialize sample data
    library.add_book(Book("12345", "The Great Gatsby", "F. Scott Fitzgerald", 1925, Fiction));
    library.add_book(Book("67890", "A Brief History of Time", "Stephen Hawking", 1988, Nonfiction));
    library.add_patron(Patron("Alice", "P001"));
    library.add_patron(Patron("Bob", "P002", 50)); // Patron with fees
    library.add_patron(Patron("Charlie", "P003"));

    int choice;

    do {
        display_menu();
        choice = get_valid_int("");

        switch (choice) {
            case 1: {
                string isbn, title, author;
                int date;
                int genre_choice;

                cout << "Enter ISBN: ";
                cin >> isbn;
                cin.ignore();

                title = get_valid_string("Enter Title: ");
                author = get_valid_string("Enter Author: ");

                date = get_valid_int("Enter Copyright Date: ");
                cout << "Select Genre (0-Fiction, 1-Nonfiction, 2-Periodical, 3-Biography, 4-Children): ";
                genre_choice = get_valid_int("");

                while (genre_choice < 0 || genre_choice > 4) {
                    cout << "Invalid choice. Please select a valid genre.\n";
                    genre_choice = get_valid_int("");
                }

                library.add_book(Book(isbn, title, author, date, static_cast<Genre>(genre_choice)));
                cout << "Book added successfully.\n";
                break;
            }
            case 2: {
                string username, card_number;
                int fees;

                username = get_valid_string("Enter Patron Name: ");
                card_number = get_valid_string("Enter Card Number: ");
                fees = get_valid_int("Enter Fees (0 if none): ");

                library.add_patron(Patron(username, card_number, fees));
                cout << "Patron added successfully.\n";
                break;
            }
            case 3: {
                string isbn, card_number, date;
                cout << "Enter ISBN of the book to check out: ";
                cin >> isbn;
                cin.ignore();

                card_number = get_valid_string("Enter Patron Card Number: ");
                date = get_valid_string("Enter Date (YYYY-MM-DD): ");

                try {
                    library.check_out_book(isbn, card_number, date);
                    cout << "Book checked out successfully.\n";
                } catch (const runtime_error& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                string isbn, card_number, date;
                cout << "Enter ISBN of the book to check in: ";
                cin >> isbn;
                cin.ignore();

                card_number = get_valid_string("Enter Patron Card Number: ");
                date = get_valid_string("Enter Date (YYYY-MM-DD): ");

                try {
                    library.check_in_book(isbn, card_number, date);
                    cout << "Book checked in successfully.\n";
                } catch (const runtime_error& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 5: {
                vector<string> patrons_owing_fees = library.patrons_with_fees();
                if (patrons_owing_fees.empty()) {
                    cout << "No patrons owe fees.\n";
                } else {
                    cout << "Patrons owing fees:\n";
                    for (const auto& name : patrons_owing_fees) {
                        cout << name << "\n";
                    }
                }
                break;
            }
            case 6: {
                library.list_books();
                break;
            }
            case 7: {
                cout << "Exiting program. Goodbye!\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 7);

    return 0;
}

