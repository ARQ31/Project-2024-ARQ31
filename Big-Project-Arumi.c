// Programmer : Ariq Marwan Permana
// Program Bisnis Tur Arumi Bali

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define MAX_PENUMPANG 100

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

//LIST VARIABEL GLOBAL DAN STRUCT

//Pendeklerasian variabel class secara global yang berguna untuk sebagai penanda/flag fungsi pembayaran agar dapat digunakan secara universal
int adminflag;
int class;
int nyawa = 3;
int JumlahPenumpang = 2; //Pendeklarasian JumlahPenumpang secara global untuk digunakan pada fungsi IsiData dan fungsi CetakTiket
int jumlahkode; //Pengdeklerasian jumlahkode secara global agar dapat digunakan pada fungsi RegKode dan CekKodeUnik
char simpan[30] = { 0 };
char simpan2[30] = { 0 };
char kode[50]; //deklarasi kode untuk menyimpan kode unik        
char tanggal[10]; //deklarasi variabel tanggal secara global untuk digunakan pada fungsi PilihTanggal dan CetakTiket
char kodeunik[256] = { 0 }; // deklarasi variabel globa kodeunik untuk digunakan pada fungsi CekKodeUnik dan CetakTiket
char hari[2][20] = { 0 };
char bulan[2][20] = { 0 };
char gabungan[2][40] = { 0 };  // Array baru untuk menyimpan hasil gabungan array hari dan bulan pada fungsi PisahString
char class3[80];
float x; //deklarasi tipe data float ini untuk digunakan pada fungsi TambahPaket dan CetakTiket 
float B; //deklarasi variabel B secara global untuk digunakan pada fungsi TambahPaketB(babysitter) dan pembayaran 
float total; // deklarasi variabel global Total untuk digunakan pada fungsi Pembayaran dan Cetak Tiket 
float class2;

struct Klien1 { //struct ntuk menampung data penumpang
    char NIK[50][100], NomorTelepon[50][100];
    int Umur[100];
    char Nama[50][100];
    char Gender[50][100];
    char TTL[50][100];
    char Askot[50][100];
    char Email[50][100];
    char RiwayatPenyakit[80][100];
} klien1;

struct Klien { // Struct untuk fungsi UrutUmur
    char NamaLengkap[100];
    char JenisKelamin[100];
    char NIK[100];
    int Umur;
    char NomorTelepon[100];
    char TTL[100];
    char Askot[100];
    char Email[100];
    char RiwayatPenyakit[100];
}klien;

struct Admin{
    char Username[20];
    char Password[20];
}admin;

struct Paket {
    char nama[50];
    float harga;
};

//LIST FUNGSI/Prosedur YANG DIGUNAKAN (Protoype fungsi)

//Fungsi untuk pendukung program
void cls();
//Fungsi utama
int PreAdmin(int nyawa);
int Admin();
int DaftarPemasukan();
void RegKode(); //Fungsi untuk meregistrasi kode unik ke sistem agar klien dapat mencetak tiket
void DaftarAdmin();
void ListKode();
void ListDataPenumpang();
int DaftarKlien();
int CariKlien();
int DaftarBeliPaket();
int CariPaket1();
void PreMenuPaket1();
int MenuPaket1();

int Paket1();
int Paket1a();

int Paket2();
int Paket2a();

int Paket3();
int Paket3a();

//Masuk ke proses pembelian paket tour
int Pilihtanggal();
void IsiData();
int PisahString();
int IsiData2();

int TambahPaket();
int TambahPaketA();
int TambahPaketA1();
int TambahPaketA2();
int TambahPaketA3();
int TambahPaketB();

int CekDiskon();
int Pembayaran();

int CekKodeUnik(int nyawa);
int CetakTiket();
int SimpanPembayaran();
int Repurchase();

int CekUlangTahun();

//Prosedur untuk fitur pendukung program ini
void cls(){
    printf("\033[2J\033[H"); //Penggunaan ANSI Escape Codes untuk membersihkan layar pada program
}

void pause() { //untuk menghentinkan sementara proses program
    printf("Tekan sembarang tombol untuk melanjutkan...\n");
    getch();
}

void sleep(int seconds){
    #ifdef _WIN32
        Sleep(seconds * 1000); //konversi detik ke milidetik (sleep untuk Windows)
    #else
        sleep(seconds); // sleep untuk Unix/Linux/MacOS
    #endif
}

void waktu(){
    char bulan[15][12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    time_t t;
    t = time(NULL);
    struct tm* date;
    date= localtime(&t);
    if (date->tm_mon + 1 == 1){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[0], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[0]);
    } else if (date->tm_mon + 1 == 2){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[1], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[1]);
    } else if (date->tm_mon + 1 == 3){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[2], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[2]);
    } else if (date->tm_mon + 1 == 4){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[3], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[3]);
    } else if (date->tm_mon + 1== 5){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[4], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[4]);
    } else if (date->tm_mon + 1 == 6){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[5], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[5]);
    } else if (date->tm_mon + 1 == 7){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[6], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[6]);
    } else if (date->tm_mon + 1 == 8){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[7], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[7]);
    } else if (date->tm_mon + 1 == 9){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[8], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[8]);
    } else if (date->tm_mon + 1 == 10){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[9], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[9]);
    } else if (date->tm_mon + 1 == 11){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[10], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[10]);
    } else if (date->tm_mon + 1 == 12){
        sprintf(simpan, "%d %s %d", date->tm_mday, bulan[11], date->tm_year + 1900);
        sprintf(simpan2, "%d %s", date->tm_mday, bulan[11]);
    } else {
        printf("Error\n");
    }
}

void Arumi(){
    char temp[255];
    FILE *Arumi;

    // membuka file
    if ((Arumi = fopen("Arumi.txt","r")) == NULL){
        printf("Error: File tidak ada!");
        // Tutup program karena file gak ada.
        exit(1);
    }

    // baca isi file dengan gets lalu simpan ke buff
    while(fgets(temp, sizeof(temp), Arumi)){
        printf("%s", temp);
    }

    // tutup file
    fclose(Arumi);
}

int main(){  
    cls();
    waktu();
    int pilih;
    printf("Loading system");
    sleep(0.5);
    printf(". ");
    sleep(0.5);
    printf(". ");
    sleep(0.5);
    printf(".");
    cls();
    Arumi();
    printf("\n");
    printf("====================== SELAMAT DATANG DI ARUMI TOUR  ========================\n");
    printf("=> Tanggal : %s                                                   \n", simpan);
    printf("=============================================================================\n");
    printf("=> (1) Tentang Kami                                                         =\n");
    printf("=> (2) Menu Paket                                                           =\n");
    printf("=> (3) Login Admin                                                          =\n");
    printf("=> (4) Keluar                                                               =\n");
    printf("=============================================================================\n");
    printf("> Pilih opsi : "); scanf("%d", &pilih);getchar();
    switch (pilih){
        case 1 :
            cls();
            printf("=========== TENTANG KAMI ======\n");
            printf("= Bisnis Tur dari Bali yang telah ada sejak 2024\n");
            pause();
            main();
            break;
        case 2 :
            MenuPaket1();
            break;
        case 3 :
            PreAdmin(nyawa);
            break;
        case 4 :
            exit(0);
            break;
        default :
            printf("Pilihan anda tidak valid!\n");
            pause();
            main();
            return 1;
    }
    return 0;
}

int PreAdmin(int nyawa){
    cls();
    char username[20], password[20];
    FILE *Adminn = fopen("Admin.dat", "r");

    // membuka file
    if (Adminn == NULL){
        printf("=> Error: File tidak ditemukan!");
        pause();
        main();
    }

    if (nyawa == 0){
        printf("Kesempatan anda sudah habis!\n");
        pause();    
        main();
        return 0;
    }

    printf("====== LOGIN ADMIN ======\n");
    printf("=> Username : "); fgets(username, sizeof(username), stdin);
    printf("=> Password : "); fgets(password, sizeof(password), stdin); 

    while (fgets(admin.Username, sizeof(admin.Username), Adminn) != NULL && fgets(admin.Password, sizeof(admin.Password), Adminn) != NULL) {
        if (strcmp(username, admin.Username) == 0 && strcmp(password, admin.Password) == 0) {
            printf("Verifikasi admin berhasil!\n");
            sleep(2);
            fclose(Adminn);
            Admin();
        }
    }
    fclose(Adminn);
    printf("Kesempatan anda tersisa %d\n", nyawa-1);
    pause();
    return PreAdmin(nyawa - 1);
}


