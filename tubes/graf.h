#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED
#define INT_MAX 2147483647 // Nilai maksimum untuk integer 32-bit
#include <iostream>
#include <string>
using namespace std;
#define info(P) P->info
#define next(P) P->next
#define simpulBerikut(P) P->simpulBerikut
#define sisiPertama(P) P->sisiPertama
#define simpulTujuan(P) P->simpulTujuan
#define first(G) G.first

typedef struct Simpul* adrSimpul;
typedef struct Sisi* adrSisi;

struct Simpul {
    string info;
    adrSimpul simpulBerikut;
    adrSisi sisiPertama;
};

struct Sisi {
    adrSimpul simpulTujuan;
    int info;
    adrSisi next;
};

struct graf {
    adrSimpul first;
};

void initialGraf(graf &G);
adrSimpul alokasiSimpul(string id);
void tambahSimpul(graf& G, string id);
adrSisi alokasiSisi(int bobot, adrSimpul tujuan);
void tambahSisi(graf& G, string idSumber, string idTujuan, int bobot);
adrSimpul cariLokasi(graf G, string tempat);
void ruteTerpendek(graf G, string awal, string akhir);
void tampilkanGraf(const graf& G);
void tampilkanMenu();
void hapusLokasi(graf &G, string simpul);
void copyGraf(graf &G, graf &alternatif);



#endif // GRAF_H_INCLUDED
