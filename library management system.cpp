#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string isbn;
    string author;
    string publisher;
    int copies = 0;
    int edition = 0;
};

// Function Prototypes
void addBook(Book*& books, int& size);
void deleteBook(Book*& books, int& size);
void modifyBook(Book books[], int size);
void searchBookByISBN(Book books[], int size);
void searchBookByTitle(Book books[], int size);
void sortByTitle(Book books[], int size);
void sortByEdition(Book books[], int size);
void borrowBook(Book books[], int size);
void returnBook(Book books[], int size);
void displayBooks(Book books[], int size);

int main() {
    int size = 0;
    Book* books = new Book[size]; // dynamic array

    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add New Book\n";
        cout << "2. Delete Book\n";
        cout << "3. Modify Book\n";
        cout << "4. Search by ISBN\n";
        cout << "5. Search by Title\n";
        cout << "6. Sort by Title\n";
        cout << "7. Sort by Edition (Same Title)\n";
        cout << "8. View All Books\n";
        cout << "9. Borrow Book\n";
        cout << "10. Return Book\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(books, size); break;
        case 2: deleteBook(books, size); break;
        case 3: modifyBook(books, size); break;
        case 4: searchBookByISBN(books, size); break;
        case 5: searchBookByTitle(books, size); break;
        case 6: sortByTitle(books, size); break;
        case 7: sortByEdition(books, size); break;
        case 8: displayBooks(books, size); break;
        case 9: borrowBook(books, size); break;
        case 10: returnBook(books, size); break;
        case 0: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    delete[] books;
    return 0;
}

// =============== ADD BOOK FUNCTION =====================
void addBook(Book*& books, int& size) {
    Book* temp = new Book[size + 1];

    for (int i = 0; i < size; i++)
        temp[i] = books[i];

    cout << "\nEnter Book Title: ";
    cin.ignore();
    getline(cin, temp[size].title);

    cout << "Enter ISBN: ";
    getline(cin, temp[size].isbn);

    cout << "Enter Author: ";
    getline(cin, temp[size].author);

    cout << "Enter Publisher: ";
    getline(cin, temp[size].publisher);

    cout << "Enter Number of Copies: ";
    cin >> temp[size].copies;

    cout << "Enter Edition: ";
    cin >> temp[size].edition;

    delete[] books;
    books = temp;
    size++;

    cout << "Book Added Successfully!\n";
}

// =============== DELETE BOOK FUNCTION =====================
void deleteBook(Book*& books, int& size) {
    if (size == 0) {
        cout << "No books to delete!\n";
        return;
    }

    string isbn;
    cin.ignore();
    cout << "Enter ISBN to delete: ";
    getline(cin, isbn);

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (books[i].isbn == isbn) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }

    Book* temp = new Book[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            temp[j++] = books[i];
        }
    }

    delete[] books;
    books = temp;
    size--;

    cout << "Book Deleted Successfully!\n";
}

// =============== MODIFY BOOK FUNCTION =====================
void modifyBook(Book books[], int size) {
    if (size == 0) {
        cout << "No books available!\n";
        return;
    }

    string isbn;
    cin.ignore();
    cout << "Enter ISBN of book to modify: ";
    getline(cin, isbn);

    for (int i = 0; i < size; i++) {
        if (books[i].isbn == isbn) {
            cout << "Enter New Title: ";
            getline(cin, books[i].title);

            cout << "Enter New Author: ";
            getline(cin, books[i].author);

            cout << "Enter New Publisher: ";
            getline(cin, books[i].publisher);

            cout << "Enter New Copies: ";
            cin >> books[i].copies;

            cout << "Enter New Edition: ";
            cin >> books[i].edition;

            cout << "Book Updated!\n";
            return;
        }
    }

    cout << "Book not found!\n";
}

// =============== SEARCH BY ISBN =====================
void searchBookByISBN(Book books[], int size) {
    string isbn;
    cin.ignore();
    cout << "Enter ISBN: ";
    getline(cin, isbn);

    for (int i = 0; i < size; i++) {
        if (books[i].isbn == isbn) {
            cout << "\nBook Found:\n";
            cout << books[i].title << " | " << books[i].author
                << " | Copies: " << books[i].copies << "\n";
            return;
        }
    }
    cout << "No book found with that ISBN.\n";
}

// =============== SEARCH BY TITLE =====================
void searchBookByTitle(Book books[], int size) {
    string title;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, title);

    for (int i = 0; i < size; i++) {
        if (books[i].title == title) {
            cout << "\nBook Found:\n";
            cout << books[i].title << " | " << books[i].author
                << " | Copies: " << books[i].copies << "\n";
            return;
        }
    }
    cout << "No book found with that title.\n";
}

// =============== SORT BY TITLE =====================
void sortByTitle(Book books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (books[j].title < books[i].title) {
                swap(books[i], books[j]);
            }
        }
    }
    cout << "Books sorted by title!\n";
}

// =============== SORT BY EDITION =====================
void sortByEdition(Book books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (books[i].title == books[j].title && books[j].edition < books[i].edition) {
                swap(books[i], books[j]);
            }
        }
    }
    cout << "Books sorted by edition (same title only)!\n";
}

// =============== BORROW BOOK =====================
void borrowBook(Book books[], int size) {
    string isbn;
    cin.ignore();
    cout << "Enter ISBN to borrow: ";
    getline(cin, isbn);

    for (int i = 0; i < size; i++) {
        if (books[i].isbn == isbn) {
            if (books[i].copies > 0) {
                books[i].copies--;
                cout << "Book Borrowed Successfully!\n";
            }
            else {
                cout << "No copies available!\n";
            }
            return;
        }
    }
    cout << "Book not found!\n";
}

// =============== RETURN BOOK =====================
void returnBook(Book books[], int size) {
    string isbn;
    cin.ignore();
    cout << "Enter ISBN to return: ";
    getline(cin, isbn);

    for (int i = 0; i < size; i++) {
        if (books[i].isbn == isbn) {
            books[i].copies++;
            cout << "Book Returned Successfully!\n";
            return;
        }
    }
    cout << "Book not found!\n";
}

// =============== DISPLAY ALL BOOKS =====================
void displayBooks(Book books[], int size) {
    if (size == 0) {
        cout << "No books to display!\n";
        return;
    }

    cout << "\n==== ALL BOOKS ====\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << books[i].title << " | ISBN: " << books[i].isbn
            << " | Copies: " << books[i].copies
            << " | Edition: " << books[i].edition << endl;
    }
}