int Admin(){
    int pilihadmin;
    cls();
    printf("============ MODE ADMIN ============\n");
    printf("= (1) Registrasikan Kode Unik      =\n");
    printf("= (2) Daftar Pemasukan             =\n");
    printf("= (3) Daftar Akun Admin            =\n");    
    printf("= (4) Daftar Kode Unik             =\n");
    printf("= (5) Daftar Data Klien/Penumpang  =\n");
    printf("= (6) Daftar Data Pembelian Paket  =\n");
    printf("= (7) Cari Data Klien/Penumpang    =\n");
    printf("= (8) Keluar dari Mode Admin       =\n");
    printf("====================================\n");
    printf("Pilih opsi : ");scanf("%d", &pilihadmin);getchar();
    if (pilihadmin == 1){
        RegKode();
    } else if(pilihadmin == 2){
        DaftarPemasukan();
    } else if(pilihadmin == 3){
        DaftarAdmin();
    } else if(pilihadmin == 4){
        ListKode();
    } else if (pilihadmin == 5) {
        DaftarKlien();
    } else if (pilihadmin == 6){
        DaftarBeliPaket();
    } else if (pilihadmin == 7){
        CariKlien();
    } else if (pilihadmin == 8) {
        main();
    } else {
        printf("Pilihan anda tidak valid!\n");
        printf("\n");
        pause();
        Admin();
        return 1;
    }
}

int DaftarBeliPaket(){
    cls();
    char buff[255];
    FILE *file2 = fopen("Tiket.txt","r");

    // membuka file
    if (file2 == NULL){
        printf("Error: File tidak ada!");
        pause();
        Admin();
    }
    else {
        printf("========== DATA PEMBELIAN PAKET ==========\n");
        printf("\n");
        while(fgets(buff, sizeof(buff), file2) != NULL ){
            printf("%s", buff);
        }
    }
    fclose(file2);
    printf("\n");
    pause();
    Admin();
}

void RegKode(){
    cls();
    char pilih;
    FILE *simpan = fopen("kumpulan_kode.txt", "a");
    if (simpan == NULL) {
        printf("Gagal membuka database kumpulan_kode.txt!\n");
        pause();
        Admin();
    }

    printf("Masukkan jumlah kode yang ingin disimpan : "); 
    scanf("%d", &jumlahkode);getchar();

    for (int m=0; m<jumlahkode; m++){
        printf("Masukkan kode ke-%d : ", m+1);
        fgets(kode, sizeof(kode), stdin); // gunakan fgets untuk membaca string dengan spasi 
        fprintf(simpan, "%s", kode);
    }

    printf("Kode unik telah teregistrasi!\n");
    pause();
    fclose(simpan);
    Admin();
}

int DaftarPemasukan(){
    cls();
    char temp[256];
    FILE *fp1 = fopen("data_income.dat", "rb");

    if (fp1 == NULL){
        printf("Error: File tidak ditemukan!");
        // Tutup program karena file gak ada.
        fclose(fp1);
        pause();
        Admin();
        return 1;
    }

    printf("===== DAFTAR PEMASUKAN =====\n");
    printf("\n");
    while(fgets(temp, sizeof(temp), fp1)){
        printf("%s", temp);
    }
    printf("\n");
    fclose(fp1);
    pause();
    Admin();
    return 0;
}

void DaftarAdmin(){
    cls();
    char buff[255];
    FILE *fp = fopen("Admin.dat","rb");

    // membuka file
    if (fp == NULL){
        printf("Error: File tidak ditemukan!");
        // Tutup program karena file gak ada.
        pause();
        Admin();
    }

    printf("===== DAFTAR AKUN ADMIN DAN PASSWORD =====\n");
    printf("\n");
    while(fgets(buff, sizeof(buff), fp)){
        printf("%s", buff);
    }
    printf("\n\n");
    fclose(fp);
    pause();
    Admin();
}

void bubbleSortUmur(struct Klien klien[], int n) {
    int temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (klien[j].Umur > klien[j+1].Umur) {
                temp = klien[j].Umur;
                klien[j].Umur = klien[j+1].Umur;
                klien[j+1].Umur = temp;
            }
        }
    }
}

void ListKode(){
    cls();
    char buff[255];
    FILE *file2 = fopen("kumpulan_kode.txt","r");

    // membuka file
    if (file2 == NULL){
        printf("Error: File tidak ada!");
        pause();
        Admin();
    }
    else {
        printf("========== DATA KODE UNIK ==========\n");
        printf("\n");
        while(fgets(buff, sizeof(buff), file2) != NULL ){
            printf("%s", buff);
        }
    }
    fclose(file2);
    printf("\n");
    pause();
    Admin();
}

//List Sorting untuk Sort Data Klien
void NamaLengkap(struct Klien klien[], int hitung) {
    struct Klien temp;
    for (int i = 0; i < hitung - 1; i++) {
        for (int j = i + 1; j < hitung; j++) {
            if (strcmp(klien[i].NamaLengkap, klien[j].NamaLengkap) > 0) {
                temp = klien[i];
                klien[i] = klien[j];
                klien[j] = temp;
            }
        }
    }
}

void JenisKelamin(struct Klien klien[], int hitung) {
    struct Klien temp;
    for (int i = 0; i < hitung - 1; i++) {
        for (int j = i + 1; j < hitung; j++) {
            if (strcmp(klien[i].JenisKelamin, klien[j].JenisKelamin) > 0) {
                temp = klien[i];
                klien[i] = klien[j];
                klien[j] = temp;
            }
        }
    }
}

void Askot(struct Klien klien[], int hitung) {
    struct Klien temp;
    for (int i = 0; i < hitung - 1; i++) {
        for (int j = i + 1; j < hitung; j++) {
            if (strcmp(klien[i].Askot, klien[j].Askot) > 0) {
                temp = klien[i];
                klien[i] = klien[j];
                klien[j] = temp;
            }
        }
    }
}

void Umur(struct Klien klien[], int hitung) {
    struct Klien temp;
    for (int i = 0; i < hitung - 1; i++) {
        for (int j = i + 1; j < hitung; j++) {
            if (klien[i].Umur > klien[j].Umur) {
                temp = klien[i];
                klien[i] = klien[j];
                klien[j] = temp;
            }
        }
    }
}

int DaftarKlien() {
    cls();
    struct Klien klien[1000];
    int hitung = 0;

    FILE *file = fopen("data_penumpang.dat", "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file.\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "=> Nama Lengkap")) {
            sscanf(line, "=> Nama Lengkap : %[^\n]", klien[hitung].NamaLengkap);
            fgets(line, sizeof(line), file); // Baca Jenis Kelamin
            sscanf(line, "=> Jenis Kelamin : %[^\n]", klien[hitung].JenisKelamin);
            fgets(line, sizeof(line), file); // Baca NIK
            sscanf(line, "=> NIK : %[^\n]", klien[hitung].NIK);
            fgets(line, sizeof(line), file); // Baca Umur
            sscanf(line, "=> Umur : %d", &klien[hitung].Umur);
            fgets(line, sizeof(line), file); // Baca Nomor Telepon
            sscanf(line, "=> Nomor Telepon : %[^\n]", klien[hitung].NomorTelepon);
            fgets(line, sizeof(line), file); // Baca TTL
            sscanf(line, "=> Tempat, Tanggal Lahir : %[^\n]", klien[hitung].TTL);
            fgets(line, sizeof(line), file); // Baca Askot
            sscanf(line, "=> Asal Kota : %[^\n]", klien[hitung].Askot);
            fgets(line, sizeof(line), file); // Baca Email
            sscanf(line, "=> Email : %[^\n]", klien[hitung].Email);
            fgets(line, sizeof(line), file); // Baca Riwayat Penyakit
            sscanf(line, "=> Riwayat Penyakit : %[^\n]", klien[hitung].RiwayatPenyakit);

            hitung++;
            if (hitung >= 1000) {
                printf("Peringatan: Jumlah data melebihi kapasitas array.\n");
                break;
            }
        }
    }
    fclose(file);

    int pilih;
    char smtr[50];
    printf("========== Pilih Sorting Berdasarkan ==========\n");
    printf("= 1. Nama Lengkap                             =\n");
    printf("= 2. Jenis Kelamin                            =\n");
    printf("= 3. Asal Kota                                =\n");
    printf("= 4. Umur                                     =\n");
    printf("= 5. Kembali ke menu sebelumnya               =\n");
    printf("===============================================\n");
    printf("=> Pilih opsi : "); 
    scanf("%d", &pilih);getchar();

    switch (pilih) {
        case 1:
            NamaLengkap(klien, hitung);
            sprintf(smtr, "Nama Lengkap");
            break;
        case 2:
            JenisKelamin(klien, hitung);
            sprintf(smtr, "Jenis Kelamin");
            break;
        case 3:
            Askot(klien, hitung);
            sprintf(smtr, "Asal Kota");
            break;
        case 4:
            Umur(klien, hitung);
            sprintf(smtr, "Umur");
            break;
        case 5 :
            Admin();
            break;
        default:
            printf("Pilihan tidak valid.\n");
            return 1;
    }

    // Menampilkan array setelah sorting
    printf("\nPengurutan %s Ascending:\n", smtr);
    for (int i = 0; i < hitung; i++) {
        printf("%d.\n", i+1);
        printf("Nama Lengkap          : %s\n", klien[i].NamaLengkap);
        printf("Jenis Kelamin         : %s\n", klien[i].JenisKelamin);
        printf("NIK                   : %s\n", klien[i].NIK);
        printf("Umur                  : %d\n", klien[i].Umur);
        printf("Nomor Telepon         : %s\n", klien[i].NomorTelepon);
        printf("Tempat, Tanggal Lahir : %s\n", klien[i].TTL);
        printf("Asal Kota             : %s\n", klien[i].Askot);
        printf("Email                 : %s\n", klien[i].Email);
        printf("Riwayat Penyakit      : %s\n", klien[i].RiwayatPenyakit);
        printf("\n");
    }
    pause();
    Admin();
    return 0;
}


