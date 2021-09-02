#include <iostream>
#include <stdexcept>
#include <type_traits>
using namespace std;

//template <typename T1, typename T2, ...>
//concept bool ConceptName() {
//
//}

//requires (arg-1, arg-2, ...) {
//    { expression1 } -> return-type1;
//    { expression2 } -> return-type2;
//    ...
//}

constexpr const char* asStr(bool x) { return x ? "True" : "False"; }

template <typename T>
    requires is_copy_constructible<T>::value
T getCopy(T* pointer) {
        if (!pointer) throw std::runtime_error{ "Null-pointer dereference" };
        return *pointer;
}

struct Highlander {
    Highlander() = default;
    Highlander(const Highlander&) = delete; // makes it not copy constructible
};

template <size_t Index, typename T, size_t Length>
T& get(T (&arr)[Length]) { 
    // the first param is a reference to an array of T type items with a length of Length
    static_assert(Index < Length, "Out-of-bounds access");
    return arr[Index];
}

int main()
{
    //cout << asStr(is_integral<int>::value) << endl;
    //cout << asStr(is_integral<const int>::value) << endl;
    //cout << asStr(is_integral<char>::value) << endl;
    //cout << asStr(is_integral<uint64_t>::value) << endl;
    //cout << asStr(is_integral<int&>::value) << endl;
    //cout << asStr(is_integral<int*>::value) << endl;
    //cout << asStr(is_integral<float>::value) << endl;

    int x[] = { 0, 1, 2, 3 };
    cout << get<3>(x) << "\n";
    cout << get<1>(x) << "\n";

    //Highlander connor;
    //auto connorPtr = &connor;
    //auto connorCopy = getCopy(connorPtr); causes a crash since it's not copy constructible
}
