#include "../headers/udata.h"

#include <iostream>
#include <fstream>
#include <string>  // Include string header

using namespace std;  // Add this to avoid prefixing std::

void UserDetails::input(const string& user,const string& pass) {
    userName = user;
    pwd = pass;
}

string UserDetails::store() const {
    return userName + " " + pwd;
}

bool UserDetails::login(const string& user,const string& pass) const {
    return (userName == user && pwd == pass);
}

bool UserDetails::signup(const string& user, const string& pass) {
    ofstream fout("UserData", ios::out | ios::app | ios::binary);
    if (!fout) {
        cerr << "Error opening file for signup." << endl;
        return false;
    }
    fout << user << " " << pass << endl;
    fout.close();
    return true;
}

bool UserDetails::authenticateUser(const string& user, const string& pass) {
    ifstream fin("UserData", ios::in | ios::binary);
    if (!fin) {
        cerr << "Error opening file for login." << endl;
        return false;
    }
    string storedUserName, storedPassword;
    while (fin >> storedUserName >> storedPassword) {
        if (storedUserName == user && storedPassword == pass) {
            return true;
        }
    }
    return false;
}
// void handleLoginSignup(UserDetails& user) {
//     int op;
//     // UserDetails user;
//     string userName1, password1;

//     cout << "\n-------------------------------------1.Login-------------------------------------\n" << endl;
//     cout << "\n-------------------------------------2.Signup-------------------------------------\n" << endl;

//     do {
//         cout << "\n-------------------------------------Enter your choice----------------------------" << endl;
//         cin >> op;

//         switch (op) {
//             case 1: {
//                 cout << "\n-------------------------------------1.Login-------------------------------------\n" << endl;
//                 cout << "Enter username or email" << endl;
//                 cin >> userName1;
//                 cout << "Enter password" << endl;
//                 cin >> password1;

//                 ifstream fin("UserData", ios::in);  // Use ios::in only
//                 if (!fin) {
//                     cout << "Error opening file" << endl;
//                     break;
//                 }

//                 string check_user, check_userPass;
//                 bool login_status = false;

//                 while (fin >> check_user >> check_userPass) {
//                     if (userName1 == check_user && password1 == check_userPass) {
//                         login_status = true;
//                         break;
//                     }
//                 }
//                 fin.close();

//                 if (login_status) {
//                     cout << "Login successful" << endl;
//                 } else {
//                     cout << "Invalid username or password!" << endl;
//                 }
//                 break;
//             }
//             case 2: {
//                 cout << "\n-------------------------------------2.Signup-------------------------------------\n" << endl;
//                 cout << "Enter username: ";
//                 cin >> userName1;
//                 cout << "Enter password: ";
//                 cin >> password1;
//                 user.input(userName1, password1);

//                 ofstream fout("UserData", ios::out | ios::app);  // Use ios::out | ios::app
//                 if (!fout) {
//                     cout << "Error opening file" << endl;
//                     break;
//                 }
//                 fout << user.store() << endl;
//                 fout.close();
//                 cout << "Signup successful!" << endl;
//                 break;
//             }
//             default: {
//                 cout << "Invalid choice. Please enter 1 for Login or 2 for Signup." << endl;
//                 break;
//             }
//         }
//     } while (op != 0);

// }
// int main1() {
//     UserDetails user;
//     handleLoginSignup(user);
//     return 0;
// }