int CariKlien() {
    struct Klien klien2[256];
    cls();
    FILE *file1 = fopen("Data_penumpang.dat", "rb");
    if (file1 == NULL) {
        printf("Error : Gagal membuka file.\n");
        pause();
        return 1;
    }
    int i = 0, ketemu = 0;
    char cari[100];
    int cari2;
    char temp[256];
    int pilih;

    printf("========== Cari Data Klien ==========\n");
    printf("= (1) Nama Lengkap                  =\n");
    printf("= (2) Umur                          =\n");
    printf("= (3) Jenis Kelamin                 =\n");
    printf("= (4) Asal Kota                     =\n");
    printf("= (5) Kembali ke menu sebelumnya    =\n");
    printf("=====================================\n");
    printf("=> Pilih opsi : "); scanf("%d", &pilih); getchar();

    if (pilih == 1) {
        printf("Masukan Nama yang ingin dicari: ");
        fgets(cari, sizeof(cari), stdin);
        cari[strcspn(cari, "\n")] = 0;
    } else if (pilih == 2) {
        printf("Masukan Umur yang ingin dicari: ");
        scanf("%d", &cari2); getchar();
    } else if (pilih == 3) {
        printf("Masukan Jenis Kelamin yang ingin dicari: ");
        fgets(cari, sizeof(cari), stdin);
        cari[strcspn(cari, "\n")] = 0;
    } else if (pilih == 4) {
        printf("Masukan Asal Kota yang ingin dicari: ");
        fgets(cari, sizeof(cari), stdin);
        cari[strcspn(cari, "\n")] = 0;
    } else if (pilih == 5) {
        Admin();
    } else {
        printf("Pilihan tidak valid.\n");
        CariKlien();
        return 1;
    }

    while (fgets(temp, sizeof(temp), file1) != NULL) {
        if (strstr(temp, "Nama Lengkap")) {
            sscanf(temp, "=> Nama Lengkap          : %[^\n]", klien2[i].NamaLengkap);
            fgets(temp, sizeof(temp), file1);
            sscanf(temp, "=> Jenis Kelamin         : %[^\n]", klien2[i].JenisKelamin);
            fgets(temp, sizeof(temp), file1);
            sscanf(temp, "=> NIK                   : %[^\n]", klien2[i].NIK);
            fgets(temp, sizeof(temp), file1);
            sscanf(temp, "=> Umur                  : %d", &klien2[i].Umur);
            fgets(temp, sizeof(temp), file1);
            sscanf(temp, "=> Nomor Telepon         : %[^\n]", klien2[i].NomorTelepon);
            fgets(temp, sizeof(temp), file1);
            sscanf(temp, "=> Tempat, Tanggal Lahir : %[^\n]", klien2[i].TTL);
            fgets(temp, sizeof(temp), file1);
            sscanf(temp, "=> Asal Kota             : %[^\n]", klien2[i].Askot);
            fgets(temp, sizeof(temp), file1);
            sscanf(temp, "=> Email                 : %[^\n]", klien2[i].Email);
            fgets(temp, sizeof(temp), file1);
            sscanf(temp, "=> Riwayat Penyakit      : %[^\n]", klien2[i].RiwayatPenyakit);

            if ((pilih == 1 && strstr(klien2[i].NamaLengkap, cari)) ||  (pilih == 2 && klien2[i].Umur == cari2) ||  (pilih == 3 && strstr(klien2[i].JenisKelamin, cari)) ||  (pilih == 4 && strstr(klien2[i].Askot, cari))) {
                ketemu = 1;
                i++;
            }
        }
    }
    fclose(file1);

    if (ketemu) {
        cls();
        printf("========== DATA DITEMUKAN! ==========\n");
        printf("\n");
        for (int j = 0; j < i; j++) {
            printf("\n=> Nama Lengkap          : %s\n", klien2[j].NamaLengkap);
            printf("=> Tempat, Tanggal Lahir : %s\n", klien2[j].TTL);
            if (pilih == 1 || pilih == 2) {
                printf("=> Umur                  : %d\n", klien2[j].Umur);
            }
            if (pilih == 3) {
                printf("=> Jenis Kelamin         : %s\n", klien2[j].JenisKelamin);
            }
            if (pilih == 4) {
                printf("=> Asal Kota             : %s\n", klien2[j].Askot);
            }
        }
        printf("\n");
        printf("=> Jumlah data yang ditemukan: %d\n", i);
        pause();
        CariKlien();
    } else {
        printf("Data tidak ditemukan.\n");
    }
    pause();
    CariKlien();
    return 0;
}

int MenuPaket1(){ //Fungsi utama memuat menu pilih pake tour liburan ke Bali
    cls();
    int menu;
    printf("+===============+ PILIH PAKET TOUR LIBURAN +=============+\n");
    printf("+ (1) Paket Ekonomis Bali 2Hari/1Malam                   +\n");
    printf("+ (2) Paket Honey Moon 3 Hari/2 Malam                    +\n");
    printf("+ (3) Paket Wisata Bali + Nusa Penida 3Hari/2Malam       +\n");
    printf("+ (4) Cari Paket Sesuai Budget                           +\n");
    printf("+ (5) Keluar                                             +\n");
    printf("+========================================================+\n");
    printf ("=> Pilih menu : "); scanf("%d", &menu);getchar();

    switch (menu){
        case 1 :
           Paket1();
           break;
        case 2 :
            Paket2();
            break;
        case 3 :
            Paket3();
            break;
        case 4 :
            CariPaket1();
            break;
        case 5 :
            main();
            break;
        case 6 :
            PreAdmin(nyawa);
            break;
        default :
            printf("Pilihan Tidak Ditemukan!\n");
            printf("Kembali ke Menu Utama");
            MenuPaket1();
            return 1;
        
    }
    return 0;
}

void cariPaket(struct Paket paket[], int n, float budget){
    int ditemukan = 0;
    
    printf("Paket yang sesuai dengan budget Anda:\n");
    for (int i = 0; i < n; i++) {
        if (paket[i].harga <= budget) {
            printf("%s - Rp%.2f\n", paket[i].nama, paket[i].harga);
            ditemukan++;
        }
    }
    pause();
    MenuPaket1();
    
    if (ditemukan == 0) {
        printf("Maaf, tidak ada paket yang sesuai dengan budget Anda.\n");
        pause();
        MenuPaket1();
    }
}

int CariPaket1() {
    struct Paket paket[] = {
        {"Paket Ekonomis Bali 2Hari/1Malam", 2500000.0},
        {"Paket Honey Moon 3 Hari/2 Malam", 3500000.0},
        {"Paket Wisata Bali + Nusa Penida 3Hari/2Malam", 4500000.0},
    };
    
    int n = sizeof(paket) / sizeof(paket[0]);
    float budget;
    
    printf("Masukkan budget Anda: Rp");
    scanf("%f", &budget);
    
    // Memanggil fungsi pencarian
    cariPaket(paket, n, budget);
    MenuPaket1();
    return 0;
}

