
#include <iostream>
#include "Tree.h"

int main() {
    Tree a;
    a.insert(5);
    a.insert(5);

    a.insert(8);
    a.insert(10);
    a.remove(5);

    std::cout << a.find(5);

    return 0;
}