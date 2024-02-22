//
//  main.cpp
//  Custom-List
//
//  Created by 杨程 on 2024/2/16.
//

#include <iostream>
//#include "List.hpp"
//#include "SingleLinkedList.hpp"
#include "DoubleLinkedList.hpp"

using namespace::std;

template <typename T>
void print(const T& value, char end = '\n') {
    if constexpr (is_arithmetic_v<T>)
        // 对于算术类型，直接打印
        cout << value;
    else if constexpr (std::is_enum_v<T>) {
        // 对于枚举类型，也直接打印
        cout << static_cast<typename underlying_type<T>::type>(value);
    } else {
        // 对于其他类型，使用 << 运算符打印
        cout << value;
    }
    cout << end;
}

int main(int argc, const char * argv[]) {
    char str[] = {'a','b','c','d','e'};
    DoubleLinkedList<char> dlist(str, 5, dll::TAIL_INSERT);
    dlist.getMetaData();
    DoubleLinkedList<char> dlist2(dlist, 2, 5);
    dlist2.getMetaData();
    return 0;
}