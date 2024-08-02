//
// Created by yangc on 2024/8/2.
//

#ifndef DATA_STRUCTURE_BINARYTREE_HPP
#define DATA_STRUCTURE_BINARYTREE_HPP

# include <iostream>
# include <queue>
# include <vector>

#define BinTreeNodePtr(T) BinaryTreeNode<T> *

template <typename T>
class BinaryTreeNode {
public:
    T data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;

    BinaryTreeNode(T data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename T>
class BinaryTree {
private:
    BinTreeNodePtr(T) root; // 根节点
    void destroy(BinTreeNodePtr(T) node) {
        if (node == nullptr) {
            return;
        }

        destroy(node->left);
        destroy(node->right);
        delete node;
    }
public:
    BinaryTree() { // 构造函数
        this->root = nullptr;
    }

    BinaryTree(BinTreeNodePtr(T) p): root(p){} // 从给出根节点构造

    BinaryTree(const std::vector<T>& arr, T nullValue) {
        if (arr.empty() || arr[0] == nullValue) return;

        // 创建根节点
        this->root = new BinaryTreeNode<T>(arr[0]);
        std::queue<BinTreeNodePtr(T)> queue;
        queue.push(root);

        int i = 1;
        while (!queue.empty()) {
            BinTreeNodePtr(T) current = queue.front();
            queue.pop();

            // 处理左子节点
            if (i < arr.size() && arr[i] != nullValue) {
                current->left = new BinaryTreeNode<T>(arr[i]);
                queue.push(current->left);
            }
            i++;

            // 处理右子节点
            if (i < arr.size() && arr[i] != nullValue) {
                current->right = new BinaryTreeNode<T>(arr[i]);
                queue.push(current->right);
            }
            i++;
        }
    } // 从二叉树顺序存储序列构造

    ~BinaryTree() { // 析构函数
        destroy(this->root);
    }

    void inOrder(BinTreeNodePtr(T) node) {
        if (node == nullptr) {
            return;
        }

        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

    void preOrder(BinTreeNodePtr(T) node) {
        if (node == nullptr) {
            return;
        }

        std::cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(BinTreeNodePtr(T) node) {
        if (node == nullptr) {
            return;
        }

        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->data << " ";
    }

    void levelOrder(BinTreeNodePtr(T) node) {
        if (node == nullptr) {
            return;
        }

        std::queue<BinaryTreeNode<T> *> q;
        q.push(node);

        while (!q.empty()) {
            BinaryTreeNode<T> *cur = q.front();
            q.pop();

            std::cout << cur->data << " ";

            if (cur->left != nullptr) {
                q.push(cur->left);
            }

            if (cur->right != nullptr) {
                q.push(cur->right);
            }
        }
    }

    BinTreeNodePtr(T) getRoot() {
        return this->root;
    }
};

#endif //DATA_STRUCTURE_BINARYTREE_HPP
