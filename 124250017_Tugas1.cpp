#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
using namespace std;

struct dataFilm{
	char judul[100];
	int harga;
	int tahun;
	float rating;
};

void bacaFile(dataFilm film[], int &jumlah){
	FILE *file_film;
	int i= 0;

	file_film = fopen("netfilm_db.txt", "r");//buat baca file "r"
	//kalo file belum ada, buat file baru "w"
	if (file_film == nullptr){
		file_film = fopen("netfilm_db.txt", "w");
		fclose(file_film);
		jumlah = 0;
		return;
	}
	
	//buat baca file sampe akhir
	while (fscanf(file_film, " %[^;];%d;%d;%f\n", film[i].judul, &film[i].harga, &film[i].tahun, &film[i].rating) != EOF){
		i++;
	}
	fclose(file_film);
	jumlah = i;
}

void saveFile(dataFilm film[], int n){
	FILE *file_film = fopen("netfilm_db.txt", "w");
	
	if (file_film == nullptr) {
		cout <<"File tidak ditemukan.\n";
		return;
	}
	
	for(int i = 0; i< n; i++){ //buat nulis data ke file
		fprintf(file_film,"%s;%d;%d;%.1f\n", film[i].judul, film[i].harga, film[i].tahun, film[i].rating);
    }
    fclose(file_film);
}

void tampilkan(dataFilm film[], int n){
	if (n == 0){
		cout <<"Belum ada data film\n";
		return;
	}
	
	cout <<"\n     N E T F L I X  C O N T E N T  K A T A L O G\n";
	cout <<"---------------------------------------------------------------------------\n";
	cout << "ID  Judul Film                            Harga        Tahun   Rating\n";
	cout <<"---------------------------------------------------------------------------\n";
	
	for (int i =0; i < n; i++){ //perulangan tampilan data
		cout <<"[" <<i+1 << "]";
		cout << left <<setw(40) << film[i].judul;
        cout << "Rp " <<setw(9)<< film[i].harga;
        cout << setw(8)<< film[i].tahun;
        cout << setw(6) <<film[i].rating <<endl;
	 }
	 cout <<"---------------------------------------------------------------------------\n";
 }
 
 void bubbleSort(dataFilm film[], int n){ //urutkan judul A-Z
	 for (int i=0; i < n-1; i++){
		 for (int j = 0; j < n - i - 1; j++){
			 if(strcmp(film[j].judul, film[j+1].judul) > 0){ //membandingkan judul film
				 dataFilm temp = film[j+1]; //temp menyimpan nilai sementara
				 film[j+1] = film[j];
				 film[j] = temp;
			 }
		 }
	 }
 }

void quickSort(dataFilm film[], int awal, int akhir){ //mengurutkan rating film tertinggi
	int low = awal;
	int high = akhir;
	
	float pivot = film[(awal + akhir)/2].rating; //buat cari nilai tengah
	do {
		while(film[low].rating > pivot)
		low++;
		while( film[high].rating < pivot)
		high--;
		
		if ( low <= high){
			swap(film[low], film[high]);
			low++;
			high--;
		}
	}
	while (low <= high);
    if (awal < high)
        quickSort(film, awal, high);
    if (low < akhir)
        quickSort(film, low, akhir);
}

void linearSearch(dataFilm film[], int n){
	char judulCari[100];
    int index = 0;
    bool ketemu = false;
    
    cout << "Keyword Judul : ";
    cin.getline(judulCari,100);
    
    while(index < n && ketemu != true){
		if(strcmp(film[index].judul, judulCari) == 0){
			cout <<"[FOUND] " << film[index].judul << " (" << film[index].tahun <<")\n";
			ketemu = true;
		}
		index++;
	}
	if(!ketemu){
		cout <<"Film tidak ditemukan\n";
	}
}

