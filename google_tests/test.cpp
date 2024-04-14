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

    // Check that database size has / hasn’t changed
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
        "Lietotâjvârds pârsniedz atïauto garumu.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageSix) {
    testLogic (
        "",
        "password",
        "Lietotâjvârds pârâk îss.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageSeven) {
    testLogic(
        "has space",
        "password",
        "Lietotâjvârds nedrîkst saturçt atstarpes.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageOne) {
    UsersTableEntry userEntry{ "testUser", "password" };
    database.UsersTable.push_back(userEntry);
    
    testLogic(
        "testUser",
        "password",
        "Lietotâjvârds jau tiek lietots citam profilam.\n"
    );

    database.UsersTable.pop_back();
}

TEST(ErrorMessageTest, ErrorMessageFive) {
    testLogic(
        "username",
        // 129 symbols
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "Parole pârsniedz atïauto garumu.\n"
    );
}

TEST(ErrorMessageTest, ErrorMessageTwo) {
    testLogic(
        "username",
        "four",
        "Parole pârâk îsa (jâbût garâkai par 5 simboliem).\n"
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
        "Parole nedrîkst saturçt atstarpes.\n"
    );
}

TEST(SuccesfulRegistrationTest, CorrectParameters) {
    testLogic (
        "username",
        "password1",
        "username veiksmîgi reìistrçts!\n",
        true
    );
}
