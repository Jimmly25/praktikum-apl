#include <iostream>
using namespace std;

struct User{
    string nama;
    string nim;
};

struct Inventaris{
    int idBarang;
    string namaBarang;
    int jumlahBarang;
    string cabangTNI;
    string status;
};

User admin = {"jimmly","096"};

Inventaris dataInventaris[100];
int jumlahData = 0;



void bubbleSortNama(bool ascending, int jumlahData){
    for(int i=0;i<jumlahData-1;i++){
        for(int j=0;j<jumlahData-i-1;j++){
            if(ascending){
                if(dataInventaris[j].namaBarang > dataInventaris[j+1].namaBarang){
                    swap(dataInventaris[j], dataInventaris[j+1]);
                }
            }else{
                if(dataInventaris[j].namaBarang < dataInventaris[j+1].namaBarang){
                    swap(dataInventaris[j], dataInventaris[j+1]);
                }
            }
        }
    }
}

void selectionSortJumlah(bool ascending, int jumlahData){
    for(int i=0;i<jumlahData-1;i++){
        int idx=i;
        for(int j=i+1;j<jumlahData;j++){
            if(ascending){
                if(dataInventaris[j].jumlahBarang < dataInventaris[idx].jumlahBarang){
                    idx=j;
                }
            }else{
                if(dataInventaris[j].jumlahBarang > dataInventaris[idx].jumlahBarang){
                    idx=j;
                }
            }
        }
        swap(dataInventaris[i], dataInventaris[idx]);
    }
}

void insertionSortID(int jumlahData){
    for(int i=1;i<jumlahData;i++){
        Inventaris key = dataInventaris[i];
        int j = i-1;

        while(j>=0 && dataInventaris[j].idBarang > key.idBarang){
            dataInventaris[j+1] = dataInventaris[j];
            j--;
        }

        dataInventaris[j+1] = key;
    }
}


void cariID(int jumlahData){
    if(jumlahData == 0){
        cout<<"Data belum ada\n";
        return;
    }

    int id;
    cout<<"Masukkan ID yang dicari: ";
    cin>>id;

    bool ketemu = false;

    for(int i=0;i<jumlahData;i++){
        if(dataInventaris[i].idBarang == id){
            cout<<"\nData ditemukan:\n";
            cout<<dataInventaris[i].idBarang<<" | "
                <<dataInventaris[i].namaBarang<<" | "
                <<dataInventaris[i].jumlahBarang<<" | "
                <<dataInventaris[i].status<<endl;
            ketemu = true;
        }
    }

    if(!ketemu)
        cout<<"Data tidak ditemukan\n";
}

void cariNama(int jumlahData){
    if(jumlahData == 0){
        cout<<"Data belum ada\n";
        return;
    }

    bubbleSortNama(true, jumlahData);

    string nama;
    cout<<"Masukkan Nama Barang yang dicari: ";
    cin.ignore();
    getline(cin, nama);

    int kiri = 0, kanan = jumlahData-1;
    bool ketemu = false;

    while(kiri <= kanan){
        int tengah = (kiri + kanan)/2;

        if(dataInventaris[tengah].namaBarang == nama){
            cout<<"\nData ditemukan:\n";
            cout<<dataInventaris[tengah].idBarang<<" | "
                <<dataInventaris[tengah].namaBarang<<" | "
                <<dataInventaris[tengah].jumlahBarang<<" | "
                <<dataInventaris[tengah].status<<endl;
            ketemu = true;
            break;
        }
        else if(dataInventaris[tengah].namaBarang < nama){
            kiri = tengah + 1;
        }
        else{
            kanan = tengah - 1;
        }
    }

    if(!ketemu)
        cout<<"Data tidak ditemukan\n";
}


