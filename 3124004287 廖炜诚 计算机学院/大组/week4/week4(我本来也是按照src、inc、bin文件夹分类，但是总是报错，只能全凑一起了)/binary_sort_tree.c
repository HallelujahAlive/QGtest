// binary_sort_tree.c
#include "binary_sort_tree.h"
#include <stdlib.h>

// BST ��ʼ��
Status BST_init(BinarySortTreePtr BST) {
    if (BST == NULL) return failed;
    BST->root = NULL;  // �����ڵ�ָ����Ϊ NULL
    return succeed;
}

// BST ����
Status BST_insert(BinarySortTreePtr BST, ElemType value) {
    if (BST == NULL) return failed;
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));  // Ϊ�½ڵ�����ڴ�
    if (newNode == NULL) return failed;  // �ڴ����ʧ��
    newNode->value = value;
    newNode->left = newNode->right = NULL;

    if (BST->root == NULL) {  // �����Ϊ�գ��½ڵ��Ϊ���ڵ�
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
            free(newNode);  // Ԫ���Ѵ��ڣ��ͷ��½ڵ��ڴ�
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

// BST ����
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

// �ҵ���С�ڵ�
NodePtr findMin(NodePtr node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// BST ɾ��
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

    if (current == NULL) return failed;  // δ�ҵ�Ҫɾ���Ľڵ�

    // ��� 1: û���ӽڵ��ֻ��һ���ӽڵ�
    if (current->left == NULL || current->right == NULL) {
        NodePtr temp;
        if (current->left == NULL) {
            temp = current->right;
        } else {
            temp = current->left;
        }

        if (parent == NULL) {  // ���ɾ�����Ǹ��ڵ�
            BST->root = temp;
        } else if (current == parent->left) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        free(current);
    } 
    // ��� 2: �������ӽڵ�
    else {
        NodePtr temp = findMin(current->right);
        current->value = temp->value;
        BST_delete((BinarySortTreePtr){current}, temp->value);
    }
    return succeed;
}

// ǰ������ݹ�
void BST_preorderR(NodePtr node, void (*visit)(NodePtr)) {
    if (node != NULL) {
        visit(node);
        BST_preorderR(node->left, visit);
        BST_preorderR(node->right, visit);
    }
}

// ǰ������ǵݹ�
Status BST_preorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST == NULL || BST->root == NULL) return failed;
    NodePtr stack[100];  // �򵥵�ջʵ��
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

// ��������ݹ�
void BST_inorderR(NodePtr node, void (*visit)(NodePtr)) {
    if (node != NULL) {
        BST_inorderR(node->left, visit);
        visit(node);
        BST_inorderR(node->right, visit);
    }
}

// ��������ǵݹ�
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

// ��������ݹ�
void BST_postorderR(NodePtr node, void (*visit)(NodePtr)) {
    if (node != NULL) {
        BST_postorderR(node->left, visit);
        BST_postorderR(node->right, visit);
        visit(node);
    }
}

// ��������ǵݹ�
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

// �������
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