int Paket1(){ //Catatan Alur Fungsi Paket1 = Paket1 -> Paket1a
    cls();
    int Opsi1, PEB;
    printf("========== PAKET EKONOMIS BALI 2 HARI/1 MALAM ==========\n");
    printf("1) Detail Paket\n2) Harga Paket\n3) Beli Paket\n4) Kembali ke Menu Sebelumnya\n");
    printf("Pilih Menu = ");scanf("%d", &PEB);getchar();
    if (PEB == 1){
        Paket1a();
    }
    else if (PEB == 2) {
        cls();
        printf("Harga Paket Ekonomis Bali untuk 2 Hari 1 Malam :\n");
        printf("Rp2.500.000\n");
        pause();
        Paket1();
    }
    else if (PEB == 3) {
        cls();
        sprintf(class3, "PAKET EKONOMIS BALI 2 HARI/1 MALAM");
        class2 = 2500000;
        class = 1;
        printf("Apakah anda yakin ingin memilih paket ini?\n");
        printf("1) Iya\n");
        printf("2) Tidak\n");
        printf("Pilih opsi : ");scanf("%d", &Opsi1);getchar();
        if (Opsi1 == 1){
            IsiData();
        } else if (Opsi1 == 2){
            Paket1();
        } else {
            printf("Pilihan anda tidak valid!\n");
            printf("\n");
            pause();
            Paket1();
            IsiData();
            return 1;
        }
    }
    else if (PEB == 4) {
        MenuPaket1();
    }
    else{
        printf("Input tidak valid, pilih opsi lain!");
        pause();
        Paket1();
        return 1;
    }
}

int Paket1a(){ //Fungsi untuk opsi detail paket1 (Paket Ekonomi)
        cls();
        int menuPEB;
        printf("================ MENU ================\n");
        printf("= (1) SUSUNAN ACARA                  =\n");
        printf("= (2) FASILITAS                      =\n");
        printf("= (3) SYARAT DAN KETENTUAN           =\n");
        printf("= (4) Kembali ke Menu Sebelumnya     =\n");
        printf("======================================\n");
        printf("=> Pilih Menu : ");scanf("%d", &menuPEB);getchar();
        switch (menuPEB){
            case 1 :
                cls();
                printf("===== SUSUNAN ACARA =====\n");
                printf("\n");
                printf("Hari 1 : Airport-Pantai Melasti-La Planca Beach Club\n");
                printf("\t- Dijemput di Airport Ngurah Rai Bali\n\t- Tour ke Pantai Pandawa\n\t- Menuju Pantai Melasti\n\t- Melihat sunset di La Planca Beach Club Seminyak\n\t- Check in hotel dan beristirahat\n");
                printf("Hari 2 : Nusa Penida Tour\n");
                printf("\t- Sarapan pagi 07.30 WITA\n\t- Menuju Pantai Sanur untuk penyebrangan ke Nusa Penida\n\t- Tiba di Nusa Penida dilanjutkan tour satu hari dengan 2 opsi pilihan:\n\t\t- Trip Barat: Pantai Crystal Bay, Angel Billabong, Broken Beach, Pantai Kelingking.\n\t\t- Trip Timur: Bukit Teletubis, Pantai Atuh, Pulau Seribu/Rumah Pohon, Pantai Diamond dan Goa Giri Putri\n\t- Makan siang di restaurant setempat\n\t- Jam 16.00 menuju pelabuhan untuk kembali ke Sanur\n\t- Tiba di sanur makan malam di Dwika restaurant\n\t- Diantar ke hotel untuk istirahat\n");
                printf("\n");
                pause();
                Paket1a();
                break;
            case 2 :
                cls();
                printf("========== FASILITAS ==========\n");
                printf("Paket Sudah Termasuk : \n");
                printf("\t- 2 malam menginap di hotel Swiss BelExpress Legian Kuta (sekamar berdua)\n\t- Private transport, sesuai program diatas\n\t- Tiket masuk objek wisata, sesuai program\n\t- 2x makan pagi, 1x makan siang dan 1x makan malam\n\t- Air mineral @500ml/hari\n\t Sopir merangkap pemandu wisata\n");
                printf("Paket Belum Termasuk : \n");
                printf("\t- Tiket pesawat & keperluan pribadi\n\t- Makan malam di La Plancha Beach club\n\t- Tipping (sukarela)\n");
                pause();
                Paket1a();
                break;
            case 3 :
                cls();
                printf("=========== SYARAT DAN KETENTUAN ==========\n");
                printf("1) Peserta\n");
                printf("\t- Peserta minimal 2 orang dewasa\n\t- Satu kamar hotel untuk 2 orang\n\t- Peserta ketiga atau ganjil akan digabung di dalam kamar yang berbeda dengan tambahan extra bed\n\t- Jika peserta ketiga atau lebih merupakan anak atau bayi akan digabung satu kamar dengan orang tua\n\t- Jika jumlah anak atau bayi tidak cukup pada satu kamar, maka akan ditempatkan di kamar yang berbeda");
                printf("\n");
                printf("2) Pembayaran\n");
                printf("\t- 50% Deposit wajib ditransfer pada saat pemesanan, sisanya dilunasi setelelah tiba di Bali\n\t- Transfer pembayaran wajib dilakukan setelah melakukan pemesanan, lalu melakukan konfirmasi ke CP yang telah diberikan\n\t- Bukti transfer bisa dikirimkan melalui WhatsApp 0811-9999-9777\n\t- Setelah melakukan pembayaran, kami akan kirimkan kembali Detail Invoice, sebagai bukti bahwa kami \n\t  sudah menerima pembayaran dan sekaligus menyatakan reservasi telah terkonfirmasi");
                printf("\n");
                printf("3) Pembatalan\n");
                printf("\t- Jika terjadi pembatalan setelah transfer, deposit akan kami kembalikan sesuai ketentuan dari vendor kami,\n\t  seperti: hotel, dan pendukung aktivitas lainnya\n\t- Deposit yang masih ada pada kami (sisa pembayaran hotel dll), akan kami kembalikan, dan untuk deposit yang sudah\n\t  kami bayarkan akan mengikuti ketentuan dari vendor kami, seperti; hotel, restaurant, dan pihak ketiga pendukung aktivitas wisata ini\n");
                printf("\n");
                pause();
                Paket1a();
                break;
            case 4 :
                Paket1();
                break;
            default :
                printf("Input tidak ditemukan, pilih menu yang lain!");
                Paket1a();
                return 1;
        }
    return 0;
}

int Paket2(){
    cls();
    int Opsi2, PHM;
    printf("========== PAKET HONEY MOON 3 HARI/2 MALAM ==========\n");
    printf("1) Detail Paket\n2) Harga Paket\n3) Beli Paket\n4) Kembali ke Menu Sebelumnya\n");
    printf("Pilih Menu = ");scanf("%d", &PHM);getchar();
    if (PHM == 1){
        Paket2a();
    }
    else if (PHM == 2){
        cls();
        printf("Paket Honey Moon 3 Hari/2 Malam : \n");
        printf("Rp3.500.000");
        pause();
        Paket2();
    }
    else if (PHM == 3) {
        cls();
        sprintf(class3, "PAKET HONEY MOON 3 HARI/2 MALAM");
        class2 = 3500000;
        class = 2;
        printf("Apakah anda yakin ingin memilih paket ini?\n");
        printf("1) Iya\n");
        printf("2) Tidak\n");
        printf("Pilih opsi : ");scanf("%d", &Opsi2);getchar();
        if (Opsi2 == 1){
            IsiData();
        } else if (Opsi2 == 2){
            Paket2();
        } else {
            printf("Pilihan anda tidak valid!\n");
            printf("\n");
            pause();
            Paket2();
            IsiData();
            return 1;
        }
    }
    else if (PHM == 4){
        MenuPaket1();
    }
    else {
        printf("Input tidak valid, pilih opsi lain!");
        Paket2();
        return 1;
    }
    return 0;
}

