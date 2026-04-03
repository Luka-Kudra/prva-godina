/*
 * ZADATAK 1 - L05
 * 
 * KAKO POKRENUTI:
 *   gcc 1-zadatak.c -o 1-zadatak
 *   1-zadatak unos imenik.bin
 *   1-zadatak citanje imenik.bin
 * 
 * ŠТА ЈЕ POTREBNO:
 *   - Za unos: program će pitati korisnika da unese ime, prezime i broj telefona
 *       Marko Markovic +38766123123
 *       Janko Jankovic 051789789
 *   - Za čitanje: datoteka imenik.bin (kreira se lors unosa)
 * 
 * OČEKIVANI ISPIS:
 *   Unos:
 *       Unesite podatke o osobama...
 *       Sprema 2 osoba u datoteku 'imenik.bin'
 *   
 *   Čitanje:
 *       Sadržaj datoteke 'imenik.bin':
 *       ====================================
 *       Marko Markovic +38766123123
 *       Janko Jankovic 051789789
 *       ====================================
 *       Ukupno osoba: 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ime[50];
    char prezime[50];
    char broj_telefona[20];
} Osoba;

void unos_podataka(const char *naziv_datoteke) {
    FILE *file = fopen(naziv_datoteke, "wb");
    if (file == NULL) {
        fprintf(stderr, "Greška: Ne mogu otvoriti datoteku '%s'\n", naziv_datoteke);
        return;
    }

    Osoba osoba;
    int broj_osoba = 0;

    printf("Unesite podatke o osobama (ime prezime broj_telefona).\n");
    printf("Za završetak unesite EOF (Ctrl+Z na Windows-u ili Ctrl+D na Linux-u):\n\n");

    while (scanf("%49s %49s %19s", osoba.ime, osoba.prezime, osoba.broj_telefona) == 3) {
        fwrite(&osoba, sizeof(Osoba), 1, file);
        broj_osoba++;
    }

    fclose(file);
    printf("\nSprema %d osoba u datoteku '%s'\n", broj_osoba, naziv_datoteke);
}

void citanje_podataka(const char *naziv_datoteke) {
    FILE *file = fopen(naziv_datoteke, "rb");
    if (file == NULL) {
        fprintf(stderr, "Greška: Ne mogu otvoriti datoteku '%s'\n", naziv_datoteke);
        return;
    }

    Osoba osoba;
    int broj_osoba = 0;

    printf("Sadržaj datoteke '%s':\n", naziv_datoteke);
    printf("====================================\n");

    while (fread(&osoba, sizeof(Osoba), 1, file) == 1) {
        printf("%s %s %s\n", osoba.ime, osoba.prezime, osoba.broj_telefona);
        broj_osoba++;
    }

    printf("====================================\n");
    printf("Ukupno osoba: %d\n", broj_osoba);

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Upotreba: %s <unos|citanje> <datoteka>\n", argv[0]);
        fprintf(stderr, "  unos    - unos novih podataka u datoteku\n");
        fprintf(stderr, "  citanje - prikaz podataka iz datoteke\n");
        return 1;
    }

    if (argc == 2) {
        // Ako je samo datoteka proslijeđena, pitaj korisnika
        printf("Odaberite opciju:\n");
        printf("1 - unos novih podataka\n");
        printf("2 - prikaz postojećih podataka\n");
        printf("Odabir (1 ili 2): ");

        int odabir;
        scanf("%d", &odabir);

        if (odabir == 1) {
            unos_podataka(argv[1]);
        } else if (odabir == 2) {
            citanje_podataka(argv[1]);
        } else {
            fprintf(stderr, "Nevaljana opcija!\n");
            return 1;
        }
    } else if (argc == 3) {
        // Ako su proslijeđeni operacija i datoteka
        if (strcmp(argv[1], "unos") == 0) {
            unos_podataka(argv[2]);
        } else if (strcmp(argv[1], "citanje") == 0) {
            citanje_podataka(argv[2]);
        } else {
            fprintf(stderr, "Nevaljana operacija: '%s'\n", argv[1]);
            fprintf(stderr, "Koristite 'unos' ili 'citanje'\n");
            return 1;
        }
    }

    return 0;
}
