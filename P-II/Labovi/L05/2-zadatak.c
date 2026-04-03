/*
 * ZADATAK 2 - L05
 * 
 * KAKO POKRENUTI:
 *   gcc 2-zadatak.c -o 2-zadatak
 *   2-zadatak unos tekst.bin
 *   2-zadatak citanje tekst.bin
 * 
 * ŠТА ЈЕ POTREBNO:
 *   - Za unos: korisnik unosi tekst, koji se šifruje s Cezarovom šifrom (pomeraj 3)
 *   - Za čitanje: datoteka tekst.bin s šifrovanim tekstom
 * 
 * OČEKIVANI ISPIS:
 *   Unos:
 *       Unesite tekst (Ctrl+Z pa Enter za završetak):
 *       HELLO WORLD
 *       Tekst je šifrovan i spreman u datoteku 'tekst.bin'
 *   
 *   Čitanje (ispisuje dešifrovan tekst - vraća original):
 *       Dešifrovan tekst iz datoteke 'tekst.bin':
 *       ====================================
 *       HELLO WORLD
 *       ====================================
 *   
 *   Napomena: A→D, B→E, C→F, ... Z→C (pomeraj 3)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define POMERAJ 3  // Pomeraj za Cezarovu šifru

char sifruj_karakter(char c) {
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' + POMERAJ) % 26;
    } else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' + POMERAJ) % 26;
    }
    return c;  // Karakteri koji nisu slova ostaju isti
}

char desifruj_karakter(char c) {
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' - POMERAJ + 26) % 26;
    } else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' - POMERAJ + 26) % 26;
    }
    return c;
}

void unos_teksta(const char *naziv_datoteke) {
    FILE *file = fopen(naziv_datoteke, "wb");
    if (file == NULL) {
        fprintf(stderr, "Greska: Ne mogu otvoriti datoteku '%s'\n", naziv_datoteke);
        return;
    }

    printf("Unesite tekst (Ctrl+Z pa Enter za zavrsetak):\n");

    char linija[1024];
    while (fgets(linija, sizeof(linija), stdin) != NULL) {
        // Šifruj svaki karakter u liniji
        for (int i = 0; linija[i] != '\0'; i++) {
            linija[i] = sifruj_karakter(linija[i]);
        }
        
        // Upiši šifrovan tekst u datoteku
        fputs(linija, file);
    }

    fclose(file);
    printf("Tekst je sifrovan i spreman u datoteku '%s'\n", naziv_datoteke);
}

void prikazi_teksta(const char *naziv_datoteke) {
    FILE *file = fopen(naziv_datoteke, "rb");
    if (file == NULL) {
        fprintf(stderr, "Greska: Ne mogu otvoriti datoteku '%s'\n", naziv_datoteke);
        return;
    }

    printf("Dešifrovan tekst iz datoteke '%s':\n", naziv_datoteke);
    printf("====================================\n");

    char linija[1024];
    while (fgets(linija, sizeof(linija), file) != NULL) {
        // Dešifruj svaki karakter u liniji
        for (int i = 0; linija[i] != '\0'; i++) {
            linija[i] = desifruj_karakter(linija[i]);
        }
        
        printf("%s", linija);
    }

    printf("====================================\n");
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Upotreba: %s <unos|citanje> <datoteka>\n", argv[0]);
        fprintf(stderr, "  unos    - unos novog teksta (sifruje se)\n");
        fprintf(stderr, "  citanje - prikaz šifrovanog teksta iz datoteke (desifruje se)\n");
        return 1;
    }

    if (argc == 2) {
        // Ako je samo datoteka proslijeđena, pitaj korisnika
        printf("Odaberite opciju:\n");
        printf("1 - unos novog teksta\n");
        printf("2 - prikaz teksta iz datoteke\n");
        printf("Odabir (1 ili 2): ");

        int odabir;
        scanf("%d", &odabir);
        getchar();  // Konsumuj newline nakon broja

        if (odabir == 1) {
            unos_teksta(argv[1]);
        } else if (odabir == 2) {
            prikazi_teksta(argv[1]);
        } else {
            fprintf(stderr, "Nevaljana opcija!\n");
            return 1;
        }
    } else if (argc == 3) {
        // Ako su proslijeđeni operacija i datoteka
        if (strcmp(argv[1], "unos") == 0) {
            unos_teksta(argv[2]);
        } else if (strcmp(argv[1], "citanje") == 0) {
            prikazi_teksta(argv[2]);
        } else {
            fprintf(stderr, "Nevaljana operacija: '%s'\n", argv[1]);
            fprintf(stderr, "Koristite 'unos' ili 'citanje'\n");
            return 1;
        }
    }

    return 0;
}
