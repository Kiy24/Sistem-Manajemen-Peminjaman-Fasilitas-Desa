#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SARANA 100
#define MAX_PINJAMAN 100
#define MAX_FASILITAS 100
#define FILE_SARANA "sarana.dat"
#define FILE_PINJAMAN "pinjaman.dat"

// ============================================================================
// 1. STRUCT DEFINITIONS
// ============================================================================

typedef struct {
    int idSarana;
    char namaSarana[50];
    int jumlahTotal;
    int jumlahTersedia;
} Sarana;

typedef struct {
    int idPeminjaman;
    int idSarana;
    char namaPeminjam[50];
    int kuantitas;
    char tglKembali[11]; 
    int status;          
} Peminjaman;

struct fasilitasDesa {
    char barang[50];
    int jumlahBarang;
};

struct Sarpras {
    int id;
    char nama[50];
    int jumlah;
    char status[20];   
    char tenggat[20];  
};

struct Barang {
    char nama[50];
    int jumlah;
    char kondisi[20];
};

struct Fasilitas {
    char nama[50];
    char lokasi[50];
    int kapasitas;
};

typedef struct {
    char nama[50];
    int jumlah;
    char tenggat[11]; 
} SarprasSorting;

// Global variables
Sarana inventaris[MAX_SARANA];
Peminjaman daftarPinjam[MAX_PINJAMAN];
int jumlahSarana = 0;
int jumlahPeminjaman = 0;

struct fasilitasDesa inventarisFasilitas[MAX_FASILITAS];
int totalBarang = 0;

// ============================================================================
// HELPER FUNCTIONS - INPUT VALIDATION
// ============================================================================

int safeInputInt(int *var) {
    if (scanf("%d", var) != 1) {
        // Clear input buffer jika scanf gagal
        while (getchar() != '\n');
        printf("[ERROR] Input harus berupa angka. Silakan coba lagi.\n");
        return 0;
    }
    // Clear newline setelah angka
    while (getchar() != '\n');
    return 1;
}

/**
 * Fungsi untuk input string yang aman (support spasi)
 * maxLen: maksimal panjang string (termasuk null terminator)
 * Return: 1 jika sukses, 0 jika gagal
 */
int safeInputString(char *str, int maxLen) {
    int c;
    while ((c = getchar()) == ' ' || c == '\t');
    if (c == '\n' || c == EOF) {
        str[0] = '\0';
        return 0;
    }
    str[0] = c;
    int i = 1;
    while (i < maxLen - 1 && (c = getchar()) != '\n' && c != EOF) {
        str[i++] = c;
    }
    if (c != '\n' && c != EOF) {
        while (getchar() != '\n');
    }
    str[i] = '\0';
    return 1;
}
int isValidDate(const char *dateStr) {
    if (strlen(dateStr) != 10) {
        return 0;
    }
    if (dateStr[2] != '/' || dateStr[5] != '/') {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(dateStr[i])) {
            return 0;
        }
    }
    int day = (dateStr[0] - '0') * 10 + (dateStr[1] - '0');
    int month = (dateStr[3] - '0') * 10 + (dateStr[4] - '0');
    int year = (dateStr[6] - '0') * 1000 + (dateStr[7] - '0') * 100 +
               (dateStr[8] - '0') * 10 + (dateStr[9] - '0');
    if (day < 1 || day > 31) return 0;
    if (month < 1 || month > 12) return 0;
    if (year < 2000 || year > 2100) return 0;

    return 1;
}

// ============================================================================
// 2. FILE HANDLING (PERSISTENSI DATA)
// ============================================================================

void loadData() {
    FILE *fs = fopen(FILE_SARANA, "rb");
    if (fs) {
        fread(&jumlahSarana, sizeof(int), 1, fs);
        fread(inventaris, sizeof(Sarana), jumlahSarana, fs);
        fclose(fs);
    }
    FILE *fp = fopen(FILE_PINJAMAN, "rb");
    if (fp) {
        fread(&jumlahPeminjaman, sizeof(int), 1, fp);
        fread(daftarPinjam, sizeof(Peminjaman), jumlahPeminjaman, fp);
        fclose(fp);
    }
    printf("[INFO] Data Sarana dan Peminjaman berhasil dimuat.\n");
}

void saveData() {
    FILE *fs = fopen(FILE_SARANA, "wb");
    if (fs) {
        fwrite(&jumlahSarana, sizeof(int), 1, fs);
        fwrite(inventaris, sizeof(Sarana), jumlahSarana, fs);
        fclose(fs);
    }
    FILE *fp = fopen(FILE_PINJAMAN, "wb");
    if (fp) {
        fwrite(&jumlahPeminjaman, sizeof(int), 1, fp);
        fwrite(daftarPinjam, sizeof(Peminjaman), jumlahPeminjaman, fp);
        fclose(fp);
    }
}

