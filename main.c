// --- III. FUNGSI PENDUKUNG ---
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
