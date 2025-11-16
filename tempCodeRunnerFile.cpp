#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

// ==================== BOOK CLASS ====================
class Book
{
public:
    string title;
    string author;
    string isbn;
    bool isAvailable;
    string borrowedByUserID; // Track who borrowed the book

    Book() : title(""), author(""), isbn(""), isAvailable(true), borrowedByUserID("") {}

    Book(string t, string a, string i)
    {
        title = t;
        author = a;
        isbn = i;
        isAvailable = true;
        borrowedByUserID = "";
    }

    void display() const
    {
        cout << left << setw(30) << title
             << setw(20) << author
             << setw(15) << isbn
             << setw(12) << (isAvailable ? "Available" : "Borrowed") << endl;
    }
};

// ==================== USER CLASS ====================
class User
{
public:
    string userID;
    string name;
    string contact;

    User() : userID(""), name(""), contact("") {}

    User(string id, string n, string c)
    {
        userID = id;
        name = n;
        contact = c;
    }

    void display() const
    {
        cout << left << setw(15) << userID
             << setw(25) << name
             << setw(20) << contact << endl;
    }
};

// ==================== TRANSACTION CLASS ====================
class Transaction
{
public:
    string userID;
    string userName;
    string isbn;
    string bookTitle;
    string transactionType; // "BORROW" or "RETURN"
    string timestamp;

    Transaction() : userID(""), userName(""), isbn(""), bookTitle(""),
                    transactionType(""), timestamp("") {}

    Transaction(string uid, string uname, string bisbn, string btitle, string type)
    {
        userID = uid;
        userName = uname;
        isbn = bisbn;
        bookTitle = btitle;
        transactionType = type;
        timestamp = getCurrentTime();
    }

    string getCurrentTime()
    {
        time_t now = time(0);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&now));
        return string(buffer);
    }

    void display() const
    {
        cout << left << setw(12) << userID
             << setw(20) << userName
             << setw(30) << bookTitle
             << setw(10) << transactionType
             << setw(20) << timestamp << endl;
    }
};

// ==================== LIBRARY MANAGEMENT SYSTEM ====================
class LibrarySystem
{
private:
    static const int MAX_BOOKS = 100;
    static const int MAX_USERS = 50;
    static const int MAX_TRANSACTIONS = 200;

    Book books[MAX_BOOKS];
    User users[MAX_USERS];
    Transaction transactions[MAX_TRANSACTIONS];

    int bookCount;
    int userCount;
    int transactionCount;

public:
    LibrarySystem() : bookCount(0), userCount(0), transactionCount(0) {}

