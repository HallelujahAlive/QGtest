// binary_sort_tree.h
#ifndef BINARY_SORT_TREE_H
#define BINARY_SORT_TREE_H

// ���岼��ֵ��״̬��
#define true 1
#define false 0
#define succeed 1
#define failed 0
#define Status int

// ����Ԫ������
typedef int ElemType;

// ��������������Ľڵ�ṹ
typedef struct Node {
    ElemType value;  // �ڵ��ֵ
    struct Node *left, *right;  // �����ӽڵ�ָ��
} Node, *NodePtr;

// ��������������Ľṹ
typedef struct BinarySortTree {
    NodePtr root;  // ���ڵ�ָ��
} BinarySortTree, *BinarySortTreePtr;

// BST ��ʼ��
Status BST_init(BinarySortTreePtr BST);

// BST ����
Status BST_insert(BinarySortTreePtr BST, ElemType value);

// BST ����
Status BST_search(BinarySortTreePtr BST, ElemType value);

// BST ɾ��
Status BST_delete(BinarySortTreePtr BST, ElemType value);

// ǰ������ݹ�
void BST_preorderR(NodePtr node, void (*visit)(NodePtr));

// ǰ������ǵݹ�
Status BST_preorderI(BinarySortTreePtr BST, void (*visit)(NodePtr));

// ��������ݹ�
void BST_inorderR(NodePtr node, void (*visit)(NodePtr));

// ��������ǵݹ�
Status BST_inorderI(BinarySortTreePtr BST, void (*visit)(NodePtr));

// ��������ݹ�
void BST_postorderR(NodePtr node, void (*visit)(NodePtr));

// ��������ǵݹ�
Status BST_postorderI(BinarySortTreePtr BST, void (*visit)(NodePtr));

// �������
Status BST_levelOrder(BinarySortTreePtr BST, void (*visit)(NodePtr));

#endif // BINARY_SORT_TREE_H