int Paket2a(){
    cls();
    int menuPHM;
    printf("================ MENU ================\n");
    printf("= (1) SUSUNAN ACARA                  =\n");
    printf("= (2) FASILITAS                      =\n");
    printf("= (3) SYARAT DAN KETENTUAN           =\n");
    printf("= (4) Kembali ke Menu Sebelumnya     =\n");
    printf("======================================\n");
    printf("Pilih Menu = ");scanf("%d", &menuPHM);getchar();
    switch (menuPHM){
        case 1 :
            cls();
            printf("===== SUSUNAN ACARA =====\n");
            printf("\n");
            printf("Hari 1: Airport - Pantai Pandawa/melasti-Jimbaran Seafood Dinner\n");
            printf("\t- Dijemput di Airport Ngurah Rai Bali\n\t- Tour ke Pantai Pandawa/Melasti\n\t- Tour ke Uluwatu.\n\t- Makan malam di tepi pantai Jimbaran\n\t- Check in hotel/Acara Bebas\n");
            printf("Hari 2: Foto adat Bali-Bedugul-Tanah Lot Sunset Tour\n");
            printf("\t- Makan pagi di hotel\n\t- Berfoto dengan tata rias ala penganten Bali\n\t- Menuju Pura Ulun Danu Bedugul\n\t- Makan siang di Mentari\n\t- Handara Gate/the gate of heaven\n\t- Tanah Lot sunset\n\t- Makan malam di Dwika restaurant\n\t- Kembali ke hotel/acara bebas\n");
            printf("Hari 3: Denpasar city-Kuta around-airport\n");
            printf("\t- Makan pagi dihotel, check out hotel\n\t- Keliling kota Denpasar\n\t- Shopping Kuta area\n\t- Diantar kembali ke airport\n\t- Acara selesai\n");
            printf("\n");
            pause();
            Paket2a();
            break;
        case 2 :
            cls();
            printf("===== FASILITAS =====\n");
            printf("Paket Sudah Termasuk : \n");
            printf("\t- 2 malam menginap di hotel Swiss BelExpress Legian Kuta\n\t- Antar jemput airport Bali ke hotel\n\t- Transport untuk tour sesuai program\n\t- Tiket masuk objek wisata\n\t- Makan pagi, makan siang, dan makan malam\n\t- Sopir merangkap pemandu wisata\n\t- Air mineral @500ml per hari\n");
            printf("\n");
            printf("Paket Belum Termasuk : \n");
            printf("\t- Tiket pesawat, dan Keperluan pribadi\n\t- Tipping (sukarela)\n");
            pause();
            Paket2a();
            break;
        case 3 :
            cls();
            printf("===== SYARAT DAN KETENTUAN =====\n");
            printf("1) Peserta\n");
            printf("\t- Hanya berlaku untuk wisatawan domestik\n\t- Berlaku untuk Pre-Honeymoon\n\t- Peserta ketiga atau ganjil akan digabung di dalam kamar yang berbeda dengan tambahan extra bed\n\t- Jika peserta ketiga atau lebih merupakan anak atau bayi akan digabung satu kamar dengan orang tua\n\t Jika jumlah anak atau bayi tidak cukup pada satu kamar, maka akan ditempatkan di kamar yang berbeda");
            printf("\n");
            printf("2) Pembayaran\n");
            printf("\t- 50% Deposit wajib ditransfer pada saat pemesanan, sisanya dilunasi setelelah tiba di Bali\n\t- Transfer pembayaran wajib dilakukan setelah melakukan pemesanan, lalu melakukan konfirmasi ke CP yang telah diberikan\n\t- Bukti transfer bisa dikirimkan melalui WhatsApp 0811-9999-9777\n\t- Setelah melakukan pembayaran, kami akan kirimkan kembali Detail Invoice, sebagai bukti bahwa kami\n\t  sudah menerima pembayaran dan sekaligus menyatakan reservasi telah terkonfirmasi\n");
            printf("\n");
            printf("3) Pembatalan\n");
            printf("\t- Jika terjadi pembatalan setelah transfer, deposit akan kami kembalikan sesuai ketentuan dari vendor kami, seperti: hotel, dan pendukung aktivitas lainnya\n\t- Deposit yang masih ada pada kami (sisa pembayaran hotel dll), akan kami kembalikan, dan untuk deposit yang sudah kami bayarkan akan mengikuti ketentuan dari\n\t  vendor kami, seperti; hotel, restaurant, dan pihak ketiga pendukung aktivitas wisata ini\n");
            pause();
            Paket2a();
            break;
        case 4 :
            Paket2();
            break;
        default :
            printf("Pilihan tidak ditemukan!\n");
            pause();
            Paket2a();
            return 1;
    }

    return 0;
}

int Paket3(){
    cls();
    int Opsi3, PWB;
    printf("========== PAKET WISATA BALI + NUSA PENIDA 3HARI/2MALAM ==========\n");
    printf("1) Detail Paket\n2) Harga Paket\n3) Beli Paket\n4) Kembali ke Menu Sebelumnya\n");
    printf("Pilih Menu = ");scanf("%d", &PWB);getchar();
    if (PWB == 1){
        Paket3a();
    }
    else if (PWB == 2) {
        cls();
        printf("Paket Wisata Bali + Nusa Penida 3Hari/2Malam\n");
        printf("Rp.4.500.000\n");
        pause();
        Paket3();
    }
    else if (PWB == 3) {
        cls();
        sprintf(class3, "PAKET WISATA BALI + NUSA PENIDA 3 HARI/2 MALAM");
        class2 = 4500000;
        class = 3;
        printf("Apakah anda yakin ingin memilih paket ini?\n");
        printf("1) Iya\n");
        printf("2) Tidak\n");
        printf("Pilih opsi : ");scanf("%d", &Opsi3);getchar();
        if (Opsi3 == 1){
            IsiData();
        } else if (Opsi3 == 2){
            Paket3();
        } else {
            printf("Pilihan anda tidak valid!\n");
            printf("\n");
            pause();
            Paket3();
            return 1;
        }
    }
    else if (PWB == 4) {
        MenuPaket1();
    }
    else{
        printf("Input tidak valid, pilih opsi lain!");
        Paket3();
        return 1;
    }
    return 0;
}

int Paket3a(){
    cls();
    int menuPWB;
    printf("================ MENU ================\n");
    printf("= (1) SUSUNAN ACARA                  =\n");
    printf("= (2) FASILITAS                      =\n");
    printf("= (3) SYARAT DAN KETENTUAN           =\n");
    printf("= (4) Kembali ke Menu Sebelumnya     =\n");
    printf("======================================\n");
    printf("Pilih Menu = ");scanf("%d", &menuPWB);getchar();
    switch (menuPWB){
        case 1 :
            cls();
            printf("===== SUSUNAN ACARA =====\n");
            printf("Hari 1: Airport-Pantai Melasti-La Planca Beach Club\n");
            printf("\t- Dijemput di Airport Ngurah Rai Bali\n\t- Tour ke Pantai Pandawa\n\t- Tour ke Pantai Melasti.\n\t- Melihat sunset di La Planca Beach Club Seminyak\n\t- Check in hotel dan beristirahat\n");
            printf("Hari 2 : Nusa Penida Tour\n");
            printf("\t- Makan pagi di hotel, tour start dari hotel jam 07.30 wita\n\t- Menuju Pantai Sanur untuk penyebrangan ke Nusa Penida\n\t- Tiba di Nusa Penida dilanjutkan tour satu hari dengan 2 opsi pilihan:\n\t\t- Trip Barat: Pantai Crystal Bay, Angel Billabong, Broken Beach, Pantai Kelingking\n\t\t- Trip Timur: Bukit Teletubis, Pantai Atuh, Pulau Seribu/Rumah Pohon, Pantai Diamond dan Goa Giri Putri\n\t- Makan siang di restaurant setempat\n\t- Jam 16.00 menuju pelabuhan untuk kembali ke Sanur\n\t- Tiba di sanur makan malam di Dwika restaurant\n\t- Diantar ke hotel untuk istirahat\n");
            printf("Hari 3: Tanjung Benoa - Kuta around - Airport\n");
            printf("\t- Makan pagi di hotel, dilanjutkan check out hotel dan tour menuju:\n\t- Tanjung Benoa, pusat rekreasi water sport (include banana boat 1x putaran)\n\t- Shopping di seputaran Kuta, krisna, Joger, agung Bali, centro dll\n\t- Makan siang di seputar Kuta area\n\t- Diantar menuju airport untuk penerbangan kembali\n");
            pause();
            Paket3a();
            break;
        case 2 :
            printf("======= FASILITAS =======\n");
            printf("Paket Sudah Termasuk : \n");
            printf("\t- 2 malam menginap di Hotel Swiss Bel Express Legian Kuta\n\t- Transport Mulai dari penjemputan di Airport Ngurah Rai Bali, Tour sesuai program dan diantar kembali ke airport pada hari terakhir\n\t- Tiket fastboat ke Nusa Penida (pp)\n\t- Tour satu hari di Nusa Penida\n\t- Makan pagi, makan siang, makan malam\n\t- Semua tiket masuk objek wisata sesuai program\n\t- 1x Banana boat di Tanjung Benoa\n\t- Air mineral 1 botol per hari selama tour\n");
            printf("Paket Belum Termasuk : \n");
            printf("\t- Voucher water sport di Tanjung Benoa (selain Banana boat)\n\t- Makanan di La Planca Beach Club\n\t- Tiket pesawat / transportasi dari daerah asal menuju Bali\n\t- Keperluan pribadi diluar program tertulis diatas\n");
            pause();
            Paket3a();
            break;
        case 3 :
            printf("========= SYARAT DAN KETENTUAN =========\n");
            printf("1) Peserta\n");
            printf("\t- Minimal peserta 2 orang dewasa\n\t- Satu kamar hotel untuk 2 orang\n\t- Peserta ketiga atau lebih akan digabung di dalam kamar yang berbeda dengan tambahan extra bed\n\t- Jika peserta ketiga atau lebih merupakan anak atau bayi, maka akan digabung satu kamar dengan orang tua\n\t Jika jumlah anak atau bayi tidak cukup pada satu kamar, maka akan ditempatkan di kamar yang berbeda\n");
            printf("\n");
            printf("2) Pembayaran\n");
            printf("\t- 50% Deposit wajib ditransfer pada saat pemesanan, sisanya dilunasi setelelah tiba di Bali\n\t- Transfer pembayaran wajib dilakukan setelah melakukan pemesanan, lalu melakukan konfirmasi ke CP yang telah diberikan\n\t- Bukti transfer bisa dikirimkan melalui WhatsApp 0811-9999-9777\n\t- Setelah melakukan pembayaran, kami akan kirimkan kembali Detail Invoice, sebagai bukti bahwa kami sudah menerima pembayaran dan sekaligus menyatakan reservasi telah terkonfirmasi");
            printf("\n");
            printf("3) Pembatalan\n");
            printf("\t- Jika terjadi pembatalan setelah transfer, deposit akan kami kembalikan sesuai ketentuan dari vendor kami,\n\t  Seperti: hotel, dan pendukung aktivitas lainnya\n\t- Deposit yang masih ada pada kami (sisa pembayaran hotel dll), akan kami kembalikan, dan untuk deposit yang sudah kami bayarkan akan mengikuti ketentuan dari vendor kami, seperti; hotel, restaurant, dan pihak ketiga pendukung aktivitas wisata ini\n");
            pause();
            Paket3a();
            break;
        case 4 :
            Paket3();
            break;
        default :
            printf("Pilihan tidak ditemukan!\n");
            pause();
            Paket3a();
            return 1;
    }
    return 0;
}

