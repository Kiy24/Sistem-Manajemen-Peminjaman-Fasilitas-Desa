
#include <stdio.h>
#include <string.h>
#define MAX_FASILITAS 100

struct fasilitasDesa{
    char barang[50];
    int jumlahBarang;
};
int totalBarang = 0;

struct fasilitasDesa inventaris[MAX_FASILITAS];


void TambahBarang() {
    printf("Nama Barang : ");
    scanf("%s", inventaris[totalBarang].barang);
    printf("Jumlah Barang : ");
    scanf("%d",&inventaris[totalBarang].jumlahBarang);
totalBarang++;
    printf("%s Berhasil ditambahkan\n", inventaris[totalBarang-1].barang);
}
void ListBarang() {
    if (totalBarang == 0){
        printf("Penyimpanan Masih Kosong!\n");}
        else {
            for (int i  = 0; i < totalBarang; i++) {
        printf("%d, %s, %d\n", i+1, inventaris[i].barang, inventaris[i].jumlahBarang);
        }
     }   
    }
