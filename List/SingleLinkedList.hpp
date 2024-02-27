//
// Created by 杨程 on 2024/2/18.
//

#pragma once

#include <iostream>
#include "ListNode.hpp"

namespace sll { // 单链表命名空间
    enum findFormate { // 查找节点的方式
        GET_NODE_BY_INDEX, // 按照下标获取节点
        GET_NODE_BY_DATA, // 按照数据获取节点
    };
    enum insertFormate { // 插入节点的方式
        TAIL_INSERT, // 尾插法
        HEAD_INSERT, // 头插法
    };
}

// MARK: - SingleLinkedList
template <typename T>
class SingleLinkedList {
protected:
    sListNodePtr(T) head; // 头结点
    int length;

    virtual void clear() {
        // 清空链表
        sListNodePtr(T) p = head->next;
        while (p) {
            sListNodePtr(T) q = p;
            p = p->next;
            delete q;
        }
        head->next = nullptr;
        length = 0;
    }

private:
    void copyFrom(SingleLinkedList<T> &list) {
        // 从另一个链表复制
        clear(); // 清空当前链表
        sListNodePtr(T) p = list.head->next; // 指向待复制链表的第一个节点
        sListNodePtr(T) q = head; // 指向当前链表的头结点
        while (p) { // 遍历待复制链表
            sListNodePtr(T) r = new sListNode<T>; // 新节点
            r->data = p->data; // 复制数据
            r->next = nullptr; // 新节点的下一个节点为空
            q->next = r; // 当前节点的下一个节点指向新节点
            q = r; // 当前节点指向新节点
            p = p->next; // 待复制链表的当前节点指向下一个节点
        }
        length = list.length;
    }
    void swapData(sListNodePtr(T) p, sListNodePtr(T) q) {
        // 交换两个节点的数据
        T temp = p->data;
        p->data = q->data;
        q->data = temp;
    }
public:
// MARK: - 构造函数和析构函数：
    SingleLinkedList() {
        // 构造函数: 空链表
        head = new sListNode<T>;
        head->next = nullptr;
        length = 0;
    }
    SingleLinkedList(T *array, int length,
                     sll::insertFormate format = sll::TAIL_INSERT) {
        // 构造函数: 从数组构造链表
        if (format == sll::TAIL_INSERT) {
            head = new sListNode<T>;
            this->length = 0;
            sListNodePtr(T)p = head;
            for (int i = 0; i < length; i++) {
                p->insertAsNext(array[i]);
                p = p->next;
                this->length++;
            }
        } else if (format == sll::HEAD_INSERT) {
            head = new sListNode<T>;
            this->length = 0;
            for (int i = 0; i < length; i++) {
                head->insertAsNext(array[i]);
                this->length++;
            }
        } else {
            std::cerr << "Format error" << std::endl;
        }
    }
    ~SingleLinkedList() {
        // 析构函数
        sListNodePtr(T) p = head;
        while (p) {
            sListNodePtr(T) q = p;
            p = p->next;
            delete q;
        }
    }

// MARK: - 插入操作：
    void insert(T data, int index); // 在指定位置（下标）插入元素
    void insertNextNode(sListNodePtr(T) p, T data); // 在指定节点后插入元素
    void insertNextNode(sListNodePtr(T) p, sListNodePtr(T) target); // 在指定节点后插入节点
    virtual void insertPriorNode(sListNodePtr(T) p, T data); // 在指定节点前插入元素
    virtual void insertPriorNode(sListNodePtr(T) p, sListNodePtr(T) target); // 在指定节点前插入节点
    void extend(T data); // 在末尾添加元素

// MARK: - 删除操作：
    T remove(int index); // 删除元素
    virtual void deleteNode(sListNodePtr(T) p); // 删除指定节点

    virtual // MARK: - 只读操作接口：
    void getMetaData(); // 获取链表元数据
    T getElem(int index); // 按照下标获取指定元素的值
    int getIndex(T data); // 获取指定元素的下标
    sListNodePtr(T) getNode(T value,
                            sll::findFormate formate = sll::GET_NODE_BY_INDEX); // 获取指定下标节点
    void reverse(); // 反转链表
    virtual bool isEmpty() {
        return head->next == nullptr;
    }
// MARK: - 重载操作符：
    T operator[](int index); // 重载下标运算符
    bool operator==(SingleLinkedList<T> &list); // 重载相等运算符
    sListNodePtr(T) operator=(SingleLinkedList<T> &list); // 重载赋值运算符
};

// MARK: - realizations
template <typename T>
sListNodePtr(T) SingleLinkedList<T>::getNode(T value, sll::findFormate formate) {
    /* 获取指定节点:
        value: 下标或者数据
        formate: 获取节点的方式, 默认按照下标查找*/
    if (formate == sll::GET_NODE_BY_INDEX) {
        //判断value是否为数字
        if (value == -1) {
            return head;
        }
        if (value < 0 || value >= length) {
            std::cerr << "Index out of range" << std::endl;
            return nullptr;
        }
        sListNodePtr(T) p = head->next;
        for (int i = 0; i < value; i++) {
            p = p->next;
        }
        return p;
    } else if (formate == sll::GET_NODE_BY_DATA) {
        sListNodePtr(T) p = head->next;
        while (p) {
            if (p->data == value) {
                return p;
            }
            p = p->next;
        }
        std::cerr << "Data not found" << std::endl;
        return nullptr;
    } else {
        std::cerr << "Formate error" << std::endl;
        return nullptr;
    }
}

