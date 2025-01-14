//
// Created by yangc on 2024/8/2.
//

#pragma once
# include <iostream>
# include <queue>
# include <vector>
# include "ycBiNode.hpp"

#define NULL_VALUE INT_MIN

template <typename T>
class ycBiTree {
protected:
    ycBiNodePosi(T) _root; // 根节点
    int _size; // 节点数

    virtual int updateHeight(ycBiNodePosi(T) x) {
        return x->height = 1 + std::max(stature(x->left), stature(x->right));
    } // 更新节点x的高度

    void updateHeightAbove(ycBiNodePosi(T) x) {
        while (x) {
            updateHeight(x);
            x = x->parent;
        }
    } // 更新节点x及其祖先的高度

    int _minDepth(ycBiNodePosi(T) node) {
        if (!node) return 0;
        if (!node->left) return _minDepth(node->right) + 1;
        if (!node->right) return _minDepth(node->left) + 1;
        return std::min(_minDepth(node->left), _minDepth(node->right)) + 1;
    }

    void remove(ycBiNodePosi(T) x) {
        if (x->left) remove(x->left);
        if (x->right) remove(x->right);
        delete x;
    }

    int stature(ycBiNodePosi(T) x) { return x ? x->height : -1; } // 节点高度（外部节点高度为0）

public:
    ycBiTree() : _root(nullptr), _size(0) {} // 构造函数
    ycBiTree(ycBiNodePosi(T) x) : _root(x), _size(x->size()) {} // 构造函数
    ~ycBiTree() { if (_size > 0) remove(_root); } // 析构函数

    void creatBinTree (std::vector<char> &str) { // 创建二叉树
        ycBiNodePosi(T) p = nullptr;
        std::queue<ycBiNodePosi(T)> q;
        int i = 0;
        _root = new ycBiNode<T>(str[i++]);
        q.push(_root);
        while (!q.empty()) {
            p = q.front();
            q.pop();
            if (i < str.size() && str[i] != NULL_VALUE) {
                p->left = new ycBiNode<T>(str[i]);
                p->left->parent = p;
                q.push(p->left);
            }
            i++;
            if (i < str.size() && str[i] != NULL_VALUE) {
                p->right = new ycBiNode<T>(str[i]);
                p->right->parent = p;
                q.push(p->right);
            }
            i++;
        }
    }

    int size() const { return _size; } // 规模
    bool empty() const { return !_root; } // 判空
    ycBiNodePosi(T) root() const { return _root; } // 树根

    ycBiNodePosi(T) insertAsRoot(T const &e) { // 插入根节点
        static_assert(!_root, "Root exists");
        _size = 1;
        return _root = new ycBiNode<T>(e);
    }

    ycBiNodePosi(T) insertAsLC(ycBiNodePosi(T) x, T const &e) { // e作为x的左孩子插入
        _size++;
        x->insertAsLeftChild(e);
        updateHeightAbove(x);
        return x->left;
    }

    ycBiNodePosi(T) insertAsRC(ycBiNodePosi(T) x, T const &e) { // e作为x的右孩子插入
        _size++;
        x->insertAsRightChild(e);
        updateHeightAbove(x);
        return x->right;
    }

    ycBiNodePosi(T) attachAsLC(ycBiNodePosi(T) x, ycBiTree<T>* &S) { // 将S作为x的左子树接入
        if (x->left == S->_root) x->left->parent = x;
        _size += S->_size;
        updateHeightAbove(x);
        S->_root = nullptr;
        S->_size = 0;
        delete S;
        S = nullptr;
        return x;
    }

    ycBiNodePosi(T) attachAsRC(ycBiNodePosi(T) x, ycBiTree<T>* &S) { // 将S作为x的右子树接入
        if (x->right == S->_root) x->right->parent = x;
        _size += S->_size;
        updateHeightAbove(x);
        S->_root = nullptr;
        S->_size = 0;
        delete S;
        S = nullptr;
        return x;
    }

    template<typename VST>
    void travLevel(VST &visit) { // 层次遍历
        if (_root) _root->travLevel(visit);
    }

    template<typename VST>
    void travPre(VST &visit) { // 先序遍历
        if (_root) _root->travPre(visit);
    }

    template<typename VST>
    void travIn(VST &visit) { // 中序遍历
        if (_root) _root->travIn(visit);
    }

    template<typename VST>
    void travPost(VST &visit) { // 后序遍历
        if (_root) _root->travPost(visit);
    }

    ycBiTree<T>* secede(ycBiNodePosi(T) x) { // 将子树x从当前树中摘除，并将其转换为一棵独立的树
        // 更新规模
        if (x->parent) {
            if (IsLChild(*x)) x->parent->left = nullptr;
            else x->parent->right = nullptr;
            updateHeightAbove(x->parent);
        }
        _size -= x->size();
        // 更新高度
        updateHeightAbove(x->parent);
        // 返回分离出来的子树
        return new ycBiTree<T>(x);
    }

    void swap() {
        swapSubtree(_root); // 从根节点开始递归交换左右子树
    }

    void swapSubtree(ycBiNodePosi(T)node) {
        if (!node) return; // 如果节点为空，直接返回
        std::swap(node->left, node->right); // 交换当前节点的左、右子树
        swapSubtree(node->left); // 递归处理左子树
        swapSubtree(node->right); // 递归处理右子树
    }

    int minDepth() {
        return _minDepth(_root);
    }
};
