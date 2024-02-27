//
// Created by yangc on 2024/2/27.
//

#pragma once

#include "../List/SingleLinkedList.hpp"

template <typename T>
class LinkedStack: private SingleLinkedList<T> {
public:
    LinkedStack(): SingleLinkedList<T>() {} // 默认构造
    ~LinkedStack() {
        this->clear();
    } // 析构函数
    void push(T const &e) {
        this->insert(e,0);
    }

    T pop() {
        if (this->isEmpty()) {
            throw std::out_of_range("Stack is empty!");
        }
        sListNodePtr(T) p = this->head->next;
        T e = p->data;
        this->head->next = p->next;
        delete p;
        this->length--;
        return e;
    }

    T& getTop() {
        if (this->isEmpty()) {
            throw std::out_of_range("Stack is empty!");
        }
        return this->head->next->data;
    }

};