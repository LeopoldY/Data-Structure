//
// Created by 杨程 on 2024/2/22.
//

#pragma once // 防止头文件重复引用

#include <iostream>
#include "SingleLinkedList.hpp"
#include "DoubleLinkedList.hpp"

// MARK: - CycleList
template <typename T>
class CircularLinkedList: public SingleLinkedList<T> { // 继承单链表
private:
    void clear() {
        // 清空链表
        if (isEmpty()) return; // 如果链表为空，直接返回
        sListNodePtr(T) p = this->head->next;
        while (p != this->head) {
            sListNodePtr(T) q = p;
            p = p->next;
            delete q;
        }
        this->head->next = this->head;
        this->length = 0;
    }
public:
// MARK: - Constructor
    CircularLinkedList(): SingleLinkedList<T>(){
        this->head->next = this->head;
    } // 默认构造函数
    CircularLinkedList(T arr[], int n): SingleLinkedList<T>(arr, n) {
        if (SingleLinkedList<T>::head == nullptr) {
            return;
        }
        sListNodePtr(T) cur = SingleLinkedList<T>::head;
        while (cur->next != nullptr) { // 找到尾节点
            cur = cur->next;
        }
        cur->next = SingleLinkedList<T>::head;
    }
// MARK: - Destructor
    ~CircularLinkedList() {
        if (!this->head) return; // 如果头结点为空，直接返回
        clear(); // 清空链表
        this->head = nullptr; // 头结点置空
    }

// MARK: - Method
    bool isEmpty() {return this->head->next == this->head;} // 判断链表是否为空
    bool isTail(sListNodePtr(T) node) {return node->next == this->head;} // 判断节点是否为尾节点

    void insertPriorNode(sListNodePtr(T) node, T data); // 插入节点
    void insertPriorNode(sListNodePtr(T) node, sListNodePtr(T) p); // 插入节点

    void deleteNode(sListNodePtr(T) node); // 删除节点
    void getMetaData();

    bool operator==(CircularLinkedList<T> &list) {
        if (this->length != list.length) return false;
        sListNodePtr(T) p = this->head->next;
        sListNodePtr(T) q = list.head->next;
        while (p != this->head) {
            if (p->data != q->data) return false;
            p = p->next;
            q = q->next;
        }
        return true;
    }
};

// MARK: - Method-Implementation
template<typename T>
void CircularLinkedList<T>::getMetaData() {
    SingleLinkedList<T>::getMetaData();
    std::cout << "This is a cycle list." << std::endl;
}

template<typename T>
void CircularLinkedList<T>::deleteNode(sListNode<T> *node) {
    if (node == nullptr) return; // 如果节点为空，直接返回
    sListNodePtr(T) curr = this->head;
    while (curr->next != node) {
        curr = curr->next;
    }
    curr->next = node->next;
    delete node;
}

template <typename T>
void CircularLinkedList<T>::insertPriorNode(sListNodePtr(T) node, T data) {
    sListNodePtr(T) newNode = new sListNode<T>(data);
    if (!newNode) { // 内存分配失败
        std::cerr << "Memory allocation failed." << std::endl;
        return;
    }
    sListNodePtr(T) curr = node;
    while (curr->next != node) {
        curr = curr->next;
    }
    curr->insertAsNext(newNode);
    this->length++;
}

template <typename T>
void CircularLinkedList<T>::insertPriorNode(sListNodePtr(T) node, sListNodePtr(T) p) {
    if (!p) return; // 如果节点为空，直接返回
    sListNodePtr(T) curr = node;
    while (curr->next != node) {
        curr = curr->next;
    }
    curr->insertAsNext(p);
    this->length++;
}

// MARK: - CycleDoubleList
template <typename T>
class CircularDoubleList: public DoubleLinkedList<T> { // 继承双链表
private:
    void clear() {
        // 清空链表
        if (this->isEmpty()) return; // 如果链表为空，直接返回
        dListNodePtr(T) p = this->head->next;
        while (p != this->tail) {
            dListNodePtr(T) q = p; // 保存待删除节点
            p = p->next;
            delete q;
        }
        this->head->next = this->tail;
        this->tail->prior = this->head;
        this->length = 0;
    }
public:
    void test() {
        this->copyFrom(this);
    }
    CircularDoubleList(): DoubleLinkedList<T>() {
        this->tail->next = this->head;
        this->head->prior = this->tail;
    } // 默认构造函数
    CircularDoubleList(T arr[], int n): DoubleLinkedList<T>(arr, n) {
        this->tail->next = this->head;
        this->head->prior = this->tail;
    } // 有参构造函数, 传入数组和数组长度
    ~CircularDoubleList() {
        clear();
        delete this->tail;
        this->head = nullptr;
    } // 析构函数

    bool isEmpty() {return this->head->next == this->tail;} // 判断链表是否为空
    bool isTail(dListNodePtr(T) node) {return node->next == this->head;} // 判断节点是否为尾节点

    void getMetaData() {
        DoubleLinkedList<T>::getMetaData();
        std::cout << "This is a cycle list." << std::endl;
    }
};
