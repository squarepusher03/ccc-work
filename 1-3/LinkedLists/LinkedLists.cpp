 #include <cstdio>

// Node of a doubly-linked list.
struct Node {
    Node* next{  }; // pointer to the next node
    Node* previous{  }; // pointer to the previous node

    // Inserts a node.
    void insert(Node* new_node) {
        if (this->next != nullptr) {
            new_node->next = this->next;
            this->next->previous = new_node;
        }
        this->next = new_node;
        this->next->previous = this;
    }

    char prefix[2]{ 'A', 'A' };
    short operating_number{ 000 };
};

int main()
{
    Node trooper1{ Node() };
    Node trooper2{ Node() };
    Node trooper3{ Node() };
    Node trooper4{ Node() };
    
    // trooper1
    trooper1.prefix[0] = 'T';
    trooper1.prefix[1] = 'K';
    trooper1.operating_number = 421;
    trooper1.insert(&trooper2);
    
    // trooper2
    trooper2.prefix[0] = 'F';
    trooper2.prefix[1] = 'N';
    trooper2.operating_number = 2187;
    trooper2.insert(&trooper3);

    // trooper3
    trooper3.prefix[0] = 'F';
    trooper3.prefix[1] = 'F';
    trooper3.operating_number = 375;
    trooper3.insert(&trooper4);

    // trooper4
    trooper4.prefix[0] = 'L';
    trooper4.prefix[1] = 'S';
    trooper4.operating_number = 005;

    printf("Forwards:\n");

    for (Node* cursor = &trooper1; cursor; cursor = cursor->next) { 
        // 1. the iterator is a Node pointer, starting with the address of the first node.
        // 2. Only loop if the current address of the pointer isn't nullptr.
        // 3. Iterates by pointing to the next node of the current element for each iteration.
        printf("stormtrooper %c%c-%d\n",
            cursor->prefix[0],
            cursor->prefix[1],
            cursor->operating_number);
    }

    printf("\nBackwards:\n");

    for (Node* cursor = &trooper4; cursor; cursor = cursor->previous) {
        printf("stormtrooper %c%c-%d\n",
            cursor->prefix[0],
            cursor->prefix[1],
            cursor->operating_number);
    }

    return 0;
}