void IsiData(){
    int i,j;
    char temp[255];
    cls();
    printf("======================== DATA KLIEN =========================\n");
    printf("= Contoh untuk mengisi tanggal keberangkatan : 17 Juni 2024 =\n");
    printf("=============================================================\n");
    printf("Masukkan Tanggal Keberangkatan = ");gets(tanggal);
    cls();
    printf("\n");
    printf("=> Jumlah maksimal penumpang adalah dua orang, jika membawa anak, bayi maupun lansia\n");
    printf("=> Silahkan isi di menu tambahan yang akan datang di proses selanjutnya");
    printf("\n");
    pause();
    cls();
    printf("=> Contoh pengisian untuk Jenis Kelamin         : (Laki - laki/Perempuan)\n");
    printf("=> Contoh pengisian untuk Tempat, Tanggal Lahir : Hiroshima, 7 Agustus 1945\n");    
    printf("\n");
    pause();
    cls();
    for(i=0; i < JumlahPenumpang; i++){
        printf("=============== DATA PENUMPANG KE - %d ===============\n", i+1);       
        printf("1) Nama Lengkap           : ");gets(klien1.Nama[i]);
        printf("2) Jenis Kelamin          : ");gets(klien1.Gender[i]);
        printf("3) NIK                    : ");gets(klien1.NIK[i]);
        printf("4) Umur                   : ");scanf("%d", &klien1.Umur[i]);getchar();
        printf("5) Nomor Telepon          : ");gets(klien1.NomorTelepon[i]);
        printf("6) Tempat, Tanggal Lahir  : ");gets(klien1.TTL[i]);
        printf("7) Asal Kota              : ");gets(klien1.Askot[i]);
        printf("8) Email                  : ");gets(klien1.Email[i]);
        printf("9) Riwayat Penyakit       : ");gets(klien1.RiwayatPenyakit[i]);
    }
    cls();
    for(j=0; j < JumlahPenumpang; j++){
        printf("================= Data Penumpang ===================\n");
        printf("1) Nama Lengkap           : %s\n", klien1.Nama[j]);
        printf("2) Jenis Kelamin          : %s\n", klien1.Gender[j]);
        printf("3) NIK                    : %s\n", klien1.NIK[j]);
        printf("4) Umur                   : %d\n", klien1.Umur[j]);
        printf("5) Nomor Telepon          : %s\n", klien1.NomorTelepon[j]);
        printf("6) Tempat, Tanggal Lahir  : %s\n", klien1.TTL[j]);
        printf("7) Asal Kota              : %s\n", klien1.Askot[j]);
        printf("8) Email                  : %s\n", klien1.Email[j]);
        printf("9) Riwayat Penyakit       : %s\n", klien1.RiwayatPenyakit[j]);
        printf("================================================\n");
    }
    pause();
    PisahString();
}

int PisahString(){
    char tempat[2][80] = { 0 }; 
    char tahun[2][50] = { 0 };
    for (int i = 0; i < 2 ; i++) {
        sscanf(klien1.TTL[i], "%[^,], %s %s %s", tempat[i], hari[i], bulan[i], tahun[i]);
        sprintf(gabungan[i], "%s %s", hari[i], bulan[i]);
        // printf("Hari dan Bulan: %s\n", gabungan[i]);
    }
    IsiData2();
    return 0;
}

int IsiData2(){
    char opsi;
    printf("Apakah data yang diinputkan sudah benar? (Y/N)\n");
    printf("=> Pilih opsi : ");scanf("%c", &opsi);getchar();
    switch(opsi){
        case 'Y' :
            printf("Data terkonfirmasi!\n");
            pause();
            TambahPaket();
            break;
        case 'N' :
            IsiData();
            break;
        default :
            printf("Pilihan anda tidak valid!");
            sleep(3);
            IsiData2();
            return 1;
    }
    return 0;
}

int TambahPaket(){
    B = 0.0;
    char pilih;
    cls();
    printf("============================================\n");
    printf("=              TAMBAHAN PAKET              =\n");
    printf("============================================\n");
    printf("= (A) Tambah Penumpang (Bayi/Anak/Lansia)  =\n");
    printf("= (B) Request Babysitter                   =\n");
    printf("= (C) Tidak ada tambahan paket             =\n");
    printf("= (D) Kembali ke menu sebelumnya           =\n");
    printf("============================================\n");
    printf("Pilih opsi : ");scanf("%c", &pilih);getchar();
    switch (pilih) {
        case 'A' :
            TambahPaketA();
            break;
        case 'B' :
            TambahPaketB();
            break;
        case 'C' :
            CekDiskon();
            break;
        case 'D' :
            MenuPaket1();
            break;
        default :
            printf("Pilihan anda tidak valid!\n");
            sleep(3);
            TambahPaket();
            return 1;
        }
        return 0;
}

int TambahPaketA(){
    char pilih1;
    cls();
    printf("======================================\n");
    printf("=       Pilih jenis penumpang!       =\n");
    printf("======================================\n");
    printf("= (1) Bayi usia (0 - 12 bulan)       =\n");
    printf("= (2) Anak usia (12 - 59 bulan)      =\n");
    printf("= (3) Lansia usia (60+)              =\n");
    printf("= (4) Kembali ke menu sebelumnya     =\n");
    printf("======================================\n");
    printf("Pilih opsi : ");scanf("%d", &pilih1);getchar();
    switch(pilih1){
        case 1 :
            TambahPaketA1();
            break;
        case 2 :
            TambahPaketA2();
            break;
        case 3 :
            TambahPaketA3();
            break;
        case 4 :
            TambahPaket();
            break;
        default :
            printf("Pilihan anda tidak valid!");
            sleep(3);
            TambahPaketA();
            return 1;
    }
    return 0;                   
}

