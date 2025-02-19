#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Book {
    string ISBN;
    string name;
    string author;
    string year;
    bool borrowed;
public:
    Book(string& ISBN, string& name, string& author, string& year) : ISBN(ISBN), name(name), author(author), year(year), borrowed(0) {}
    string getISBN() { return ISBN; }
    string getName() { return name; }
    string getAuthor() { return author; }
    string getYear() { return year; }
    bool isBorrowed() { return borrowed; }
};

class Member {
    string ID;
    string name;
    string phone;
public:
    Member(string& ID, string& name, string& phone) : ID(ID), name(name), phone(phone) {}
    string getID() { return ID; }
    string getName() { return name; }
    string getPhone() { return phone; }
};

class BookManagement {
public:
    void addBook(string& ISBN, string& name, string& author, string& year) {
        ofstream file("Book.txt", ios::app);
        if (file.is_open()) {
            file << ISBN << " " << name << " " << author << " " << year << " " << 0 << endl;
        }
        file.close();
    }

    void displayBooks() {
        ifstream file("Book.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << endl;
            }
        }
        file.close();
    }

    void searchBook(string& nameforsearch) {
        ifstream file("Book.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string ISBN, name, author, year;
                bool borrowed;

                ss >> ISBN >> name >> author >> year >> borrowed;

                if (name == nameforsearch) {
                    cout << ISBN << " " << name << " " << author << " " << year << endl;
                    break;
                }
            }
            file.close();
        }
    }

    void removeBook(string& bookforremove) {
        ifstream file("Book.txt");
        ofstream tempFile("tempBook.txt");
        string line;

        if (file.is_open() && tempFile.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string ISBN, name, author, year;
                bool borrowed;

                ss >> ISBN >> name >> author >> year >> borrowed;

                if (name != bookforremove) {
                    tempFile << ISBN << " " << name << " " << author << " " << year << " " << borrowed << endl;
                }
            }
            file.close();
            tempFile.close();

            remove("Book.txt");
            rename("tempBook.txt", "Book.txt");
        }
        else {
            cout << "Dosya acilamadi!" << endl;
        }
    }
    void returnBook(string& bookname) {
        ifstream otherfile("loan.txt");
        ifstream file("Book.txt");
        ofstream tempFile("tempBook.txt");
        ofstream tempFile2("tempBook2.txt");
        string line;

        if (file.is_open() && tempFile.is_open() && otherfile.is_open() && tempFile2.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string ISBN, name, author, year;
                bool borrowed;

                ss >> ISBN >> name >> author >> year >> borrowed;


                if (name == bookname) {
                    tempFile << ISBN << " " << name << " " << author << " " << year << " " << 0 << endl;


                }
                else
                    tempFile << ISBN << " " << name << " " << author << " " << year << " " << borrowed << endl;

            }
            while (getline(otherfile, line)) {
                stringstream ss(line);
                string ISBN, name, author, year;
                bool borrowed;

                ss >> ISBN >> name >> author >> year >> borrowed;


                if (name != bookname) {
                    tempFile2 << ISBN << " " << name << " " << author << " " << year << " " << borrowed << endl;
                }


            }
            file.close();
            tempFile.close();
            tempFile2.close();
            otherfile.close();
            remove("Book.txt");
            rename("tempBook.txt", "Book.txt");
            remove("loan.txt");
            rename("tempBook2.txt", "loan.txt");

        }
        



    
    }
    void borrowBook(string&bookname) {
        ofstream otherfile("loan.txt",ios::app);
        ifstream file("Book.txt");
        ofstream tempFile("tempBook.txt");
        string line;

        if (file.is_open() && tempFile.is_open() && otherfile.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string ISBN, name, author, year;
                bool borrowed;

                ss >> ISBN >> name >> author >> year >> borrowed;


                if (name == bookname) {
                    tempFile << ISBN << " " << name << " " << author << " " << year << " " << 1 << endl;
                    otherfile << ISBN << " " << name << " " << author << " " << year << " " << 1 << endl;

                }
                else
                    tempFile << ISBN << " " << name << " " << author << " " << year << " " << borrowed << endl;

            }
           
            file.close();
            tempFile.close();
            
            otherfile.close();
            remove("Book.txt");
            rename("tempBook.txt", "Book.txt");
            

        }





    }
};