// ============================================================================
// 3. ALGORITMA SEARCHING
// ============================================================================

int cariSaranaIndexByID(int id) {
    int i;
    for (i = 0; i < jumlahSarana; i++) {
        if (inventaris[i].idSarana == id) {
            return i;
        }
    }
    return -1;
}

// ============================================================================
// 4. KONVERSI TANGGAL STRING KE INTEGER UNTUK SORTING
// ============================================================================

long long dateToLong(const char *dateStr) {
    long long day, month, year;

    if (strlen(dateStr) < 10) {
        return 0;
    }

    day = strtol(dateStr, NULL, 10);
    month = strtol(dateStr + 3, NULL, 10);
    year = strtol(dateStr + 6, NULL, 10);

    return year * 10000 + month * 100 + day;
}

// ============================================================================
// 5. TAMBAH INVENTARIS
// ============================================================================

void tambahSarana() {
    if (jumlahSarana >= MAX_SARANA) {
        printf("[ERROR] Kapasitas maksimum sarana tercapai.\n");
        return;
    }
    int idBaru = 1;
    for (int i = 0; i < jumlahSarana; i++) {
        if (inventaris[i].idSarana >= idBaru) {
            idBaru = inventaris[i].idSarana + 1;
        }
    }

    printf("\n=== TAMBAH SARANA BARU ===\n");
    inventaris[jumlahSarana].idSarana = idBaru;
    printf("ID Sarana (otomatis): %d\n", idBaru);

    printf("Nama Sarana: ");
    if (!safeInputString(inventaris[jumlahSarana].namaSarana, 50)) {
        printf("[ERROR] Nama sarana tidak boleh kosong.\n");
        return;
    }

    printf("Jumlah Total: ");
    int jumlah;
    while (1) {
        if (safeInputInt(&jumlah)) {
            if (jumlah < 0) {
                printf("[ERROR] Jumlah tidak boleh negatif. Masukkan lagi: ");
            } else {
                inventaris[jumlahSarana].jumlahTotal = jumlah;
                break;
            }
        } else {
            printf("Masukkan lagi: ");
        }
    }
    inventaris[jumlahSarana].jumlahTersedia = inventaris[jumlahSarana].jumlahTotal;

    printf("[INFO] Sarana '%s' berhasil ditambahkan dengan ID %d.\n",
           inventaris[jumlahSarana].namaSarana, idBaru);
    jumlahSarana++;
}

void tambahBarang() {
    printf("Nama Barang : ");
    safeInputString(inventarisFasilitas[totalBarang].barang, 50);

    printf("Jumlah Barang : ");
    while (!safeInputInt(&inventarisFasilitas[totalBarang].jumlahBarang)) {
        printf("Masukkan lagi: ");
    }

    printf("%s Berhasil ditambahkan\n", inventarisFasilitas[totalBarang].barang);
    totalBarang++;
}

// ============================================================================
// 6. CATAT PEMINJAMAN
// ============================================================================

void catatPeminjaman() {
    if (jumlahPeminjaman >= MAX_PINJAMAN) {
        printf("[ERROR] Kapasitas maksimum peminjaman tercapai.\n");
        return;
    }
    int idPeminjamanBaru = 1;
    for (int i = 0; i < jumlahPeminjaman; i++) {
        if (daftarPinjam[i].idPeminjaman >= idPeminjamanBaru) {
            idPeminjamanBaru = daftarPinjam[i].idPeminjaman + 1;
        }
    }

    printf("\n=== CATAT PEMINJAMAN BARU ===\n");
    daftarPinjam[jumlahPeminjaman].idPeminjaman = idPeminjamanBaru;
    printf("ID Peminjaman (otomatis): %d\n", idPeminjamanBaru);
    int idSarana;
    printf("ID Sarana: ");
    while (1) {
        if (safeInputInt(&idSarana)) {
            int index = cariSaranaIndexByID(idSarana);
            if (index == -1) {
                printf("[ERROR] Sarana dengan ID %d tidak ditemukan.\n", idSarana);
                printf("Masukkan ID Sarana yang valid: ");
            } else {
                daftarPinjam[jumlahPeminjaman].idSarana = idSarana;
                break;
            }
        } else {
            printf("Masukkan lagi: ");
        }
    }

    printf("Nama Peminjam: ");
    if (!safeInputString(daftarPinjam[jumlahPeminjaman].namaPeminjam, 50)) {
        printf("[ERROR] Nama peminjam tidak boleh kosong.\n");
        return;
    }

    printf("Kuantitas: ");
    int qty;
    while (1) {
        if (safeInputInt(&qty)) {
            if (qty <= 0) {
                printf("[ERROR] Kuantitas harus lebih dari 0. Masukkan lagi: ");
            } else {
                daftarPinjam[jumlahPeminjaman].kuantitas = qty;
                break;
            }
        } else {
            printf("Masukkan lagi: ");
        }
    }

    printf("Tanggal Kembali (DD/MM/YYYY): ");
    char tempDate[20];
    while (1) {
        if (safeInputString(tempDate, 20)) {
            if (isValidDate(tempDate)) {
                strcpy(daftarPinjam[jumlahPeminjaman].tglKembali, tempDate);
                break;
            } else {
                printf("[ERROR] Format tanggal salah. Gunakan DD/MM/YYYY (contoh: 25/12/2025)\n");
                printf("Masukkan lagi: ");
            }
        } else {
            printf("Masukkan lagi: ");
        }
    }
    daftarPinjam[jumlahPeminjaman].status = 0;
    printf("[INFO] Peminjaman berhasil dicatat dengan ID %d.\n", idPeminjamanBaru);
    jumlahPeminjaman++;
}

