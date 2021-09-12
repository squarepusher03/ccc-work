#include <new>
#include <iostream>
using namespace std;

struct Bucket {
    const static size_t dataSize{ 4096 };
    std::byte data[dataSize];
};

struct Heap {
    void* allocate(size_t bytes) {
        if (bytes > Bucket::dataSize) throw std::bad_alloc{};
        for (size_t i{}; i < nHeapBuckets; i++) {
            if (!bucketUsed[i]) {
                bucketUsed[i] = true;
                return buckets[i].data;
            }
        }
        throw std::bad_alloc{};
    }

    void free(void* p) {
        for (size_t i{}; i < nHeapBuckets; i++) { 
            if (buckets[i].data == p) {
                bucketUsed[i] = false;
                return;
            }
        }
    }

    static const size_t nHeapBuckets{ 10 };
    Bucket buckets[nHeapBuckets]{};
    bool bucketUsed[nHeapBuckets]{};
};

Heap heap;

void* operator new(size_t nBytes) {
    return heap.allocate(nBytes);
}

void operator delete(void* p) {
    return heap.free(p);
}

int main()
{
    cout << "Buckets: " << heap.buckets << "\n";
    auto breakfast = new unsigned int{ 0xC0FFEE };
    auto dinner = new unsigned int{ 0xDEADBEEF };
    cout << "Breakfast: " << breakfast << " 0x" << *breakfast << "\n";
    cout << "Dinner: " << dinner << " 0x" << *dinner << "\n";
    delete breakfast;
    delete dinner;

    try {
        while (true) {
            new char;
            cout << "Allocated a char.\n";
        }
    }
    catch (const std::bad_alloc&) {
        cout << "std::bad_alloc caught.\n";
    }
}