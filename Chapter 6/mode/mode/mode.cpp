#include <iostream>
#include <utility>

void selectionSort(int arr[], size_t length) {
    int smallest, temp;

    for (size_t i = 0; i < length; i++) {
        smallest = i;
        for (size_t j = i + 1; j < length; j++) {
            if (arr[j] < arr[smallest]) {
                smallest = j;
            }
        }

        temp = arr[smallest];
        arr[smallest] = arr[i];
        arr[i] = temp;
    }
}

void printArray(int x[], size_t length) {
    for (size_t i = 0; i < length; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << "\n";
}

int mode(int arr[], size_t length) {
    for (size_t i = 0; i < length; i++) {

    }
}

int main()
{
    int x[] = { 11, 3, 11, 7, 11, 2, 3 };
    printArray(x, 7);
    selectionSort(x, 7);
    printArray(x, 7);
    //std::cout << "mode: " << mode(x, 7) << "\n";
}