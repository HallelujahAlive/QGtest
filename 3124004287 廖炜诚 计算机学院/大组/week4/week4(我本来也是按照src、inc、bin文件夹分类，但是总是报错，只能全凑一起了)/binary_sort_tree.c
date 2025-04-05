// binary_sort_tree.c
#include "binary_sort_tree.h"
#include <stdlib.h>

// BST 初始化
Status BST_init(BinarySortTreePtr BST) {
    if (BST == NULL) return failed;
    BST->root = NULL;  // 将根节点指针置为 NULL
    return succeed;
}

// BST 插入
Status BST_insert(BinarySortTreePtr BST, ElemType value) {
    if (BST == NULL) return failed;
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));  // 为新节点分配内存
    if (newNode == NULL) return failed;  // 内存分配失败
    newNode->value = value;
    newNode->left = newNode->right = NULL;

    if (BST->root == NULL) {  // 如果树为空，新节点成为根节点
        BST->root = newNode;
        return succeed;
    }

    NodePtr current = BST->root;
    NodePtr parent = NULL;
    while (current != NULL) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            free(newNode);  // 元素已存在，释放新节点内存
            return failed;
        }
    }

    if (value < parent->value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return succeed;
}

// BST 查找
Status BST_search(BinarySortTreePtr BST, ElemType value) {
    if (BST == NULL || BST->root == NULL) return false;
    NodePtr current = BST->root;
    while (current != NULL) {
        if (value == current->value) {
            return true;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

// 找到最小节点
NodePtr findMin(NodePtr node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// BST 删除
Status BST_delete(BinarySortTreePtr BST, ElemType value) {
    if (BST == NULL || BST->root == NULL) return failed;
    NodePtr current = BST->root;
    NodePtr parent = NULL;
    while (current != NULL && current->value != value) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) return failed;  // 未找到要删除的节点

    // 情况 1: 没有子节点或只有一个子节点
    if (current->left == NULL || current->right == NULL) {
        NodePtr temp;
        if (current->left == NULL) {
            temp = current->right;
        } else {
            temp = current->left;
        }

        if (parent == NULL) {  // 如果删除的是根节点
            BST->root = temp;
        } else if (current == parent->left) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        free(current);
    } 
    // 情况 2: 有两个子节点
    else {
        NodePtr temp = findMin(current->right);
        current->value = temp->value;
        BST_delete((BinarySortTreePtr){current}, temp->value);
    }
    return succeed;
}

// 前序遍历递归
void BST_preorderR(NodePtr node, void (*visit)(NodePtr)) {
    if (node != NULL) {
        visit(node);
        BST_preorderR(node->left, visit);
        BST_preorderR(node->right, visit);
    }
}

// 前序遍历非递归
Status BST_preorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST == NULL || BST->root == NULL) return failed;
    NodePtr stack[100];  // 简单的栈实现
    int top = -1;
    stack[++top] = BST->root;

    while (top >= 0) {
        NodePtr current = stack[top--];
        visit(current);

        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
    return succeed;
}

// 中序遍历递归
void BST_inorderR(NodePtr node, void (*visit)(NodePtr)) {
    if (node != NULL) {
        BST_inorderR(node->left, visit);
        visit(node);
        BST_inorderR(node->right, visit);
    }
}

// 中序遍历非递归
Status BST_inorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST == NULL || BST->root == NULL) return failed;
    NodePtr stack[100];
    int top = -1;
    NodePtr current = BST->root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        visit(current);
        current = current->right;
    }
    return succeed;
}

// 后序遍历递归
void BST_postorderR(NodePtr node, void (*visit)(NodePtr)) {
    if (node != NULL) {
        BST_postorderR(node->left, visit);
        BST_postorderR(node->right, visit);
        visit(node);
    }
}

// 后序遍历非递归
Status BST_postorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST == NULL || BST->root == NULL) return failed;
    NodePtr stack1[100], stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = BST->root;

    while (top1 >= 0) {
        NodePtr current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL) {
            stack1[++top1] = current->left;
        }
        if (current->right != NULL) {
            stack1[++top1] = current->right;
        }
    }

    while (top2 >= 0) {
        visit(stack2[top2--]);
    }
    return succeed;
}

// 层序遍历
Status BST_levelOrder(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST == NULL || BST->root == NULL) return failed;
    NodePtr queue[100];
    int front = 0, rear = 0;
    queue[rear++] = BST->root;

    while (front < rear) {
        NodePtr current = queue[front++];
        visit(current);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    return succeed;
}
