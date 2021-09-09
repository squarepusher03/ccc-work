#include <iostream>
using namespace std;

int main() {
	char key{'a'};
	size_t tally{};
	
	auto a_search = [&, key](const char* str) mutable {
		size_t index{}, result{};
		
		while (str[index]) {
			if (str[index] == key) result++;
			index++;
		}

		tally += result;
		return result;
	};

	cout << "tally: " << tally << endl;
	auto str1 = a_search("aaa aa aaa"); // 8
	cout << "str1: " << str1 << endl;

	cout << "tally: " << tally << endl;
	auto str2 = a_search("ababbba aaba"); // 6
	cout << "str2: " << str2 << endl;

	cout << "tally: " << tally << endl;
}