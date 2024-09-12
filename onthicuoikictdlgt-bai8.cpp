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

SinhVien* getTail(SinhVien *cur) {
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

SinhVien* partition(SinhVien *head, SinhVien *end, SinhVien **newHead, SinhVien **newEnd) {
    SinhVien *pivot = end;
    SinhVien *prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (strcmp(cur->mssv, pivot->mssv) < 0) {
            if ((*newHead) == NULL)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            SinhVien *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

SinhVien* quickSortRecur(SinhVien *head, SinhVien *end) {
    if (!head || head == end)
        return head;

    SinhVien *newHead = NULL, *newEnd = NULL;
    SinhVien *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        SinhVien *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

void quickSort(SinhVien **headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
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

    // Sap xep sinh vien theo ma so sinh vien
    quickSort(&head);

    // Ghi ket qua ra file output.txt
    ghiDanhSachSinhVien(head, "output.txt");

    return 0;
}

