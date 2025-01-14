//
// Created by yangc on 2024/8/3.
//

#ifndef DATA_STRUCTURE_TREESOLUTION_HPP
#define DATA_STRUCTURE_TREESOLUTION_HPP

#include "../Tree/ycBinaryTree.hpp"
#include "../Stack&Queue/Stack.hpp"
#include "../Stack&Queue/Queue.hpp"
#include <vector>

class TreeSolution {
private:
    template<typename T>
    bool isMirrorTree(BinTreeNodePtr(T) p, BinTreeNodePtr(T) q) {
        if (p == nullptr && q == nullptr) return true;
        if (p == nullptr || q == nullptr) return false;

        return p->data == q->data &&
               isMirrorTree(p->left, q->right) &&
               isMirrorTree(p->right, q->left);
    }

    template<typename T>
    int height(BinTreeNodePtr(T) root) {
        if (!root) return 0;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (leftHeight == -1 || rightHeight == -1 || abs(rightHeight - leftHeight) > 1) return -1;

        return std::max(leftHeight, rightHeight) + 1;
    }

    template<typename T>
    BinTreeNodePtr(T) findMin(BinTreeNodePtr(T) root) {
        while (root->left) {
            root = root->left;
        }
        return root;
    }
public:
    // 1. 判断两棵树是否相同
    template<typename T>
    bool isSameTree(ycBiNode<T> *p, ycBiNode<T> *q) {
        if (p == nullptr && q == nullptr) return true;
        if (p == nullptr || q == nullptr) return false;

        return p->data == q->data &&
               isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }

    // 2. 判断是否为对称二叉树
    template<typename T>
    bool isSymmetric(BinTreeNodePtr(T) root) {
        if (root == nullptr) return true;
        if (root->left == nullptr && root->right == nullptr) return true;
        if (root->left == nullptr || root->right == nullptr) return false;

//        return isMirrorTree(_root->left, _root->right);
        Stack<BinTreeNodePtr(T)> s(100);
        s.push(root->left);
        s.push(root->right);

        while (!s.isEmpty()) {
            ycBiNode<int> *right = s.top();
            s.pop();
            ycBiNode<int> *left = s.top();
            s.pop();

            if (left == nullptr && right == nullptr) continue;
            if (left == nullptr || right == nullptr) return false;
            if (left->data != right->data) return false;

            s.push(left->left);
            s.push(right->right);
            s.push(left->right);
            s.push(right->left);
        }

        return true;
    }