void buatPengajuan(string cabang, int *jumlahData){
    if(*jumlahData >= 100){
        cout<<"Data inventaris penuh\n";
        return;
    }

    cout<<"\n=== BUAT PENGAJUAN INVENTARIS ===\n";

    int id;
    bool idAda;

    do{
        idAda=false;
        cout<<"ID Barang : ";
        cin>>id;

        for(int i=0;i<*jumlahData;i++){
            if(dataInventaris[i].idBarang==id){
                cout<<"ID sudah digunakan\n";
                idAda=true;
            }
        }
    }while(idAda);

    dataInventaris[*jumlahData].idBarang=id;

    cout<<"Nama Barang : ";
    cin.ignore();
    getline(cin,dataInventaris[*jumlahData].namaBarang);

    cout<<"Jumlah Barang : ";
    cin>>dataInventaris[*jumlahData].jumlahBarang;

    dataInventaris[*jumlahData].cabangTNI=cabang;
    dataInventaris[*jumlahData].status="Diajukan";

    (*jumlahData)++;

    cout<<"Pengajuan berhasil dibuat\n";
}

void lihatInventaris(string cabang, int jumlahData){
    cout<<"\n=== DATA INVENTARIS "<<cabang<<" ===\n";
    cout<<"ID | Nama Barang | Jumlah | Status\n";
    cout<<"---------------------------------\n";

    bool ada=false;

    for(int i=0;i<jumlahData;i++){
        if(dataInventaris[i].cabangTNI==cabang){
            cout<<dataInventaris[i].idBarang<<" | "
                <<dataInventaris[i].namaBarang<<" | "
                <<dataInventaris[i].jumlahBarang<<" | "
                <<dataInventaris[i].status<<endl;
            ada=true;
        }
    }

    if(!ada)
        cout<<"Belum ada data\n";
}

void lihatSemuaInventaris(int jumlahData){
    string cabang[3]={"TNI_AD","TNI_AU","TNI_AL"};

    for(int c=0;c<3;c++){
        cout<<"\n=== INVENTARIS "<<cabang[c]<<" ===\n";
        cout<<"ID | Nama Barang | Jumlah | Status\n";
        cout<<"---------------------------------\n";

        bool ada=false;

        for(int i=0;i<jumlahData;i++){
            if(dataInventaris[i].cabangTNI==cabang[c]){
                cout<<dataInventaris[i].idBarang<<" | "
                    <<dataInventaris[i].namaBarang<<" | "
                    <<dataInventaris[i].jumlahBarang<<" | "
                    <<dataInventaris[i].status<<endl;
                ada=true;
            }
        }

        if(!ada)
            cout<<"Belum ada data\n";
    }
}

