//
// Created by 杨程 on 2024/2/23.
//
#pragma once

#include <iostream>
#define MAX_STACK_SIZE 100

template <typename T>
class Stack{
protected:
    int size;
    int capacity;
    T *data;
public:
    Stack(int capacity = MAX_STACK_SIZE) {
        this->capacity = capacity;
        this->size = 0;
        this->data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(T e) {
        if (size == capacity) {
            std::cerr << "The stack is full." << std::endl;
            return;
        }

        data[size++] = e;
    }

    T pop() {
        if (size == 0) {
            std::cerr << "The stack is empty." << std::endl;
            return NULL;
        }

        return data[--size];
    }

    T top() {
        if (size == 0) {
            std::cerr << "The stack is empty." << std::endl;
            return NULL;
        }

        return data[size - 1];
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

};