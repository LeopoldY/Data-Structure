//
// Created by 杨程 on 2024/2/18.
//

#pragma once

#include "ListNode.hpp"
#include <iostream>

namespace dll {
    enum InsertMode {
        HEAD_INSERT, TAIL_INSERT
    };
    enum FindMode {
        GET_NODE_BY_INDEX, GET_NODE_BY_DATA
    };
}

template <typename T>
class DoubleLinkedList {
protected:
    dListNodePtr(T) head;
    dListNodePtr(T) tail;
    int length;
private:
    void init() { // 初始化链表
        head = new dListNode<T>();
        tail = new dListNode<T>();
        head->next = tail;
        tail->prior = head;
        length = 0;
    }
    void clear() { // 清空链表
        dListNodePtr(T) p = head->next;
        while (p != tail) {
            dListNodePtr(T) q = p;
            p = p->next;
            q->remove();
        }
        head->next = tail;
        tail->prior = head;
        length = 0;
    }
    // 从链表 list 的 lo 到 hi 之间的元素复制到当前链表
    void copyFrom(DoubleLinkedList<T> &list , int lo, int hi) {
        if (lo < 0 || lo >= list.length || hi > list.length) { // 检查范围
            std::cerr << "Invalid range" << std::endl;
            return;
        }
        clear();
        dListNodePtr(T) p = list.getNode(lo);
        dListNodePtr(T) q = head;
        for (int i = lo; i < hi; i++) {
            dListNodePtr(T) newNode = new dListNode<T>(p->data);
            q = q->insertAsNext(newNode);
            length++;
            p = p->next;
        }
    }
    void copyFrom(DoubleLinkedList<T> &list) {copyFrom(list, 0, list.length);} // 复制整个链表
    void copyFrom(T *arr, int lo, int hi) {
        clear();
        dListNodePtr(T) p = head;
        for (int i = lo; i < hi; i++) {
            p = p->insertAsNext(arr[i]);
            length++;
        }
    } // 从数组的 lo 到 hi 之间的元素复制到当前链表
    void swapData(dListNodePtr(T) p, dListNodePtr(T) q) {
        T temp = p->data;
        p->data = q->data;
        q->data = temp;
    } // 交换两个节点的数据
public:
    DoubleLinkedList() {init();} // 默认构造函数
    DoubleLinkedList(T *arr, int lo, int hi) {
        // 从数组的 lo 到 hi 之间的元素创建链表
        init();
        copyFrom(arr, lo, hi);
    } // 从数组指定位置创建链表
    DoubleLinkedList(T *arr, int length, dll::InsertMode mode = dll::TAIL_INSERT) {
        // 从数组创建链表
        init();
        if (mode == dll::HEAD_INSERT) {
            for (int i = 0; i < length; i++) {
                head->insertAsNext(arr[i]);
                this->length++;
            }
        } else if (mode == dll::TAIL_INSERT) {
            copyFrom(arr, 0, length);
        } else {
            std::cerr << "Invalid insert mode" << std::endl;
        }
    }
    DoubleLinkedList(DoubleLinkedList<T> &list) {init(); copyFrom(list, 0, list.length);} // 复制构造函数
    DoubleLinkedList(DoubleLinkedList<T> &list, int lo, int hi) {init();copyFrom(list, lo, hi);} // 复制构造函数
    ~DoubleLinkedList() {
        dListNodePtr(T) p = head;
        while (p) {
            dListNodePtr(T) q = p->next; // 保存下一个节点的指针
            delete p;
            p = q;
        }
    }

    virtual void getMetaData() {
        dListNodePtr(T) p = head->next;
        std::cout << "{[";
        while (p != tail) {
            std::cout << p->data << " ";
            p = p->next;
        }
        std::cout << "] length:" << length << '}' <<std::endl;
    }

    void insert(int index, T data); // 在指定位置插入元素
    void insertAsPrior(dListNodePtr(T) p, T const &e); // 在节点 p 之前插入元素 e
    void insertAsNext(dListNodePtr(T) p, T const &e); // 在节点 p 之后插入元素 e

    void deleteNode(dListNodePtr(T) p); // 删除节点 p
    void remove(int index); // 删除指定下标的节点

    dListNodePtr(T) getNode(T value, dll::FindMode = dll::GET_NODE_BY_INDEX); // 获取节点
    virtual bool isEmpty() { return length == 0; } // 判断链表是否为空

    void reverse(); // 反转链表
};

template <typename T>
dListNodePtr(T) DoubleLinkedList<T>::getNode(T value, dll::FindMode mode) {
    dListNodePtr(T) p = head->next;
    if (mode == dll::GET_NODE_BY_DATA) {
        while (p != tail) {
            if (p->data == value) {
                return p;
            }
            p = p->next;
        }
    } else if (mode == dll::GET_NODE_BY_INDEX) {
        for (int i = 0; i < value; i++) {
            p = p->next;
        }
        return p;
    } else {
        std::cerr << "Invalid find mode" << std::endl;
    }
    return nullptr;
}

template <typename T>
void DoubleLinkedList<T>::reverse() {
    dListNodePtr(T) p = head->next;
    dListNodePtr(T) q = tail->prior;
    for (int i = 0; i < length / 2; i++) {
        swapData(p, q);
        p = p->next;
        q = q->prior;
    }
}

template <typename T>
void DoubleLinkedList<T>::insert(int index, T data) {
    dListNodePtr(T) p = getNode(index);
    p->insertAsPrior(data);
    length++;
}

template <typename T>
void DoubleLinkedList<T>::insertAsPrior(dListNodePtr(T) p, T const &e) {
    p->insertAsPrior(e);
    length++;
}

template <typename T>
void DoubleLinkedList<T>::insertAsNext(dListNodePtr(T) p, T const &e) {
    p->insertAsNext(e);
    length++;
}

template <typename T>
void DoubleLinkedList<T>::deleteNode(dListNodePtr(T) p) {
    p->remove();
    length--;
}

template <typename T>
void DoubleLinkedList<T>::remove(int index) {
    dListNodePtr(T) p = getNode(index);
    p->remove();
    length--;
}