
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
int main() {
    int pilihan;
    do {
        printf("Menu Inventaris Fasilitas Desa:\n");
        printf("1. Tambahkan Fasilitas\n");
        printf("2. Daftar Fasilitas\n");
        printf("3. Keluar\n");
        printf("Pilih opsi (1-3): ");
        if (scanf("%d", &pilihan) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Input tidak valid. Silakan coba lagi.\n\n");
            pilihan = 0;
            continue;
        }
        switch (pilihan) {
            case 1:
                TambahBarang();
                break;
            case 2:
                ListBarang();
                break;
            case 3:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Opsi tidak valid. Silakan coba lagi.\n\n");
        }
    } while (pilihan != 3);


}