// ============================================================================
// 7. DATA INVENTARIS (SEARCHING)
// ============================================================================

void cariFasilitas() {
    int id;
    printf("\n=== CARI DETAIL SARANA ===\n");
    printf("Masukkan ID Sarana: ");

    if (!safeInputInt(&id)) {
        return;
    }

    int index = cariSaranaIndexByID(id);
    if (index != -1) {
        printf("\nSarana ditemukan:\n");
        printf("ID          : %d\n", inventaris[index].idSarana);
        printf("Nama        : %s\n", inventaris[index].namaSarana);
        printf("Jumlah Total: %d\n", inventaris[index].jumlahTotal);
        printf("Tersedia    : %d\n", inventaris[index].jumlahTersedia);
    } else {
        printf("[ERROR] Sarana dengan ID %d tidak ditemukan.\n", id);
    }
}

void cariBarang() {
    char cari[50];
    int ketemu = 0;

    printf("Masukkan nama barang yang ingin dicari: ");
    if (!safeInputString(cari, 50)) {
        printf("[ERROR] Input tidak valid.\n");
        return;
    }

    for (int i = 0; i < totalBarang; i++) {
        if (strcmp(inventarisFasilitas[i].barang, cari) == 0) {
            printf("Barang ditemukan!\n");
            printf("%d, %s, %d\n", i+1, inventarisFasilitas[i].barang, inventarisFasilitas[i].jumlahBarang);
            ketemu = 1;
            break;
        }
    }

    if (!ketemu) {
        printf("Barang %s tidak ditemukan dalam inventaris.\n", cari);
    }
}

// ============================================================================
// 8. URUTKAN JADWAL PENGEMBALIAN
// ============================================================================

void urutkanJadwalPengembalian() {
    printf("\n=== JADWAL PENGEMBALIAN (Terurut) ===\n");
    if (jumlahPeminjaman == 0) {
        printf("Belum ada data peminjaman.\n");
        return;
    }
    for (int i = 0; i < jumlahPeminjaman - 1; i++) {
        for (int j = 0; j < jumlahPeminjaman - i - 1; j++) {
            if (dateToLong(daftarPinjam[j].tglKembali) > dateToLong(daftarPinjam[j+1].tglKembali)) {
                Peminjaman temp = daftarPinjam[j];
                daftarPinjam[j] = daftarPinjam[j+1];
                daftarPinjam[j+1] = temp;
            }
        }
    }

    printf("%-5s %-20s %-12s %-10s\n", "ID", "Peminjam", "Tgl Kembali", "Status");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < jumlahPeminjaman; i++) {
        printf("%-5d %-20s %-12s %-10s\n",
               daftarPinjam[i].idPeminjaman,
               daftarPinjam[i].namaPeminjam,
               daftarPinjam[i].tglKembali,
               daftarPinjam[i].status == 0 ? "Dipinjam" : "Selesai");
    }
}
int compareJumlahAsc(const void *a, const void *b) {
    SarprasSorting *s1 = (SarprasSorting *)a;
    SarprasSorting *s2 = (SarprasSorting *)b;
    return s1->jumlah - s2->jumlah;
}

int compareJumlahDesc(const void *a, const void *b) {
    SarprasSorting *s1 = (SarprasSorting *)a;
    SarprasSorting *s2 = (SarprasSorting *)b;
    return s2->jumlah - s1->jumlah;
}

int compareTenggat(const void *a, const void *b) {
    SarprasSorting *s1 = (SarprasSorting *)a;
    SarprasSorting *s2 = (SarprasSorting *)b;
    return strcmp(s1->tenggat, s2->tenggat);
}

void tampilkanData(SarprasSorting s[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Nama: %-15s | Jumlah: %3d | Tenggat: %s\n",
               s[i].nama, s[i].jumlah, s[i].tenggat);
    }
    printf("\n");
}

