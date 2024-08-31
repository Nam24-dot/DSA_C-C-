#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Dinh nghia kich thuoc toi da cua ngan xep

// Cau truc cua mot ngan xep
struct Stack {
    int arr[MAX];  // Mang luu tru cac phan tu cua ngan xep
    int top;       // Chi so cua phan tu tren cung
};

// Ham khoi tao ngan xep
void initStack(struct Stack* stack) {
    stack->top = -1;  // Dat top ban dau la -1, nghia la ngan xep rong
}

// Ham kiem tra ngan xep co rong khong
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Ham kiem tra ngan xep co day khong
int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

// Ham them phan tu vao ngan xep
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Ngan xep day! Khong the them phan tu %d.\n", value);
        return;
    }
    stack->arr[++stack->top] = value;
    printf("Phan tu %d da duoc them vao ngan xep.\n", value);
}

// Ham lay phan tu tu ngan xep
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Ngan xep rong! Khong the lay phan tu.\n");
        return -1;  // Tra ve gia tri khong hop le de bao loi
    }
    return stack->arr[stack->top--];
}

// Ham xem phan tu tren cung cua ngan xep
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Ngan xep rong!\n");
        return -1;  // Tra ve gia tri khong hop le de bao loi
    }
    return stack->arr[stack->top];
}

int main() {
    struct Stack stack;

    initStack(&stack);  // Khoi tao ngan xep

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Phan tu tren cung cua ngan xep la: %d\n", peek(&stack));

    printf("Phan tu %d da duoc lay ra khoi ngan xep.\n", pop(&stack));
    printf("Phan tu %d da duoc lay ra khoi ngan xep.\n", pop(&stack));

    if (!isEmpty(&stack)) {
        printf("Phan tu tren cung sau khi pop la: %d\n", peek(&stack));
    }

    return 0;
}

