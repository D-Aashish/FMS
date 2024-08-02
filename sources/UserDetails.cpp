#include "../headers/udata.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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
