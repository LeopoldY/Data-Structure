//
// Created by 杨程 on 2024/2/23.
//

#pragma once

#include <iostream>

#define MAX_QUEUE_SIZE 100

template <typename T>
class Queue{
private:
    T *data;
    int front;
    int rear;
    int maxSize;
public:
    Queue(int size = MAX_QUEUE_SIZE) {
        data = new T[size];
        maxSize = size;
        front = rear = 0;
    }

    ~Queue() {
        delete[] data;
    }

    bool isEmpty() {
        return front == rear;
    }

    bool isFull() {
        return (rear + 1) % maxSize == front;
    }

    void push(T e) {
        if (isFull()) {
            std::cerr << "Queue is full." << std::endl;
            return;
        }

        data[rear] = e;
        rear = (rear + 1) % maxSize;
    }

    T pop() {
        if (isEmpty()) {
            std::cerr << "Queue is empty." << std::endl;
            return T();
        }

        T e = data[front];
        front = (front + 1) % maxSize;
        return e;
    }

    T getFront() {
        if (isEmpty()) {
            std::cerr << "Queue is empty." << std::endl;
            return T();
        }

        return data[front];
    }

    int getLength() {
        return (rear - front + maxSize) % maxSize;
    }
};