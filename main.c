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

struct fasilitasDesa{
    char barang[50];
    int jumlahBarang;
};
int totalBarang = 0;

struct fasilitasDesa inventaris[MAX_FASILITAS];


void tambahBarang() {
    printf("Nama Barang : ");
    scanf("%s", inventaris[totalBarang].barang);
    printf("Jumlah Barang : ");
    scanf("%d",&inventaris[totalBarang].jumlahBarang);
    printf("%s Berhasil ditambahkan\n", inventaris[totalBarang].barang);
totalBarang++;
}
void listBarang() {
    if (totalBarang == 0){
        printf("Penyimpanan Masih Kosong!\n");}
        else {
            for (int i  = 0; i < totalBarang; i++) {
        printf("%d, %s, %d\n", i+1, inventaris[i].barang, inventaris[i].jumlahBarang);
        }
     }
    }

void cariBarang() {
    char cari[50];
    int ketemu = 0;

    printf("Masukkan nama barang yang ingin dicari: ");
    scanf("%s", cari);

    for (int i = 0; i < totalBarang; i++) {
        if (strcmp(inventaris[i].barang, cari) == 0) {
            printf("Barang ditemukan!\n");
            printf("%d, %s, %d\n", i+1, inventaris[i].barang, inventaris[i].jumlahBarang);
            ketemu = 1;
            break;
        }
    }

    if (!ketemu) {
        printf("Barang %s tidak ditemukan dalam inventaris.\n", cari);
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

#include <stdio.h>

// struct barang
struct Barang {
    char nama[50];
    int jumlah;
    char kondisi[20];
};

// struct fasilitas
struct Fasilitas {
    char nama[50];
    char lokasi[50];
    int kapasitas;
};

int main() {
    struct Barang barang;
    struct Fasilitas fasilitas;

    printf("=====================================\n");
    printf("        INPUT DATA SARPRAS\n");
    printf("=====================================\n\n");

    // ------------------------------
    // INPUT DATA BARANG
    // ------------------------------
    printf("=== INPUT DATA BARANG ===\n");

    printf("Masukkan Nama Barang      : ");
    scanf(" %s", barang.nama);   // membaca string dengan spasi

    printf("Masukkan Jumlah Barang    : ");
    scanf("%d", &barang.jumlah);

    printf("Masukkan Kondisi Barang   : ");
    scanf(" %s", barang.kondisi);


    // ------------------------------
    // INPUT DATA FASILITAS
    // ------------------------------
    printf("\n=== INPUT DATA FASILITAS ===\n");

    printf("Masukkan Nama Fasilitas   : ");
    scanf(" %s", fasilitas.nama);

    printf("Masukkan Lokasi Fasilitas : ");
    scanf(" %s", fasilitas.lokasi);

    printf("Masukkan Kapasitas        : ");
    scanf("%d", &fasilitas.kapasitas);


    // ------------------------------
    // OUTPUT (MENAMPILKAN DATA)
    // ------------------------------
    printf("\n=====================================\n");
    printf("           OUTPUT DATA\n");
    printf("=====================================\n");

    printf("\n>>> DATA BARANG <<<\n");
    printf("Nama Barang  : %s\n", barang.nama);
    printf("Jumlah       : %d unit\n", barang.jumlah);
    printf("Kondisi      : %s\n", barang.kondisi);

    printf("\n>>> DATA FASILITAS <<<\n");
    printf("Nama Fasilitas : %s\n", fasilitas.nama);
    printf("Lokasi         : %s\n", fasilitas.lokasi);
    printf("Kapasitas      : %d orang\n", fasilitas.kapasitas);

    return 0;
}

