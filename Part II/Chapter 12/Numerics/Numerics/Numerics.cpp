#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <complex>
#include <cmath>
#include <boost/math/constants/constants.hpp>
using namespace std;

TEST_CASE("complex has a real and imaginary component") {
    complex<double> a{ 0.5, 14.13 };
    REQUIRE(real(a) == Approx(.5));
    REQUIRE(imag(a) == Approx(14.13));
}

TEST_CASE("boost::math offers constants") {
    using namespace boost::math::double_constants;
    // calculates volume of sphere with radius of 10 units
    auto sphere_volume = four_thirds_pi * pow(10, 3);
    REQUIRE(sphere_volume == Approx(4188.7902047));
}