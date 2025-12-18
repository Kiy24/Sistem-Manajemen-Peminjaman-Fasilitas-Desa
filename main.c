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