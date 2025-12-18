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
