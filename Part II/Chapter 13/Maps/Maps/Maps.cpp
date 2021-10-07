#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <map>
using namespace std;

auto color_of_magic = "Color of Magic";
auto the_light_fantastic = "The Light Fantastic";
auto equal_rites = "Equal Rites";
auto mort = "Mort";

TEST_CASE("map supports") {
    SECTION("default construction") {
        map<const char*, int> emp;
        REQUIRE(emp.empty());
    }

    SECTION("braced intialization") {
        map<const char*, int> pub_year{
            { color_of_magic, 1983 },
            { the_light_fantastic, 1986 },
            { equal_rites, 1987 },
            { mort, 1987 }
        };
        REQUIRE(pub_year.size() == 4);
    }
}