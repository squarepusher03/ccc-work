#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <list>
using namespace std;

TEST_CASE("list supports front insertion") {
    list<int> odds{ 11, 22, 33, 44, 55 };
    odds.remove_if([](int x) { return x % 2 == 0; });
    auto odds_iter = odds.begin();
    REQUIRE(*odds_iter == 11);
    ++odds_iter;
    REQUIRE(*odds_iter == 33);
    ++odds_iter;
    REQUIRE(*odds_iter == 55);
    --odds_iter;
    REQUIRE(*odds_iter == 33);
}