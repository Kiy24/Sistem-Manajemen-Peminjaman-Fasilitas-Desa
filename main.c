#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SARANA 100
#define MAX_PINJAMAN 100
#define MAX_FASILITAS 100
#define FILE_SARANA "sarana.dat"
#define FILE_PINJAMAN "pinjaman.dat"

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

Sarana inventaris[MAX_SARANA];
Peminjaman daftarPinjam[MAX_PINJAMAN];
int jumlahSarana = 0;
int jumlahPeminjaman = 0;

struct fasilitasDesa inventarisFasilitas[MAX_FASILITAS];
int totalBarang = 0;

int cariSaranaIndexByID(int id);
long long dateToLong(const char *dateStr);
void loadData();
void saveData();
void tambahBarang();
void listBarang();
void cariBarang();
void fungsiPengembalianTogar(struct Sarpras daftar[], int totalData);
void tampilkanMenu();
void tambahSarana();
void tampilkanInventaris();
void catatPeminjaman();
void cariFasilitas();
void urutkanJadwalPengembalian();
void prosesPengembalian();
int compareJumlahAsc(const void *a, const void *b);
int compareJumlahDesc(const void *a, const void *b);
int compareTenggat(const void *a, const void *b);
void tampilkanData(SarprasSorting s[], int n);

int cariSaranaIndexByID(int id) {
    int i;
    for (i = 0; i < jumlahSarana; i++) {
        if (inventaris[i].idSarana == id) {
            return i;
        }
    }
    return -1;
}

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

void tambahBarang() {
    printf("Nama Barang : ");
    scanf("%s", inventarisFasilitas[totalBarang].barang);
    printf("Jumlah Barang : ");
    scanf("%d", &inventarisFasilitas[totalBarang].jumlahBarang);
    printf("%s Berhasil ditambahkan\n", inventarisFasilitas[totalBarang].barang);
    totalBarang++;
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

void cariBarang() {
    char cari[50];
    int ketemu = 0;

    printf("Masukkan nama barang yang ingin dicari: ");
    scanf("%s", cari);

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

void fungsiPengembalianTogar(struct Sarpras daftar[], int totalData) {
    int idCari;
    int ditemukan = 0;

    printf("\n==========================================\n");
    printf("   SISTEM PENGEMBALIAN SARPRAS DESA     \n");
    printf("==========================================\n");
    
    printf(" Masukkan ID Barang yang dikembalikan: ");
    if (scanf("%d", &idCari) != 1) {
        printf(" [!] Input tidak valid. Gunakan angka.\n");
        while(getchar() != '\n'); // Clear buffer
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

void tambahSarana() {
    if (jumlahSarana >= MAX_SARANA) {
        printf("[ERROR] Kapasitas maksimum sarana tercapai.\n");
        return;
    }
    
    printf("\n=== TAMBAH SARANA BARU ===\n");
    printf("ID Sarana: ");
    scanf("%d", &inventaris[jumlahSarana].idSarana);
    printf("Nama Sarana: ");
    scanf("%s", inventaris[jumlahSarana].namaSarana);
    printf("Jumlah Total: ");
    scanf("%d", &inventaris[jumlahSarana].jumlahTotal);
    inventaris[jumlahSarana].jumlahTersedia = inventaris[jumlahSarana].jumlahTotal;
    
    printf("[INFO] Sarana '%s' berhasil ditambahkan.\n", inventaris[jumlahSarana].namaSarana);
    jumlahSarana++;
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

void catatPeminjaman() {
    if (jumlahPeminjaman >= MAX_PINJAMAN) {
        printf("[ERROR] Kapasitas maksimum peminjaman tercapai.\n");
        return;
    }
    
    printf("\n=== CATAT PEMINJAMAN BARU ===\n");
    printf("ID Peminjaman: ");
    scanf("%d", &daftarPinjam[jumlahPeminjaman].idPeminjaman);
    printf("ID Sarana: ");
    scanf("%d", &daftarPinjam[jumlahPeminjaman].idSarana);
    printf("Nama Peminjam: ");
    scanf("%s", daftarPinjam[jumlahPeminjaman].namaPeminjam);
    printf("Kuantitas: ");
    scanf("%d", &daftarPinjam[jumlahPeminjaman].kuantitas);
    printf("Tanggal Kembali (DD/MM/YYYY): ");
    scanf("%s", daftarPinjam[jumlahPeminjaman].tglKembali);
    daftarPinjam[jumlahPeminjaman].status = 0;
    
    printf("[INFO] Peminjaman berhasil dicatat.\n");
    jumlahPeminjaman++;
}

void cariFasilitas() {
    int id;
    printf("\n=== CARI DETAIL SARANA ===\n");
    printf("Masukkan ID Sarana: ");
    scanf("%d", &id);
    
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

void prosesPengembalian() {
    int id;
    printf("\n=== PROSES PENGEMBALIAN SARANA ===\n");
    printf("Masukkan ID Peminjaman: ");
    scanf("%d", &id);
    
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

int main() {
    loadData();
    int pilihan;

    do {
        tampilkanMenu();
        if (scanf("%d", &pilihan) != 1) {
            // Handle input non-integer
            while (getchar() != '\n');
            pilihan = 0;
            printf("[ERROR] Input harus berupa angka.\n");
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
            default: printf("[ERROR] Pilihan tidak valid.\n");
        }
    } while (pilihan != 7);

    return 0;
}
