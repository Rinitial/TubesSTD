#include "graf.h"

void initialGraf(graf &G) {
    first(G) = NULL;
}

adrSimpul alokasiSimpul(string id) {
    adrSimpul simpulBaru = new Simpul;
    info(simpulBaru) = id;
    simpulBerikut(simpulBaru) = NULL;
    sisiPertama(simpulBaru) = NULL;
    return simpulBaru;
}

void tambahSimpul(graf& G, string id) {
    adrSimpul simpulBaru = alokasiSimpul(id);
    if (first(G) == NULL) {
        first(G) = simpulBaru;
    } else {
        adrSimpul temp = first(G);
        while (simpulBerikut(temp) != NULL) {
            temp = simpulBerikut(temp);
        }
        simpulBerikut(temp) = simpulBaru;
    }
}

adrSisi alokasiSisi(int bobot, adrSimpul tujuan) {
    adrSisi sisiBaru = new Sisi;
    info(sisiBaru) = bobot;
    simpulTujuan(sisiBaru) = tujuan;
    next(sisiBaru) = NULL;
    return sisiBaru;
}

void tambahSisi(graf& G, string idSumber, string idTujuan, int bobot) {
    adrSimpul sumber = G.first;
    while (sumber != NULL && info(sumber) != idSumber) {
        sumber = simpulBerikut(sumber);
    }

    adrSimpul tujuan = G.first;
    while (tujuan != NULL && info(tujuan) != idTujuan) {
        tujuan = simpulBerikut(tujuan);
    }

    if (sumber != NULL && tujuan != NULL) {
        adrSisi sisiBaru = alokasiSisi(bobot, tujuan);
        next(sisiBaru) = sisiPertama(sumber);
        sisiPertama(sumber) = sisiBaru;

        adrSisi sisiBaru2 = alokasiSisi(bobot, sumber);
        next(sisiBaru2) = sisiPertama(tujuan);
        sisiPertama(tujuan) = sisiBaru2;
    } else {
        cout << "Error: Simpul sumber atau tujuan tidak ditemukan!" << endl;
    }
}

adrSimpul cariLokasi(graf G, string tempat) {
    adrSimpul current = first(G);
    while (current != NULL && info(current) != tempat) {
        current = simpulBerikut(current);
    }
    if (current != NULL) {
        return current;
    } else {
        return NULL;
    }
}

void ruteTerpendek(graf G, string awal, string akhir) {
    adrSimpul Awal = cariLokasi(G, awal);
    adrSimpul Akhir = cariLokasi(G, akhir);

    if (Awal == NULL || Akhir == NULL) {
        cout << "Error: Tempat awal atau akhir tidak ditemukan." << endl;
        return;
    }

    const int MAX_SIMPUL = 100;
    int jarak[MAX_SIMPUL];
    bool visited[MAX_SIMPUL];
    adrSimpul simpulArray[MAX_SIMPUL];
    int predecessor[MAX_SIMPUL]; // Untuk melacak jalur
    int idxAwal = -1, idxAkhir = -1;

    int jumlahSimpul = 0;
    adrSimpul current = first(G);
    while (current != NULL) {
        simpulArray[jumlahSimpul] = current;
        jarak[jumlahSimpul] = INT_MAX;
        visited[jumlahSimpul] = false;
        predecessor[jumlahSimpul] = -1; // Tidak ada predecessor
        if (current == Awal) idxAwal = jumlahSimpul;
        if (current == Akhir) idxAkhir = jumlahSimpul;
        jumlahSimpul++;
        current = simpulBerikut(current);
    }

    jarak[idxAwal] = 0;

    for (int i = 0; i < jumlahSimpul; ++i) {
        int minJarak = INT_MAX;
        int idxMin = -1;

        for (int j = 0; j < jumlahSimpul; ++j) {
            if (!visited[j] && jarak[j] < minJarak) {
                minJarak = jarak[j];
                idxMin = j;
            }
        }

        if (idxMin == -1) break;
        visited[idxMin] = true;

        adrSisi sisi = sisiPertama(simpulArray[idxMin]);
        while (sisi != NULL) {
            int idxTetangga = -1;
            for (int k = 0; k < jumlahSimpul; ++k) {
                if (simpulArray[k] == simpulTujuan(sisi)) {
                    idxTetangga = k;
                    break;
                }
            }
            if (idxTetangga != -1 && !visited[idxTetangga]) {
                int jarakBaru = jarak[idxMin] + info(sisi);
                if (jarakBaru < jarak[idxTetangga]) {
                    jarak[idxTetangga] = jarakBaru;
                    predecessor[idxTetangga] = idxMin; // Simpan jalur
                }
            }
            sisi = next(sisi);
        }
    }

    if (jarak[idxAkhir] == INT_MAX) {
        cout << "Tidak ada rute dari " << awal << " ke " << akhir << "." << endl;
    } else {
        cout << "Rute Terpendek dari " << awal << " ke " << akhir << " melalui jalan berikut:" << endl;

        // Rekonstruksi jalur dari predecessor
        int path[MAX_SIMPUL];
        int pathIdx = 0;
        for (int idx = idxAkhir; idx != -1; idx = predecessor[idx]) {
            path[pathIdx++] = idx;
        }

        // Cetak jalur dari awal ke akhir
        for (int i = pathIdx - 1; i >= 0; --i) {
            cout << info(simpulArray[path[i]]);
            if (i > 0) cout << " - ";
        }
        cout << endl;

        cout << "Dengan total jarak = " << jarak[idxAkhir] << "." << endl;
    }
}