void ubahPengajuan(string cabang, int jumlahData){
    int id;
    cout<<"Masukkan ID barang yang ingin diubah : ";
    cin>>id;

    for(int i=0;i<jumlahData;i++){
        if(dataInventaris[i].idBarang==id &&
           dataInventaris[i].cabangTNI==cabang){

            if(dataInventaris[i].status!="Diajukan"){
                cout<<"Pengajuan sudah diproses\n";
                return;
            }

            cout<<"Nama Barang Baru : ";
            cin.ignore();
            getline(cin,dataInventaris[i].namaBarang);

            cout<<"Jumlah Baru : ";
            cin>>dataInventaris[i].jumlahBarang;

            cout<<"Data berhasil diubah\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

void hapusPengajuan(string cabang, int *jumlahData){
    int id;
    cout<<"Masukkan ID barang yang ingin dihapus : ";
    cin>>id;

    for(int i=0;i<*jumlahData;i++){
        if(dataInventaris[i].idBarang==id &&
           dataInventaris[i].cabangTNI==cabang){

            for(int j=i;j<*jumlahData-1;j++){
                dataInventaris[j]=dataInventaris[j+1];
            }

            (*jumlahData)--;

            cout<<"Pengajuan berhasil dihapus\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

void setujuiPengajuan(int jumlahData){
    int id;
    cout<<"Masukkan ID barang yang disetujui : ";
    cin>>id;

    for(int i=0;i<jumlahData;i++){
        if(dataInventaris[i].idBarang==id){
            dataInventaris[i].status="Disetujui";
            cout<<"Pengajuan berhasil disetujui\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

void beliInventaris(int jumlahData){
    int id;
    cout<<"Masukkan ID barang yang dibeli : ";
    cin>>id;

    for(int i=0;i<jumlahData;i++){
        if(dataInventaris[i].idBarang==id){
            dataInventaris[i].status="Dibeli";
            cout<<"Inventaris berhasil dibeli\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

void tambahInventarisAdmin(int *jumlahData){
    if(*jumlahData>=100){
        cout<<"Data penuh\n";
        return;
    }

    cout<<"\n=== TAMBAH INVENTARIS ADMIN ===\n";

    cout<<"ID Barang : ";
    cin>>dataInventaris[*jumlahData].idBarang;

    cout<<"Nama Barang : ";
    cin.ignore();
    getline(cin,dataInventaris[*jumlahData].namaBarang);

    cout<<"Jumlah Barang : ";
    cin>>dataInventaris[*jumlahData].jumlahBarang;

    int pilihan;

    cout<<"Cabang TNI\n";
    cout<<"1. TNI AD\n";
    cout<<"2. TNI AU\n";
    cout<<"3. TNI AL\n";
    cout<<"Pilih : ";
    cin>>pilihan;

    if(pilihan==1)
        dataInventaris[*jumlahData].cabangTNI="TNI_AD";
    else if(pilihan==2)
        dataInventaris[*jumlahData].cabangTNI="TNI_AU";
    else
        dataInventaris[*jumlahData].cabangTNI="TNI_AL";

    dataInventaris[*jumlahData].status="Dibeli";

    (*jumlahData)++;

    cout<<"Inventaris berhasil ditambahkan\n";
}

void hapusInventarisAdmin(int *jumlahData){
    int id;
    cout<<"Masukkan ID inventaris yang ingin dihapus : ";
    cin>>id;

    for(int i=0;i<*jumlahData;i++){
        if(dataInventaris[i].idBarang==id){
            for(int j=i;j<*jumlahData-1;j++){
                dataInventaris[j]=dataInventaris[j+1];
            }
            (*jumlahData)--;
            cout<<"Inventaris berhasil dihapus\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}


int main(){

    int pilihanLogin;

    do{

        cout<<"\n=== SISTEM INVENTARIS KEMENTERIAN ===\n";
        cout<<"1. Login Admin\n";
        cout<<"2. TNI AD\n";
        cout<<"3. TNI AU\n";
        cout<<"4. TNI AL\n";
        cout<<"5. Keluar\n";

        cout<<"Pilih menu : ";
        cin>>pilihanLogin;

        if(pilihanLogin==1){

            User loginUser;
            int percobaan=0;
            bool berhasil=false;

            while(percobaan<3){
                cout<<"Nama : ";
                cin>>loginUser.nama;
                cout<<"NIM : ";
                cin>>loginUser.nim;

                if(loginUser.nama==admin.nama && loginUser.nim==admin.nim){
                    berhasil=true;
                    break;
                } else {
                    cout<<"Login gagal\n";
                    percobaan++;
                }
            }

            if(!berhasil){
                cout<<"Gagal login\n";
                return 0;
            }

            int menuAdmin;

            do{
                cout<<"\n=== MENU ADMIN ===\n";
                cout<<"1. Menyetujui Pengajuan\n";
                cout<<"2. Membeli Inventaris\n";
                cout<<"3. Menambah Inventaris\n";
                cout<<"4. Menghapus Inventaris\n";
                cout<<"5. Melihat Semua Inventaris\n";
                cout<<"6. Sorting Data\n";
                cout<<"7. Searching Data\n";
                cout<<"8. Keluar\n";

                cout<<"Pilih menu : ";
                cin>>menuAdmin;

                switch(menuAdmin){

                    case 1: setujuiPengajuan(jumlahData); break;
                    case 2: beliInventaris(jumlahData); break;
                    case 3: tambahInventarisAdmin(&jumlahData); break;
                    case 4: hapusInventarisAdmin(&jumlahData); break;
                    case 5: lihatSemuaInventaris(jumlahData); break;

                    case 6:{
                        if(jumlahData == 0){
                            cout<<"Data belum ada, tidak bisa dilakukan sorting\n";
                            break;
                        }

                        int pilihSort;
                        cout<<"\n=== MENU SORTING ===\n";
                        cout<<"1. Sorting Nama Barang\n";
                        cout<<"2. Sorting Jumlah Barang\n";
                        cout<<"3. Sorting ID Barang\n";
                        cout<<"Pilih: ";
                        cin>>pilihSort;

                        if(pilihSort==1){
                            int tipe;
                            cout<<"1. Ascending\n2. Descending\nPilih: ";
                            cin>>tipe;
                            bubbleSortNama(tipe==1, jumlahData);
                        }
                        else if(pilihSort==2){
                            int tipe;
                            cout<<"1. Ascending\n2. Descending\nPilih: ";
                            cin>>tipe;
                            selectionSortJumlah(tipe==1, jumlahData);
                        }
                        else if(pilihSort==3){
                            insertionSortID(jumlahData);
                        }

                        cout<<"\n=== HASIL SETELAH SORTING ===\n";
                        lihatSemuaInventaris(jumlahData);

                        break;
                    }

                
                    case 7:{
                        if(jumlahData == 0){
                            cout<<"Data belum ada, tidak bisa melakukan searching\n";
                            break;
                        }

                        int pilihCari;

                        do{
                            cout<<"\n=== MENU SEARCHING ===\n";
                            cout<<"1. Cari berdasarkan ID\n";
                            cout<<"2. Cari berdasarkan Nama\n";
                            cout<<"Pilih: ";
                            cin>>pilihCari;

                            if(pilihCari < 1 || pilihCari > 2)
                                cout<<"Pilihan tidak valid!\n";

                        }while(pilihCari < 1 || pilihCari > 2);

                        if(pilihCari == 1)
                            cariID(jumlahData);
                        else
                            cariNama(jumlahData);

                        break;
                    }
                    

                    case 8: break;

                    default:
                        cout<<"Pilihan tidak valid\n";
                }

            }while(menuAdmin!=8);
        }

        else if(pilihanLogin>=2 && pilihanLogin<=4){

            string cabang;

            if(pilihanLogin==2)
                cabang="TNI_AD";
            else if(pilihanLogin==3)
                cabang="TNI_AU";
            else
                cabang="TNI_AL";

            int menuUser;

            do{
                cout<<"\n=== MENU USER "<<cabang<<" ===\n";
                cout<<"1. Membuat Pengajuan\n";
                cout<<"2. Mengubah Pengajuan\n";
                cout<<"3. Melihat Inventaris\n";
                cout<<"4. Menghapus Pengajuan\n";
                cout<<"5. Keluar\n";

                cout<<"Pilih menu : ";
                cin>>menuUser;

                switch(menuUser){

                    case 1: buatPengajuan(cabang, &jumlahData); break;
                    case 2: ubahPengajuan(cabang, jumlahData); break;
                    case 3: lihatInventaris(cabang, jumlahData); break;
                    case 4: hapusPengajuan(cabang, &jumlahData); break;
                    case 5: break;

                    default:
                        cout<<"Pilihan tidak valid\n";
                }

            }while(menuUser!=5);
        }

        else if(pilihanLogin!=5){
            cout<<"Pilihan tidak valid\n";
        }

    }while(pilihanLogin!=5);

    cout<<"Program selesai\n";
}