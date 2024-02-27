//
// Created by yangc on 2024/2/27.
//

#pragma once

#include <iostream>
#include "../List/SingleLinkedList.hpp"

template <typename T>
class LinkedQueue: private SingleLinkedList<T> { // 链式队列
protected:
    sListNodePtr(T) rear;
    sListNodePtr(T) front;

private:
    void clear() {
        SingleLinkedList<T>::clear();
        rear = front = nullptr;
    }
public:
    LinkedQueue(): SingleLinkedList<T>(),
            rear(this->head), front(this->head) {} // 默认构造
    T dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty!");
        }
        T e = front->next->data;
        sListNodePtr(T) p = front->next;
        this->head->next = p->next;
        delete p;
        this->length--;
        return e;
    }
    void enqueue(T const &e) {
        sListNodePtr(T) p = new sListNode<T>;
        p->data = e;
        p->next = nullptr;

        rear->next = p;
        rear = p;

        this->length++;
    }
    T& getFront() { return front->next->data; }
    T& getRear() { return rear->data; }
    bool isEmpty() { return this->length == 0; }
    int size() { return this->length; }

    ~LinkedQueue() { clear(); }
};
