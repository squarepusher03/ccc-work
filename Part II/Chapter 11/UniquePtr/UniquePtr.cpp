#define CATCH_CONFIG_MAIN
#include <iostream>
#include <memory>
#include "../../lib/catch.hpp"
#pragma warning( disable : 4996 )
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
	squares[0] = 1;
	REQUIRE(squares[0] == 1);
	REQUIRE(squares[1] == 4);
	REQUIRE(squares[2] == 9);
}

auto my_deleter = [](int* x) {
	cout << "Deleting unique ptr.\n";
	delete x;
};

unique_ptr<int, decltype(my_deleter)> my_up{
	new int,
	my_deleter
};

// ---------------

//using FileGuard = unique_ptr<FILE, int(*)(FILE*)>;
//
//void say_hello(FileGuard file) {
//	fprintf(file.get(), "HELLO DAVE");
//}
//
//int main() {
//	auto file = fopen("HAL9000", "w"); 
//	if (!file) return errno;
//	FileGuard file_guard{ file, fclose };
//	// File open here
//	say_hello(move(file_guard));
//	// File close here
//	return 0;
//}