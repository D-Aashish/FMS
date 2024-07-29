#ifndef UDATA_H
#define UDATA_H

#pragma once

#include <string>

using namespace std;

class UserDetails {
private:
    string userName;
    string pwd;

public:
    void input(const string& user,const string& pass);
    string store() const;
    bool login(const string& user,const string& pass) const;
};

#endif // UDATA_H
