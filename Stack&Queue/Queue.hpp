//
// Created by 杨程 on 2024/2/23.
//

#pragma once

#include <iostream>

#include "../List/List.hpp"

#define MAX_QUEUE_SIZE 10

template <typename T>
class Queue: private List<T>{
protected:
    int front;
    int rear;
public:
    Queue(): List<T>(MAX_QUEUE_SIZE), front(0), rear(0) {} // 默认构造
    explicit Queue(T const &size): List<T>(size), front(0), rear(0) {} // 重载构造
    T dequeue() {
        if (this->isEmpty()) {
            throw std::out_of_range("Queue is empty!");
        }
        T e = this->data[front];
        front = (front + 1) % this->capacity;
        this->length--;
        return e;
    }
    void enqueue(T const &e) {
        if (isFull()) {
            throw std::out_of_range("Queue is full!");
        }
        this->data[rear] = e;
        rear = (rear + 1) % this->capacity;
        this->length++;
    }
    T& getFront() { return this->data[front]; }
    T& getRear() { return this->data[rear]; }
    bool isFull() { return this->length == this->capacity; }
};