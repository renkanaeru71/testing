#include <iostream>
#include <iomanip>
#include <conio.h> // untuk getch(), pause (umumnya tersedia di Geany/Windows)

using namespace std;

// Produk
const int PRODUCT_COUNT = 7;
string productName[PRODUCT_COUNT] = {
    "Energy Drink",
    "Permen 1 pack",
    "Golda Coffe",
    "Citato",
    "Silver Queen",
    "Sabun",
    "Indomie"
};
int productPrice[PRODUCT_COUNT] = {
    13000,  // Energy Drink
    20000,  // Permen 1 pack
    5000,   // Golda Coffe
    10000,  // Citato
    27000,  // Silver Queen
    5500,   // Sabun
    3000    // Indomie
};

// Cart (jumlah per produk)
int cartQty[PRODUCT_COUNT];

// Utility: bersihkan layar sederhana (cetak beberapa baris kosong)
void clearScreen() {
    for (int i = 0; i < 30; ++i) cout << '\n';
}

// Tampilkan header toko + garis
void header() {
    cout << "==============================================\n";
    cout << "               ReSkuy Store - Kasir           \n";
    cout << "        Kapanewon Tulalit - Sistem Kasir      \n";
    cout << "==============================================\n\n";
}

// Tampilkan daftar produk (rapi)
void showProducts() {
    cout << left << setw(4) << "No" << setw(20) << "Nama Barang" << right << setw(12) << "Harga (Rp)" << "\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < PRODUCT_COUNT; ++i) {
        cout << left << setw(4) << (i + 1)
             << setw(20) << productName[i]
             << right << setw(12) << productPrice[i] << "\n";
    }
    cout << "------------------------------------------------\n";
}

// Input pesanan: menambah jumlah (jika barang sama -> ditambah)
void inputPesanan() {
    while (true) {
        clearScreen();
        header();
        cout << "Menu: INPUT PESANAN\n\n";
        showProducts();
        int pilih;
        cout << "\nMasukkan nomor barang (1-" << PRODUCT_COUNT << "), 0 untuk kembali: ";
        if (!(cin >> pilih)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Input tidak valid. Tekan tombol apa saja untuk ulang..."; getch();
            continue;
        }
        if (pilih == 0) return;
        if (pilih < 1 || pilih > PRODUCT_COUNT) {
            cout << "Nomor barang tidak valid. Tekan tombol apa saja untuk ulang..."; getch();
            continue;
        }
        int qty;
        cout << "Jumlah: ";
        if (!(cin >> qty) || qty <= 0) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Jumlah tidak valid. Tekan tombol apa saja untuk ulang..."; getch();
            continue;
        }
        // tambahkan ke cart (jika sudah ada, jumlah bertambah)
        cartQty[pilih - 1] += qty;
        cout << "\n>> Barang '" << productName[pilih - 1] << "' sebanyak " << qty << " ditambahkan ke keranjang.\n";

        // Tanya lanjut
        char lagi;
        cout << "Tambah barang lain? (y/n): ";
        cin >> lagi;
        if (lagi == 'y' || lagi == 'Y') continue;
        else return;
    }
}

// Tampilkan nota sementara / daftar pesanan dan total
long long tampilkanNotaSementara() {
    clearScreen();
    header();
    cout << "NOTA SEMENTARA\n\n";
    cout << left << setw(4) << "No" << setw(20) << "Nama Barang" << setw(8) << "Qty" << right << setw(12) << "Sub Harga\n";
    cout << "-------------------------------------------------------------\n";
    long long total = 0;
    int nomor = 1;
    for (int i = 0; i < PRODUCT_COUNT; ++i) {
        if (cartQty[i] > 0) {
            long long subtotal = (long long)cartQty[i] * productPrice[i];
            cout << left << setw(4) << nomor
                 << setw(20) << productName[i]
                 << setw(8) << cartQty[i]
                 << right << setw(12) << subtotal << "\n";
            total += subtotal;
            nomor++;
        }
    }
    if (total == 0) {
        cout << " -- Keranjang kosong --\n";
    }
    cout << "-------------------------------------------------------------\n";
    cout << right << setw(34) << "TOTAL: " << setw(12) << total << "\n\n";
    return total;
}

