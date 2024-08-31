#include <stdio.h>

// Ham tim kiem nhi phan
int timKiemNhiPhan(int arr[], int n, int x) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Kiem tra phan tu o vi tri mid
        if (arr[mid] == x)
            return mid;  // Tra ve chi so cua phan tu neu tim thay

        // Neu x lon hon, bo qua phan ben trai
        if (arr[mid] < x)
            left = mid + 1;
        // Neu x nho hon, bo qua phan ben phai
        else
            right = mid - 1;
    }
    return -1;  // Tra ve -1 neu khong tim thay phan tu
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};  // Mang da duoc sap xep
    int n = sizeof(arr) / sizeof(arr[0]);  // So phan tu trong mang
    int x = 30;  // Phan tu can tim

    int ketQua = timKiemNhiPhan(arr, n, x);
    if (ketQua != -1) {
        printf("Phan tu duoc tim thay tai vi tri %d\n", ketQua);
    } else {
        printf("Khong tim thay phan tu\n");
    }

    return 0;
}

