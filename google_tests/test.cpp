#include "pch.h"

#include "Kods.h"
#include <sstream>

void testLogic(const string username, const string password, const string expectedOutput, const bool success = false) {
    int initialDatabaseSize = database.UsersTable.size();

    // Redirect cout to a stringstream
    stringstream capturedOutput;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(capturedOutput.rdbuf());

    registerUser(username, password);

    cout.rdbuf(coutBuffer);

    // Check that we got the expected output message
    ASSERT_EQ(capturedOutput.str(), expectedOutput);

    // Check that database size has / hasn�t changed
    int newDatabaseSize = database.UsersTable.size();

    if (!success) {
        ASSERT_EQ(newDatabaseSize, initialDatabaseSize);
    } else {
        ASSERT_EQ(newDatabaseSize, initialDatabaseSize + 1);
    }
}

TEST(ErrorMessageTest, ErrorMessageFour) {
    testLogic (
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "password",
        "Lietot�jv�rds p�rsniedz at�auto garumu.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageSix) {
    testLogic (
        "",
        "password",
        "Lietot�jv�rds p�r�k �ss.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageSeven) {
    testLogic(
        "has space",
        "password",
        "Lietot�jv�rds nedr�kst satur�t atstarpes.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageOne) {
    UsersTableEntry userEntry{ "testUser", "password" };
    database.UsersTable.push_back(userEntry);
    
    testLogic(
        "testUser",
        "password",
        "Lietot�jv�rds jau tiek lietots citam profilam.\n"
    );

    database.UsersTable.pop_back();
}

TEST(ErrorMessageTest, ErrorMessageFive) {
    testLogic(
        "username",
        // 129 symbols
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "Parole p�rsniedz at�auto garumu.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageTwo) {
    testLogic(
        "username",
        "four",
        "Parole p�r�k �sa (j�b�t gar�kai par 5 simboliem).\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageThree) {
    testLogic(
        "username",
        "numberless",
        "Parole nesatur vismaz vienu ciparu.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageEight) {
    testLogic(
        "username",
        "has 2 spaces",
        "Parole nedr�kst satur�t atstarpes.\n"
    );
}

TEST(SuccesfulRegistrationTest, CorrectParameters) {
    testLogic (
        "username",
        "password1",
        "username veiksm�gi re�istr�ts!\n",
        true
    );
}
