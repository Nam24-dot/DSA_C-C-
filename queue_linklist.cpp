#include <stdio.h>
#include <stdlib.h>

// Dinh nghia mot node cua danh sach lien ket
struct Node {
    int data;
    struct Node* next;
};

// Cau truc cua mot hang doi
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Ham tao mot node moi
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Ham khoi tao hang doi
void initQueue(struct Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Ham kiem tra hang doi co rong khong
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Ham them phan tu vao hang doi
void enqueue(struct Queue* queue, int value) {
    struct Node* node = newNode(value);
    if (isEmpty(queue)) {
        queue->front = queue->rear = node;
        return;
    }
    queue->rear->next = node;
    queue->rear = node;
    printf("Phan tu %d da duoc them vao hang doi.\n", value);
}

// Ham lay phan tu ra khoi hang doi
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Hang doi rong! Khong the lay phan tu.\n");
        return -1; // Tra ve gia tri khong hop le de bao loi
    }
    struct Node* temp = queue->front;
    int value = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return value;
}

// Ham xem phan tu dau hang doi
int front(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Hang doi rong!\n");
        return -1; // Tra ve gia tri khong hop le de bao loi
    }
    return queue->front->data;
}

int main() {
    struct Queue queue;

    initQueue(&queue); // Khoi tao hang doi

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Phan tu dau hang doi la: %d\n", front(&queue));

    printf("Phan tu %d da duoc lay ra khoi hang doi.\n", dequeue(&queue));
    printf("Phan tu %d da duoc lay ra khoi hang doi.\n", dequeue(&queue));

    if (!isEmpty(&queue)) {
        printf("Phan tu dau hang doi sau khi dequeue la: %d\n", front(&queue));
    }

    return 0;
}

