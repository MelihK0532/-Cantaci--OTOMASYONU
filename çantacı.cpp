/* Alper Melih Kýrçiçek (No - 2312721033)  || ÇANTACI OTOMASYONU  */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>

using namespace std;

const int a = 100;

struct Urun {
    string ad;
    double fiyat;
    int stokAdedi;
};

struct Musteri {
    string ad;
    string soyad;
    string telefon;
};

struct Satis {
    Musteri musteri;
    Urun urun;
    int adet;
};

struct CantaciOtomasyonu {
    Musteri musteriler[a];
    Urun urunler[a];
    Satis satislar[a];
    int musteriSayisi;
    int urunSayisi;
    int satisSayisi;

    CantaciOtomasyonu() : musteriSayisi(0), urunSayisi(0), satisSayisi(0) {
        dosyadanYukle();
    }

    ~CantaciOtomasyonu() {
        dosyayaKaydet();
    }

    void dosyadanYukle() {
        ifstream dosya("veriler.txt");
        if (dosya.is_open()) {
            dosya >> musteriSayisi;
            for (int i = 0; i < musteriSayisi; i++) {
                dosya >> musteriler[i].ad >> musteriler[i].soyad >> musteriler[i].telefon;
            }

            dosya >> urunSayisi;
            for (int i = 0; i < urunSayisi; i++) {
                dosya >> urunler[i].ad >> urunler[i].fiyat >> urunler[i].stokAdedi;
            }

            dosya >> satisSayisi;
            for (int i = 0; i < satisSayisi; i++) {
                dosya >> satislar[i].musteri.ad >> satislar[i].musteri.soyad >> satislar[i].musteri.telefon
                      >> satislar[i].urun.ad >> satislar[i].urun.fiyat >> satislar[i].urun.stokAdedi
                      >> satislar[i].adet;
            }

            dosya.close();
        }
    }

    void dosyayaKaydet() {
        ofstream dosya("veriler.txt");
        if (dosya.is_open()) {
            dosya << musteriSayisi << endl;
            for (int i = 0; i < musteriSayisi; i++) {
                dosya << musteriler[i].ad << " " << musteriler[i].soyad << " " << musteriler[i].telefon << endl;
            }

            dosya << urunSayisi << endl;
            for (int i = 0; i < urunSayisi; i++) {
                dosya << urunler[i].ad << " " << urunler[i].fiyat << " " << urunler[i].stokAdedi << endl;
            }

            dosya << satisSayisi << endl;
            for (int i = 0; i < satisSayisi; i++) {
                dosya << satislar[i].musteri.ad << " " << satislar[i].musteri.soyad << " " << satislar[i].musteri.telefon
                      << " " << satislar[i].urun.ad << " " << satislar[i].urun.fiyat << " " << satislar[i].urun.stokAdedi
                      << " " << satislar[i].adet << endl;
            }

            dosya.close();
        }
    }

    void musteriEkle() {
        if (musteriSayisi < a) {
            cout << "Musteri Adi: ";
            cin >> musteriler[musteriSayisi].ad;
            cout << "Musteri Soyadi: ";
            cin >> musteriler[musteriSayisi].soyad;
            cout << "Musteri Telefon: ";
            cin >> musteriler[musteriSayisi].telefon;

            musteriSayisi++;

            cout << "Musteri basariyla eklendi." << endl;
        } else {
            cout << "Musteri limitine ulasildi." << endl;
        }
    }

    void urunEkle() {
        if (urunSayisi < a) {
            cout << "Urun Adi: ";
            cin >> urunler[urunSayisi].ad;
            cout << "Urun Fiyati: ";
            cin >> urunler[urunSayisi].fiyat;
            cout << "Urun Stok Adedi: ";
            cin >> urunler[urunSayisi].stokAdedi;

            urunSayisi++;

            cout << "Urun basariyla eklendi." << endl;
        } else {
            cout << "Urun limitine ulasildi." << endl;
        }
    }

    void urunSat() {
        string musteriAdi, urunAdi;
        int adet;
        cout << "Musteri Adi: ";
        cin >> musteriAdi;
        cout << "Urun Adi: ";
        cin >> urunAdi;
        cout << "Adet: ";
        cin >> adet;

        int musteriIndex = -1;
        int urunIndex = -1;

        for (int i = 0; musteriIndex == -1 && i < musteriSayisi; i++) {
            if (musteriler[i].ad == musteriAdi) {
                musteriIndex = i;
            }
        }

        for (int i = 0; urunIndex == -1 && i < urunSayisi; i++) {
            if (urunler[i].ad == urunAdi) {
                urunIndex = i;
            }
        }

        if (musteriIndex != -1 && urunIndex != -1) {
            if (urunler[urunIndex].stokAdedi >= adet) {
                satislar[satisSayisi].musteri = musteriler[musteriIndex];
                satislar[satisSayisi].urun = urunler[urunIndex];
                satislar[satisSayisi].adet = adet;
                satisSayisi++;

                urunler[urunIndex].stokAdedi -= adet;
                cout << "Urun basariyla satildi." << endl;
            } else {
                cout << "Urun stokta yeterli miktarda bulunmamaktadir." << endl;
            }
        } else {
            cout << "Musteri veya urun bulunamadi." << endl;
        }
    }

    void envanterGoruntule() {
        cout << setw(20) << "Urun Adi" << setw(15) << "Fiyati" << setw(15) << "Stok Adedi" << endl;
        for (int i = 0; i < urunSayisi; i++) {
            cout << setw(20) << urunler[i].ad << setw(15) << urunler[i].fiyat << setw(15) << urunler[i].stokAdedi << endl;
        }
    }

    void satislariGoruntule() {
        cout << setw(20) << "Musteri Adi" << setw(20) << "Urun Adi" << setw(10) << "Adet" << endl;
        for (int i = 0; i < satisSayisi; i++) {
            cout << setw(20) << satislar[i].musteri.ad << setw(20) << satislar[i].urun.ad << setw(10) << satislar[i].adet << endl;
        }
    }
};

int main() {
    CantaciOtomasyonu cantaciOtomasyonu;
    char anamenu; 

    do {
        system("cls");

        cout << "|-------Hosgeldiniz-------|" << endl;
        cout << "|      Secim Yapiniz      |" << endl;
        cout << "|   1- Musteri Ekleme     |" << endl;
        cout << "|   2- Urun Ekle          |" << endl;
        cout << "|   3- Urun Sat           |" << endl;
        cout << "|   4- Envanter Goruntule |" << endl;
        cout << "|   5- Satislari Goruntule|" << endl;
        cout << "|-------------------------|" << endl;

        char secim;
        cin >> secim;

        switch (secim) {
            case '1':
                cantaciOtomasyonu.musteriEkle();
                break;
            case '2':
                cantaciOtomasyonu.urunEkle();
                break;
            case '3':
                cantaciOtomasyonu.urunSat();
                break;
            case '4':
                cantaciOtomasyonu.envanterGoruntule();
                break;
            case '5':
                cantaciOtomasyonu.satislariGoruntule();
                break;
            default:
                cout << "Gecersiz secim. Tekrar deneyin." << endl;
                break;
        }

        cout << "Anamenuye Donmek icin: a, cikmak icin: c" << endl;
        anamenu = _getch();

    } while (anamenu == 'a');

    return 0;
}

