//Nhóm 1 
// Van Dinh Nam - 22207063 
// Tran Gia Lac - 22207054  
// Le Tan Phi Pha - 22207066  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 10000
#define POSTCODE_LEN 7
#define SELLER_LEN 10

typedef struct {
    int YearBuilt;
    int Landsize;
    char Postcode[POSTCODE_LEN];
    int Price;
    char Seller[SELLER_LEN];
} home;

home home_data[MAX_RECORDS];

// Ham doc du lieu tu file CSV
void doc_csv(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Khong mo duoc file %s de doc.\n", filename);
        return;
    }

    char line[1024];
    int index = 0;

    // Bo qua dong header
    fgets(line, 1024, file);

    while (fgets(line, 1024, file) && index < MAX_RECORDS) {
        char* token;
        int count = 0;

        token = strtok(line, ",");
        while (token != NULL) {
            count++;

            // Lay gia tri cho YearBuilt
            if (count == 16) {
                home_data[index].YearBuilt = token ? atoi(token) : 0;
            }

            // Lay gia tri cho Landsize
            if (count == 14) {
                home_data[index].Landsize = token ? atoi(token) : 0;
            }

            // Lay gia tri cho Postcode
            if (count == 10) {
                if (token)
                    strncpy(home_data[index].Postcode, token, POSTCODE_LEN);
                else
                    memset(home_data[index].Postcode, 0, POSTCODE_LEN);
            }

            // Lay gia tri cho Price
            if (count == 5) {
                home_data[index].Price = token ? atoi(token) : 0;
            }

            // Lay gia tri cho SellerG
            if (count == 7) {
                if (token)
                    strncpy(home_data[index].Seller, token, SELLER_LEN);
                else
                    memset(home_data[index].Seller, 0, SELLER_LEN);
            }

            token = strtok(NULL, ",");
        }

        index++;
    }

    fclose(file);
}

// Ham ghi du lieu ra file CSV
void ghi_csv(const char* filename, home* data, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong mo duoc file %s de ghi.\n", filename);
        return;
    }

    fprintf(file, "YearBuilt,Landsize,Postcode,Price,Seller\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%d,%s,%d,%s\n",
                data[i].YearBuilt,
                data[i].Landsize,
                data[i].Postcode,
                data[i].Price,
                data[i].Seller);
    }

    fclose(file);
}

// Cac ham ho tro Merge Sort
void merge(home* data, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    home* L = (home*)malloc(n1 * sizeof(home));
    home* R = (home*)malloc(n2 * sizeof(home));

    for (int i = 0; i < n1; i++)
        L[i] = data[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].YearBuilt <= R[j].YearBuilt) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(home* data, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort(data, l, m);
        merge_sort(data, m + 1, r);

        merge(data, l, m, r);
    }
}

// Cac ham ho tro Radix Sort
int get_max_postcode(home* data, int n) {
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int postcode_num = atoi(data[i].Postcode);
        if (postcode_num > mx) {
            mx = postcode_num;
        }
    }
    return mx;
}

void count_sort(home* data, int n, int exp) {
    home* output = (home*)malloc(n * sizeof(home));
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int index = (atoi(data[i].Postcode) / exp) % 10;
        count[index]++;
    }

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int index = (atoi(data[i].Postcode) / exp) % 10;
        output[count[index] - 1] = data[i];
        count[index]--;
    }

    for (int i = 0; i < n; i++)
        data[i] = output[i];

    free(output);
}

void radix_sort(home* data, int n) {
    int max = get_max_postcode(data, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        count_sort(data, n, exp);
}

// Ham tim nguoi ban nhieu nha nhat
void tim_nguoi_ban_nhieu_nhat(home* data, int n) {
    int max_count = 0;
    char top_seller[SELLER_LEN] = {0};
    int counts[1000] = {0}; // gia su khong co qua 1000 nguoi ban khac nhau
    char sellers[1000][SELLER_LEN] = {0}; // luu tru nguoi ban khac nhau
    int seller_count = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < seller_count; j++) {
            if (strncmp(data[i].Seller, sellers[j], SELLER_LEN) == 0) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(sellers[seller_count], data[i].Seller, SELLER_LEN);
            counts[seller_count]++;
            seller_count++;
        }
    }

    for (int i = 0; i < seller_count; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            strncpy(top_seller, sellers[i], SELLER_LEN);
        }
    }

    printf("Nguoi ban nhieu nha nhat: %s voi %d ngoi nha.\n", top_seller, max_count);
}

int main() {
    const char* input_filename = "melb_data.csv";

    // Buoc 2: Doc du lieu tu file CSV
    doc_csv(input_filename);

    // Buoc 3: Ghi du lieu ra file CSV
    ghi_csv("home_data.csv", home_data, MAX_RECORDS);

    // Buoc 4: Sap xep theo YearBuilt bang Merge Sort va ghi ra file
    merge_sort(home_data, 0, MAX_RECORDS - 1);
    ghi_csv("YearBuilt.csv", home_data, MAX_RECORDS);

    // Buoc 5: Sap xep theo Postcode bang Radix Sort va ghi ra file
    radix_sort(home_data, MAX_RECORDS);
    ghi_csv("Postcode.csv", home_data, MAX_RECORDS);

    // Buoc 6: Tim nguoi ban nhieu nha nhat
    tim_nguoi_ban_nhieu_nhat(home_data, MAX_RECORDS);

    return 0;
}

