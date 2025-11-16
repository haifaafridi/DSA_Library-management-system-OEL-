# 📚 Library Management System  
**Experiment 15 – Open Ended Lab Project**

A console-based **Library Management System** implemented in **C++**, designed to manage books, students, and borrowing/returning operations. This project demonstrates OOP, file handling, and basic data structures.

---

## ⭐ Features
- Add new books  
- Search books  
- Display all books  
- Borrow a book  
- Return a book  
- Track availability  
- File-based persistent storage  
- Bubble Sort used to sort books (if relevant)

---

## 🛠 Technologies Used
- C++  
- File Handling (`fstream`)  
- Object-Oriented Programming  
- Arrays / Simple Data Structures  
- Bubble Sort Algorithm  

---

## 📂 Project Structure
LibraryManagement/
│── main.cpp
│── book.txt # Stores book records
│── students.txt # Stores student borrow/return logs
│── README.md

yaml
Copy code

---

## 📘 How the System Works

### ✔ Add a Book
```cpp
Book b;
b.addBook();
✔ Display All Books
cpp
Copy code
b.displayBooks();
(Insert screenshot in your report)

✔ Borrow a Book
cpp
Copy code
b.borrowBook(studentName, bookID);
✔ Return a Book
cpp
Copy code
b.returnBook(studentName, bookID);

🔍 Bubble Sort Usage
Bubble Sort is used to sort books alphabetically by title before displaying.

cpp
Copy code
for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
        if (books[j].title > books[j + 1].title) {
            swap(books[j], books[j + 1]);
        }
    }
}

▶️ How to Run
Using VS Code / Command Line
bash
Copy code
g++ main.cpp -o library
./library




👤 Author
Haifa Khan Afridi, Emman khattak
BESE 30C – Military College of Signals (MCS), NUST