template <typename T>
void SingleLinkedList<T>::reverse() {
    // 反转链表
    sListNodePtr(T) p = head->next; // p 指向第一个节点
    sListNodePtr(T) q = nullptr; // q 指向前一个节点
    while (p) {
        sListNodePtr(T) r = p->next;
        p->next = q;
        q = p;
        p = r;
    }
    head->next = q;
}

template <typename T>
sListNodePtr(T) SingleLinkedList<T>::operator=(SingleLinkedList<T> &list) {
    // 重载赋值运算符
    copyFrom(list);
    return head;
}

template <typename T>
bool SingleLinkedList<T>::operator==(SingleLinkedList<T> &list) {
    // 重载相等运算符
    if (this->length != list.length) {
        return false;
    }
    sListNodePtr(T) p = this->head->next;
    sListNodePtr(T) q = list.head->next;
    while (p && q) {
        if (p->data != q->data) {
            return false;
        }
        p = p->next;
        q = q->next;
    }
    return true;
}

template <typename T>
T SingleLinkedList<T>::remove(int index) {
    // 根据下标删除元素
    if (index < 0 || index >= length) { // 下标越界
        std::cerr << "Index out of range" << std::endl;
        return -1; // 返回错误值
    }
    sListNodePtr(T) p = getNode(--index);// p 指向待删除节点的前一个节点
    sListNodePtr(T) q = p->next; // q 指向待删除节点
    T e = q->data; // 保存待删除节点的数据
    p->next = q->next;
    delete q;
    length--;
    return e;
}

template <typename T>
void SingleLinkedList<T>::deleteNode(sListNodePtr(T) p) {
    // 删除指定节点
    if (!p) { // p 为空
        std::cerr << "Node is null" << std::endl;
        return;
    } else if (!p->next) { // p 是最后一个节点
        remove(length - 1);
        return;
    }
    sListNodePtr(T) q = p->next; // q指向待删除的后一个节点
    p->data = q->data;
    p->next = q->next; // 将后一个节点的数据复制到当前节点
    delete q; // 删除后一个节点
    length--;
}

template <typename T>
T SingleLinkedList<T>::operator[](int index) {
    // 重载下标运算符
    if (index < 0 || index >= length) {
        std::cerr << "Index out of range" << std::endl;
        return -1;
    }
    sListNodePtr(T) p = head->next;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->data;
}

template <typename T>
void SingleLinkedList<T>::getMetaData() {
    // 获取链表元数据
    std::cout << "{[";
    sListNodePtr(T) p = head->next;
    for(int i = 0; i < length; i++) {
        // 通过长度遍历链表，以防止循环链表的死循环
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << "] ";
    std::cout << "Length: " << length << "}" << std::endl;
}

template <typename T>
void SingleLinkedList<T>::insert(T data, int index) {
    // 在指定下标位置插入元素
    if (index < 0 || index > length) {
        std::cerr << "Index out of range" << std::endl;
        return;
    }
    sListNodePtr(T) p = getNode(--index); // 指向待插入节点的前一个节点
//    for (int i = 0; i < index; i++) {
//        p = p->next;
//    }
    p->insertAsNext(data);
    length++;
}

template <typename T>
void SingleLinkedList<T>::insertNextNode(sListNodePtr(T) p, T data) {
    // 在指定节点后插入元素
    if (!p) {
        std::cerr << "Node is null" << std::endl;
        return;
    }
    p->insertAsNext(data);
    length++;
}

template <typename T>
void SingleLinkedList<T>::insertNextNode(sListNodePtr(T) p, sListNodePtr(T) target) {
    // 在指定节点后插入节点
    if (!p && !target) {
        std::cerr << "Node is null" << std::endl;
        return;
    }
    p->insertAsNext(target);
    length++;
}

template <typename T>
void SingleLinkedList<T>::insertPriorNode(sListNodePtr(T) p, T data) {
    // 在指定节点前插入元素
    if (!p) {
        std::cerr << "Node is null" << std::endl;
        return;
    }
    sListNode<T> *target = new sListNode<T>(data);
    p->insertAsNext(target);
    swapData(p, target);
    length++;
}

template <typename T>
void SingleLinkedList<T>::insertPriorNode(sListNodePtr(T) p, sListNodePtr(T) target) {
    // 在指定节点前插入节点
    if (!p && !target) {
        std::cerr << "Node is null" << std::endl;
        return;
    }
    p->insertAsNext(target);
    swapData(p, target);
    length++;
}

template <typename T>
void SingleLinkedList<T>::extend(T data) {
    // 在末尾添加元素
    insert(data, length);
}

template <typename T>
T SingleLinkedList<T>::getElem(int index) {
    // 按照下标获取指定元素的值
    if (index < 0 || index >= length) {
        std::cerr << "Index out of range" << std::endl;
        return -1;
    }
    return this->operator[](index);
}

template <typename T>
int SingleLinkedList<T>::getIndex(T data) {
    // 获取指定元素的下标
    sListNodePtr(T) p = head->next;
    for (int i = 0; i < length; i++) {
        if (p->data == data) {
            return i;
        }
        p = p->next;
    }
    return -1;
}