// ============================================================================
// 9. CATAT PENGEMBALIAN SARANA
// ============================================================================

void prosesPengembalian() {
    int id;
    printf("\n=== PROSES PENGEMBALIAN SARANA ===\n");
    printf("Masukkan ID Peminjaman: ");

    if (!safeInputInt(&id)) {
        return;
    }

    int found = 0;
    for (int i = 0; i < jumlahPeminjaman; i++) {
        if (daftarPinjam[i].idPeminjaman == id) {
            found = 1;
            if (daftarPinjam[i].status == 1) {
                printf("[INFO] Peminjaman sudah selesai sebelumnya.\n");
            } else {
                daftarPinjam[i].status = 1;
                printf("[INFO] Pengembalian berhasil diproses.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("[ERROR] ID Peminjaman tidak ditemukan.\n");
    }
}

void fungsiPengembalianTogar(struct Sarpras daftar[], int totalData) {
    int idCari;
    int ditemukan = 0;

    printf("\n==========================================\n");
    printf("   SISTEM PENGEMBALIAN SARPRAS DESA     \n");
    printf("==========================================\n");

    printf(" Masukkan ID Barang yang dikembalikan: ");
    if (!safeInputInt(&idCari)) {
        return;
    }

    for (int i = 0; i < totalData; i++) {
        if (daftar[i].id == idCari) {
            ditemukan = 1;

            if (strcmp(daftar[i].status, "Dipinjam") != 0) {
                printf("\n [!] PERINGATAN: Barang '%s' sudah ada di tempat.\n", daftar[i].nama);
                printf("     Status saat ini: %s\n", daftar[i].status);
            } else {
                strcpy(daftar[i].status, "Tersedia");
                strcpy(daftar[i].tenggat, "-");

                printf("\n [SUKSES] Pengembalian Berhasil Dicatat!\n");
                printf(" Barang       : %s\n", daftar[i].nama);
                printf(" Status Baru  : %s (Siap dipinjam kembali)\n", daftar[i].status);
            }
            break;
        }
    }

    if (!ditemukan) {
        printf("\n [X] ERROR: ID Barang %d tidak ditemukan dalam database.\n", idCari);
    }
    printf("==========================================\n");
}

// ============================================================================
// 10. MENU DAN TAMPILAN
// ============================================================================

void tampilkanMenu() {
    printf("\n====================================\n");
    printf("SIMPASDES (Sarana Desa)\n");
    printf("====================================\n");
    printf("1. Tambah Jenis Sarana Baru\n");
    printf("2. Tampilkan Inventaris Sarana\n");
    printf("3. Catat Peminjaman Baru\n");
    printf("4. Cari Detail Sarana (Searching)\n");
    printf("5. Urutkan Jadwal Pengembalian (Sorting)\n");
    printf("6. Proses Pengembalian Sarana\n");
    printf("7. Keluar & Simpan Data\n");
    printf("------------------------------------\n");
    printf("Pilih menu (1-7): ");
}

void tampilkanInventaris() {
    printf("\n=== INVENTARIS SARANA ===\n");
    if (jumlahSarana == 0) {
        printf("Belum ada sarana terdaftar.\n");
        return;
    }

    printf("%-5s %-20s %-10s %-10s\n", "ID", "Nama", "Total", "Tersedia");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < jumlahSarana; i++) {
        printf("%-5d %-20s %-10d %-10d\n",
               inventaris[i].idSarana,
               inventaris[i].namaSarana,
               inventaris[i].jumlahTotal,
               inventaris[i].jumlahTersedia);
    }
}

void listBarang() {
    if (totalBarang == 0) {
        printf("Penyimpanan Masih Kosong!\n");
    } else {
        for (int i = 0; i < totalBarang; i++) {
            printf("%d, %s, %d\n", i+1, inventarisFasilitas[i].barang, inventarisFasilitas[i].jumlahBarang);
        }
    }
}

// Main function
int main() {
    loadData();
    int pilihan;

    do {
        tampilkanMenu();
        if (!safeInputInt(&pilihan)) {
            pilihan = 0;
            continue;
        }

        switch (pilihan) {
            case 1: tambahSarana(); break;
            case 2: tampilkanInventaris(); break;
            case 3: catatPeminjaman(); break;
            case 4: cariFasilitas(); break;
            case 5: urutkanJadwalPengembalian(); break;
            case 6: prosesPengembalian(); break;
            case 7:
                saveData();
                printf("Terima kasih. Data telah disimpan dan program diakhiri.\n");
                break;
            default: printf("[ERROR] Pilihan tidak valid. Masukkan angka 1-7.\n");
        }
    } while (pilihan != 7);

    return 0;
}
