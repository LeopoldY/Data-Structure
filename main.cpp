# include <iostream>
# include "Stack&Queue/Stack.hpp"
# include "Stack&Queue/Queue.hpp"
# include "Tree/BinaryTree.hpp"
# include <vector>

#define NULL_VALUE INT_MIN

class Solution {
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
public:
    // 1. 判断两棵树是否相同
    template<typename T>
    bool isSameTree(BinaryTreeNode<T> *p, BinaryTreeNode<T> *q) {
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

//        return isMirrorTree(root->left, root->right);
        Stack<BinTreeNodePtr(T)> s(100);
        s.push(root->left);
        s.push(root->right);

        while (!s.isEmpty()) {
            BinaryTreeNode<int> *right = s.top();
            s.pop();
            BinaryTreeNode<int> *left = s.top();
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
            BinaryTreeNode<T>* current = queue.getFront();
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
            BinaryTreeNode<T>* node = stack.top();
            stack.pop();
            std::cout << node->data << " ";
        }
        std::cout << std::endl;
    }

    // 5. 二叉树的最近公共祖先 *
    template<typename T>
    BinTreeNodePtr(T) findLCA(BinTreeNodePtr(T) root, BinTreeNodePtr(T) p, BinTreeNodePtr(T) q){
        if (root == nullptr || root == p || root == q) return root;
        // ???
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
    BinTreeNodePtr(T) tree2List(BinTreeNodePtr(T) root) {

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

        /*
         * 0: parent of x
         * 1: depth of x
         * 2: parent of y
         * 3: depth of y
         */
        int NodeInfo[4] = {0,0,0,0};
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
                        NodeInfo[0] = curr->data;
                        NodeInfo[1] = depth;
                    }
                    if (curr->left->data == y) {
                        NodeInfo[2] = curr->data;
                        NodeInfo[3] = depth;
                    }
                    q.push(curr->left);
                }

                if (curr->right){
                    if (curr->right->data == x) {
                        NodeInfo[0] = curr->data;
                        NodeInfo[1] = depth;
                    }
                    if (curr->right->data == y) {
                        NodeInfo[2] = curr->data;
                        NodeInfo[3] = depth;
                    }
                    q.push(curr->right);
                }

                if (NodeInfo[1] != 0 && NodeInfo[3] != 0) {
                    return NodeInfo[1] == NodeInfo[3] && NodeInfo[0] != NodeInfo[2];
                }

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


int main() {
    Solution solution;
    BinaryTreeNode<int>* root = new BinaryTreeNode<int>(1);
    root->left = new BinaryTreeNode<int>(10);
    root->right = new BinaryTreeNode<int>(4);
    root->left->left = new BinaryTreeNode<int>(3);
    root->right->left = new BinaryTreeNode<int>(7);
    root->right->right = new BinaryTreeNode<int>(9);
    root->left->left->left = new BinaryTreeNode<int>(12);
    root->left->left->right = new BinaryTreeNode<int>(8);
    root->right->left->left = new BinaryTreeNode<int>(6);
    root->right->right->right = new BinaryTreeNode<int>(2);

    bool result = solution.isEvenOddTree(root);
    std::cout << (result ? "true" : "false") << std::endl;

    return 0;
}
