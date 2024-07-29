#include <iostream>
#include <string>
#include <fstream>
#include "headers/udata.h"  // Ensure you have the correct path
#include "headers/splitter.h"
#include "headers/merger.h"

using namespace std;

void handleLoginSignup(UserDetails& user) {
    int option;
    string userName, password;

    cout << "-------------------------------------1.Login-------------------------------------\n";
    cout << "-------------------------------------2.Signup-------------------------------------\n";

    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1: {
            cout << "Enter username: ";
            cin >> userName;
            cout << "Enter password: ";
            cin >> password;
            ifstream fin("UserData", ios::in | ios::binary);
            if (!fin) {
                cerr << "Error opening file for login." << endl;
                return;
            }
            string storedUserName, storedPassword;
            bool loginSuccessful = false;
            while (fin >> storedUserName >> storedPassword) {
                if (storedUserName == userName && storedPassword == password) {
                    loginSuccessful = true;
                    break;
                }
            }
            fin.close();
            if (loginSuccessful) {
                cout << "Login successful!" << endl;
            } else {
                cout << "Invalid username or password!" << endl;
            }
            break;
        }
        case 2: {
            cout << "Enter username: ";
            cin >> userName;
            cout << "Enter password: ";
            cin >> password;
            user.input(userName, password);
            ofstream fout("UserData", ios::out | ios::app | ios::binary);
            if (!fout) {
                cerr << "Error opening file for signup." << endl;
                return;
            }
            fout << user.store() << endl;
            fout.close();
            cout << "Signup successful!" << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please enter 1 for Login or 2 for Signup." << endl;
            break;
    }
}

void handleFileOperations(int argc, char** argv) {
    int option;
    cout << "-------------------------------------1.Split-------------------------------------\n";
    cout << "-------------------------------------2.Merge-------------------------------------\n";
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1: {
            // Initialize FileSplitter with argc and argv
            FileSplitter splitter(argc, argv);
            splitter.split();
            break;
        }
        case 2: {
            // Initialize FileMerger with argc and argv
            FileMerger merger(argc, argv);
            merger.merge();
            break;
        }
        default:
            cout << "Invalid choice. Please enter 1 for Split or 2 for Merge." << endl;
            break;
    }
}

int main(int argc, char** argv) {
    UserDetails user;
    handleLoginSignup(user);
    handleFileOperations(argc, argv);
    return 0;
}