int TambahPaketA1(){
    cls();
    int opsi;
    char opsi1a;
    float z, bayi;
    if (class == 1){
        z = 600000;
        printf("===========================================\n");
        printf("=                 Rp600.000/BAYI             =\n");
    } else if (class == 2){
        z = 800000;
        printf("==========================================\n");
        printf("=            PERBAYI/Rp800.000           =\n");
    } else {
        z = 1000000;
        printf("==========================================\n");
        printf("=            Rp1.000.000/BAYI            =\n");
    }
    printf("==========================================\n");
    printf("= (1) Lanjutkan                          =\n");
    printf("= (2) Batalkan                           =\n");
    printf("==========================================\n");
    printf("Pilih opsi : ");scanf("%d", &opsi);getchar();

    switch(opsi){
        case 1 :
            printf("=> Berapa banyak bayi yang ditambahkan? : ");scanf("%f", &bayi);getchar();
            x = bayi * z;
            cls();
            printf("=> total harga : Rp%.2f\n", x + class2);
            printf("loading");
            sleep(1);
            printf(". ");
            sleep(1);
            printf(" . ");
            sleep(1);
            printf(" .");
            cls();
            printf("=> Konfirmasi tambahan paket? (Y/N)\n");scanf("%c", &opsi1a);getchar();
            switch(opsi1a){
                case 'Y' :
                    printf("Tambahan paket terkonfirmasi!\n");
                    sleep(3);
                    cls();
                    CekDiskon();
                    break;
                case 'N' :
                    TambahPaketA1();
                    break;
                default :
                    printf("Pilihan anda tidak valid!\n");
                    pause();
                    TambahPaketA1();
                    return 1;
            }
        case 2 :
            TambahPaketA();
            break;
        default :
            printf("Pilihan anda tidak valid!\n");
            sleep(3);
            TambahPaketA2(); 
            return 1;
    }
    return 0;
}

int TambahPaketA2(){
    cls();
    int opsi;
    char opsi1a;
    float z, anak;
    if (class == 1){
        z = 750000;
        printf("==========================================\n");
        printf("=            PERANAK/Rp750.000           =\n");
    } else if(class == 2){
        z = 950000;
        printf("==========================================\n");
        printf("=            PERANAK/Rp950.000           =\n");
    } else {
        z = 1150000;
        printf("==========================================\n");
        printf("=           PERANAK/Rp1.150.000          =\n");
    }
    printf("==========================================\n");
    printf("= (1) Lanjutkan                          =\n");
    printf("= (2) Batalkan                           =\n");
    printf("==========================================\n");
    printf("Pilih opsi : ");scanf("%d", &opsi);getchar();

    switch(opsi){
        case 1 :
            printf("=> Berapa banyak anak yang ditambahkan? : ");scanf("%f", &anak);getchar();
            x = anak * z;
            cls();
            printf("=> total harga : Rp%.2f\n", x + class2);
            printf("loading");
            sleep(1);
            printf(". ");
            sleep(1);
            printf(" . ");
            sleep(1);
            printf(" .");
            cls();
            printf("=> Konfirmasi tambahan paket? (Y/N)\n");scanf("%c", &opsi1a);getchar();
            switch(opsi1a){
                case 'Y' :
                    printf("Tambahan paket terkonfirmasi!\n");
                    sleep(3);
                    cls();
                    CekDiskon();
                    break;
                case 'N' :
                    TambahPaketA2();
                    break;
                default :
                    printf("Pilihan anda tidak valid!\n");
                    pause();
                    TambahPaketA2();
                    return 1;
            }
        case 2 :
            TambahPaketA();
            break;
        default :
            printf("Pilihan anda tidak valid!\n");
            sleep(3);
            TambahPaketA2();
            return 1;   
    }   
    return 0;
}

int TambahPaketA3(){
    cls();
    int opsi;
    char opsi1a;
    float z, lansia;
    if (class == 1){
        z = 1000000;
        printf("============================================\n");
        printf("=             LANSIA/Rp1.000.000           =\n");
    } else if (class == 2){
        z = 1500000;
        printf("===========================================\n");
        printf("=            LANSIA/Rp1.500.000           =\n");
    } else {
        z = 4250000;
        printf("===========================================\n");
        printf("=            LANSIA/Rp4.250.000           =\n");
    }
    printf("==========================================\n");
    printf("= (1) Lanjutkan                          =\n");
    printf("= (2) Batalkan                           =\n");
    printf("==========================================\n");
    printf("Pilih opsi : ");scanf("%d", &opsi);getchar();

    switch(opsi){
        case 1 :
            printf("test kode = %,1f", z);
            printf("=> Berapa banyak Lansia yang ditambahkan? : ");scanf("%f", &lansia);getchar();
            x = lansia * z;
            cls();
            printf("=> total harga : Rp%.2f\n", x + class2);
            printf("loading");
            sleep(1);
            printf(". ");
            sleep(1);
            printf(" . ");
            sleep(1);
            printf(" .");
            cls();
            printf("=> Konfirmasi tambahan paket? (Y/N)\n");scanf("%c",&opsi1a);getchar();
            switch(opsi1a) {
                case 'Y' :
                    cls();
                    printf("Tambahan paket terkonfirmasi!\n");
                    sleep(3);
                    cls();
                    CekDiskon();
                    break;
                case 'N' :
                    TambahPaketA3();
                    break;
                default :
                    printf("Pilihan anda tidak valid!\n");
                    pause();
                    TambahPaketA3();
                    return 1;
            }
        case 2 :
            TambahPaketA();
            break;
        default :
            printf("Pilihan anda tidak valid!\n");
            sleep(3);
            TambahPaketA3(); 
            return 1;
    }
    return 0;
}

int TambahPaketB(){
    int pilih, jam, konfirmasi;
    float babysitter, gajibaby, A, hari;
    printf("loading");
    sleep(1);
    printf(". ");
    sleep(1);
    printf(" . ");
    sleep(1);
    printf(" .");        
    cls();
    if (class){
        printf("==========================================\n");
        printf("=           REQUEST BABYSITTER           =\n");
        printf("==========================================\n");
        printf("= (1) PERHARI (Rp500.000)                =\n");
        printf("= (2) PERJAM (Rp30.000)                  =\n");
        printf("= (3) Kembali ke menu sebelumnya         =\n");
        printf("==========================================\n");
        printf("=> Pilih opsi : ");scanf("%d", &pilih);getchar();
        switch(pilih){
            case 1 :
                gajibaby = 500000;
                printf("=> Berapa Babysitter yang anda butuhkan? : ");
                scanf("%f", &babysitter);
                A = babysitter * gajibaby;
                printf("=> Untuk berapa hari anda membutuhkan babysitter? : ");
                scanf("%f", &hari);
                B = hari * A;
                cls();
                printf("loading");
                sleep(1);
                printf(". ");
                sleep(1);
                printf(" . ");
                sleep(1);
                printf(" .");
                cls();
                printf("=============================================================\n");
                printf("=  Apakah anda sudah yakin untuk opsi tambahan babysitter?  =\n");
                printf("=============================================================\n");
                printf("=> (1) Yakin                                                =\n");
                printf("=> (2) Belum yakin                                          =\n");
                printf("=============================================================\n");
                printf("=> Pilih opsi : ");scanf("%d", &konfirmasi);getchar();
                switch (konfirmasi){
                    case 1 :
                        CekDiskon();
                        break;
                    case 2 :
                        TambahPaketB();
                        break;
                    case 3 :
                        printf("Pilihan anda tidak valid!\n");
                        pause();
                        TambahPaketB();
                        return 1;
                }
            case 2 :
                gajibaby = 30000;
                printf("=> Berapa Babysitter yang anda butuhkan? : ");
                scanf("%f", &babysitter);
                A = babysitter * gajibaby;
                printf("=> Untuk berapa hari anda membutuhkan babysitter? : ");
                scanf("%f", &hari);
                B = hari * A;
                pause();
                cls();
                printf("loading");
                sleep(1);
                printf(". ");
                sleep(1);
                printf(" . ");
                sleep(1);
                printf(" .");
                cls();
                printf("=============================================================\n");
                printf("=  Apakah anda sudah yakin untuk opsi tambahan babysitter?  =\n");
                printf("=============================================================\n");
                printf("=> (1) Yakin\n");
                printf("=> (2) Belum yakin\n");
                printf("=============================================================\n");
                printf("=> Pilih opsi : ");scanf("%d", &konfirmasi);getchar();
                switch (konfirmasi){
                    case 1 :
                        CekDiskon();
                        break;
                    case 2 :
                        TambahPaketB();
                        break;
                    case 3 :
                        printf("Pilihan anda tidak valid!\n");
                        pause();
                        TambahPaketB();
                        return 1;
                }
            case 3 :
                TambahPaket();
                break;
            default :
                printf("Pilihan anda tidak valid!\n");
                pause();
                TambahPaketB();
        }
    }
    return 0;
}

