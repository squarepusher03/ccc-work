#include <iostream>
using namespace std;

auto my_deleter = [](int* x) {
	cout << "Deleting unique ptr.\n";
	delete x;
};

unique_ptr<int, decltype(my_deleter)> my_up{
	new int,
	my_deleter
};

int main() {

}