cmake_minimum_required(VERSION 3.27)
project(Data_Structure)

set(CMAKE_CXX_STANDARD 17)

add_executable(Data_Structure main.cpp
        List/List.hpp
        List/StaticList.hpp
        List/CycleList.hpp
        List/DoubleLinkedList.hpp
        List/SingleLinkedList.hpp
        Stack&Queue/Stack.hpp
        Stack&Queue/Queue.hpp
        Stack&Queue/LinkedStack.hpp
        Stack&Queue/LinkedQueue.hpp
        List/ListNode.hpp
        Tree/BinaryTree.hpp
        Tree/BinaryTree.hpp
)
