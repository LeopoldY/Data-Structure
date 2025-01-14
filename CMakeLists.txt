cmake_minimum_required(VERSION 3.27)
project(Data_Structure)

set(CMAKE_CXX_STANDARD 17)

add_executable(Data_Structure main.cpp
        List/Vector.hpp
        List/StaticList.hpp
        List/CycleList.hpp
        List/DoubleLinkedList.hpp
        List/SingleList.hpp
        Stack&Queue/Stack.hpp
        Stack&Queue/Queue.hpp
        Stack&Queue/ycLinkedStack.hpp
        Stack&Queue/LinkedQueue.hpp
        List/ListNode.hpp
        Tree/ycBinaryTree.hpp
        Tree/ycBinaryTree.hpp
        Solution/TreeSolution.hpp
        Solution/StackAndQueueSolution.hpp
        Stack&Queue/MyStack.hpp
        Stack&Queue/MyQueue.hpp
        Graph/AdjMatrixGraph.hpp
        Graph/AdjMatrixGraph.hpp
        Solution/Solution.hpp
        Tree/ycBiNode.hpp
        List/myString.hpp
)