void tampilkanGraf(const graf& G) {
    adrSimpul temp = G.first;
    while (temp != NULL) {
        cout << "Tempat: " << info(temp) << ":";
        adrSisi sisi = sisiPertama(temp);
        while (sisi != NULL) {
            cout << " -> " << info(simpulTujuan(sisi)) << "(" << info(sisi) << ")";
            sisi = next(sisi);
        }
        cout << endl;
        temp = simpulBerikut(temp);
    }
}

void tampilkanMenu() {
    cout << "\nMenu Pilihan:\n";
    cout << "1. Tambahkan Tempat\n";
    cout << "2. Tambahkan Jalan\n";
    cout << "3. Print Graf\n";
    cout << "4. Cari Rute Terpendek\n";
    cout << "5. Hapus Lokasi yang bermasalah\n";
    cout << "0. Keluar\n";
    cout << "Pilih opsi: ";
}

void hapusLokasi(graf &G, string simpul) {
    adrSimpul s = cariLokasi(G, simpul);

    if (s == NULL) {
        cout << "Error: Tempat yang ingin dihapus tidak ditemukan.\n";
        return;
    }

   //hapus semua sisi dari loksi
    adrSisi sisiTemp = sisiPertama(s);
    while (sisiTemp != NULL) {
        adrSisi sisiHapus = sisiTemp;
        sisiTemp = next(sisiTemp);
        delete sisiHapus;
    }
    sisiPertama(s) = NULL;

    // Hapus semua sisi dari seluruh simpul yang mengarah ke lokasi yang ingin dihpus
    adrSimpul curSimpul = first(G);
    while (curSimpul != NULL) {
        adrSisi prevSisi = NULL;
        adrSisi curSisi = sisiPertama(curSimpul);

        while (curSisi != NULL) {
            if (simpulTujuan(curSisi) == s) {
                if (prevSisi == NULL) {
                    sisiPertama(curSimpul) = next(curSisi);
                } else {
                    next(prevSisi) = next(curSisi);
                }
                adrSisi sisiHapus = curSisi;
                curSisi = next(curSisi);
                delete sisiHapus;
            } else {
                prevSisi = curSisi;
                curSisi = next(curSisi);
            }
        }
        curSimpul = simpulBerikut(curSimpul);
    }

    // Hapus simpul dari graf
    if (first(G) == s) {
        first(G) = simpulBerikut(s);
    } else {
        adrSimpul prevSimpul = first(G);
        while (simpulBerikut(prevSimpul) != s) {
            prevSimpul = simpulBerikut(prevSimpul);
        }
        simpulBerikut(prevSimpul) = simpulBerikut(s);
    }

    delete s;
    cout << "Tempat \"" << simpul << "\" berhasil dihapus dari graf.\n";
}

void copyGraf(graf &G, graf &alternatif) {
    adrSimpul currentG = first(G);

    while (currentG != NULL) {
        tambahSimpul(alternatif, info(currentG));
        currentG = simpulBerikut(currentG);
    }

    currentG = first(G);
    while (currentG != NULL) {
        adrSisi sisiCurrent = sisiPertama(currentG);
        while (sisiCurrent != NULL) {
            adrSimpul sumberAlternatif = first(alternatif);
            while (sumberAlternatif != NULL && info(sumberAlternatif) != info(currentG)) {
                sumberAlternatif = simpulBerikut(sumberAlternatif);
            }

            adrSimpul tujuanAlternatif = first(alternatif);
            while (tujuanAlternatif != NULL && info(tujuanAlternatif) != info(simpulTujuan(sisiCurrent))) {
                tujuanAlternatif = simpulBerikut(tujuanAlternatif);
            }

            if (sumberAlternatif != NULL && tujuanAlternatif != NULL) {
                tambahSisi(alternatif, info(sumberAlternatif), info(tujuanAlternatif), info(sisiCurrent));
            }

            sisiCurrent = next(sisiCurrent);
        }
        currentG = simpulBerikut(currentG);
    }
}

