//
// Created by 杨程 on 2024/2/19.
//

#pragma once

#define sListNodePtr(T) sListNode<T> * // 单链表节点指针
#define dListNodePtr(T) dListNode<T> * // 双链表节点指针
#define StaticNodePtr(T) StaticNode<T> * // 静态链表节点指针

template <typename T> struct StaticNode { // 静态链表节点
    T data;
    int next;

    StaticNode() {
        data = 0;
        next = -2;
    } // 默认构造函数
    explicit StaticNode(T data, int next = -2) {
        this->data = data;
        this->next = next;
    }

    ~StaticNode() {
        next = -1;
    }
};

template <typename T> struct sListNode { // 单链表节点
    T data;
    sListNodePtr(T) next;

    sListNode() {
        data = 0;
        next = nullptr;
    }
    explicit sListNode(T data, sListNodePtr(T) next = nullptr) {
        this->data = data;
        this->next = next;
    }

    sListNodePtr(T) insertAsNext(T const &e) {
        // 在当前节点之后插入新节点
        sListNodePtr(T) x = new sListNode(e, this->next);
        this->next = x;
        return x;
    }

    sListNodePtr(T) insertAsNext(sListNodePtr(T) x) {
        // 在当前节点之后插入新节点
        x->next = this->next;
        this->next = x;
        return x;
    }

};

template <typename T>
struct dListNode {
    T data;
    dListNodePtr(T) prior;
    dListNodePtr(T) next;

    dListNode() {
        data = 0;
        prior = nullptr;
        next = nullptr;
    }
    explicit dListNode(T data,
                       dListNodePtr(T) prior = nullptr,
                       dListNodePtr(T) next = nullptr) {
        this->data = data;
        this->prior = prior;
        this->next = next;
    }

    ~dListNode() {
        prior = nullptr;
        next = nullptr;
    }

    dListNodePtr(T) insertAsPrior(T const &e) {
        // 在当前节点之前插入新节点
        dListNodePtr(T) x = new dListNode(e, this->prior, this);
        this->prior->next = x;
        this->prior = x;
        return x;
    }
    dListNodePtr(T) insertAsPrior(dListNodePtr(T) x) {
        // 在当前节点之前插入新节点
        x->prior = this->prior;
        x->next = this;
        this->prior->next = x;
        this->prior = x;
        return x;
    }

    dListNodePtr(T) insertAsNext(T const &e) {
        // 在当前节点之后插入新节点
        dListNodePtr(T) x = new dListNode(e);
        x->prior = this;
        x->next = this->next;
        this->next->prior = x;
        this->next = x;
        return x;
    }
    dListNodePtr(T) insertAsNext(dListNodePtr(T) x) {
        // 在当前节点之后插入新节点
        x->prior = this;
        x->next = this->next;
        this->next->prior = x;
        this->next = x;
        return x;
    }

    void remove() {
        // 删除当前节点
        this->prior->next = this->next;
        this->next->prior = this->prior;
        delete this;
    }

};