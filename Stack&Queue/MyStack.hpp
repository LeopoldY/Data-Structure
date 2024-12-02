//
// Created by yangc on 2024/8/6.
//

#ifndef DATA_STRUCTURE_MYSTACK_HPP
#define DATA_STRUCTURE_MYSTACK_HPP

#include <queue>
class MyStack {
private:
    std::queue<int> queue;
    std::queue<int> helper;
public:
    MyStack() {
        queue = std::queue<int>();
        helper = std::queue<int>();
    }

    void push(int x) {
        queue.push(x);
    }

    int pop() {
        while (queue.size() > 1) {
            helper.push(queue.front());
            queue.pop();
        }

        int top = queue.front();
        queue.pop();
        while (!helper.empty()) {
            queue.push(helper.front());
            helper.pop();
        }

        return top;
    }

    int top() {
        while (queue.size() > 1) {
            helper.push(queue.front());
            queue.pop();
        }

        int top = queue.front();
        helper.push(queue.front());
        queue.pop();
        while (!helper.empty()) {
            queue.push(helper.front());
            helper.pop();
        }

        return top;
    }

    bool empty() {
        return queue.empty();
    }
};


#endif //DATA_STRUCTURE_MYSTACK_HPP
