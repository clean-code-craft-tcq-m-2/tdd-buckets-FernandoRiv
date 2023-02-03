#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargeRate.h"
#include <string.h>

TEST_CASE("Characters to int test conversion"){
    sessionValues.clear();
    SECTION("Addition of digit character input"){
        char digit[] = "12";
        REQUIRE(addParsedSession(digit) == true);
    }
    SECTION("Attempt of non digit character input"){
        char nonDigit[] = "HI";
        REQUIRE(addParsedSession(nonDigit) == false);
    }
    SECTION("Attempt of non digit special characters"){
        char nonDigitSpecialChars[] = "/0";
        REQUIRE(addParsedSession(nonDigitSpecialChars) == false);
    }
    SECTION("Attempt of nullptr at character input"){
        REQUIRE(addParsedSession(nullptr) == false);
    }
    SECTION("Attempt of digit + non digit at character input"){
        char digitNonDigit[] = "12CD1";
        REQUIRE(addParsedSession(digitNonDigit) == false);
    }
}

TEST_CASE("Parsing array of charging sessions"){
    sessionValues.clear();
    SECTION("Smallest set of valid digit sequences"){
        char sessions[] = "4, 5";
        std::list<long> parsedSessions = parseChargeSessions(sessions);
        REQUIRE(parsedSessions.size() == 2);
    }
    SECTION("Digit sequence with non digit"){
        char sessions[] = "4, 5, n, 123";
        std::list<long> parsedSessions = parseChargeSessions(sessions);
        REQUIRE(parsedSessions.size() == 3);
    }
}

TEST_CASE("Range calculation"){
    sessionValues.clear();
    chargeRanges.clear();
    SECTION("Different set of valid digit sequences + isolated sessions"){
        char sessions[] = "12, 4, 5, 9, 20, 6, 4, 4, 13, 14";
        char toStringArray[200];
        std::list<long> parsedSessions = parseChargeSessions(sessions);
        std::list<chargeRange> ranges = calculateRanges();
        REQUIRE(ranges.size() == 2);
        // 1st range evaluation
        std::list<chargeRange>::iterator it = ranges.begin();
        REQUIRE(it->lowValue  == 12);
        REQUIRE(it->highValue == 14);
        REQUIRE(it->readings  == 3);
        REQUIRE(it->getRangeString(toStringArray, sizeof(toStringArray)));
        REQUIRE(strcmp(toStringArray, "12-14, 3\n") == 0);
        it++;
        // 2nd range evaluation
        REQUIRE(it->lowValue  == 4);
        REQUIRE(it->highValue == 6);
        REQUIRE(it->readings  == 5);
        REQUIRE(it->getRangeString(toStringArray, sizeof(toStringArray)));
        REQUIRE(strcmp(toStringArray, "4-6, 5\n") == 0);
        it++;
        REQUIRE(it == ranges.end());
    }
}