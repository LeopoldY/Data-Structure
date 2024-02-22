#include <iostream>
#include "./List/DoubleLinkedList.hpp"

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    DoubleLinkedList<int> list(arr, 5);
    list.getMetaData();
    return 0;
}