void binary(dataFilm film[], int n){
	char judulCari[100];
	int awal, tengah, akhir;
	bool ketemu = false;
	
	cout <<"Judul Lengkap (Exact) : ";
	cin.getline(judulCari,100);
	
	awal = 0;
	akhir = n -1;
	while (( !ketemu) && ( awal <= akhir)){
		tengah = (awal + akhir )/2;
		int hasil = strcmp(judulCari, film[tengah].judul);
		if( hasil == 0){
			ketemu = true;
        }
        else if(hasil < 0){
			akhir =tengah - 1;
		}
		else{
			awal = tengah + 1;
		}
	}
	if (ketemu){
		cout <<"\nFilm ditemukan\n";
		cout << film[tengah].judul <<" " << film[tengah].tahun << " " << film[tengah].rating <<" " << endl;
	} else{
		cout <<"Judul tidak ditemukan. Pastikan data sudah di-sort A-Z.\n";
	}
}

void tambahFilm (dataFilm film[], int &n){
	cout <<"Input Judul : ";
	cin.getline(film[n].judul, 100);
	
	cout <<"Input Harga : ";
	cin >> film[n].harga;
	
	cout << "Input Tahun : ";
	cin >>film[n].tahun;
	
	cout << "Input Rating : ";
	cin >> film[n].rating;
	cin.ignore();
	
	n++;
	cout <<"[ SUCCESS ] Data berhasil disinkronkan ke netfilm_db.txt\n";
	cout << "[ SUCCESS ] Film berhasil ditambahkan\n";
}

int main(){
	dataFilm film[100]; 
	int jumlah;
	bacaFile(film, jumlah);
	
	int menu;
	do {
		cout <<"\n============================================\n";
		cout <<"         NETFILM SYSTEM - DASHBOARD\n";
		cout <<"============================================\n";
		cout << "[1] Lihat Katalog Film\n";
		cout << "[2] Urutkan Rating (Quick Sort)\n";
		cout <<"[3] Urutkan Abjad (Bubble Sort)\n";
		cout <<"[4] Cari Film (Linear Search)\n";
		cout <<"[5] Cari Film (Binary Search)\n";
		cout <<"[6] Tambah Film Baru\n";
		cout <<"[0] Keluar & Simpan\n";
		cout <<"============================================\n";
		cout <<"Pilih Menu : ";
		cin >> menu;
		cin.ignore();
		
		if( menu ==1){ //menampilkan data
			tampilkan(film,jumlah);
			cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
		}
		else if(menu== 2){ //menu quick sort
			quickSort(film, 0, jumlah-1);
			tampilkan(film,jumlah);
			cout <<"[!] Katalog berhasil diurutkan berdasarkan Rating Tertinggi.\n";
			cout << "\nTekan Enter untuk melanjutkan...";
			cin.get();
		}
		else if (menu ==3){ //menu bubble sort
			bubbleSort(film, jumlah);
			tampilkan(film, jumlah);
			cout << "[!] Katalog berhasil diurutkan berdasarkan Abjad (A-Z).\n";
			cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
		}
		else if( menu == 4){ //linear search
			if ( jumlah >= 30 ){
				cout <<"Gunakan Binary Search jika data lebih atau sama dengan 30 film\n";
			} else {
				linearSearch(film,  jumlah);
			}
			cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
		} else if (menu == 5){
			if (jumlah < 30){
				cout <<"Jumlah film kurang dari 10. Gunakan linear search.\n";
			} else {
				binary(film,jumlah);
			}
			cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
		}
		
		else if(menu== 6){ //menu tambah film
			tambahFilm(film,jumlah);
			cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
		}
		else if (menu == 0) { //keluar dan simpan file
			saveFile (film,jumlah);
			cout <<"[SUCCESS ] Data berhasil disinkronkan ke netfilm_db.txt\n";
			cout << "\nSistem Offline. Terimakasih!\n";
		} else{
			cout <<"Menu tidak tersedia\n";
		} 
	} while( menu !=0);
}
