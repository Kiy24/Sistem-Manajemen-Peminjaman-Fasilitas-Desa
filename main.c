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
    char tglKembali[11]; // Format DD/MM/YYYY
    int status;          // 0: Dipinjam, 1: Selesai
} Peminjaman;

Sarana inventaris[MAX_SARANA];
Peminjaman daftarPinjam[MAX_PINJAMAN];
int jumlahSarana = 0;
int jumlahPeminjaman = 0;

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

struct Sarpras {
    int id;
    char nama[50];
    int jumlah;
    char status[20];   // "Tersedia" atau "Dipinjam"
    char tenggat[20];  // Tanggal kembali
};

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