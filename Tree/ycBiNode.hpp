//
// Created by yangc on 25-1-10.
//

#pragma once
#include <queue>

#define ycBiNodePosi(T) ycBiNode<T> * // 二叉树节点位置

template <typename T>
struct ycBiNode {
    T data; // 数据
    ycBiNode *parent; // 父节点
    ycBiNode *left; // 左孩子
    ycBiNode *right; // 右孩子
    int height; // 高度

    ycBiNode(T data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->height = 0;
    }

    int size() { // 后代总数
        int s = 1;
        if (left) s += left->size();
        if (right) s += right->size();
        return s;
    }

    ycBiNodePosi(T) insertAsLeftChild(T const &e) {
        return left = new ycBiNode(e);
    }

    ycBiNodePosi(T) insertAsRightChild(T const &e) {
        return right = new ycBiNode(e);
    }

    ycBiNodePosi(T) succ() { // 中序遍历意义下的直接后继
        ycBiNodePosi(T) s = this;
        if (right) {
            s = right;
            while (HasLChild(*s)) {
                s = s->left;
            }
        } else {
            while (IsRChild(*s)) {
                s = s->parent;
            }
            s = s->parent;
        }
        return s;
    }

    template <typename VST> void travLevel(VST &visit) { // 子树层次遍历
        std::queue<ycBiNodePosi(T)> q;
        q.push(this);
        while (!q.empty()) {
            ycBiNodePosi(T) x = q.front();
            q.pop();
            visit(x->data);
            if (x->left) q.push(x->left);
            if (x->right) q.push(x->right);
        }
    }

    template <typename VST> void travPre(VST &visit) {
        travPre_R(this, visit);
    }

    template <typename VST> void travIn(VST &visit) {
        travIn_R(this, visit);
    }

    template <typename VST> void travPost(VST &visit) {
        travPost_R(this, visit);
    }

    template <typename VST>
    static void travPre_R(ycBiNodePosi(T) x, VST &visit) {
        if (!x) return;
        visit(x->data);
        travPre_R(x->left, visit);
        travPre_R(x->right, visit);
    }

    template <typename VST>
    static void travIn_R(ycBiNodePosi(T) x, VST &visit) {
        if (!x) return;
        travIn_R(x->left, visit);
        visit(x->data);
        travIn_R(x->right, visit);
    }

    template <typename VST>
    static void travPost_R(ycBiNodePosi(T) x, VST &visit) {
        if (!x) return;
        travPost_R(x->left, visit);
        travPost_R(x->right, visit);
        visit(x->data);
    }
};
