//
//  Vector.hpp
//  Custom-Vector
//
//  Created by 杨程 on 2024/2/17.
//

#pragma once

#include <iostream>

template <typename T>
class Vector { // 顺序表模板类
protected:
    T *data; // 数据
    int length; // 长度，顺序表目前的数据量
    int capacity; // 总容量，顺序表能够容纳的最多数据量

private:
    void clear(){
        delete[] data;
        data = nullptr;
        length = 0;
        capacity = 0;
    }
    
    void copyFrom(const Vector& other) {
        if (this == &other) return; // 若指针地址相同，则返回，以防止自拷贝
        clear();
        
        length = other.length;
        capacity = other.capacity;
        
        data = new T[capacity];
        if (!data) throw std::bad_alloc(); // 如果分配失败，抛出异常
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }
    
public:
    // 构造函数
    explicit Vector(int capacity = 0) : capacity(capacity), length(0) {
        data = new T[capacity];
    }

    Vector(const T* arr, int arrSize, int size):
            capacity(size), length(arrSize) { // 从数组复制
        if (size < arrSize) {
            throw std::out_of_range(
                    "Capacity must be greater than or equal to the length!"
                    );
        }
        data = new T[capacity];
        for (int i = 0; i < arrSize; i++) {
            data[i] = arr[i];
        }
    }
    
    // 析构函数
    ~Vector() { delete [] data; }
    
    // 重载 [] 运算符
    int& operator[](int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    // 重载运算符 ==
    bool operator==(const Vector& other) const {
        if (this->length != other.length) return false;
        
        for (int i = 0; i<length; i++) {
            if (this->data[i] != other.data[i]) return false;
        }
        
        return true;
    }
    // 重载运算符 =
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        clear();
        copyFrom(other);
        return *this;
    }
    
    void getAllElem() { // 打印所有元素
        if (length == 0 || capacity == 0) return;
        std::cout << '[';
        for (int i = 0; i < length-1; i++) {
            std::cout << data[i] << ',' ;
        }
        std::cout << data[length-1] << ']' << std::endl;
    }
    
    void getMetaData() {
        std::cout << "{\n"
                  << "element: ";
        getAllElem();
        std::cout << "length: " << length << std::endl;
        std::cout << "capacity: " << capacity << std::endl;
        std::cout << "}\n";
    }
    
    int size() { return length; }
    int getMaxLength() { return capacity; }
    int get(int i) { return data[i]; }
    void put(int i, T e) { data[i] = e; }

    
    bool insert(int i, T e) { // 在下标 i 处插入 e
        if (i < 0 || i > length || length == capacity) return false;
        
        for (int j = length; j > i; j--) data[j] = data[j-1];
        data[i] = e;
        length++;
        return true;
    }

    bool disordered() { // 判断是否有序
        for (int i = 1; i < length; i++) {
            if (data[i-1] > data[i]) return true;
        }
        return false;
    }

    void sort() { // 对顺序表进行排序
        if (!disordered()) return;
        for (int i = 0; i < length; i++) {
            for (int j = i+1; j < length; j++) {
                if (data[i] > data[j]) {
                    T temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }

    int find(T e, int lo, int hi) { // 从区间 [lo, hi) 查找元素 e
        while ((lo < hi--) && (e != data[hi]));
        return hi;
    }

    bool search(T e) { // 查找元素 e 是否存在
        for (int i = 0; i < length; i++) {
            if (data[i] == e) return true;
        }
        return false;
    }

    int deduplicate() { // 删除重复元素
        int oldLength = length;
        int i = 1;
        while (i < length) {
            if (find(data[i], 0, i) < 0) {
                i++;
            } else {
                remove(i);
            }
        }
        return oldLength - length;
    }

    int uniquify() { // 有序去重
        int i = 0, j = 0;
        while (++j < length) {
            if (data[i] != data[j]) {
                data[++i] = data[j];
            }
        }
        length = ++i;
        return j - i;
    }


    
    bool extend(T e) { // 在末尾添加元素
        if (length == capacity) expand(1);
        data[length] = e;
        length++;
        return true;
    }
    
    void expand(int size) { // 扩展容量，新容量为 capacity+_size
        T* newData = new(std::nothrow) T[capacity+size]; // 使用nothrow_new来避免异常
        if (!newData) { // 检查是否分配成功
            throw std::bad_alloc(); // 如果分配失败，抛出异常
        }
        for (int i = 0; i < length; i++) {
            newData[i] = data[i]; // 复制现有数据
        }
        delete[] data; // 释放旧内存
        data = newData; // 更新指针
        capacity = capacity + size; // 更新容量
    }
    
    T remove(int i) { // 按照下标删除元素
        if (i < 0 || i >= length) throw std::out_of_range("Index out of range");
        T e = data[i];
        for (int j = i; j < length-1; j++) data[j] = data[j+1];
        length--;
        return e;
    }
    
    int locateElem(T e) {
        for (int i = 0; i < length; i++) {
            if (data[i] == e) return i;
        }
        return -1;
    }

    virtual bool isEmpty() { return length == 0; }

    void traverse(void (*visit)(T&)) { // 遍历
        for (int i = 0; i < length; i++) {
            visit(data[i]);
        }
    }

};
