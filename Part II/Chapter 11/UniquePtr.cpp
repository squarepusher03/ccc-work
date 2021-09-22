#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../lib/catch.hpp"
using namespace std;

struct ptr {
	const char* message;
	static int x;

	ptr(const char* m="") : message{ m } { x++; }
	~ptr() { x--; }
};

int ptr::x{};
using UniquePtr = std::unique_ptr<ptr>;

// Unique pointers support every operation that scoped pointers do.
// They cannot be copied though (exclusive ownership, but transferable)

TEST_CASE("UniquePtr can be used in move") {
	auto a = make_unique<ptr>();
	SECTION("construction") {
		auto b{ move(a) };
		REQUIRE(ptr::x == 1);
	}

	SECTION("assignment") {
		auto b = make_unique<ptr>();
		REQUIRE(ptr::x == 2);
		b = move(a);
		REQUIRE(ptr::x == 1);
	}
}

TEST_CASE("UniquePtr to array supports operator[]") {
	unique_ptr<int[]> squares{
		new int[5]{ 1, 4, 9, 16, 25 }
	};
}