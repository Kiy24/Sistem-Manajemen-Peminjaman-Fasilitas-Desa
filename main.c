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
