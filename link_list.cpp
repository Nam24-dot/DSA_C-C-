#include <stdio.h>
#include <stdlib.h>

// Dinh nghia mot node cua danh sach lien ket
struct Node {
    int data;
    struct Node* next;
};

// Ham chen mot node moi vao dau danh sach lien ket
void insertAtHead(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Ham chen mot node moi vao cuoi danh sach lien ket
void insertAtEnd(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
    return;
}

// Ham xoa mot node co khoa cho truoc
void deleteNode(struct Node** head_ref, int key) {
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

// Ham in cac phan tu trong danh sach lien ket
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    insertAtEnd(&head, 6);
    insertAtHead(&head, 7);
    insertAtHead(&head, 1);
    insertAtEnd(&head, 4);
    insertAtHead(&head, 8);

    printf("Danh sach lien ket: ");
    printList(head);

    deleteNode(&head, 1);
    printf("Danh sach lien ket sau khi xoa 1: ");
    printList(head);

    return 0;
}

