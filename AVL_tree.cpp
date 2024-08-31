#include <stdio.h>
#include <stdlib.h>

// Dinh nghia cau truc mot node cua cay AVL
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Ham lay gia tri max
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Ham lay chieu cao cua node
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Ham tao mot node moi
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Node moi tao co chieu cao la 1
    return(node);
}

// Ham quay trai
struct Node *rotateLeft(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Thuc hien quay
    y->left = x;
    x->right = T2;

    // Cap nhat chieu cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Tra ve node moi
    return y;
}

// Ham quay phai
struct Node *rotateRight(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Thuc hien quay
    x->right = y;
    y->left = T2;

    // Cap nhat chieu cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Tra ve node moi
    return x;
}

// Ham lay chi so can bang cua node N
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Ham chen mot node vao cay AVL
struct Node* insert(struct Node* node, int data) {
    if (node == NULL)
        return(newNode(data));

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Gia tri trung, khong chen
        return node;

    // Cap nhat chieu cao cho node to tien
    node->height = 1 + max(height(node->left), height(node->right));

    // Lay chi so can bang de kiem tra node co can bang hay khong
    int balance = getBalance(node);

    // Neu node bi mat can bang, co 4 truong hop

    // Truong hop Left Left
    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    // Truong hop Right Right
    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    // Truong hop Left Right
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Truong hop Right Left
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Ham duyet cay theo thu tu giua (Inorder)
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Duyet cay theo thu tu giua (Inorder traversal) cua cay AVL: ");
    inOrder(root);

    return 0;
}

