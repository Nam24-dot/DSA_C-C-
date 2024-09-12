#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char hoTen[21];
    char mssv[11];
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
    while (fscanf(file, "%20[^\n]%*c%10[^\n]%*c", 
                  danhSach[*soLuong].hoTen, danhSach[*soLuong].mssv) == 2) {
        for (int i = 0; i < 5; ++i) {
            fscanf(file, "%f", &danhSach[*soLuong].diem[i]);
        }
        fgetc(file); // Doc ky tu newline
        (*soLuong)++;
    }

    fclose(file);
}

void capNhatDiemTrungBinhSinhVien(SinhVien *danhSach, int soLuong, const char *mssv, float diemMoi[5]) {
    for (int i = 0; i < soLuong; ++i) {
        if (strcmp(danhSach[i].mssv, mssv) == 0) {
            memcpy(danhSach[i].diem, diemMoi, sizeof(float) * 5);
            return;
        }
    }
}

int partition(SinhVien *danhSach, int low, int high) {
    float pivot = tinhDiemTrungBinh(&danhSach[high]);
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (tinhDiemTrungBinh(&danhSach[j]) < pivot) {
            i++;
            SinhVien temp = danhSach[i];
            danhSach[i] = danhSach[j];
            danhSach[j] = temp;
        }
    }
    SinhVien temp = danhSach[i + 1];
    danhSach[i + 1] = danhSach[high];
    danhSach[high] = temp;
    return i + 1;
}

void quickSort(SinhVien *danhSach, int low, int high) {
    if (low < high) {
        int pi = partition(danhSach, low, high);
        quickSort(danhSach, low, pi - 1);
        quickSort(danhSach, pi + 1, high);
    }
}

void ghiThongTinSinhVien(const SinhVien *danhSach, int soLuong, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Khong the mo file output.txt");
        return;
    }

    for (int i = 0; i < soLuong; ++i) {
        fprintf(file, "%s\n%s\n", danhSach[i].hoTen, danhSach[i].mssv);
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
    float diemMoi[5] = {9.0, 8.5, 7.5, 9.5, 8.0};

    docThongTinSinhVien(danhSach, &soLuong, "input.txt");

    // Cap nhat diem trung binh cua sinh vien theo MSSV (vi du MSSV la "1234567890")
    capNhatDiemTrungBinhSinhVien(danhSach, soLuong, "1234567890", diemMoi);

    // Sap xep sinh vien theo diem trung binh tang dan
    quickSort(danhSach, 0, soLuong - 1);

    // Ghi ket qua ra file output.txt
    ghiThongTinSinhVien(danhSach, soLuong, "output.txt");

    return 0;
}

