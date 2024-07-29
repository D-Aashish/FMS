#include <iostream>
#include <string>
#include <fstream>
#include "headers/udata.h"
#include "headers/splitter.h"
#include "headers/merger.h"

using namespace std;

bool handleLoginSignup(UserDetails& user) {
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
                ifstream fin("UserData", ios::in | ios::binary);
                if (!fin) {
                    cerr << "Error opening file for login." << endl;
                    return false;
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
                    return true;  // Login successful
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
                user.input(userName, password);
                ofstream fout("UserData", ios::out | ios::app | ios::binary);
                if (!fout) {
                    cerr << "Error opening file for signup." << endl;
                    return false;
                }
                fout << user.store() << endl;
                fout.close();
                cout << "Signup successful!" << endl;
                return true;  // Signup successful
            }
            default:
                cout << "Invalid choice. Please enter 1 for Login or 2 for Signup." << endl;
                break;
        }
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
            // Get filename and part size for splitting
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
            // Create FileSplitter object with parameters
            FileSplitter splitter(filename, partsSize);  // Pass parameters directly
            splitter.split();
            break;
        }
        case 2: {
            // Get filename and number of parts for merging
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

            // Create FileMerger object with parameters
            FileMerger merger(filename, numParts);  // Pass parameters directly
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
    bool loginSuccessful = handleLoginSignup(user);
    if (loginSuccessful) {
        handleFileOperations(argc, argv);
    }
    return 0;
}
