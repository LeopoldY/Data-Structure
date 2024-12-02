//
// Created by yangc on 2024/8/3.
//

#ifndef DATA_STRUCTURE_STACKANDQUEUESOLUTION_HPP
#define DATA_STRUCTURE_STACKANDQUEUESOLUTION_HPP

#include <iostream>
#include <string>
#include "../Stack&Queue/Stack.hpp"
#include "../Stack&Queue/Queue.hpp"


class SQSolution {
public:
    // 1. 有效的括号
    bool isValid(std::string s) {
        Stack<char> stack;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            } else {
                if (stack.isEmpty()) {
                    return false;
                }

                char topChar = stack.pop();
                if (c == ')' && topChar != '(') {
                    return false;
                }
                if (c == ']' && topChar != '[') {
                    return false;
                }
                if (c == '}' && topChar != '{') {
                    return false;
                }
            }
        }

        return stack.isEmpty();
    }

    // 2. 逆波兰式求值
    int evalRPN(std::vector<std::string> &tokens) {
        Stack<int> stack;
        for (const std::string &token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int num2 = stack.pop();
                int num1 = stack.pop();
                switch (token[0]) {
                    case '+':
                        stack.push(num1 + num2);
                        break;
                    case '-':
                        stack.push(num1 - num2);
                        break;
                    case '*':
                        stack.push(num1 * num2);
                        break;
                    case '/':
                        stack.push(num1 / num2);
                        break;
                }
            } else {
                stack.push(std::stoi(token));
            }
        }

        return stack.pop();
    }
};

#endif //DATA_STRUCTURE_STACKANDQUEUESOLUTION_HPP
