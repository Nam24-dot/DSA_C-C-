#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien {
    char hoTen[21];
    char mssv[11];
    char ngaySinh[11];
    float diem[5];
    struct SinhVien *next;
} SinhVien;

SinhVien* taoSinhVien(char hoTen[], char mssv[], char ngaySinh[], float diem[]) {
    SinhVien* sv = (SinhVien*)malloc(sizeof(SinhVien));
    strncpy(sv->hoTen, hoTen, 21);
    strncpy(sv->mssv, mssv, 11);
    strncpy(sv->ngaySinh, ngaySinh, 11);
    memcpy(sv->diem, diem, sizeof(float) * 5);
    sv->next = NULL;
    return sv;
}

void themDau(SinhVien **head, SinhVien *sv) {
    sv->next = *head;
    *head = sv;
}

void docThongTinSinhVien(SinhVien **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Khong the mo file input.txt");
        return;
    }

    char hoTen[21], mssv[11], ngaySinh[11];
    float diem[5];

    while (fscanf(file, "%20[^\n]%*c%10[^\n]%*c%10[^\n]%*c%f%f%f%f%f%*c", hoTen, mssv, ngaySinh, 
                  &diem[0], &diem[1], &diem[2], &diem[3], &diem[4]) == 8) {
        SinhVien *sv = taoSinhVien(hoTen, mssv, ngaySinh, diem);
        themDau(head, sv);
    }

    fclose(file);
}

void xoaSinhVienLienKe(SinhVien *head, const char *mssv) {
    while (head != NULL && head->next != NULL) {
        if (strcmp(head->mssv, mssv) == 0) {
            SinhVien *temp = head->next;
            head->next = temp->next;
            free(temp);
            return;
        }
        head = head->next;
    }
}

float tinhDiemTrungBinh(SinhVien *sv) {
    float sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += sv->diem[i];
    }
    return sum / 5;
}

void merge(SinhVien **head, SinhVien *a, SinhVien *b) {
    SinhVien *temp = NULL;
    if (tinhDiemTrungBinh(a) <= tinhDiemTrungBinh(b)) {
        *head = a;
        a = a->next;
    } else {
        *head = b;
        b = b->next;
    }
    temp = *head;

    while (a && b) {
        if (tinhDiemTrungBinh(a) <= tinhDiemTrungBinh(b)) {
            temp->next = a;
            temp = a;
            a = a->next;
        } else {
            temp->next = b;
            temp = b;
            b = b->next;
        }
    }

    if (a) temp->next = a;
    else temp->next = b;
}

void mergeSort(SinhVien **head) {
    if (!*head || !(*head)->next) return;

    SinhVien *a = *head;
    SinhVien *b = (*head)->next->next;
    while (b && b->next) {
        a = a->next;
        b = b->next->next;
    }
    b = a->next;
    a->next = NULL;
    a = *head;

    mergeSort(&a);
    mergeSort(&b);
    merge(head, a, b);
}

void ghiDanhSachSinhVien(SinhVien *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Khong the mo file output.txt");
        return;
    }

    SinhVien *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s\n%s\n%s\n%.2f %.2f %.2f %.2f %.2f\n", 
                temp->hoTen, temp->mssv, temp->ngaySinh, 
                temp->diem[0], temp->diem[1], temp->diem[2], 
                temp->diem[3], temp->diem[4]);
        temp = temp->next;
    }

    fclose(file);
}

int main() {
    SinhVien *head = NULL;

    docThongTinSinhVien(&head, "input.txt");

    // Xoa sinh vien lien ke theo MSSV (vi du MSSV la "1234567890")
    xoaSinhVienLienKe(head, "1234567890");

    // Sap xep sinh vien theo diem trung binh tang dan
    mergeSort(&head);

    // Ghi ket qua ra file output.txt
    ghiDanhSachSinhVien(head, "output.txt");

    return 0;
}

