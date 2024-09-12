#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char hoTen[21];
    char mssv[11];
    char ngaySinh[11];
    float diem[5];
} SinhVien;

float tinhDiemTrungBinh(const SinhVien* sv) {
    float sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += sv->diem[i];
    }
    return sum / 5;
}

void docThongTinSinhVien(SinhVien *danhSach, int *soLuong, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Khong the mo file input.txt");
        return;
    }

    *soLuong = 0;
    while (fscanf(file, "%20[^\n]%*c%10[^\n]%*c%10[^\n]%*c", 
                  danhSach[*soLuong].hoTen, danhSach[*soLuong].mssv, danhSach[*soLuong].ngaySinh) == 3) {
        for (int i = 0; i < 5; ++i) {
            fscanf(file, "%f", &danhSach[*soLuong].diem[i]);
        }
        fgetc(file); // Doc ky tu newline
        (*soLuong)++;
    }

    fclose(file);
}

void capNhatHoTenSinhVien(SinhVien *danhSach, int soLuong, const char *mssv, const char *hoTenMoi) {
    for (int i = 0; i < soLuong; ++i) {
        if (strcmp(danhSach[i].mssv, mssv) == 0) {
            strncpy(danhSach[i].hoTen, hoTenMoi, 20);
            danhSach[i].hoTen[20] = '\0'; // Dam bao chuoi ket thuc bang null
            return;
        }
    }
}

void heapify(SinhVien *danhSach, int n, int i) {
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && tinhDiemTrungBinh(&danhSach[left]) > tinhDiemTrungBinh(&danhSach[largest])) {
        largest = left;
    }

    if (right < n && tinhDiemTrungBinh(&danhSach[right]) > tinhDiemTrungBinh(&danhSach[largest])) {
        largest = right;
    }

    if (largest != i) {
        SinhVien temp = danhSach[i];
        danhSach[i] = danhSach[largest];
        danhSach[largest] = temp;
        heapify(danhSach, n, largest);
    }
}

void heapSort(SinhVien *danhSach, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(danhSach, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        SinhVien temp = danhSach[0];
        danhSach[0] = danhSach[i];
        danhSach[i] = temp;
        heapify(danhSach, i, 0);
    }
}

void ghiThongTinSinhVien(const SinhVien *danhSach, int soLuong, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Khong the mo file output.txt");
        return;
    }

    for (int i = 0; i < soLuong; ++i) {
        fprintf(file, "%s\n%s\n%s\n", danhSach[i].hoTen, danhSach[i].mssv, danhSach[i].ngaySinh);
        for (int j = 0; j < 5; ++j) {
            fprintf(file, "%.2f ", danhSach[i].diem[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    SinhVien danhSach[100];
    int soLuong;

    docThongTinSinhVien(danhSach, &soLuong, "input.txt");

    // Cap nhat ten cua sinh vien theo MSSV (vi du MSSV la "1234567890" va ten moi la "Nguyen Van A")
    capNhatHoTenSinhVien(danhSach, soLuong, "1234567890", "Nguyen Van A");

    // Sap xep sinh vien theo diem trung binh tang dan
    heapSort(danhSach, soLuong);

    // Ghi ket qua ra file output.txt
    ghiThongTinSinhVien(danhSach, soLuong, "output.txt");

    return 0;
}

