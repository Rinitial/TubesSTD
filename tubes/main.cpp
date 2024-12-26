#include "graf.h"

int main() {
    graf G;
    graf alternatif;
    initialGraf(alternatif);
    initialGraf(G);


    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int jumlah;
                cout << "Masukkan jumlah tempat yang ingin ditambahkan: ";
                cin >> jumlah;

                for (int i = 0; i < jumlah; ++i) {
                    string idSimpul;
                    cout << "Masukkan nama tempat (ID) ke-" << (i+1) << ": ";
                    cin >> idSimpul;
                    tambahSimpul(G, idSimpul);
                    cout << "Tempat \"" << idSimpul << "\" berhasil ditambahkan ke graf.\n";
                }
                break;
            }

            case 2: {
                cout << "\nDaftar Tempat:\n";
                adrSimpul temp = G.first;
                int no = 1;
                while (temp != NULL) {
                    cout << no++ << ". " << info(temp) << endl;
                    temp = simpulBerikut(temp);
                }
                int pilihanAsal, pilihanTujuan;
                cout << "Masukkan nomor tempat asal: ";
                cin >> pilihanAsal;
                cout << "Masukkan nomor tempat tujuan: ";
                cin >> pilihanTujuan;
                adrSimpul asal = G.first;
                adrSimpul tujuan = G.first;
                int i = 1;
                while (asal != NULL && i < pilihanAsal) {
                    asal = simpulBerikut(asal);
                    i++;
                }
                i = 1;
                while (tujuan != NULL && i < pilihanTujuan) {
                    tujuan = simpulBerikut(tujuan);
                    i++;
                }
                if (asal != NULL && tujuan != NULL) {
                    int bobot;
                    cout << "Masukkan bobot/jarak jalan: ";
                    cin >> bobot;
                    tambahSisi(G, info(asal), info(tujuan), bobot);
                    cout << "Jalan berhasil ditambahkan antara " << info(asal) << " dan " << info(tujuan) << ".\n";
                }
                break;
            }

            case 3:
                tampilkanGraf(G);
                break;

            case 4: {
                string asal, tujuan, b, a;
                cout << "Masukkan tempat asal: ";
                cin >> asal;
                cout << "Masukkan tempat tujuan: ";
                cin >> tujuan;
                cout << "Apakah ada tempat yang bermasalah? Y/N" << endl;
                cin >> a;
                if (a == "Y"){
                    cout << "Masukkan nama tempat yang ingin dihapus: ";
                    cin >> b;
                    copyGraf(G, alternatif);
                    hapusLokasi(alternatif, b);
                    ruteTerpendek(alternatif, asal, tujuan);
                } else if (a == "N"){
                    ruteTerpendek(G, asal, tujuan);
                }

                break;
            }

            case 5: {
                string namaTempat;
                cout << "Masukkan nama tempat yang ingin dihapus: ";
                cin >> namaTempat;
                hapusLokasi(G, namaTempat);
                break;
            }

            case 0:
                cout << "Terima kasih, program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 0);
}
