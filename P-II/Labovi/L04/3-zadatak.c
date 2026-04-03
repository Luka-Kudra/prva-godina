/*
 * ZADATAK 3 - L04
 * 
 * KAKO POKRENUTI:
 *   gcc 3-zadatak.c -o 3-zadatak
 *   .\3-zadatak ARTIKLI.TXT
 * 
 * ŠТА ЈЕ POTREBNO:
 *   - Program će trebati od korisnika da unese:
 *       n=2
 *       1. artikal: A0001 Banane 2.00
 *       2. artikal: B1234 Jabuke 1.50
 *   - Datoteka ARTIKLI.TXT će biti kreira sa tabelom
 * 
 * OČEKIVANI ISPIS:
 *   - U datotuku ARTIKLI.TXT se ispisuje formatirana tablica:
 *       ===== ===== =================== ======
 *       RB.   SIFRA NAZIV               CIJENA
 *       ===== ===== =================== ======
 *       1     A0001 Banane              2.00
 *       2     B1234 Jabuke              1.50
 *       ===== ===== =================== ======
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sifra[6];      // 5 znakova + null terminator
    char naziv[21];     // 20 znakova + null terminator
    double cijena;
} Artikal;

int main(int argc, char *argv[]) {
    // Provjera broja argumenata
    if (argc != 2) {
        fprintf(stderr, "Upotreba: %s <datoteka>\n", argv[0]);
        return 1;
    }

    FILE *outputFile = fopen(argv[1], "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Greska: Ne mogu otvoriti datoteku '%s'\n", argv[1]);
        return 1;
    }

    int n;
    printf("n=");
    scanf("%d", &n);

    Artikal *artikli = (Artikal *)malloc(n * sizeof(Artikal));
    if (artikli == NULL) {
        fprintf(stderr, "Greska: Nedovoljna memorija\n");
        fclose(outputFile);
        return 1;
    }

    // Učitavanje podataka
    for (int i = 0; i < n; i++) {
        printf("%d. artikal: ", i + 1);
        scanf("%s %s %lf", artikli[i].sifra, artikli[i].naziv, &artikli[i].cijena);
    }

    // Ispis u datoteku
    fprintf(outputFile, "===== ===== =================== ======\n");
    fprintf(outputFile, "RB.   SIFRA NAZIV               CIJENA\n");
    fprintf(outputFile, "===== ===== =================== ======\n");

    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%-5d %-5s %-19s %.2f\n", 
                i + 1, artikli[i].sifra, artikli[i].naziv, artikli[i].cijena);
    }

    fprintf(outputFile, "===== ===== =================== ======\n");

    fclose(outputFile);
    free(artikli);

    return 0;
}
