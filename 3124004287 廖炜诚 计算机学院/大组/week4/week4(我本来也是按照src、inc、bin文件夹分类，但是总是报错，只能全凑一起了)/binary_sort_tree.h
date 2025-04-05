// binary_sort_tree.h
#ifndef BINARY_SORT_TREE_H
#define BINARY_SORT_TREE_H

// 定义布尔值和状态码
#define true 1
#define false 0
#define succeed 1
#define failed 0
#define Status int

// 定义元素类型
typedef int ElemType;

// 定义二叉排序树的节点结构
typedef struct Node {
    ElemType value;  // 节点的值
    struct Node *left, *right;  // 左右子节点指针
} Node, *NodePtr;

// 定义二叉排序树的结构
typedef struct BinarySortTree {
    NodePtr root;  // 根节点指针
} BinarySortTree, *BinarySortTreePtr;

// BST 初始化
Status BST_init(BinarySortTreePtr BST);

// BST 插入
Status BST_insert(BinarySortTreePtr BST, ElemType value);

// BST 查找
Status BST_search(BinarySortTreePtr BST, ElemType value);

// BST 删除
Status BST_delete(BinarySortTreePtr BST, ElemType value);

// 前序遍历递归
void BST_preorderR(NodePtr node, void (*visit)(NodePtr));

// 前序遍历非递归
Status BST_preorderI(BinarySortTreePtr BST, void (*visit)(NodePtr));

// 中序遍历递归
void BST_inorderR(NodePtr node, void (*visit)(NodePtr));

// 中序遍历非递归
Status BST_inorderI(BinarySortTreePtr BST, void (*visit)(NodePtr));

// 后序遍历递归
void BST_postorderR(NodePtr node, void (*visit)(NodePtr));

// 后序遍历非递归
Status BST_postorderI(BinarySortTreePtr BST, void (*visit)(NodePtr));

// 层序遍历
Status BST_levelOrder(BinarySortTreePtr BST, void (*visit)(NodePtr));

#endif // BINARY_SORT_TREE_H
