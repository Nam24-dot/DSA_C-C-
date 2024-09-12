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

void shellSort(SinhVien *danhSach, int soLuong) {
    for (int gap = soLuong / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < soLuong; ++i) {
            SinhVien temp = danhSach[i];
            int j;
            for (j = i; j >= gap && strcmp(danhSach[j - gap].ngaySinh, temp.ngaySinh) > 0; j -= gap) {
                danhSach[j] = danhSach[j - gap];
            }
            danhSach[j] = temp;
        }
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

    // Sap xep sinh vien theo tuoi (ngay sinh)
    shellSort(danhSach, soLuong);

    // Ghi ket qua ra file output.txt
    ghiThongTinSinhVien(danhSach, soLuong, "output.txt");

    return 0;
}

