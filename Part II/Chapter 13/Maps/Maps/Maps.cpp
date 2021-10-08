#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <array>
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

TEST_CASE("map is an associative array with") {
    map<const char*, int> pub_year{
        { color_of_magic, 1983 },
        { the_light_fantastic, 1986 }
    };

    SECTION("operator[]") {
        REQUIRE(pub_year[color_of_magic] == 1983);

        pub_year[equal_rites] = 1987;
        REQUIRE(pub_year[equal_rites] == 1987);

        REQUIRE(pub_year[mort] == 0);
    }

    SECTION("an at method") {
        REQUIRE(pub_year.at(color_of_magic) == 1983);

        REQUIRE_THROWS_AS(pub_year.at(equal_rites), out_of_range);
    }
}

TEST_CASE("map supports insert") {
    map<const char*, int> pub_year;
    pub_year.insert({ color_of_magic, 1983 });
    REQUIRE(pub_year.size() == 1);

    pair<const char*, int> tlfp{ the_light_fantastic, 1986 };
    pub_year.insert(tlfp);
    REQUIRE(pub_year.size() == 2);

    auto [iter, is_new] = pub_year.insert({ the_light_fantastic, 9999 });
    REQUIRE(iter->first == the_light_fantastic);
    REQUIRE(iter->second == 1986);
    REQUIRE_FALSE(is_new);
    REQUIRE(pub_year.size() == 2);
}

TEST_CASE("map supports insert_or_assign") {
    map<const char*, int> pub_year{
        { the_light_fantastic, 9999 }
    };
    auto [iter, is_new] = pub_year.insert_or_assign(the_light_fantastic, 1986);
    REQUIRE(iter->second == 1986);
    REQUIRE_FALSE(is_new);
}

TEST_CASE("we can remove map elements using") {
    map<const char*, int> pub_year{
        { color_of_magic, 1983 },
        { mort, 1987 }
    };

    SECTION("erase") {
        pub_year.erase(mort);
        REQUIRE(pub_year.find(mort) == pub_year.end());
    }

    SECTION("clear") {
        pub_year.clear();
        REQUIRE(pub_year.empty());
    }
}

TEST_CASE("multimap supports non-unique keys") {
    array<char, 64> far_out{
        "Far out in the uncharted backwaters of the unfashionable end..."
    };

    multimap<char, size_t> indices;
    for (size_t index{}; index < far_out.size(); index++) {
        indices.emplace(far_out[index], index);
    }

    REQUIRE(indices.count('a') == 6);

    auto [iter, end] = indices.equal_range('d');
    REQUIRE(iter->second == 23);
    iter++;
    REQUIRE(iter->second == 59);
    iter++;
    REQUIRE(iter == end);
}