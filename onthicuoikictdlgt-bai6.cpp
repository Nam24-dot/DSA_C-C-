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

void capNhatNamSinhSinhVien(SinhVien *danhSach, int soLuong, const char *mssv, const char *namSinhMoi) {
    for (int i = 0; i < soLuong; ++i) {
        if (strcmp(danhSach[i].mssv, mssv) == 0) {
            strncpy(danhSach[i].ngaySinh + 6, namSinhMoi, 4);
            return;
        }
    }
}

void merge(SinhVien *danhSach, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    SinhVien *L = (SinhVien *)malloc(n1 * sizeof(SinhVien));
    SinhVien *R = (SinhVien *)malloc(n2 * sizeof(SinhVien));

    for (int i = 0; i < n1; ++i)
        L[i] = danhSach[l + i];
    for (int i = 0; i < n2; ++i)
        R[i] = danhSach[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (tinhDiemTrungBinh(&L[i]) <= tinhDiemTrungBinh(&R[j])) {
            danhSach[k] = L[i];
            i++;
        } else {
            danhSach[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        danhSach[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        danhSach[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(SinhVien *danhSach, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(danhSach, l, m);
        mergeSort(danhSach, m + 1, r);
        merge(danhSach, l, m, r);
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

    // Cap nhat nam sinh cua sinh vien theo MSSV (vi du MSSV la "1234567890" va nam sinh moi la "1990")
    capNhatNamSinhSinhVien(danhSach, soLuong, "1234567890", "1990");

    // Sap xep sinh vien theo diem trung binh
    mergeSort(danhSach, 0, soLuong - 1);

    // Ghi ket qua ra file output.txt
    ghiThongTinSinhVien(danhSach, soLuong, "output.txt");

    return 0;
}

