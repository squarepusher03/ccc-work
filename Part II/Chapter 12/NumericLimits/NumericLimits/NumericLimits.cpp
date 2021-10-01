#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <limits>
#include <boost/numeric/conversion/cast.hpp>
#include <ratio>
using namespace std;

TEST_CASE("numeric_limits::min provides the smallest finite value") {
    constexpr auto my_cup = numeric_limits<int>::min();
    constexpr auto underfloweth = my_cup - 1;
    REQUIRE(my_cup < underfloweth); // works, but is also a software vulnerability, DO NOT USE
}

TEST_CASE("boost::numeric_cast checks overflow") {
    constexpr auto yuge = numeric_limits<double>::max();
    REQUIRE_THROWS_AS(boost::numeric_cast<int>(yuge), boost::numeric::positive_overflow);
    // numeric cast is also a good replacement for narrow_cast
}

// ------------- I'm not making an entire new project for one test case -------------
// ------------- Ratio -------------

TEST_CASE("std::ratio") {
    using ten = ratio<10, 1>;
    using two_thirds = ratio<2, 3>;
    using result = ratio_multiply<ten, two_thirds>;
    REQUIRE(result::num == 20);
    REQUIRE(result::den == 3);
}