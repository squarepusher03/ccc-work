#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../lib/catch.hpp"
#include "../lib/scoped_ptr.hpp"
#include "../lib/scoped_array.hpp"
using namespace std;

struct ptr {
	const char* message;
	static int x;

	ptr(const char* m="") : message{ m } { x++; }
	~ptr() { x--; }
};

int ptr::x{};
using ScopedPtr = boost::scoped_ptr<ptr>;

TEST_CASE("ScopedPtr evaluates to") {
	SECTION("true when full") {
		ScopedPtr a{ new ptr{} };
		REQUIRE(a);
	}

	SECTION("false when empty") {
		ScopedPtr a;
		REQUIRE_FALSE(a);
	}
}

TEST_CASE("ScopedPtr is a RAII wrapper.") {
	REQUIRE(ptr::x == 0);
	ScopedPtr a{ new ptr{} };
	REQUIRE(ptr::x == 1);
	{
		ScopedPtr b{ new ptr{} };
		REQUIRE(ptr::x == 2);
	}
	REQUIRE(ptr::x == 1);
}

TEST_CASE("ScopedPtr supports pointer semantics, like") {
	auto message = "Hello, world!";
	ScopedPtr a{ new  ptr{ message } };
	SECTION("operator*") {
		REQUIRE((*a).message == message);
	}

	SECTION("operator->") {
		REQUIRE(a->message == message);
	}

	SECTION("get(), which returns a raw pointer") {
		REQUIRE(a.get() != nullptr);
	}
}

TEST_CASE("ScopedPtr supports comparison with nullptr") {
	SECTION("operator==") {
		ScopedPtr a{};
		REQUIRE(a == nullptr);
	}

	SECTION("operator!=") {
		ScopedPtr a{ new ptr{} };
		REQUIRE(a != nullptr);
	}
}

TEST_CASE("ScopedPtr supports swap") {
	auto message1 = "Hello, World!";
	auto message2 = "Merry Christmas!";
	ScopedPtr a { new ptr{ message1 } };
	ScopedPtr b { new ptr{ message2 } };
	swap(a, b);

	REQUIRE(b->message == message1);
	REQUIRE(a->message == message2);
}

TEST_CASE("ScopedPtr reset") {
	ScopedPtr a{ new ptr{} };
	SECTION("destructs owned object.") {
		a.reset();
		REQUIRE(ptr::x == 0);
	}

	SECTION("can replace an owned object") {
		auto message = "Hello, world!";
		auto y = new ptr{ message };
		REQUIRE(ptr::x == 2);
		
		// deletes old dynamic object and takes ownership of the passed object.
		a.reset(y);

		REQUIRE(ptr::x == 1);
		REQUIRE(a->message == y->message);
		REQUIRE(a.get() == y);
	}
}

TEST_CASE("ScopedArray supports operator[]") {
	boost::scoped_array<int> squares {
		new int[5] { 0, 4, 9, 25 }
	};
	squares[0] = 1;
	REQUIRE(squares[0] == 1);
	REQUIRE(squares[1] == 4);
	REQUIRE(squares[2] == 9);
}