#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tampilkanMenu() {
    printf("\n====================================\n");
    printf("SIMPASDES (Sarana Desa)\n");
    printf("====================================\n");
    printf("1. Tambah Jenis Sarana Baru\n"); // Fitur 1a
    printf("2. Tampilkan Inventaris Sarana\n"); // Fitur 1b
    printf("3. Catat Peminjaman Baru\n"); // Fitur 2
    printf("4. Cari Detail Sarana (Searching)\n"); // Fitur 3
    printf("5. Urutkan Jadwal Pengembalian (Sorting)\n"); // Fitur 4
    printf("6. Proses Pengembalian Sarana\n"); // Fitur 5
    printf("7. Keluar & Simpan Data\n");
    printf("------------------------------------\n");
    printf("Pilih menu (1-7): ");
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
