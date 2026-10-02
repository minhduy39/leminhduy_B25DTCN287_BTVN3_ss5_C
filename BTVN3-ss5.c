#include <stdio.h>
#include <stdbool.h>

#define MAX 100
#define DON_GIA_GOC 150000LL
#define DON_GIA_BHYT 30000LL
#define TUOI_UU_TIEN 70

// Ham xoa bo dem ban phim
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Ham tinh phi kham thuc te cua 1 benh nhan
long long tinh_phi_kham(int bhyt) {
    return (bhyt == 1) ? DON_GIA_BHYT : DON_GIA_GOC;
}

// Ham in danh sach hang cho va xuat bao cao
void in_danh_sach(const int ma_stt[], const int tuoi[], const int bhyt[], int n) {
    if (n == 0) {
        printf("\n[THONG BAO] Hang cho hien tai dang RONG!\n");
        return;
    }

    long long tong_doanh_thu = 0;
    int so_ca_uu_tien = 0;

    printf("\n%-6s %-12s %-8s %-12s %-18s %-12s\n", 
           "Index", "Ma STT", "Tuoi", "BHYT", "Phi Kham (VND)", "Doi Tuong");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        long long phi = tinh_phi_kham(bhyt[i]);
        tong_doanh_thu += phi;
        
        bool is_uu_tien = (tuoi[i] >= TUOI_UU_TIEN);
        if (is_uu_tien) {
            so_ca_uu_tien++;
        }

        printf("%-6d %-12d %-8d %-12s %-18lld %-12s\n",
               i,
               ma_stt[i],
               tuoi[i],
               (bhyt[i] == 1) ? "Co BHYT" : "Khong",
               phi,
               is_uu_tien ? "UU TIEN" : "Thuong");
    }

    printf("-----------------------------------------------------------------------\n");
    printf(">> Tong so benh nhan active : %d\n", n);
    printf(">> Tong doanh thu d? kiien   : %lld VNÐ\n", tong_doanh_thu);
    printf(">> So ca thuoc luong UU TIEN: %d\n", so_ca_uu_tien);
}

int main(void) {
    int ma_stt[MAX];
    int tuoi[MAX];
    int bhyt[MAX];
    int n = 0;

    printf("=========================================================\n");
    printf("   HE THONG KIOSK QUAN LY HANG CHO KHAM - MEDICARE\n");
    printf("=========================================================\n\n");

    // 1. NHAP SO LUONG BENH NHAN BAN DAU
    do {
        printf("Nhap so luong benh nhan ban dau (0 <= n <= %d): ", MAX);
        if (scanf("%d", &n) != 1) {
            printf("[LOI] Vui long nhap so nguyen!\n");
            clear_input_buffer();
            n = -1;
            continue;
        }
        if (n < 0 || n > MAX) {
            printf("[LOI] So luong phai nam trong kho?ng [0, %d]. Nhap lai!\n", MAX);
        }
    } while (n < 0 || n > MAX);

    // 2. NHAP THONG TIN CHI TIET TUNG BENH NHAN
    for (int i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin Benh nhan tai Index %d ---\n", i);
        
        // Auto gen hoac nhap Ma STT
        ma_stt[i] = 1001 + i;
        printf("Ma STT cap t? dong: %d\n", ma_stt[i]);

        // Input Data Validation: Tuoi
        do {
            printf("Nhap tuoi (1 - 120): ");
            if (scanf("%d", &tuoi[i]) != 1) {
                printf("[LOI] Vui long nhap so nguyen!\n");
                clear_input_buffer();
                tuoi[i] = -1;
                continue;
            }
            if (tuoi[i] < 1 || tuoi[i] > 120) {
                printf("[LOI] Tuoi khong hop le! Vui long nhap lai.\n");
            }
        } while (tuoi[i] < 1 || tuoi[i] > 120);

        // Input Data Validation: BHYT
        do {
            printf("Trang thai BHYT (1: Co BHYT, 0: Khong BHYT): ");
            if (scanf("%d", &bhyt[i]) != 1) {
                printf("[LOI] Vui long nhap 0 hoac 1!\n");
                clear_input_buffer();
                bhyt[i] = -1;
                continue;
            }
            if (bhyt[i] != 0 && bhyt[i] != 1) {
                printf("[LOI] Trang thai BHYT chi nhan 0 hoac 1. Nhap lai!\n");
            }
        } while (bhyt[i] != 0 && bhyt[i] != 1);
    }

    // 3. IN BANGLIST BAN DAU
    printf("\n=======================================================================");
    printf("\n                    DANH SACH HANG CHO BAN DAU                         ");
    printf("\n=======================================================================");
    in_danh_sach(ma_stt, tuoi, bhyt, n);

    // 4. THAO TAC HUY LUOT KHAM TAI CHU SO K
    if (n > 0) {
        int K;
        printf("\n=========================================================\n");
        printf("THAO TAC HUY DANG KY KHAM BENH\n");
        printf("=========================================================\n");
        printf("Nhap vi tri chi so (Index K) muon huy (0 <= K < %d): ", n);
        
        if (scanf("%d", &K) != 1) {
            printf("\n[LOI CRITICAL] Vi tri K nhap vao khong phai so nguyen. Thao tac bi huy!\n");
        } else if (K < 0 || K >= n) {
            // Ràng bu?c ki?m soát v? trí h?y không h?p l?
            printf("\n[LOI CRITICAL] Chi so K = %d VUOT BIEN hoac KHONG HOP LE! (Khong thuoc [0, %d])\n", K, n - 1);
            printf(">> Thao tac huy bi TU CHOI de bao ve du lieu!\n");
        } else {
            // THUC HIEN DON DICH MANG (HARD DELETE / SHIFT ARRAY)
            int ma_stt_huy = ma_stt[K];
            
            for (int i = K; i < n - 1; i++) {
                ma_stt[i] = ma_stt[i + 1];
                tuoi[i]   = tuoi[i + 1];
                bhyt[i]   = bhyt[i + 1];
            }
            
            // Giam kich thuoc m?ng active
            n--;

            printf("\n[THANH CONG] Da huy luot kham cua Benh nhan co Ma STT %d tai Index %d!\n", ma_stt_huy, K);
        }
    } else {
        printf("\n[THONG BAO] Hang cho rong, khong the thuc hien thao tac huy!\n");
    }

    // 5. IN DANH SACH SAU KHI TAI CAU TRUC
    printf("\n=======================================================================");
    printf("\n               DANH SACH HANG CHO SAU KHI TAI CAU TRUC                  ");
    printf("\n=======================================================================");
    in_danh_sach(ma_stt, tuoi, bhyt, n);

    return 0;
}
