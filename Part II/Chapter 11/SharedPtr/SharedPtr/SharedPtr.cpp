#define CATCH_CONFIG_MAIN
#include <iostream>
#include <memory>
#include "../../../lib/catch.hpp"
using namespace std;

struct obj {
	const char* message;
	static int x;

	obj(const char* m = "") : message{ m } { x++; }
	~obj() { x--; }
};

int obj::x{};
using SharedPtr = shared_ptr<obj>;

TEST_CASE("SharedPtr can be used in copy") {
	auto a = make_shared<obj>();

	// b shares ownership with a over the obj
	SECTION("construction") {
		auto b{ a };
		REQUIRE(obj::x == 1);
	}

	// the same here
	SECTION("assignment") {
		SharedPtr b;
		b = a;
		REQUIRE(obj::x == 1);
	}

	SECTION("assignment, and original gets discarded") {
		// b has it's own obj, making the total obj's 2.
		auto b = make_shared<obj>();
		REQUIRE(obj::x == 2);
		// b destroys it's obj to make room for a's, then shares ownership of a's obj.
		b = a;
		REQUIRE(obj::x == 1);
	}
}