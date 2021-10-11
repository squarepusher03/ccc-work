#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string>

TEST_CASE("std::string supports constructing") {
    SECTION("empty strings") {
        std::string cheese;
        REQUIRE(cheese.empty());
    }

    SECTION("repeated characters") {
        std::string roadside_assistance(3, 'A');
        REQUIRE(roadside_assistance == "AAA");
    }
}

TEST_CASE("std::string supports substrings") {
    auto word = "gobbledygook";
    REQUIRE(std::string(word) == "gobbledygook");
    REQUIRE(std::string(word, 6) == "gobble");
}

TEST_CASE("std::string supports") {
    std::string word{ "catawampus" };

    SECTION("copy constructing") {
        REQUIRE(std::string(word) == "catawampus");
    }

    SECTION("move constructing") {
        REQUIRE(std::string(std::move(word)) == "catawampus");
    }

    SECTION("constructing from substrings") {
        REQUIRE(std::string(word, 0, 3) == "cat");
        REQUIRE(std::string(word, 4) == "wampus");
    }
}

TEST_CASE("std::string supports comparison with") {
    using namespace std::literals::string_literals;
    std::string word("allusion");

    SECTION("operator== and !=") {
        REQUIRE(word == "allusion");
        REQUIRE(word == "allusion"s);
        REQUIRE(word != "Allusion"s);
        REQUIRE(word != "illusion"s);
        REQUIRE_FALSE(word == "illusion"s);
    }

    SECTION("operator<") {
        REQUIRE(word < "illusion");
        REQUIRE(word < "illusion"s);
        REQUIRE(word > "Illusion"s); // A < Z < a < z
    }
}

TEST_CASE("std::string supports appending with") {
    std::string word("butt");

    SECTION("push_back") {
        word.push_back('e');
        REQUIRE(word == "butte");
    }

    SECTION("operator+=") {
        word += "erfinger";
        REQUIRE(word == "butterfinger");
    }
}