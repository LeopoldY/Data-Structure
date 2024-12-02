# include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "Graph/AdjMatrixGraph.hpp"

class Solution {
private:
    std::vector<int> getNext(std::string str){
        int len = str.size();
        std::vector<int> next(len, 0);
        next[0] = -1;
        int i = 2, j = -1;
        while(i < len - 1){
            if(j == -1 || str[i] == str[j]){
                i++;
                j++;
                next[i] = j;
            }else{
                j = next[j];
            }
        }
        return next;
    }
public:
    // 1. 有效的括号
    bool isValid(std::string s) {
        std::stack<char> stack;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            } else {
                if (stack.empty()) {
                    return false;
                }

                char topChar = stack.top();
                stack.pop();
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

        return stack.empty();
    }

    // 2. 逆波兰式求值
    int evalRPN(std::vector<std::string> &tokens) {
        std::stack<int> stack;
        for (const std::string &token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int num2 = stack.top();
                stack.pop();
                int num1 = stack.top();
                stack.pop();
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

        return stack.top();
    }

    // 3. KMP 算法
    int index_KMP(std::string s, std::string str){
        int i = 0, j = 0;
        int s_len = s.size();
        int str_len = str.size();
        std::vector<int> next = getNext(str);
        while(i < s_len && j < str_len){
            if(j == -1 || s[i] == str[j]){
                i++;
                j++;
            }else{
                j = next[j];
            }
        }
        if(j == str_len){
            return i - j;
        }else{
            return -1;
        }

    }
};

int main() {
    // 示例输入
    MGraph G;
    G.numVex = 6;
    G.numArc = 6;
    G.edge[0][1] = 1; G.edge[0][2] = 1;
    G.edge[1][3] = 1; G.edge[2][3] = 1;
    G.edge[3][4] = 1; G.edge[4][5] = 1;

    if (uniquely(G)) {
        cout << "The graph has a unique topological order.\n";
    } else {
        cout << "The graph does not have a unique topological order.\n";
    }

    return 0;
}