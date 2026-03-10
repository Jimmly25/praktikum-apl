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

void buatPengajuan(string cabang){

    if(jumlahData >= 100){
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

        for(int i=0;i<jumlahData;i++){
            if(dataInventaris[i].idBarang==id){
                cout<<"ID sudah digunakan\n";
                idAda=true;
            }
        }

    }while(idAda);

    dataInventaris[jumlahData].idBarang=id;

    cout<<"Nama Barang : ";
    cin.ignore();
    getline(cin,dataInventaris[jumlahData].namaBarang);

    cout<<"Jumlah Barang : ";
    cin>>dataInventaris[jumlahData].jumlahBarang;

    dataInventaris[jumlahData].cabangTNI=cabang;
    dataInventaris[jumlahData].status="Diajukan";

    jumlahData++;

    cout<<"Pengajuan berhasil dibuat\n";
}

void lihatInventaris(string cabang){

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

void lihatSemuaInventaris(){

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

void ubahPengajuan(string cabang){

    int id;

    cout<<"Masukkan ID barang yang ingin diubah : ";
    cin>>id;

    for(int i=0;i<jumlahData;i++){

        if(dataInventaris[i].idBarang==id &&
           dataInventaris[i].cabangTNI==cabang){

            if(dataInventaris[i].status!="Diajukan"){
                cout<<"Pengajuan sudah diproses dan tidak bisa diubah\n";
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

void hapusPengajuan(string cabang){

    int id;

    cout<<"Masukkan ID barang yang ingin dihapus : ";
    cin>>id;

    for(int i=0;i<jumlahData;i++){

        if(dataInventaris[i].idBarang==id &&
           dataInventaris[i].cabangTNI==cabang){

            if(dataInventaris[i].status!="Diajukan"){
                cout<<"Pengajuan sudah diproses dan tidak bisa dihapus\n";
                return;
            }

            for(int j=i;j<jumlahData-1;j++){
                dataInventaris[j]=dataInventaris[j+1];
            }

            jumlahData--;

            cout<<"Pengajuan berhasil dihapus\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

void setujuiPengajuan(){

    int id;

    cout<<"Masukkan ID barang yang disetujui : ";
    cin>>id;

    for(int i=0;i<jumlahData;i++){

        if(dataInventaris[i].idBarang==id){

            if(dataInventaris[i].status!="Diajukan"){
                cout<<"Pengajuan sudah diproses\n";
                return;
            }

            dataInventaris[i].status="Disetujui";

            cout<<"Pengajuan berhasil disetujui\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

void beliInventaris(){

    int id;

    cout<<"Masukkan ID barang yang dibeli : ";
    cin>>id;

    for(int i=0;i<jumlahData;i++){

        if(dataInventaris[i].idBarang==id){

            if(dataInventaris[i].status!="Disetujui"){
                cout<<"Barang harus disetujui dahulu\n";
                return;
            }

            dataInventaris[i].status="Dibeli";

            cout<<"Inventaris berhasil dibeli\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

void tambahInventarisAdmin(){

    if(jumlahData>=100){
        cout<<"Data penuh\n";
        return;
    }

    cout<<"\n=== TAMBAH INVENTARIS ADMIN ===\n";

    cout<<"ID Barang : ";
    cin>>dataInventaris[jumlahData].idBarang;

    cout<<"Nama Barang : ";
    cin.ignore();
    getline(cin,dataInventaris[jumlahData].namaBarang);

    cout<<"Jumlah Barang : ";
    cin>>dataInventaris[jumlahData].jumlahBarang;

    int pilihan;

    cout<<"Cabang TNI\n";
    cout<<"1. TNI AD\n";
    cout<<"2. TNI AU\n";
    cout<<"3. TNI AL\n";
    cout<<"Pilih : ";
    cin>>pilihan;

    if(pilihan==1)
        dataInventaris[jumlahData].cabangTNI="TNI_AD";
    else if(pilihan==2)
        dataInventaris[jumlahData].cabangTNI="TNI_AU";
    else
        dataInventaris[jumlahData].cabangTNI="TNI_AL";

    dataInventaris[jumlahData].status="Dibeli";

    jumlahData++;

    cout<<"Inventaris berhasil ditambahkan\n";
}

void hapusInventarisAdmin(){

    int id;

    cout<<"Masukkan ID inventaris yang ingin dihapus : ";
    cin>>id;

    for(int i=0;i<jumlahData;i++){

        if(dataInventaris[i].idBarang==id){

            for(int j=i;j<jumlahData-1;j++){
                dataInventaris[j]=dataInventaris[j+1];
            }

            jumlahData--;

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
                }
                else{
                    cout<<"Login gagal\n";
                    percobaan++;
                }
            }

            if(!berhasil){
                cout<<"Anda gagal login 3 kali. Program berhenti.\n";
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
                cout<<"6. Keluar\n";

                cout<<"Pilih menu : ";
                cin>>menuAdmin;

                switch(menuAdmin){

                    case 1: setujuiPengajuan(); break;
                    case 2: beliInventaris(); break;
                    case 3: tambahInventarisAdmin(); break;
                    case 4: hapusInventarisAdmin(); break;
                    case 5: lihatSemuaInventaris(); break;
                    case 6: break;

                    default:
                        cout<<"Pilihan tidak valid\n";
                }

            }while(menuAdmin!=6);
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

            cout<<"\n=== MENU USER "<<cabang<<" ===\n";
            cout<<"1. Membuat Pengajuan\n";
            cout<<"2. Mengubah Pengajuan\n";
            cout<<"3. Melihat Inventaris\n";
            cout<<"4. Menghapus Pengajuan\n";
            cout<<"5. Keluar\n";

            cout<<"Pilih menu : ";
            cin>>menuUser;

            switch(menuUser){

                case 1: buatPengajuan(cabang); break;
                case 2: ubahPengajuan(cabang); break;
                case 3: lihatInventaris(cabang); break;
                case 4: hapusPengajuan(cabang); break;
                case 5: break;

                default:
                    cout<<"Pilihan tidak valid\n";
            }
        }

        else if(pilihanLogin!=5){
            cout<<"Pilihan tidak valid\n";
        }

    }while(pilihanLogin!=5);

    cout<<"Program selesai\n";
}