class MemberManagement {
public:
    void addMember(string& ID, string& name, string& phone) {
        ofstream file("Member.txt", ios::app);
        if (file.is_open()) {
            file << ID << " " << name << " " << phone << endl;
        }
        file.close();
    }

    void displayMembers() {
        ifstream file("Member.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << endl;
            }
        }
        file.close();
    }

    void searchMember(string& nameforsearch) {
        ifstream file("Member.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string ID, name, phone;
                ss >> ID >> name >> phone;

                if (name == nameforsearch) {
                    cout << ID << " " << name << " " << phone << endl;
                    break;
                }
            }
            file.close();
        }
    }

    void removeMember(string& nameforremove) {
        ifstream file("Member.txt");
        ofstream tempFile("tempMember.txt");
        string line;

        if (file.is_open() && tempFile.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string ID, name, phone;
                ss >> ID >> name >> phone;

                if (name != nameforremove) {
                    tempFile << ID << " " << name << " " << phone << endl;
                }
            }
            file.close();
            tempFile.close();

            remove("Member.txt");
            rename("tempMember.txt", "Member.txt");
        }

    }
};
void printMenu() {
    cout << "------------------------------" << endl;
    cout << "WELCOME TO LİBRARY MANAGEMENT" << endl;
    cout << "--------------------------------" << endl;
    cout << "1- Add a book" << endl;
    cout << "2- List books" << endl;
    cout << "3- Search a book" << endl;
    cout << "4- Remove a book" << endl;
    cout << "5- Borrow a book" << endl;
    cout << "6- Return a book" << endl;
    cout << "7- Add member" << endl;
    cout << "8- List members" << endl;
    cout << "9- Search a member" << endl;
    cout << "10- Remove a member" << endl;
    cout << "0 - Exit" << endl;
}

int main() {
    MemberManagement member;
    BookManagement book;
    int option;
    string ISBN, name, author, year, ID, phone;
    do {
        printMenu();
        cout << "Choose the process :";
        cin >> option;
        switch (option) {
        case 1:
            cout << "Enter ISBN :";
            cin >> ISBN;
            cout << "Enter name :";
            cin >> name;
            cout << "Enter author :";
            cin >> author;
            cout << "Enter year :";
            cin >> year;
            book.addBook(ISBN,name,author,year);
            break;
        case 2:
            book.displayBooks();
            break;
        case 3:
            cout << "Enter the name of book you want to search :";
            cin >> name;
            book.searchBook(name);
            break;
        case 4:
            cout << "Enter the name of book you want to remove :";
            cin >> name;
            book.removeBook(name);
            break;
        case 5:
            cout << "Enter the name of book you want to borrow :";
            cin >> name;
            book.borrowBook(name);
            break;
        case 6:
            cout << "Enter the name of book you want to return :";
            cin >> name;
            book.returnBook(name);
            break;
        case 7:
            cout << "Enter ID :";
            cin >> ID;
            cout << "Enter name :";
            cin >> name;
            cout << "Enter phone number :";
            cin >> phone;
            member.addMember(ID, name, phone);
            break;
        case 8:
            member.displayMembers();
            break;
        case 9:
            cout << "Enter the name :";
            cin >> name;
            member.searchMember(name);
            break;
        case 10:
            cout << "Enter the name :";
            cin >> name;
            member.removeMember(name);
            break;
        case 0:
            cout << "You are exiting the program !";
            break;

        }
    } while (option != 0);
    

}
