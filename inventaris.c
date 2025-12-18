
#include <stdio.h>
#include <string.h>
#define MAX_FASILITAS 100

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
