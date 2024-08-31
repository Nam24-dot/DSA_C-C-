#include <stdio.h>

// Ham tim kiem tuyen tinh
int timKiemTuyenTinh(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;  // Tra ve chi so cua phan tu neu tim thay
        }
    }
    return -1;  // Tra ve -1 neu khong tim thay phan tu
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};  // Mang can tim kiem
    int n = sizeof(arr) / sizeof(arr[0]);  // So phan tu trong mang
    int x = 30;  // Phan tu can tim

    int ketQua = timKiemTuyenTinh(arr, n, x);
    if (ketQua != -1) {
        printf("Phan tu duoc tim thay tai vi tri %d\n", ketQua);
    } else {
        printf("Khong tim thay phan tu\n");
    }

    return 0;
}

