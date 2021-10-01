#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <random>
using namespace std;

TEST_CASE("mt19937_64 is pseudorandom") {
    mt19937_64 mt_engine{ 91586 };
    REQUIRE(mt_engine() == 8346843996631475880);
    REQUIRE(mt_engine() == 2237671392849523263);
    REQUIRE(mt_engine() == 7333164488732543658);
}

TEST_CASE("random_device is invocable") {
    random_device rd_engine{};
    REQUIRE_NOTHROW(rd_engine());
}