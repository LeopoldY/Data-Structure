# 自定义列表类

通过C++模板类实现的顺序表、单向链表以及双向链表。

## **Usage**

### 顺序表 (List)

1. 在主函数中引入 `List.hpp`

2. 使用以下语句进行实例化：

    1. 无参构造：

       ```c++
       List<TypeName> variableName; 
       ```

    2. 从数组构造:

       ```c++
       List<TypeName> variableName(arr, arrSize, capacity); 
       ```

### 单向链表 (Single Linked List)

1. 在主函数中引入 `SingleLinkedList.hpp`

2. 使用以下语句进行实例化：

    1. 无参构造：

       ```c++
       SingleLinkedList<TypeName> variableName; 
       ```

    2. 从数组构造:

       ```c++
       SingleLinkedList<TypeName> variableName(arr, arrSize, insertFormate); 
       ```

其中，```insertFormate```为构造方式，注意使用`sll`命名空间下的`sll::HEAD_INSERT`或`sll::TAIL_INSERT`

