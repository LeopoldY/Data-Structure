//
// Created by 杨程 on 2024/2/22.
//

#pragma once

#include <iostream>
#include "ListNode.hpp"
#include "List.hpp"

namespace sl{
    const int MAX_SIZE = 10; // 静态链表的最大容量
}

template <typename T>
class StaticList: public List<T> { // 静态链表模板类
protected:
    StaticNodePtr(T) head; // 头节点
private:
    void init(){
//        for (int i = 0; i < this->capacity; i++) {
//            data[i].data = 0;
//            data[i].next = -2;
//        }
//        head = data;
//        head->next = -1;
    }

public:
    explicit StaticList(int size = sl::MAX_SIZE): List<StaticNode<T>>(size) {
        this->head = this->data;
    }; // 构造函数
};