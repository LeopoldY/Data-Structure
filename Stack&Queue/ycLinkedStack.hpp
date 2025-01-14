//
// Created by yangc on 2024/2/27.
//

#pragma once

#include "../List/SingleList.hpp"

template <typename T>
class ycLinkedStack: public SingleList<T> {
public:
    ycLinkedStack(): SingleList<T>() {} // 默认构造
    ~ycLinkedStack() {
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