    // ========== BOOK MANAGEMENT ==========
    void addBook()
    {
        if (bookCount >= MAX_BOOKS)
        {
            cout << "\n[ERROR] Book storage is full!\n";
            return;
        }

        string title, author, isbn;
        cout << "\n=== Add New Book ===\n";
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter ISBN: ";
        getline(cin, isbn);

        // Check for duplicate ISBN
        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].isbn == isbn)
            {
                cout << "[ERROR] Book with ISBN " << isbn << " already exists!\n";
                return;
            }
        }

        books[bookCount] = Book(title, author, isbn);
        bookCount++;
        cout << "[SUCCESS] Book added successfully!\n";
    }

    void displayAllBooks()
    {
        if (bookCount == 0)
        {
            cout << "\n[INFO] No books in the library.\n";
            return;
        }

        cout << "\n=== Library Books ===\n";
        cout << left << setw(30) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(12) << "Status" << endl;
        cout << string(77, '-') << endl;

        for (int i = 0; i < bookCount; i++)
        {
            books[i].display();
        }
    }

    // ========== USER MANAGEMENT ==========
    void addUser()
    {
        if (userCount >= MAX_USERS)
        {
            cout << "\n[ERROR] User storage is full!\n";
            return;
        }

        string userID, name, contact;
        cout << "\n=== Add New User ===\n";
        cin.ignore();
        cout << "Enter User ID: ";
        getline(cin, userID);

        // Check for duplicate User ID
        for (int i = 0; i < userCount; i++)
        {
            if (users[i].userID == userID)
            {
                cout << "[ERROR] User with ID " << userID << " already exists!\n";
                return;
            }
        }

        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Contact: ";
        getline(cin, contact);

        users[userCount] = User(userID, name, contact);
        userCount++;
        cout << "[SUCCESS] User added successfully!\n";
    }

    void displayAllUsers()
    {
        if (userCount == 0)
        {
            cout << "\n[INFO] No users registered.\n";
            return;
        }

        cout << "\n=== Registered Users ===\n";
        cout << left << setw(15) << "User ID"
             << setw(25) << "Name"
             << setw(20) << "Contact" << endl;
        cout << string(60, '-') << endl;

        for (int i = 0; i < userCount; i++)
        {
            users[i].display();
        }
    }

    // ========== BORROWING AND RETURNING ==========
    void borrowBook()
    {
        string userID, isbn;
        cout << "\n=== Borrow Book ===\n";
        cin.ignore();
        cout << "Enter User ID: ";
        getline(cin, userID);

        // Find user
        int userIndex = -1;
        for (int i = 0; i < userCount; i++)
        {
            if (users[i].userID == userID)
            {
                userIndex = i;
                break;
            }
        }

        if (userIndex == -1)
        {
            cout << "[ERROR] User not found!\n";
            return;
        }

        cout << "Enter Book ISBN: ";
        getline(cin, isbn);

        // Find book
        int bookIndex = -1;
        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].isbn == isbn)
            {
                bookIndex = i;
                break;
            }
        }

        if (bookIndex == -1)
        {
            cout << "[ERROR] Book not found!\n";
            return;
        }

        if (!books[bookIndex].isAvailable)
        {
            cout << "[ERROR] Book is already borrowed by User ID: "
                 << books[bookIndex].borrowedByUserID << "!\n";
            return;
        }

        // Process borrowing
        books[bookIndex].isAvailable = false;
        books[bookIndex].borrowedByUserID = userID; // Track borrower

        if (transactionCount < MAX_TRANSACTIONS)
        {
            transactions[transactionCount] = Transaction(
                users[userIndex].userID,
                users[userIndex].name,
                books[bookIndex].isbn,
                books[bookIndex].title,
                "BORROW");
            transactionCount++;
        }

        cout << "[SUCCESS] Book borrowed successfully by " << users[userIndex].name << "!\n";
    }

    void returnBook()
    {
        string userID, isbn;
        cout << "\n=== Return Book ===\n";
        cin.ignore();
        cout << "Enter User ID: ";
        getline(cin, userID);

        // Find user
        int userIndex = -1;
        for (int i = 0; i < userCount; i++)
        {
            if (users[i].userID == userID)
            {
                userIndex = i;
                break;
            }
        }

        if (userIndex == -1)
        {
            cout << "[ERROR] User not found!\n";
            return;
        }

        cout << "Enter Book ISBN: ";
        getline(cin, isbn);

        // Find book
        int bookIndex = -1;
        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].isbn == isbn)
            {
                bookIndex = i;
                break;
            }
        }

        if (bookIndex == -1)
        {
            cout << "[ERROR] Book not found!\n";
            return;
        }

        if (books[bookIndex].isAvailable)
        {
            cout << "[ERROR] Book is not currently borrowed!\n";
            return;
        }

        // CRITICAL FIX: Verify that the user returning the book is the one who borrowed it
        if (books[bookIndex].borrowedByUserID != userID)
        {
            cout << "[ERROR] This book was borrowed by User ID: "
                 << books[bookIndex].borrowedByUserID
                 << ". Only they can return it!\n";
            return;
        }

        // Process return
        books[bookIndex].isAvailable = true;
        books[bookIndex].borrowedByUserID = ""; // Clear borrower

        if (transactionCount < MAX_TRANSACTIONS)
        {
            transactions[transactionCount] = Transaction(
                users[userIndex].userID,
                users[userIndex].name,
                books[bookIndex].isbn,
                books[bookIndex].title,
                "RETURN");
            transactionCount++;
        }

        cout << "[SUCCESS] Book returned successfully by " << users[userIndex].name << "!\n";
    }

    // ========== TRANSACTION HISTORY ==========
    void displayTransactionHistory()
    {
        if (transactionCount == 0)
        {
            cout << "\n[INFO] No transactions recorded.\n";
            return;
        }

        cout << "\n=== Transaction History ===\n";
        cout << left << setw(12) << "User ID"
             << setw(20) << "User Name"
             << setw(30) << "Book Title"
             << setw(10) << "Type"
             << setw(20) << "Timestamp" << endl;
        cout << string(92, '-') << endl;

        for (int i = 0; i < transactionCount; i++)
        {
            transactions[i].display();
        }
    }

    // ========== SEARCH FUNCTIONS ==========
    void searchBookByTitle()
    {
        string title;
        cout << "\n=== Search Book by Title ===\n";
        cin.ignore();
        cout << "Enter Title (partial match allowed): ";
        getline(cin, title);

        transform(title.begin(), title.end(), title.begin(), ::tolower);

        bool found = false;
        cout << "\n"
             << left << setw(30) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(12) << "Status" << endl;
        cout << string(77, '-') << endl;

        for (int i = 0; i < bookCount; i++)
        {
            string bookTitle = books[i].title;
            transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(), ::tolower);

            if (bookTitle.find(title) != string::npos)
            {
                books[i].display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "[INFO] No books found with that title.\n";
        }
    }

    void searchBookByAuthor()
    {
        string author;
        cout << "\n=== Search Book by Author ===\n";
        cin.ignore();
        cout << "Enter Author (partial match allowed): ";
        getline(cin, author);

        transform(author.begin(), author.end(), author.begin(), ::tolower);

        bool found = false;
        cout << "\n"
             << left << setw(30) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(12) << "Status" << endl;
        cout << string(77, '-') << endl;

        for (int i = 0; i < bookCount; i++)
        {
            string bookAuthor = books[i].author;
            transform(bookAuthor.begin(), bookAuthor.end(), bookAuthor.begin(), ::tolower);

            if (bookAuthor.find(author) != string::npos)
            {
                books[i].display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "[INFO] No books found by that author.\n";
        }
    }

    void searchBookByISBN()
    {
        string isbn;
        cout << "\n=== Search Book by ISBN ===\n";
        cin.ignore();
        cout << "Enter ISBN: ";
        getline(cin, isbn);

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].isbn == isbn)
            {
                cout << "\n[FOUND] Book Details:\n";
                cout << left << setw(30) << "Title"
                     << setw(20) << "Author"
                     << setw(15) << "ISBN"
                     << setw(12) << "Status" << endl;
                cout << string(77, '-') << endl;
                books[i].display();
                return;
            }
        }

        cout << "[INFO] No book found with ISBN: " << isbn << endl;
    }

    void searchUserByID()
    {
        string userID;
        cout << "\n=== Search User by ID ===\n";
        cin.ignore();
        cout << "Enter User ID: ";
        getline(cin, userID);

        for (int i = 0; i < userCount; i++)
        {
            if (users[i].userID == userID)
            {
                cout << "\n[FOUND] User Details:\n";
                cout << left << setw(15) << "User ID"
                     << setw(25) << "Name"
                     << setw(20) << "Contact" << endl;
                cout << string(60, '-') << endl;
                users[i].display();
                return;
            }
        }

        cout << "[INFO] No user found with ID: " << userID << endl;
    }

    void searchUserByName()
    {
        string name;
        cout << "\n=== Search User by Name ===\n";
        cin.ignore();
        cout << "Enter Name (partial match allowed): ";
        getline(cin, name);

        transform(name.begin(), name.end(), name.begin(), ::tolower);

        bool found = false;
        cout << "\n"
             << left << setw(15) << "User ID"
             << setw(25) << "Name"
             << setw(20) << "Contact" << endl;
        cout << string(60, '-') << endl;

        for (int i = 0; i < userCount; i++)
        {
            string userName = users[i].name;
            transform(userName.begin(), userName.end(), userName.begin(), ::tolower);

            if (userName.find(name) != string::npos)
            {
                users[i].display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "[INFO] No users found with that name.\n";
        }
    }

    // ========== SORTING FUNCTIONS (Bubble Sort) ==========
    void sortBooksByTitle()
    {
        if (bookCount == 0)
        {
            cout << "\n[INFO] No books to sort.\n";
            return;
        }

        for (int i = 0; i < bookCount - 1; i++)
        {
            for (int j = 0; j < bookCount - i - 1; j++)
            {
                string title1 = books[j].title;
                string title2 = books[j + 1].title;
                transform(title1.begin(), title1.end(), title1.begin(), ::tolower);
                transform(title2.begin(), title2.end(), title2.begin(), ::tolower);

                if (title1 > title2)
                {
                    Book temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }

        cout << "\n[SUCCESS] Books sorted by title!\n";
        displayAllBooks();
    }

    void sortBooksByAuthor()
    {
        if (bookCount == 0)
        {
            cout << "\n[INFO] No books to sort.\n";
            return;
        }

        for (int i = 0; i < bookCount - 1; i++)
        {
            for (int j = 0; j < bookCount - i - 1; j++)
            {
                string author1 = books[j].author;
                string author2 = books[j + 1].author;
                transform(author1.begin(), author1.end(), author1.begin(), ::tolower);
                transform(author2.begin(), author2.end(), author2.begin(), ::tolower);

                if (author1 > author2)
                {
                    Book temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }

        cout << "\n[SUCCESS] Books sorted by author!\n";
        displayAllBooks();
    }

    // ========== FILE HANDLING ==========
    void saveToFile()
    {
        // Save Books
        ofstream bookFile("books.txt");
        if (bookFile.is_open())
        {
            bookFile << bookCount << endl;
            for (int i = 0; i < bookCount; i++)
            {
                bookFile << books[i].title << "|"
                         << books[i].author << "|"
                         << books[i].isbn << "|"
                         << books[i].isAvailable << "|"
                         << books[i].borrowedByUserID << endl;
            }
            bookFile.close();
        }

        // Save Users
        ofstream userFile("users.txt");
        if (userFile.is_open())
        {
            userFile << userCount << endl;
            for (int i = 0; i < userCount; i++)
            {
                userFile << users[i].userID << "|"
                         << users[i].name << "|"
                         << users[i].contact << endl;
            }
            userFile.close();
        }

        // Save Transactions
        ofstream transFile("transactions.txt");
        if (transFile.is_open())
        {
            transFile << transactionCount << endl;
            for (int i = 0; i < transactionCount; i++)
            {
                transFile << transactions[i].userID << "|"
                          << transactions[i].userName << "|"
                          << transactions[i].isbn << "|"
                          << transactions[i].bookTitle << "|"
                          << transactions[i].transactionType << "|"
                          << transactions[i].timestamp << endl;
            }
            transFile.close();
        }

        cout << "\n[SUCCESS] All data saved to files!\n";
    }

    void loadFromFile()
    {
        // Load Books
        ifstream bookFile("books.txt");
        if (bookFile.is_open())
        {
            bookFile >> bookCount;
            bookFile.ignore();
            for (int i = 0; i < bookCount; i++)
            {
                string line;
                getline(bookFile, line);

                size_t pos1 = line.find('|');
                size_t pos2 = line.find('|', pos1 + 1);
                size_t pos3 = line.find('|', pos2 + 1);
                size_t pos4 = line.find('|', pos3 + 1);

                books[i].title = line.substr(0, pos1);
                books[i].author = line.substr(pos1 + 1, pos2 - pos1 - 1);
                books[i].isbn = line.substr(pos2 + 1, pos3 - pos2 - 1);
                books[i].isAvailable = (line.substr(pos3 + 1, pos4 - pos3 - 1) == "1");
                books[i].borrowedByUserID = line.substr(pos4 + 1);
            }
            bookFile.close();
        }

        // Load Users
        ifstream userFile("users.txt");
        if (userFile.is_open())
        {
            userFile >> userCount;
            userFile.ignore();
            for (int i = 0; i < userCount; i++)
            {
                string line;
                getline(userFile, line);

                size_t pos1 = line.find('|');
                size_t pos2 = line.find('|', pos1 + 1);

                users[i].userID = line.substr(0, pos1);
                users[i].name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                users[i].contact = line.substr(pos2 + 1);
            }
            userFile.close();
        }

        // Load Transactions
        ifstream transFile("transactions.txt");
        if (transFile.is_open())
        {
            transFile >> transactionCount;
            transFile.ignore();
            for (int i = 0; i < transactionCount; i++)
            {
                string line;
                getline(transFile, line);

                size_t pos1 = line.find('|');
                size_t pos2 = line.find('|', pos1 + 1);
                size_t pos3 = line.find('|', pos2 + 1);
                size_t pos4 = line.find('|', pos3 + 1);
                size_t pos5 = line.find('|', pos4 + 1);

                transactions[i].userID = line.substr(0, pos1);
                transactions[i].userName = line.substr(pos1 + 1, pos2 - pos1 - 1);
                transactions[i].isbn = line.substr(pos2 + 1, pos3 - pos2 - 1);
                transactions[i].bookTitle = line.substr(pos3 + 1, pos4 - pos3 - 1);
                transactions[i].transactionType = line.substr(pos4 + 1, pos5 - pos4 - 1);
                transactions[i].timestamp = line.substr(pos5 + 1);
            }
            transFile.close();
        }

        cout << "\n[SUCCESS] Data loaded from files!\n";
    }

    // ========== DEMO DATA ==========
    void loadSampleData()
    {
        // Sample Books
        books[0] = Book("The Great Gatsby", "F. Scott Fitzgerald", "ISBN001");
        books[1] = Book("To Kill a Mockingbird", "Harper Lee", "ISBN002");
        books[2] = Book("1984", "George Orwell", "ISBN003");
        books[3] = Book("Pride and Prejudice", "Jane Austen", "ISBN004");
        books[4] = Book("The Catcher in the Rye", "J.D. Salinger", "ISBN005");
        bookCount = 5;

        // Sample Users
        users[0] = User("U001", "John Smith", "john@email.com");
        users[1] = User("U002", "Emma Johnson", "emma@email.com");
        users[2] = User("U003", "Michael Brown", "michael@email.com");
        userCount = 3;

        cout << "\n[SUCCESS] Sample data loaded!\n";
        cout << "Books: " << bookCount << " | Users: " << userCount << endl;
    }
};

// ==================== MAIN MENU ====================
void displayMenu()
{
    cout << "\n";
    cout << "\n";
    cout << "    LIBRARY MANAGEMENT SYSTEM - MENU        \n";
    cout << "\n";
    cout << "  BOOK MANAGEMENT                           \n";
    cout << "    1. Add Book                             \n";
    cout << "    2. Display All Books                    \n";
    cout << "    3. Sort Books by Title                  \n";
    cout << "    4. Sort Books by Author                 \n";
    cout << "\n";
    cout << "  USER MANAGEMENT                           \n";
    cout << "    5. Add User                             \n";
    cout << "    6. Display All Users                    \n";
    cout << "\n";
    cout << "  TRANSACTIONS                              \n";
    cout << "    7. Borrow Book                          \n";
    cout << "    8. Return Book                          \n";
    cout << "    9. Display Transaction History          \n";
    cout << "\n";
    cout << "  SEARCH FUNCTIONS                          \n";
    cout << "   10. Search Book by Title                 \n";
    cout << "   11. Search Book by Author                \n";
    cout << "   12. Search Book by ISBN                  \n";
    cout << "   13. Search User by ID                    \n";
    cout << "   14. Search User by Name                  \n";
    cout << "\n";
    cout << "  FILE OPERATIONS                           \n";
    cout << "   15. Save Data to File                    \n";
    cout << "   16. Load Data from File                  \n";
    cout << "   17. Load Sample Data                     \n";
    cout << "\n";
    cout << "    0. Exit Program                         \n";
    cout << "\n";
    cout << "Enter your choice: ";
}

// ==================== MAIN FUNCTION ====================
int main()
{
    LibrarySystem library;
    int choice;

    cout << "\n";
    cout << "  WELCOME TO LIBRARY MANAGEMENT SYSTEM      \n";
    cout << "\n";

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.displayAllBooks();
            break;
        case 3:
            library.sortBooksByTitle();
            break;
        case 4:
            library.sortBooksByAuthor();
            break;
        case 5:
            library.addUser();
            break;
        case 6:
            library.displayAllUsers();
            break;
        case 7:
            library.borrowBook();
            break;
        case 8:
            library.returnBook();
            break;
        case 9:
            library.displayTransactionHistory();
            break;
        case 10:
            library.searchBookByTitle();
            break;
        case 11:
            library.searchBookByAuthor();
            break;
        case 12:
            library.searchBookByISBN();
            break;
        case 13:
            library.searchUserByID();
            break;
        case 14:
            library.searchUserByName();
            break;
        case 15:
            library.saveToFile();
            break;
        case 16:
            library.loadFromFile();
            break;
        case 17:
            library.loadSampleData();
            break;
        case 0:
            cout << "\nExiting Library Management System. Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

        if (choice != 0)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}