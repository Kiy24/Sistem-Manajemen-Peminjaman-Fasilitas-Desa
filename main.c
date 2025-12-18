#include <stdio.h>
#include <string.h>

// Struktur data sarpras
struct Sarpras {
    int id;
    char nama[50];
    int jumlah;
    char status[20];   // "Tersedia" atau "Dipinjam"
    char tenggat[20];  // Tanggal kembali
};

// --- FUNGSI PENCATATAN PENGEMBALIAN BARANG (BANG TOGAR) ---
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

            // Validasi apakah barang tersebut statusnya sedang dipinjam
            if (strcmp(daftar[i].status, "Dipinjam") != 0) {
                printf("\n [!] PERINGATAN: Barang '%s' sudah ada di tempat.\n", daftar[i].nama);
                printf("     Status saat ini: %s\n", daftar[i].status);
            } else {
                // Proses Pengembalian (Update Data)
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