// Pembayaran dan cetak nota akhir; setelah sukses, reset cart
void pembayaranDanNota() {
    while (true) {
        long long total = tampilkanNotaSementara();
        if (total == 0) {
            cout << "Tidak ada barang. Kembali ke menu utama.\n";
            cout << "Tekan tombol apa saja..."; getch();
            return;
        }
        cout << "Masukkan jumlah uang pelanggan (Rp): ";
        long long uang;
        if (!(cin >> uang)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Input tidak valid. Tekan apa saja untuk ulang..."; getch();
            continue;
        }
        if (uang < total) {
            cout << "\nUang kurang. Lakukan input ulang!\n";
            cout << "Tekan tombol apa saja untuk mencoba lagi..."; getch();
            continue;
        }
        long long kembalian = uang - total;

        // Cetak Nota Akhir
        clearScreen();
        header();
        cout << "========== NOTA PEMBELIAN ==========\n\n";
        cout << left << setw(4) << "No" << setw(20) << "Nama Barang" << setw(8) << "Qty" << right << setw(12) << "Sub Harga\n";
        cout << "-------------------------------------------------------------\n";
        int nomor = 1;
        for (int i = 0; i < PRODUCT_COUNT; ++i) {
            if (cartQty[i] > 0) {
                long long subtotal = (long long)cartQty[i] * productPrice[i];
                cout << left << setw(4) << nomor
                     << setw(20) << productName[i]
                     << setw(8) << cartQty[i]
                     << right << setw(12) << subtotal << "\n";
                nomor++;
            }
        }
        cout << "-------------------------------------------------------------\n";
        cout << right << setw(34) << "TOTAL: " << setw(12) << total << "\n";
        cout << right << setw(34) << "UANG PEMBELI: " << setw(12) << uang << "\n";
        cout << right << setw(34) << "KEMBALIAN: " << setw(12) << kembalian << "\n";
        cout << "\nTerima kasih atas pembelian di ReSkuy Store!\n";
        cout << "Tekan tombol apa saja untuk kembali ke menu utama..."; getch();

        // Setelah pembayaran berhasil, hapus data pesanan (reset cart)
        for (int i = 0; i < PRODUCT_COUNT; ++i) cartQty[i] = 0;
        return;
    }
}

int main() {
    // Inisialisasi cart
    for (int i = 0; i < PRODUCT_COUNT; ++i) cartQty[i] = 0;

    // Login: Username = NIM (masukan bebas), Password = 123456710, maksimal 3 kali
    const string correctPassword = "123456710";
    string username, password;
    int attempts = 0;
    bool loggedIn = false;

    while (attempts < 3 && !loggedIn) {
        clearScreen();
        header();
        cout << "Silakan Login (Maks 3 kali percobaan)\n\n";
        cout << "Username (NIM) : ";
        cin >> username;
        cout << "Password       : ";
        cin >> password;
        attempts++;
        if (password == correctPassword) {
            loggedIn = true;
            cout << "\nLogin berhasil. Selamat datang, " << username << "!\n";
            cout << "Tekan tombol apa saja untuk melanjutkan..."; getch();
            break;
        } else {
            cout << "\nPassword salah. Sisa kesempatan: " << (3 - attempts) << "\n";
            if (attempts < 3) {
                cout << "Tekan tombol apa saja untuk coba lagi..."; getch();
            } else {
                cout << "Kesempatan habis. Anda dikeluarkan dari sistem.\n";
                cout << "Tekan tombol apa saja untuk keluar..."; getch();
                return 0;
            }
        }
    }

    // Menu utama
    while (loggedIn) {
        clearScreen();
        header();
        cout << "MENU UTAMA\n\n";
        cout << "A. Input Pesanan\n";
        cout << "B. Pembayaran dan Nota\n";
        cout << "C. Keluar\n\n";
        cout << "Pilih menu (A/B/C): ";
        char pilihan;
        cin >> pilihan;
        if (pilihan == 'A' || pilihan == 'a') {
            inputPesanan();
        } else if (pilihan == 'B' || pilihan == 'b') {
            pembayaranDanNota();
        } else if (pilihan == 'C' || pilihan == 'c') {
            clearScreen();
            header();
            cout << "Anda memilih keluar. Terima kasih.\n";
            cout << "Tekan tombol apa saja untuk menutup program..."; getch();
            break;
        } else {
            cout << "Pilihan tidak valid. Tekan tombol apa saja untuk ulang..."; getch();
        }
    }

    return 0;
}