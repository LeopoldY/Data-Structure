//
// Created by 杨程 on 2024/2/23.
//
#pragma once

#include <iostream>
#include "../List/List.hpp"

template <typename T>
class Stack: private List<T>{
public:
    Stack(): List<T>() {} // 默认构造
    explicit Stack(T const &size): List<T>(size) {} // 重载构造
    T pop() {
        if (this->isEmpty()) {
            throw std::out_of_range("Stack is empty!");
        }
        return this->remove(this->length - 1);
    }
    void push(T const &e) { this->extend(e); }
    T& top() {
        if (this->isEmpty()) {
            throw std::out_of_range("Stack is empty!");
        }
        return this->data[this->length - 1];
    }
};