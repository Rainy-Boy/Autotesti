#include "Kods.h"

Database database;

void registerUser(const string& username, const string& password) {
    // Check username size
    if (username.size() == 0) {
        cout << "Lietot�jv�rds p�r�k �ss." << endl;
        return;
    }
    else if (username.size() > 50) {
        cout << "Lietot�jv�rds p�rsniedz at�auto garumu." << endl;
        return;
    }

    // Checks if the username has whitespace
    for (const char& ch : username) {
        if (isspace(ch)) {
            cout << "Lietot�jv�rds nedr�kst satur�t atstarpes." << endl;
            return;
        }
    }

    // Check if username is unique
    for (const UsersTableEntry& user : database.UsersTable) {
        if (username == user.username) {
            cout << "Lietot�jv�rds jau tiek lietots citam profilam." << endl;
            return;
        }
    }

    // Check password size
    if (password.size() < 5) {
        cout << "Parole p�r�k �sa (j�b�t gar�kai par 5 simboliem)." << endl;
        return;
    }
    else if (password.size() > 128) {
        cout << "Parole p�rsniedz at�auto garumu." << endl;
        return;
    }

    // Check that password has at least 1 number
    bool hasNumber = false;
    for (const char& c : password) {
        if (isdigit(c)) {
            hasNumber = true;
            break;
        }
    }

    if (!hasNumber) {
        cout << "Parole nesatur vismaz vienu ciparu." << endl;
        return;
    }

    // Checks if the password has whitespace
    for (const char& ch : password) {
        if (isspace(ch)) {
            cout << "Parole nedr�kst satur�t atstarpes." << endl;
            return;
        }
    }

    // Save data to "database"
    UsersTableEntry userEntry{ username, password };
    database.UsersTable.push_back(userEntry);

    cout << username << " veiksm�gi re�istr�ts!" << endl;
}