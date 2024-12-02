//
// Created by yangc on 2024/8/6.
//

#ifndef DATA_STRUCTURE_MYQUEUE_HPP
#define DATA_STRUCTURE_MYQUEUE_HPP

#include <stack>
class MyQueue {
private:
    std::stack<int> stack;
    std::stack<int> helper;
public:
    MyQueue() {
        stack = std::stack<int>();
        helper = std::stack<int>();
    }

    void push(int x) {
        stack.push(x);
    }

    int pop() {
        while (!stack.empty()) {
            helper.push(stack.top());
            stack.pop();
        }

        int top = helper.top();
        helper.pop();
        while (!helper.empty()) {
            stack.push(helper.top());
            helper.pop();
        }

        return top;
    }

    int peek() {
        while (!stack.empty()) {
            helper.push(stack.top());
            stack.pop();
        }

        int top = helper.top();
        while (!helper.empty()) {
            stack.push(helper.top());
            helper.pop();
        }

        return top;
    }

    bool empty() {
        return stack.empty();
    }
};


#endif //DATA_STRUCTURE_MYQUEUE_HPP
