#include "Tree/ycBiNode.hpp"
#include "Tree/ycBinaryTree.hpp"
#include <iostream>
#include <vector>
using namespace std;

void printNode(int data) {
    cout << data << " ";
}

int main() {
    // 1. 创建一个二叉树实例
    ycBiTree<int> tree;

    // 2. 使用 insertAsRoot 插入根节点
    auto root = tree.insertAsRoot(1);
    cout << "Inserted root: " << root->data << endl;

    // 3. 插入左、右子节点
    auto leftChild = tree.insertAsLC(root, 2);
    auto rightChild = tree.insertAsRC(root, 3);
    cout << "Inserted left child: " << leftChild->data << endl;
    cout << "Inserted right child: " << rightChild->data << endl;

    // 4. 插入更多节点
    tree.insertAsLC(leftChild, 4);
    tree.insertAsRC(leftChild, 5);
    tree.insertAsLC(rightChild, 6);
    tree.insertAsRC(rightChild, 7);

    // 5. 遍历树
    cout << "Level-order traversal: ";
    tree.travLevel(printNode);
    cout << endl;

    cout << "Pre-order traversal: ";
    tree.travPre(printNode);
    cout << endl;

    cout << "In-order traversal: ";
    tree.travIn(printNode);
    cout << endl;

    cout << "Post-order traversal: ";
    tree.travPost(printNode);
    cout << endl;

    // 6. 交换左右子树
    tree.swap();
    cout << "After swapping left and right subtrees:" << endl;

    cout << "Level-order traversal: ";
    tree.travLevel(printNode);
    cout << endl;

    // 7. 测试最小深度
    cout << "Minimum depth of the tree: " << tree.minDepth() << endl;

    return 0;
}

