/*
 * ZADATAK 3 - L05
 * 
 * KAKO POKRENUTI:
 *   gcc 3-zadatak.c -o 3-zadatak
 *   .\3-zadatak unos brojevi.bin
 *   3-zadatak citanje brojevi.bin
 * 
 * ŠТА ЈЕ POTREBNO:
 *   - Za unos: korisnik unosi proizvoljan broj cijelobrojnih podataka
 *       Primer: 5 3 9 1 7 (Ctrl+Z za završetak)
 *   - Za čitanje: datoteka brojevi.bin s brojevima
 * 
 * OČEKIVANI ISPIS:
 *   Unos:
 *       Unesite cijelobrojne podatke (Ctrl+Z pa Enter za završetak):
 *       5 3 9 1 7
 *       Uspješno sprema 5 brojeva u datoteku 'brojevi.bin' (sortirano opadajuće)
 *   
 *   Čitanje (brojevi sortirani opadajuće):
 *       Sadržaj datoteke 'brojevi.bin':
 *       ====================================
 *       9
 *       7
 *       5
 *       3
 *       1
 *       ====================================
 *       Ukupno brojeva: 5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funkcija za poređenje elemenata pri qsort - sortira u opadajućem redoslijedu
int kompajruj_opadajuce(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    
    if (x > y) return -1;
    if (x < y) return 1;
    return 0;
}

void unos_podataka(const char *naziv_datoteke) {
    FILE *file = fopen(naziv_datoteke, "wb");
    if (file == NULL) {
        fprintf(stderr, "Greska: Ne mogu otvoriti datoteku '%s'\n", naziv_datoteke);
        return;
    }

    int *brojevi = (int *)malloc(10 * sizeof(int));
    if (brojevi == NULL) {
        fprintf(stderr, "Greska: Nedovoljna memorija\n");
        fclose(file);
        return;
    }

    int kapacitet = 10;
    int broj_elemenata = 0;
    int broj;

    printf("Unesite cijelobrojne podatke (Ctrl+Z pa Enter za završetak):\n");

    while (scanf("%d", &broj) == 1) {
        // Ako trebamo više memorije
        if (broj_elemenata >= kapacitet) {
            kapacitet *= 2;
            int *temp = (int *)realloc(brojevi, kapacitet * sizeof(int));
            if (temp == NULL) {
                fprintf(stderr, "Greska: Nedovoljna memorija\n");
                free(brojevi);
                fclose(file);
                return;
            }
            brojevi = temp;
        }

        brojevi[broj_elemenata++] = broj;
    }

    // Sortiranje u opadajućem redoslijedu
    qsort(brojevi, broj_elemenata, sizeof(int), kompajruj_opadajuce);

    // Prvo upisujemo broj elemenata
    fwrite(&broj_elemenata, sizeof(int), 1, file);

    // Zatim upisujemo sve brojeve
    fwrite(brojevi, sizeof(int), broj_elemenata, file);

    fclose(file);
    free(brojevi);

    printf("Uspjesno sprema %d brojeva u datoteku '%s' (sortirano opadajuće)\n", 
           broj_elemenata, naziv_datoteke);
}

void citanje_podataka(const char *naziv_datoteke) {
    FILE *file = fopen(naziv_datoteke, "rb");
    if (file == NULL) {
        fprintf(stderr, "Greska: Ne mogu otvoriti datoteku '%s'\n", naziv_datoteke);
        return;
    }

    // Čitamo broj elemenata
    int broj_elemenata;
    if (fread(&broj_elemenata, sizeof(int), 1, file) != 1) {
        fprintf(stderr, "Greska: Datoteka je prazna ili oštećena\n");
        fclose(file);
        return;
    }

    int *brojevi = (int *)malloc(broj_elemenata * sizeof(int));
    if (brojevi == NULL) {
        fprintf(stderr, "Greska: Nedovoljna memorija\n");
        fclose(file);
        return;
    }

    // Čitamo sve brojeve
    if (fread(brojevi, sizeof(int), broj_elemenata, file) != broj_elemenata) {
        fprintf(stderr, "Greska: Greska pri citanju datoteke\n");
        free(brojevi);
        fclose(file);
        return;
    }

    fclose(file);

    // Ispis podataka
    printf("Sadrzaj datoteke '%s':\n", naziv_datoteke);
    printf("====================================\n");

    for (int i = 0; i < broj_elemenata; i++) {
        printf("%d\n", brojevi[i]);
    }

    printf("====================================\n");
    printf("Ukupno brojeva: %d\n", broj_elemenata);

    free(brojevi);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Upotreba: %s <unos|citanje> <datoteka>\n", argv[0]);
        fprintf(stderr, "  unos    - unos novih podataka\n");
        fprintf(stderr, "  citanje - prikaz podataka iz datoteke\n");
        return 1;
    }

    if (argc == 2) {
        // Ako je samo datoteka proslijeđena, pitaj korisnika
        printf("Odaberite opciju:\n");
        printf("1 - unos novih podataka\n");
        printf("2 - prikaz podataka iz datoteke\n");
        printf("Odabir (1 ili 2): ");

        int odabir;
        scanf("%d", &odabir);
        getchar();  // Konsumuj newline nakon broja

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
