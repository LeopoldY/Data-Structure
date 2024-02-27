//
// Created by 杨程 on 2024/2/23.
//
#pragma once

#include <iostream>
#include "../List/List.hpp"

template <typename T>
class Stack: private List<T>{
protected:
    int top;
public:
    Stack(): List<T>() {this->top = -1;} // 默认构造
    explicit Stack(T const &size): List<T>(size) {this->top = -1;} // 重载构造
    T pop() {
        if (this->isEmpty()) {
            throw std::out_of_range("Stack is empty!");
        }
        return this->remove(this->length - 1);
    }
    void push(T const &e) {
        this->extend(e);
        this->top++;
    }
    T& getTop() {
        if (this->top == -1) std::cerr << "stack is empty!" << std::endl;
        return this->data[top];
    }

};