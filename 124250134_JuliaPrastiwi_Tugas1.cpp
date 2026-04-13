#include <iostream>
#include <iomanip>
using namespace std;

struct datanya{
    char namaLukisan[200], namaPelukis[200];
    int harga;
};

datanya lukisan[50];
int jumlah = 0;

void tambahData();
void simpanData();
void bacaData();
void tampilkanData();
void termurah();
void termahal();
void cariData();
void hapusData();

int main(){
    int pilMenu;
    do{
        cout << "\n===============================================\n";
        cout << "       SISTEM MANAJEMEN LUKISAN GALERI         \n";
        cout << "===============================================\n";
        cout << "1. Tambah Data Lukisan\n";
        cout << "2. Tampilkan Data Lukisan\n";
        cout << "3. Cari Berdasarkan Pelukis\n";
        cout << "4. Hapus Data Lukisan\n";  
        cout << "5. Keluar\n";
        cout << "-----------------------------------------------\n";
        cout << "Pilih menu: ";cin>>pilMenu;
        cin.ignore();
        cout << endl;

        switch(pilMenu){
            case 1: tambahData(); break;
            case 2: tampilkanData();break;
            case 3: cariData();break;
            case 4: hapusData();break;
            case 5: cout << "Terima Kasih!\n";break;
            default: cout << "Pilihan Anda tidak valid!\n";
        }
    }while(pilMenu!=5);
}

void tambahData(){
    bacaData();
    char simpan;
    do{
        datanya *p = &lukisan[jumlah]; //pointer ke elemen array
        cout << "=== Tambah Data Lukisan ===\n";
        cout << "Nama Lukisan   : ";cin.getline(p -> namaLukisan, 200);
        cout << "Nama Pelukis   : ";cin.getline(p -> namaPelukis, 200);
        cout << "Harga          : ";cin>>p->harga;
        cout << "Data Sudah Benar? (y/n) : ";cin>>simpan;
        cout << endl;
        cin.ignore(); 
    }while(simpan=='n');

    if(simpan=='y'){
        cout << "Data berhasil ditambahkan!\n\n";
        jumlah++;
        simpanData();
    }else{
        cout << "Pilihan Anda tidak valid\n";
    }
}

void simpanData(){
    FILE *database = fopen("lukisan.txt", "w");
    if(database==NULL){
        cout << "Gagal Membuka File\n";
        return;
    }
    for(int i=0; i<jumlah; i++){
        fprintf(database, "%s, %s, %d\n", lukisan[i].namaLukisan, lukisan[i].namaPelukis, lukisan[i].harga);
    }
    fclose(database);
}

void bacaData(){
    FILE *database = fopen("lukisan.txt", "r");
    if(database == NULL){
        return;
    }

    jumlah = 0; //reset jumlah
    while(fscanf(database, "%[^,], %[^,], %d\n", lukisan[jumlah].namaLukisan, lukisan[jumlah].namaPelukis, &lukisan[jumlah].harga) == 3){
        jumlah++;
    }

    fclose(database);
}

void tampilkanData(){
    bacaData();
    int pil;
    if(jumlah>0){
        cout << "================ Tampilkan Data ===============\n";
        cout << "1. Harga Termurah\n";
        cout << "2. Harga Termahal\n";
        cout << "Pilih: ";cin>>pil;
        cin.ignore();
        cout << endl;
    
        switch(pil){
            case 1: termurah();break;
            case 2: termahal(); break;
            default: cout << "Pilihan tidak Valid!";
        }
    }else{
        cout << "Data Masih Kosong\n";
    }
}


void termurah(){
    bacaData();

    //sorting
    datanya temp; //variabel temp tipe data= datanya atau (struct)

    for(int i=0; i<jumlah-1; i++){
        for(int j=0; j<jumlah-i-1; j++){
            if(lukisan[j].harga>lukisan[j+1].harga){
                temp = lukisan[j];
                lukisan[j] = lukisan[j+1];
                lukisan[j+1] = temp;
            }
        }
    }
    cout << "=================================================================================\n";
    cout << left << setw(5) << "No"
        << setw(30) << "Nama Lukisan"
        << setw(30) << "Pelukis"
        << setw(10) << "Harga";
    cout << "\n=================================================================================\n";

    for(int i=0; i<jumlah; i++){
        cout << left << setw(5) << i+1
            << setw(30) << lukisan[i].namaLukisan
            << setw(30) << lukisan[i].namaPelukis
            << setw(10) << lukisan[i].harga << endl;
    }
    cout << "=================================================================================\n";
    cout << "total Data: " << jumlah << endl;
}

void termahal(){
    bacaData();

    //sorting
    datanya temp; //variabel temp tipe data= datanya atau (struct)

    for(int i=0; i<jumlah-1; i++){
        for(int j=0; j<jumlah-i-1; j++){
            if(lukisan[j].harga<lukisan[j+1].harga){
                temp = lukisan[j];
                lukisan[j] = lukisan[j+1];
                lukisan[j+1] = temp;
            }
        }
    }
    cout << "=================================================================================\n";
    cout << left << setw(5) << "No"
        << setw(30) << "Nama Lukisan"
        << setw(30) << "Pelukis"
        << setw(10) << "Harga";
    cout << "\n=================================================================================\n";

    for(int i=0; i<jumlah; i++){
        cout << left << setw(5) << i+1
            << setw(30) << lukisan[i].namaLukisan
            << setw(30) << lukisan[i].namaPelukis
            << setw(10) << lukisan[i].harga << endl;
    }
    cout << "=================================================================================\n";
    cout << "total Data: " << jumlah << endl;
}

void cariData(){
    bacaData();

    string cariPelukis;
    cout << "Cari Pelukis: ";getline(cin, cariPelukis);
    bool found = false;

    for(int i=0; i<jumlah; i++){
        if(string(lukisan[i].namaPelukis) == cariPelukis){
            if(!found){
                cout << "Data Ditemukan!\n";
                found = true;
            }
            cout << lukisan[i].namaLukisan << " | Rp " << lukisan[i].harga << endl;
        }
    }
    if(found==false){
        cout << "Data Tidak Ditemukan!\n";
    }
}

void hapusData(){
    bacaData();

    string target;
    int idxTarget = -1;

    cout << "Nama Lukisan: ";getline(cin, target);

    for(int i=0; i<jumlah; i++){
        if(string(lukisan[i].namaLukisan)==target){
            idxTarget=i;
            break;
        }
    }

    if(idxTarget == -1){
        cout << "Data tidak ditemukan!\n";
        return;
    }

    for(int i=idxTarget; i<jumlah-1; i++){
        lukisan[i] = lukisan[i+1];
    }
    jumlah--;
    simpanData();
    cout << "Data berhasil dihapus!\n";
}



