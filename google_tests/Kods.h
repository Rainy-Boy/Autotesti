#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

struct UsersTableEntry {
    string username;
    string password;
};

struct Database {
    vector<UsersTableEntry> UsersTable;
};

extern struct Database database;

void registerUser(const string& username, const string& password);

