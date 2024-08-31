#include <stdio.h>
#include <stdlib.h>

// Dinh nghia cau truc mot node cua cay nhi phan
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Ham tao mot node moi
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

// Ham duyet cay theo thu tu truoc (Preorder)
void preOrder(struct Node* node) {
    if (node == NULL)
        return;

    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}

// Ham duyet cay theo thu tu giua (Inorder)
void inOrder(struct Node* node) {
    if (node == NULL)
        return;

    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}

// Ham duyet cay theo thu tu sau (Postorder)
void postOrder(struct Node* node) {
    if (node == NULL)
        return;

    postOrder(node->left);
    postOrder(node->right);
    printf("%d ", node->data);
}

int main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printf("Duyet cay theo thu tu truoc (Preorder traversal): ");
    preOrder(root);

    printf("\nDuyet cay theo thu tu giua (Inorder traversal): ");
    inOrder(root);

    printf("\nDuyet cay theo thu tu sau (Postorder traversal): ");
    postOrder(root);

    return 0;
}

