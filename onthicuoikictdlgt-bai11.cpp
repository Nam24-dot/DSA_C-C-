#include <stdio.h>
#include <stdlib.h>

// Dinh nghia cau truc cua mot node trong cay
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Dinh nghia cau truc cua mot node trong danh sach lien ket
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// Ham tao mot node moi cua cay
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Ham tao mot node moi cua danh sach lien ket
ListNode* createListNode(int data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Ham them mot node vao cay nhi phan tim kiem
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Ham tim node co gia tri nho nhat trong cay con ben phai
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Ham xoa mot node khoi cay nhi phan tim kiem
Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    } else if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Truong hop node co 1 hoac 0 con
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Truong hop node co 2 con
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Ham duyet cay theo thu tu NLR (Node-Left-Right)
void preorderTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Ham chuyen cay nhi phan tim kiem sang danh sach lien ket
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
	        printf("3. Duyet cay theo thu tu NRL\n");
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
	                preorderTraversal(root);
	                printf("\n");
	                break;
	            case 4:
	                {
	                    ListNode* head = NULL;
	                    treeToList(root, &head);
	                    printf("Danh sach lien ket tu cay BST: ");
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

