#include  <iostream>
using namespace std;

int main() {
    string namebenar = "jimmly";
    string paswwordbenar = "096";


    string nameInput;
    string passwordInput;
    int jumlahpercobaan = 0;
    bool statuslogin = false;




    cout << "======================================" << endl;
    cout << "      PROGRAM KONVERSI WAKTU          " << endl;
    cout << "======================================" << endl;

    while (jumlahpercobaan < 3 && statuslogin == false) {
        cout << "\n===== LOGIN =====" << endl;
        cout << "masukkan nama      : ";
        cin >> nameInput;
        cout << "masukkan password  : ";
        cin >> passwordInput;

        if(nameInput == namebenar && passwordInput == paswwordbenar) {
            statuslogin = true;
            cout << "\nLOGIN BERHASIL" << endl;

        } else {
            jumlahpercobaan++;
            cout << "LOGIN GAGAL !! Percobaan ke-" << jumlahpercobaan << endl;
        }
    }

     if (statuslogin == false) {
        cout << "\nAnda gagal login 3 kali. Program berhenti." << endl;
        return 0;
    }

    int pilihanmenu;

    do {
        cout << "\n======================================" << endl;
        cout << "             MENU UTAMA               " << endl;
        cout << "======================================" << endl;
        cout << "1. Konversi Jam ke Menit & Detik" << endl;
        cout << "2. Konversi Menit ke Jam & Detik" << endl;
        cout << "3. Konversi Detik ke Jam & Menit" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih Menu (1-4): ";
        cin >> pilihanmenu;
        
        switch (pilihanmenu) {
            case 1: { 
             int nilaiJam;
                cout << "Masukkan jumlah Jam: ";
                cin >> nilaiJam;

                int hasilMenit = nilaiJam * 60;
                int hasilDetik = nilaiJam * 3600;

                cout << nilaiJam << " Jam = "
                     << hasilMenit << " Menit dan "
                     << hasilDetik << " Detik" << endl;
                break;
            }

            case 2: {
                int nilaiMenit;
                cout << "Masukkan jumlah Menit: ";
                cin >> nilaiMenit;

                int hasilJam = nilaiMenit / 60;
                int hasilDetik = nilaiMenit * 60;

                cout << nilaiMenit << " Menit = "
                     << hasilJam << " Jam dan "
                     << hasilDetik << " Detik" << endl;
                break;
            }

            case 3: {
                int nilaiDetik;
                cout << "Masukkan jumlah Detik: ";
                cin >> nilaiDetik;

                int hasilJam = nilaiDetik / 3600;
                int hasilMenit = nilaiDetik / 60;

                cout << nilaiDetik << " Detik = "
                     << hasilJam << " Jam dan "
                     << hasilMenit << " Menit" << endl;
                break;
            }

            case 4:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihanmenu != 4);

    return 0;
    
}