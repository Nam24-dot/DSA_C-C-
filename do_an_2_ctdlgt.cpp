#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Dinh nghia cau truc sach
typedef struct Sach {
    char ten[31];
    char maSo[13];
    int giaTien;
    int soLuong;
    struct Sach* tiep;
} Sach;

// Ham tao sach moi
Sach* taoSachMoi(const char* ten, const char* maSo, int giaTien, int soLuong) {
    Sach* sachMoi = (Sach*)malloc(sizeof(Sach));
    strncpy(sachMoi->ten, ten, 30);
    strncpy(sachMoi->maSo, maSo, 12);
    sachMoi->giaTien = giaTien;
    sachMoi->soLuong = soLuong;
    sachMoi->tiep = NULL;
    return sachMoi;
}

// Ham them sach vao cuoi danh sach
void themSachVaoCuoi(Sach** dau, const char* ten, const char* maSo, int giaTien, int soLuong) {
    Sach* sachMoi = taoSachMoi(ten, maSo, giaTien, soLuong);
    if (*dau == NULL) {
        *dau = sachMoi;
    } else {
        Sach* tam = *dau;
        while (tam->tiep != NULL) {
            tam = tam->tiep;
        }
        tam->tiep = sachMoi;
    }
}

// Ham doc danh sach sach tu file
void docSachTuFile(Sach** dau, const char* tenFile) {
    FILE* file = fopen(tenFile, "r");
    if (!file) {
        printf("Khong the mo file %s.\n", tenFile);
        return;
    }
    char dong[100];
    while (fgets(dong, sizeof(dong), file)) {
        char ten[31];
        char maSo[13];
        int giaTien, soLuong;
        sscanf(dong, "%30[^,],%12[^,],%d,%d", ten, maSo, &giaTien, &soLuong);
        themSachVaoCuoi(dau, ten, maSo, giaTien, soLuong);
    }
    fclose(file);
}

// Ham ghi danh sach sach vao file
void ghiSachVaoFile(Sach* dau, const char* tenFile) {
    FILE* file = fopen(tenFile, "w");
    if (!file) {
        printf("Khong the mo file %s.\n", tenFile);
        return;
    }
    Sach* tam = dau;
    while (tam) {
        fprintf(file, "%s,%s,%d,%d\n", tam->ten, tam->maSo, tam->giaTien, tam->soLuong);
        tam = tam->tiep;
    }
    fclose(file);
}

// Ham tim sach theo ma so sach
Sach* timSachTheoMa(Sach* dau, const char* maSo) {
    Sach* tam = dau;
    while (tam) {
        if (strcmp(tam->maSo, maSo) == 0) {
            return tam;
        }
        tam = tam->tiep;
    }
    return NULL;
}

// Ham hien thi thong tin cua sach
void hienThiThongTinSach(Sach* sach) {
    if (sach) {
        printf("Ten sach: %s\n", sach->ten);
        printf("Ma so sach: %s\n", sach->maSo);
        printf("Gia tien: %d\n", sach->giaTien);
        printf("So luong con lai: %d\n", sach->soLuong);
    } else {
        printf("Khong tim thay sach.\n");
    }
}

// Ham sua thong tin sach
void suaThongTinSach(Sach* sach) {
    if (sach) {
        printf("Nhap ten sach moi: ");
        scanf("%s", sach->ten);
        printf("Nhap ma so sach moi: ");
        scanf("%s", sach->maSo);
        printf("Nhap gia tien moi: ");
        scanf("%d", &sach->giaTien);
        printf("Nhap so luong con lai moi: ");
        scanf("%d", &sach->soLuong);
        printf("Da sua thong tin sach.\n");
    } else {
        printf("Khong tim thay sach de sua.\n");
    }
}

// Ham sap xep danh sach theo ma so sach bang thuat toan Radix Sort
void sapXepTheoMaSo(Sach** dau, int maxLen) {
    Sach* bins[10] = {NULL};
    Sach* tails[10] = {NULL};
    int i, digit;
    Sach* tam;
    Sach* list = *dau;

    for (i = maxLen - 1; i >= 0; i--) {
        tam = list;
        while (tam) {
            digit = (tam->maSo[i] - '0');
            if (bins[digit] == NULL) {
                bins[digit] = tam;
                tails[digit] = tam;
            } else {
                tails[digit]->tiep = tam;
                tails[digit] = tam;
            }
            tam = tam->tiep;
        }

        list = NULL;
        Sach* tail = NULL;
        for (int j = 0; j < 10; j++) {
            if (bins[j] != NULL) {
                if (list == NULL) {
                    list = bins[j];
                    tail = tails[j];
                } else {
                    tail->tiep = bins[j];
                    tail = tails[j];
                }
                bins[j] = tails[j] = NULL;
            }
        }
        if (tail != NULL) tail->tiep = NULL;
    }

    *dau = list;
}

// Ham hien thi menu
void hienThiMenu() {
    printf("\n=== MENU ===\n");
    printf("1. Them sach\n");
    printf("2. Hien thi tat ca sach\n");
    printf("3. Tim kiem sach theo ma so\n");
    printf("4. Sua thong tin sach theo ma so\n");
    printf("5. Sap xep sach theo ma so\n");
    printf("6. Thoat\n");
    printf("Chon mot tuy chon: ");
}

// Ham hien thi toan bo danh sach sach
void hienThiTatCaSach(Sach* dau) {
    Sach* tam = dau;
    while (tam) {
        hienThiThongTinSach(tam);
        tam = tam->tiep;
        printf("\n");
    }
}

int main() {
    Sach* dau = NULL;
    int luaChon;
    char maSo[13];

    // Doc danh sach sach tu file khi khoi dong chuong trinh
    docSachTuFile(&dau, "data.txt");

    while (1) {
        hienThiMenu();
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1: {
                char ten[31];
                int giaTien, soLuong;
                printf("Nhap ten sach: ");
                scanf("%s", ten);
                printf("Nhap ma so sach: ");
                scanf("%s", maSo);
                printf("Nhap gia tien: ");
                scanf("%d", &giaTien);
                printf("Nhap so luong con lai: ");
                scanf("%d", &soLuong);
                themSachVaoCuoi(&dau, ten, maSo, giaTien, soLuong);
                printf("Da them sach.\n");
                break;
            }
            case 2:
                hienThiTatCaSach(dau);
                break;
            case 3: {
                printf("Nhap ma so sach can tim: ");
                scanf("%s", maSo);
                Sach* sach = timSachTheoMa(dau, maSo);
                hienThiThongTinSach(sach);
                break;
            }
            case 4: {
                printf("Nhap ma so sach can sua: ");
                scanf("%s", maSo);
                Sach* sachDeSua = timSachTheoMa(dau, maSo);
                suaThongTinSach(sachDeSua);
                break;
            }
            case 5:
                sapXepTheoMaSo(&dau, 12);
                printf("Da sap xep sach theo ma so.\n");
                break;
            case 6:
                printf("Thoat chuong trinh.\n");
                // Ghi danh sach sach vao file truoc khi thoat
                ghiSachVaoFile(dau, "data.txt");
                exit(0);
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }

    return 0;
}