int CekDiskon(){
    cls();
    int a = sizeof(gabungan) / sizeof(gabungan[0]), i;
    for(i=0;i<a;i++){
        if (strcmp(gabungan[i], simpan2) == 0) {
            total = class2 + x + B;
            float diskon1 = total * 0.15;
            float diskon2 = total - diskon1;
            total = diskon2;
            cls();
            printf("=> Selamat anda mendapatkan diskon!\n");
            printf("=> Semoga hari ulang tahun Anda penuh dengan kebahagiaan.\n"); 
            printf("=> Selamat ulang tahun!\n");
            pause();
            Pembayaran();
            return 0;
        }
    }
    total = class2 + x + B;
    printf("=> Maaf anda tidak mendapatkan diskon\n");
    sleep(3);
    Pembayaran();
    return 1;   
}

int Pembayaran(){ //Fungsi Pembayaran Agar Calon Klien Dapat Memilih Metode Pembayaran
    int Menupaket, back;
    cls();
    if (class == 1) {
        printf("=============  PAKET EKONOMIS BALI 2 HARI/1 MALAM  ===========\n");
    } else if (class == 2) {
        printf("=============== PAKET HONEY MOON 3 HARI/2 MALAM ==============\n");
    } else {
        printf("=====  PAKET WISATA BALI + NUSA PENIDA 3HARI/2MALAM  =====\n");
    }
                                                                            
    printf("= 1) Via Transfer Bank BRIsik dan Bank MandiSendiri (Mobile) =\n");
    printf("= 2) Batalkan Pemesanan Paket                                =\n");
    printf("==============================================================\n");
    printf("Pilih Menu : ");
    scanf("%d", &Menupaket);getchar();
    if (Menupaket == 1) {
        cls();
        printf("========================================================\n");
        printf("= Nominal yang harus dibayarkan adalah                 =\n");        
        printf("= Rp%.2f                                         =\n", total);
        printf("========================================================\n");
        printf("=   Silahkan Transfer ke Nomor Rekening Dibawah Ini    =\n");
        printf("========================================================\n");
        printf("= 1. Bank BRIsik Mobile (5672 2314 1233 578)           =\n");
        printf("= 2. Bank Mandisendiri Mobile (92837 1259 3731)        =\n");
        printf("========================================================\n");
        printf("=  Konfirmasi Pembayaran Anda ke Kontak Berikut Ini :  =\n");
        printf("=                   0811-9999-9777                     =\n");
        printf("========================================================\n");
        pause();
        CekKodeUnik(nyawa);
    } else if (Menupaket == 2) {
        MenuPaket1();
    } else {
        printf("Input tidak valid, pilih menu yang lain!");
        CekDiskon();
        return 1;
    }
    return 0;
}

int CekKodeUnik(int nyawa) {
    cls();
    int found = 0; 
    char kodefile[256];
    FILE *cek = fopen("kumpulan_kode.txt", "r");
    FILE *cek2 = fopen("kumpulan_kode2.txt", "w");

    if (nyawa == 0){
        printf("Kesempatan anda habis!");
        pause();
        main();
    }
    
    if (cek == NULL) {
        printf("===================================================\n");
        printf("=           Error : Data Kode tidak ada!          =\n");
        printf("===================================================\n");
        printf("= Kemungkinan data anda belum diverifikasi Admin  =\n");
        printf("= Info lebih lanjut hubungi CP : 0811-9999-9777   =\n");
        printf("===================================================\n");
        pause();
        main();
        return 1;
    }
    
    printf("Masukkan kode unik: ");
    fgets(kodeunik, sizeof(kodeunik), stdin);
    kodeunik[strcspn(kodeunik, "\n")] = 0;

    while (fgets(kodefile, sizeof(kodefile), cek) != NULL) {
        kodefile[strcspn(kodefile, "\n")] = 0;
        if (strcmp(kodeunik, kodefile) == 0) {
            printf("Verifikasi kode unik berhasil!\n");
            pause();
            found = 1;
            break;
        }
    }
    
    if (found) {
        while (fgets(kodefile, sizeof(kodefile), cek) != NULL){
            if (strcmp(kodefile, kodeunik) != 0){
                fputs(kodefile, cek2);
            }
        }
        fclose(cek);
        fclose(cek2);   
        remove ("kumpulan_kode.txt");
        rename ("kumpulan_kode2.txt", "kumpulan_kode.txt");
        CetakTiket();

    } else {
        printf("Kode anda tidak valid! Kesempatan anda tersisa : %d\n", nyawa-1);
        pause();
        return CekKodeUnik(nyawa - 1);
    }
    return 0;
}

int CetakTiket(){
    cls();
    int x;
    char pilih;
    FILE *simpan_penumpang = fopen("Data_Penumpang.dat", "ab"); //Untuk menyimpan data klien
    FILE *tiket = fopen("Tiket.txt", "a");
    for (x=0; x < JumlahPenumpang;x++){
        fprintf(tiket, "===================== TIKET ======================\n"); 
        fprintf(tiket, "= %s\n", class3);
        fprintf(tiket, "==================================================\n");
        fprintf(tiket, "= Nama Lengkap           : %s\n", klien1.Nama[x]); 
        fprintf(tiket, "= NIK                    : %s\n", klien1.NIK[x]); 
        fprintf(tiket, "= Umur                   : %d\n", klien1.Umur[x]); 
        fprintf(tiket, "= Nomor Telepon          : %s\n", klien1.NomorTelepon[x]); 
        fprintf(tiket, "= Tempat, Tanggal Lahir  : %s\n", klien1.TTL[x]); 
        fprintf(tiket, "= Asal Kota              : %s\n", klien1.Askot[x]);
        fprintf(tiket, "= Email                  : %s\n", klien1.Email[x]); 
        fprintf(tiket, "= Riwayat Penyakit       : %s\n", klien1.RiwayatPenyakit[x]); 
        fprintf(tiket, "==================================================\n"); 
        fprintf(tiket, "= Tanggal keberangkatan  : %s\n", tanggal); 
        fprintf(tiket, "= Total harga (Rp)       : %.1f\n", total); 
        fprintf(tiket, "==================================================\n"); 
    }
    if (simpan_penumpang == NULL){
        printf("=> Data penumpang gagal diproses!\n");
        pause();
        main();
        return 1;
    }
    for (int k=0; k< JumlahPenumpang; k++){
        fprintf(simpan_penumpang, "=> Nama Lengkap          : %s\n", klien1.Nama[k]); 
        fprintf(simpan_penumpang, "=> Jenis Kelamin         : %s\n", klien1.Gender[k]); 
        fprintf(simpan_penumpang, "=> NIK                   : %s\n", klien1.NIK[k]); 
        fprintf(simpan_penumpang, "=> Umur                  : %d\n", klien1.Umur[k]); 
        fprintf(simpan_penumpang, "=> Nomor Telepon         : %s\n", klien1.NomorTelepon[k]); 
        fprintf(simpan_penumpang, "=> Tempat, Tanggal Lahir : %s\n", klien1.TTL[k]);
        fprintf(simpan_penumpang, "=> Asal Kota             : %s\n", klien1.Askot[k]);
        fprintf(simpan_penumpang, "=> Email                 : %s\n", klien1.Email[k]);
        fprintf(simpan_penumpang, "=> Riwayat Penyakit      : %s\n", klien1.RiwayatPenyakit[k]); 
        fprintf(simpan_penumpang, "\n"); 
    }
    fclose (simpan_penumpang);
    fclose(tiket);
    printf("Tiket anda tercetak!\n");
    sleep(3);
    SimpanPembayaran();
    return 0;
}

int SimpanPembayaran(){
    FILE *simpanbayar = fopen("Data_income.dat", "ab");
    
    if (simpanbayar == NULL){
        printf("=> Data pembayaran gagal diproses!\n");
        pause();
        Repurchase();
        return 1;
    } 
    fprintf(simpanbayar, "Tanggal Pemesanan : %s\n", simpan);
    fprintf(simpanbayar, "Dibayarkan(Rp)    : %.1f\n", total);
    fprintf(simpanbayar, "\n");
    fclose(simpanbayar);
    printf("=> Data pembayaran berhasil disimpan!\n");
    sleep(2);
    Repurchase();
    return 0;
}

int Repurchase(){
    cls();
    char pilih;
    printf("=======================================\n");
    printf("= Apakah anda ingin repurchase? (Y/N) =\n");
    printf("=======================================\n");
    printf("=> Pilih Opsi! : ");scanf("%c", &pilih);getchar();
    switch(pilih){
    case 'Y' :
        MenuPaket1();
        break;
    case 'N' :
        main();
        break;
    default :
        printf("Pilihan anda tidak valid!\n");
        sleep(3);
        Repurchase();
        return 1;
    }
    return 0;
}
