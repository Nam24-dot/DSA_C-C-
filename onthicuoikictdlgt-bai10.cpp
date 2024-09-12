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

void themCuoi(SinhVien **head, SinhVien *sv) {
    if (*head == NULL) {
        *head = sv;
    } else {
        SinhVien *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = sv;
    }
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
        themCuoi(head, sv);
    }

    fclose(file);
}

void xoaDau(SinhVien **head) {
    if (*head == NULL) return;
    SinhVien *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void selectionSort(SinhVien **head) {
    SinhVien *sorted = NULL;
    SinhVien *current = *head;

    while (current != NULL) {
        SinhVien **minNode = &current;
        SinhVien *temp = current->next;

        while (temp != NULL) {
            if (strcmp((*minNode)->ngaySinh, temp->ngaySinh) > 0) {
                minNode = &temp;
            }
            temp = temp->next;
        }

        SinhVien *min = *minNode;
        *minNode = min->next;

        min->next = sorted;
        sorted = min;

        current = current == min ? *minNode : current;
    }

    *head = sorted;
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

    // Xoa sinh vien o dau danh sach
    xoaDau(&head);

    // Sap xep sinh vien theo tuoi (ngay sinh)
    selectionSort(&head);

    // Ghi ket qua ra file output.txt
    ghiDanhSachSinhVien(head, "output.txt");

    return 0;
}

