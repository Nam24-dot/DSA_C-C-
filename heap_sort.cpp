#include <stdio.h>

// Ham hoan doi hai phan tu
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Ham tao heap
void heapify(int arr[], int n, int i) {
    int largest = i; // Goc la lon nhat
    int left = 2 * i + 1; // Con trai
    int right = 2 * i + 2; // Con phai

    // Neu con trai lon hon goc
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Neu con phai lon hon goc
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Neu goc khong con lon nhat
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // De quy goi heapify de dam bao heap tinh
        heapify(arr, n, largest);
    }
}

// Ham sap xep heap
void heapSort(int arr[], int n) {
    // Xay dung heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Trich xuat tung phan tu ra khoi heap
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);

        // Goi ham heapify cho heap da rut gon
        heapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);

    printf("Mang sau khi sap xep: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

