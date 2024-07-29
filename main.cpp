#include <iostream>
#include <string>
#include "headers/udata.h"
#include "headers/splitter.h"
#include "headers/merger.h"

using namespace std;

void handleLoginSignup(UserDetails& user) {
    int option;
    string userName, password;

    while (true) {
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
                if (user.authenticateUser(userName, password)) {
                    cout << "Login successful!" << endl;
                    return;  // Exit function if login successful
                } else {
                    cout << "Invalid username or password! Please try again." << endl;
                }
                break;
            }
            case 2: {
                cout << "Enter username: ";
                cin >> userName;
                cout << "Enter password: ";
                cin >> password;
                if (user.signup(userName, password)) {
                    cout << "Signup successful!" << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice. Please enter 1 for Login or 2 for Signup." << endl;
                break;
        }
    }
}

void handleFileOperations() {
    int option;
    cout << "-------------------------------------1.Split-------------------------------------\n";
    cout << "-------------------------------------2.Merge-------------------------------------\n";
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1: {
            string filename;
            int partsSize;
            cout << "Enter the filename to split: ";
            cin >> filename;

            if (filename.empty()) {
                cerr << "Error: Filename cannot be empty." << endl;
                return;
            }

            cout << "Enter the size of each part (in bytes): ";
            cin >> partsSize;

            if (partsSize <= 0) {
                cerr << "Error: Part size must be a positive integer." << endl;
                return;
            }
            FileSplitter splitter(filename, partsSize);
            splitter.split();
            break;
        }
        case 2: {
            string filename;
            int numParts;
            cout << "Enter the base filename for merging: ";
            cin >> filename;

            if (filename.empty()) {
                cerr << "Error: Filename cannot be empty." << endl;
                return;
            }

            cout << "Enter the number of parts to merge: ";
            cin >> numParts;

            if (numParts <= 0) {
                cerr << "Error: Number of parts must be a positive integer." << endl;
                return;
            }

            FileMerger merger(filename, numParts);
            merger.merge();
            break;
        }
        default:
            cout << "Invalid choice. Please enter 1 for Split or 2 for Merge." << endl;
            break;
    }
}

int main() {
    UserDetails user;
    handleLoginSignup(user);
    handleFileOperations();
    return 0;
}