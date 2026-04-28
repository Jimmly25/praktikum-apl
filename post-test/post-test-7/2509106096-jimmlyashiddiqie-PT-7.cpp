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

// ===== VALIDASI =====
void validasiInput(){
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        throw "Input tidak valid! Harus angka.";
    }
}

void bubbleSortNama(bool ascending, int jumlahData){
    try{
        if(jumlahData == 0) throw "Data kosong, tidak bisa sorting!";
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
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void selectionSortJumlah(bool ascending, int jumlahData){
    try{
        if(jumlahData == 0) throw "Data kosong!";
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
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void insertionSortID(int jumlahData){
    try{
        if(jumlahData == 0) throw "Data kosong!";
        for(int i=1;i<jumlahData;i++){
            Inventaris key = dataInventaris[i];
            int j = i-1;

            while(j>=0 && dataInventaris[j].idBarang > key.idBarang){
                dataInventaris[j+1] = dataInventaris[j];
                j--;
            }

            dataInventaris[j+1] = key;
        }
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void cariID(int jumlahData){
    try{
        if(jumlahData == 0) throw "Data belum ada";

        int id;
        cout<<"Masukkan ID yang dicari: ";
        cin>>id;
        validasiInput();

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

        if(!ketemu) throw "Data tidak ditemukan";
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void cariNama(int jumlahData){
    try{
        if(jumlahData == 0) throw "Data belum ada";

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

        if(!ketemu) throw "Data tidak ditemukan";
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void buatPengajuan(string cabang, int *jumlahData){
    try{
        if(*jumlahData >= 100) throw "Data inventaris penuh";

        cout<<"\n=== BUAT PENGAJUAN INVENTARIS ===\n";

        int id;
        bool idAda;

        do{
            idAda=false;
            cout<<"ID Barang : ";
            cin>>id;
            validasiInput();

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
        validasiInput();

        dataInventaris[*jumlahData].cabangTNI=cabang;
        dataInventaris[*jumlahData].status="Diajukan";

        (*jumlahData)++;

        cout<<"Pengajuan berhasil dibuat\n";
    }catch(const char* e){
        cout<<e<<endl;
    }
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
    try{
        int id;
        cout<<"Masukkan ID barang yang ingin diubah : ";
        cin>>id;
        validasiInput();

        for(int i=0;i<jumlahData;i++){
            if(dataInventaris[i].idBarang==id &&
               dataInventaris[i].cabangTNI==cabang){

                if(dataInventaris[i].status!="Diajukan"){
                    throw "Pengajuan sudah diproses";
                }

                cout<<"Nama Barang Baru : ";
                cin.ignore();
                getline(cin,dataInventaris[i].namaBarang);

                cout<<"Jumlah Baru : ";
                cin>>dataInventaris[i].jumlahBarang;
                validasiInput();

                cout<<"Data berhasil diubah\n";
                return;
            }
        }

        throw "Data tidak ditemukan";
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void hapusPengajuan(string cabang, int *jumlahData){
    try{
        int id;
        cout<<"Masukkan ID barang yang ingin dihapus : ";
        cin>>id;
        validasiInput();

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

        throw "Data tidak ditemukan";
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void setujuiPengajuan(int jumlahData){
    try{
        int id;
        cout<<"Masukkan ID barang yang disetujui : ";
        cin>>id;
        validasiInput();

        for(int i=0;i<jumlahData;i++){
            if(dataInventaris[i].idBarang==id){
                dataInventaris[i].status="Disetujui";
                cout<<"Pengajuan berhasil disetujui\n";
                return;
            }
        }

        throw "Data tidak ditemukan";
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void beliInventaris(int jumlahData){
    try{
        int id;
        cout<<"Masukkan ID barang yang dibeli : ";
        cin>>id;
        validasiInput();

        for(int i=0;i<jumlahData;i++){
            if(dataInventaris[i].idBarang==id){
                dataInventaris[i].status="Dibeli";
                cout<<"Inventaris berhasil dibeli\n";
                return;
            }
        }

        throw "Data tidak ditemukan";
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void tambahInventarisAdmin(int *jumlahData){
    try{
        if(*jumlahData>=100) throw "Data penuh";

        cout<<"\n=== TAMBAH INVENTARIS ADMIN ===\n";

        cout<<"ID Barang : ";
        cin>>dataInventaris[*jumlahData].idBarang;
        validasiInput();

        cout<<"Nama Barang : ";
        cin.ignore();
        getline(cin,dataInventaris[*jumlahData].namaBarang);

        cout<<"Jumlah Barang : ";
        cin>>dataInventaris[*jumlahData].jumlahBarang;
        validasiInput();

        int pilihan;

        cout<<"Cabang TNI\n1. TNI AD\n2. TNI AU\n3. TNI AL\nPilih : ";
        cin>>pilihan;
        validasiInput();

        if(pilihan<1 || pilihan>3) throw "Pilihan tidak valid";

        if(pilihan==1)
            dataInventaris[*jumlahData].cabangTNI="TNI_AD";
        else if(pilihan==2)
            dataInventaris[*jumlahData].cabangTNI="TNI_AU";
        else
            dataInventaris[*jumlahData].cabangTNI="TNI_AL";

        dataInventaris[*jumlahData].status="Dibeli";

        (*jumlahData)++;

        cout<<"Inventaris berhasil ditambahkan\n";
    }catch(const char* e){
        cout<<e<<endl;
    }
}

void hapusInventarisAdmin(int *jumlahData){
    try{
        int id;
        cout<<"Masukkan ID inventaris yang ingin dihapus : ";
        cin>>id;
        validasiInput();

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

        throw "Data tidak ditemukan";
    }catch(const char* e){
        cout<<e<<endl;
    }
}

int main(){

    int pilihanLogin;

    do{
        try{
            cout<<"\n=== SISTEM INVENTARIS KEMENTERIAN ===\n";
            cout<<"1. Login Admin\n";
            cout<<"2. TNI AD\n";
            cout<<"3. TNI AU\n";
            cout<<"4. TNI AL\n";
            cout<<"5. Keluar\n";

            cout<<"Pilih menu : ";
            cin>>pilihanLogin;
            validasiInput();

            if(pilihanLogin < 1 || pilihanLogin > 5)
                throw "Pilihan tidak valid";
        }
        catch(const char* e){
            cout<<e<<endl;
            continue;
        }

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
                try{
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
                    validasiInput();

                    if(menuAdmin <1 || menuAdmin>8)
                        throw "Pilihan tidak valid";

                    switch(menuAdmin){
                        case 1: setujuiPengajuan(jumlahData); break;
                        case 2: beliInventaris(jumlahData); break;
                        case 3: tambahInventarisAdmin(&jumlahData); break;
                        case 4: hapusInventarisAdmin(&jumlahData); break;
                        case 5: lihatSemuaInventaris(jumlahData); break;

                        case 6:{
                            if(jumlahData==0) throw "Data kosong";
                            int pilihSort;
                            cout<<"Pilih: ";
                            cin>>pilihSort;
                            validasiInput();
                            break;
                        }

                        case 7:{
                            if(jumlahData==0) throw "Data kosong";
                            int pilihCari;
                            cout<<"Pilih: ";
                            cin>>pilihCari;
                            validasiInput();
                            break;
                        }

                        case 8: break;
                    }
                }
                catch(const char* e){
                    cout<<e<<endl;
                }

            }while(menuAdmin!=8);
        }

        else if(pilihanLogin>=2 && pilihanLogin<=4){

            string cabang;

            if(pilihanLogin==2) cabang="TNI_AD";
            else if(pilihanLogin==3) cabang="TNI_AU";
            else cabang="TNI_AL";

            int menuUser;

            do{
                try{
                    cout<<"\n=== MENU USER "<<cabang<<" ===\n";
                    cout<<"1. Membuat Pengajuan\n";
                    cout<<"2. Mengubah Pengajuan\n";
                    cout<<"3. Melihat Inventaris\n";
                    cout<<"4. Menghapus Pengajuan\n";
                    cout<<"5. Keluar\n";

                    cout<<"Pilih menu : ";
                    cin>>menuUser;
                    validasiInput();

                    if(menuUser<1 || menuUser>5)
                        throw "Pilihan tidak valid";

                    switch(menuUser){
                        case 1: buatPengajuan(cabang,&jumlahData); break;
                        case 2: ubahPengajuan(cabang,jumlahData); break;
                        case 3: lihatInventaris(cabang,jumlahData); break;
                        case 4: hapusPengajuan(cabang,&jumlahData); break;
                        case 5: break;
                    }
                }
                catch(const char* e){
                    cout<<e<<endl;
                }

            }while(menuUser!=5);
        }

    }while(pilihanLogin!=5);

    cout<<"Program selesai\n";
}