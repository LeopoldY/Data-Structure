//
// Created by 杨程 on 2024/2/23.
//

#pragma once

#include <iostream>

#include "../List/List.hpp"

template <typename T>
class Queue: private List<T>{
public:
    Queue(): List<T>() {} // 默认构造
    explicit Queue(T const &size): List<T>(size) {} // 重载构造
    T dequeue() {
        if (this->isEmpty()) {
            throw std::out_of_range("Queue is empty!");
        }
        return this->remove(0);
    }
    void enqueue(T const &e) { this->insert(e); }
    T& front() { return this->data[0]; }
    T& rear() { return this->data[this->length - 1]; }
};