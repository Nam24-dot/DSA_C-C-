#include <stdio.h>
#include <stdlib.h>

// Dinh nghia cau truc cua mot node trong cay AVL
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Dinh nghia cau truc cua mot node trong danh sach lien ket
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// Ham tra ve gia tri lon nhat giua hai so nguyen
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Ham tra ve chieu cao cua mot node
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Ham tao mot node moi cho cay AVL
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Ham quay phai cay con voi goc y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Ham quay trai cay con voi goc x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Ham lay chi so can bang cua node N
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Ham chen mot node moi vao cay AVL
Node* insertNode(Node* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Ham tim node co gia tri nho nhat trong cay con ben phai
Node* findMin(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Ham xoa mot node khoi cay AVL
Node* deleteNode(Node* root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Ham duyet cay theo thu tu LRN (Left-Right-Node)
void postorderTraversal(Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Ham tao mot node moi cua danh sach lien ket
ListNode* createListNode(int data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Ham chuyen cay AVL sang danh sach lien ket
void treeToList(Node* root, ListNode** head) {
    if (root == NULL) {
        return;
    }

    static ListNode* prev = NULL;
    treeToList(root->left, head);

    ListNode* newNode = createListNode(root->data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        prev->next = newNode;
    }
    prev = newNode;

    treeToList(root->right, head);
}

// Ham in danh sach lien ket
void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Them node vao cay\n");
        printf("2. Xoa node khoi cay\n");
        printf("3. Duyet cay theo thu tu LRN\n");
        printf("4. Chuyen cay sang danh sach lien ket\n");
        printf("5. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap gia tri can them: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Duyet cay theo LRN: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 4:
                {
                    ListNode* head = NULL;
                    treeToList(root, &head);
                    printf("Danh sach lien ket tu cay AVL: ");
                    printList(head);
                }
                break;
            case 5:
                exit(0);
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }

    return 0;
}