    // 3. 二叉树最大深度
    template<typename T>
    int maxDepth(BinTreeNodePtr(T) root) {
        if (root == nullptr) return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    // 4. 二叉树的逆序层序遍历
    template<typename T>
    void reversedLevelOrder(BinTreeNodePtr(T) root) {
        if (root == nullptr) {
            return;
        }

        Queue<BinTreeNodePtr(T)> queue;
        Stack<BinTreeNodePtr(T)> stack;

        queue.push(root);

        while (!queue.isEmpty()) {
            ycBiNode<T>* current = queue.getFront();
            queue.pop();
            stack.push(current);

            // 先推入右子节点，再推入左子节点，这样出栈时先输出左子节点
            if (current->right) {
                queue.push(current->right);
            }
            if (current->left) {
                queue.push(current->left);
            }
        }

        // 输出逆序层序遍历结果
        while (!stack.isEmpty()) {
            ycBiNode<T>* node = stack.top();
            stack.pop();
            std::cout << node->data << " ";
        }
        std::cout << std::endl;
    }

    // 5. 二叉树的最近公共祖先 *
    template<typename T>
    BinTreeNodePtr(T) findLCA(BinTreeNodePtr(T) root, BinTreeNodePtr(T) p, BinTreeNodePtr(T) q){
        if (root == nullptr || root == p || root == q) return root;

        BinTreeNodePtr(T) left = findLCA(root->left, p, q);
        BinTreeNodePtr(T) right = findLCA(root->right, p, q);

        if (left && right) return root;

        return left ? left : right;
    }

    // 6. 判断是否为平衡二叉树
    template<typename T>
    bool isAVL(BinTreeNodePtr(T) root) {
        if (root == nullptr) return true;
        return height(root) != -1;
    }

    // 7. 路径总和
    template<typename T>
    bool isExistPath(BinTreeNodePtr(T) root, int targetSum) {
        if (root == nullptr) {
            return false;
        }

        // 如果是叶子节点，检查路径和是否等于targetSum
        if (root->left == nullptr && root->right == nullptr) {
            return root->data == targetSum;
        }

        // 递归检查左右子树
        int newSum = targetSum - root->data;
        return isExistPath(root->left, newSum) || isExistPath(root->right, newSum);
    }

    // 8. 二叉树转换单链表 *
    template<typename T>
    void tree2List(BinTreeNodePtr(T) root) {
        if (!root) return;

        tree2List(root->left);
        tree2List(root->right);

        BinTreeNodePtr(T) right = root->right;
        root->right = root->left;
        root->left = nullptr;
        BinTreeNodePtr(T) p = root;
        while (p->right) {
            p = p->right;
        }

        p->right = right;
    }

    // 9. 二叉树的右视图
    template<typename T>
    std::vector<T> rightView(BinTreeNodePtr(T) root) {
        std::vector<T> result;
        if (!root) return result;

        Queue<BinTreeNodePtr(T)> q;
        q.push(root);

        while(!q.isEmpty()) { // 层序遍历
            T rightMostVal = 0;
            int levelSize = q.getLength();
            for (int i = 0; i < levelSize; i++) {
                BinTreeNodePtr(T) curr = q.getFront();
                q.pop();

                rightMostVal = curr->data; // 记录当前层最右侧的数值

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            result.push_back(rightMostVal);

        }
        return result;
    }

    // 10. 找出二叉树每行最大值
    template<typename T>
    std::vector<T> maxPerLevel(BinTreeNodePtr(T) root) {
        std::vector<T> result;
        if (!root) return result;

        Queue<BinTreeNodePtr(T)> q;
        q.push(root);

        while (!q.isEmpty()) {
            int levelSize = q.getLength();
            T maxVal = q.getFront()->data;

            for (int i = 0; i < levelSize; i++) {
                BinTreeNodePtr(T) curr = q.getFront();
                q.pop();

                maxVal = std::max(maxVal, curr->data);

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            result.push_back(maxVal);
        }
        return result;
    }

    // 11. 最左下角的值
    template<typename T>
    T findBottomLeftValue(BinTreeNodePtr(T) root) {
        if (!root) return T();

        Queue<BinTreeNodePtr(T)> q;
        q.push(root);

        T result;
        while (!q.isEmpty()) {
            int levelSize = q.getLength();
            result = q.getFront()->data;
            for (int i = 0; i < levelSize; i++) {
                BinTreeNodePtr(T)curr = q.getFront();
                q.pop();

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        return result;
    }

    // 12. 翻转二叉树
    template<typename T>
    BinTreeNodePtr(T) invertTree(BinTreeNodePtr(T) root) {
        if (!root) return nullptr;

        BinTreeNodePtr(T) left = invertTree(root->left);
        BinTreeNodePtr(T) right = invertTree(root->right);

        root->left = right;
        root->right = left;

        return root;
    }

    // 13. 二叉树的直径
    template<typename T>
    int diameterOfBinaryTree(BinTreeNodePtr(T) root) {
        if (!root) return 0;

        int leftHeight = maxDepth(root->left);
        int rightHeight = maxDepth(root->right);

        int leftDiameter = diameterOfBinaryTree(root->left);
        int rightDiameter = diameterOfBinaryTree(root->right);

        return std::max(leftHeight + rightHeight, std::max(leftDiameter, rightDiameter));
    }

    // 14. 二叉搜索树的删除节点操作 *
    template<typename T>
    BinTreeNodePtr(T) deleteNode(BinTreeNodePtr(T) root, T key) {
        if (root == nullptr) return nullptr;

        // 找到要删除的节点
        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                BinTreeNodePtr(T) temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BinTreeNodePtr(T) temp = root->left;
                delete root;
                return temp;
            }
        }

        // 有两个子节点
        BinTreeNodePtr(T) temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);

        return root;

    }

    // 15. 合并二叉树
    template<typename T>
    BinTreeNodePtr(T) mergeTrees(BinTreeNodePtr(T) t1, BinTreeNodePtr(T) t2) {
        if (!t1) return t2;
        if (!t2) return t1;

        t1->data += t2->data;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);

        return t1;
    }

    // 16. 二叉树的堂兄弟节点
    template<typename T>
    bool isCousin(BinTreeNodePtr(T) root, T x, T y) {
        if (!root || root->data == x || root->data == y) return false;

        int xParent = 0, yParent = 0, xDepth = 0, yDepth = 0;
        int depth = 0;

        Queue<BinTreeNodePtr(T)> q;
        q.push(root);

        while(!q.isEmpty()) {
            depth++;
            int levelSize = q.getLength();

            for (int i = 0; i < levelSize; i++){
                BinTreeNodePtr(T) curr = q.getFront();
                q.pop();

                if (curr->left){
                    if (curr->left->data == x) {
                        xParent = curr->data;
                        xDepth = depth;
                    }
                    if (curr->left->data == y) {
                        yParent = curr->data;
                        yDepth = depth;
                    }
                    q.push(curr->left);
                }

                if (curr->right){
                    if (curr->right->data == x) {
                        xParent = curr->data;
                        xDepth = depth;
                    }
                    if (curr->right->data == y) {
                        yParent = curr->data;
                        yDepth = depth;
                    }
                    q.push(curr->right);
                }

                if (xParent && yParent && xParent != yParent && xDepth == yDepth) return true;

            }

        }
        return false;
    }

    // 17. 判断奇偶树
    template<typename T>
    bool isEvenOddTree(BinTreeNodePtr(T) root) {
        if (!root) return false;

        Queue<BinTreeNodePtr(T)> q;
        q.push(root);

        int level = 0;
        while (!q.isEmpty()) {
            int levelSize = q.getLength();
            int prevVal = level % 2 == 0 ? INT_MIN : INT_MAX;

            for (int i = 0; i < levelSize; i++) {
                BinTreeNodePtr(T) curr = q.getFront();
                q.pop();

                if (level % 2 == 0) { // 偶数层
                    if (curr->data % 2 == 0) return false; // 偶数层节点值为奇数
                    if (curr->data <= prevVal) return false;
                } else { // 奇数层
                    if (curr->data % 2 != 0) return false; // 奇数层节点值为偶数
                    if (curr->data >= prevVal) return false;
                }

                prevVal = curr->data;

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            level++;
        }
        return true;
    }
};


#endif //DATA_STRUCTURE_TREESOLUTION_HPP
