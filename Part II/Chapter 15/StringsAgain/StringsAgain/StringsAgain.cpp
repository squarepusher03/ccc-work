#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string>
using namespace std::literals::string_literals;

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

    SECTION("append char") {
        word.append(1, 's');
        REQUIRE(word == "butts");
    }

    SECTION("append (half-open range)") {
        std::string other("onomatopoeia");
        word.append(other.begin(), other.begin() + 2);
        REQUIRE(word == "button");
    }
}

TEST_CASE("std::string supports removal with") {
    std::string word("therein");

    SECTION("pop_back") {
        word.pop_back();
        word.pop_back();
        REQUIRE(word == "there");
    }

    SECTION("clear") {
        word.clear();
        REQUIRE(word.empty());
    }

    SECTION("erase using half-open range") {
        word.erase(word.begin(), word.begin() + 3);
        REQUIRE(word == "rein");
    }

    SECTION("erase using an index and length") {
        word.erase(5, 2);
        REQUIRE(word == "there");
    }
}

TEST_CASE("std::string replace works with") {
    std::string word("substitution");

    SECTION("a range and a char*") {
        word.replace(word.begin() + 9, word.end(), "e");
        REQUIRE(word == "substitute");
    }

    SECTION("two ranges") {
        std::string other("innuendo");
        word.replace(word.begin(), word.begin() + 3, other.begin(), other.begin() + 2);
        REQUIRE(word == "institution");
    }

    SECTION("an index/length and a string") {
        std::string other("vers");
        word.replace(3, 6, other);
        REQUIRE(word == "subversion");
    }
}

TEST_CASE("std::string resize") {
    std::string word("shamp");

    SECTION("can remove elements") {
        word.resize(4);
        REQUIRE(word == "sham");
    }

    SECTION("can add elements") {
        word.resize(7, 'o');
        REQUIRE(word == "shampoo");
    }
}

TEST_CASE("std::string subtr with") {
    std::string word("hobbits");

    SECTION("no arguments copies the string") {
        REQUIRE(word.substr() == "hobbits");
    }

    SECTION("position takes the remainder") {
        REQUIRE(word.substr(3) == "bits");
    }

    SECTION("position/index takes a substring") {
        REQUIRE(word.substr(3, 3) == "bit");
    }
}

TEST_CASE("std::string find") {
    std::string word("pizzazz");

    SECTION("locates substrings from strings") {
        REQUIRE(word.find("zz"s) == 2); // pi(z)zazz word[2]
    }

    SECTION("accepts a position argument") {
        REQUIRE(word.find("zz"s, 3) == 5); // pizza(z)z word[5]
    }

    SECTION("locates substrings from char*") {
        REQUIRE(word.find("zaz") == 3); // piz(z)azz // word[3]
    }

    SECTION("returns npos when not found") {
        REQUIRE(word.find('x') == std::string::npos);
    }
}

TEST_CASE("std::string rfind") {
    // just reverse .find()
    std::string word("pizzazz");

    SECTION("locates substrings from strings") {
        REQUIRE(word.rfind("zz"s) == 5); // pizza(z)z word[5]
    }

    SECTION("accepts a position argument") {
        REQUIRE(word.rfind("zz"s, 3) == 2); // pi(z)zazz word[2]
    }

    SECTION("locates substrings from char*") {
        REQUIRE(word.rfind("zaz") == 3); // piz(z)azz word[3]
    }

    SECTION("returns npos when not found") {
        REQUIRE(word.rfind('x') == std::string::npos);
    }
}

TEST_CASE("std::string find_*_of") {
    std::string sentence("I am a Zizzer-Zazzer-Zuzz as you can plainly see.");

    SECTION("locates characters within another string") {
        REQUIRE(sentence.find_first_of("Zz"s) == 7); // (Z)izzer
    }

    SECTION("accepts a position argument") {
        REQUIRE(sentence.find_first_of("Zz"s, 11) == 14); // (Z)azzer
    }

    SECTION("returns npos when not found") {
        REQUIRE(sentence.find_first_of("Xx"s) == std::string::npos);
    }

    SECTION("find_last_of finds last element within another string") {
        REQUIRE(sentence.find_last_of("Zz"s) == 24); // Zuz(z)
    }

    SECTION("find_first_not_of finds first element not within another string") {
        REQUIRE(sentence.find_first_not_of(" -IZaeimrz"s) == 22); // Z(u)zz
    }

    SECTION("find_last_not_of finds last element not within another string") {
        REQUIRE(sentence.find_last_not_of(" .es"s) == 43); // plainl(y)
    }
}

TEST_CASE("STL string conversion function") {
    SECTION("to_string") {
        REQUIRE("8975309"s == std::to_string(8975309));
    }

    SECTION("to_wstring") {
        // fails on some systems due to double type precision inaccuracies
        REQUIRE(L"109951.1627776"s == std::to_wstring(109951.1627776)); 
    }

    SECTION("stoi") {
        REQUIRE(std::stoi("8675309"s) == 8675309);
    }

    SECTION("stoul with all valid characters") {

    }
}