#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char hoTen[21];
    char mssv[11];
    char ngaySinh[11];
    float diem[5];
} SinhVien;

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

void radixSort(SinhVien *danhSach, int soLuong) {
    int maxLen = 10; // Do dai ma so sinh vien
    for (int exp = maxLen - 1; exp >= 0; exp--) {
        SinhVien output[soLuong];
        int count[256] = {0};

        for (int i = 0; i < soLuong; i++)
            count[(unsigned char)danhSach[i].mssv[exp]]++;

        for (int i = 1; i < 256; i++)
            count[i] += count[i - 1];

        for (int i = soLuong - 1; i >= 0; i--) {
            output[count[(unsigned char)danhSach[i].mssv[exp]] - 1] = danhSach[i];
            count[(unsigned char)danhSach[i].mssv[exp]]--;
        }

        for (int i = 0; i < soLuong; i++)
            danhSach[i] = output[i];
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

    // Sap xep sinh vien theo ma so sinh vien
    radixSort(danhSach, soLuong);

    // Ghi ket qua ra file output.txt
    ghiThongTinSinhVien(danhSach, soLuong, "output.txt");

    return 0;
}

