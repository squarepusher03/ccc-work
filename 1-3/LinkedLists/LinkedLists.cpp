 #include <cstdio>

// Element-nth, Element-nth+1, ... nullptr
struct Element {
    Element* next; // pointer to the next element
    void insert_after(Element* new_element) { // takes in pointer of the new element
        new_element->next = this->next; // points the inserting new element's "next" to the next element
        this->next = new_element; // points the "next" of this element to the new element
    }
    char prefix[2];
    short operating_number;
};

int main()
{
    Element* trooper1 = new Element();
    Element* trooper2 = new Element();
    Element* trooper3 = new Element();
    
    // trooper1
    trooper1->prefix[0] = 'T';
    trooper1->prefix[1] = 'K';
    trooper1->operating_number = 421;
    trooper1->insert_after(trooper2);
    
    // trooper2
    trooper2->prefix[0] = 'F';
    trooper2->prefix[1] = 'N';
    trooper2->operating_number = 2187;
    trooper2->insert_after(trooper3);

    // trooper3
    trooper3->prefix[0] = 'L';
    trooper3->prefix[1] = 'S';
    trooper3->operating_number = 005;

    for (Element* cursor = trooper1; cursor; cursor = cursor->next) { 
        // 1. the iterator is an Element pointer, starting with the address of the first element.
        // 2. Only loop if the current address of the pointer isn't nullptr.
        // 3. Iterates by pointing to the next element of the current element for each iteration.
        printf("stormtrooper %c%c-%d\n",
            cursor->prefix[0], 
            cursor->prefix[1],
            cursor->operating_number);
    }

    delete trooper1;
    delete trooper2;
    delete trooper3;

    return 0;
}