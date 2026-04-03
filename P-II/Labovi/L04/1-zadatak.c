/*
 * ZADATAK 1 - L04
 * 
 * KAKO POKRENUTI:
 *   gcc 1-zadatak.c -o 1-zadatak
 *   .\1-zadatak A.TXT B.TXT
 * 
 * OČEKIVANI ISPIS:
 *   - U datoteku B.TXT: sve riječi odvojene u nove linije:
 *       Univerzitet
 *       u
 *       Banjon
 *       Luci
 *       osnovan
 *       je
 *       novembra
 *       godine
 *   - Na stdout: najduža riječ (npr. "Univerzitet")
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Provjera broja argumenata
    if (argc != 3) {
        fprintf(stderr, "Upotreba: %s <ulazna_datoteka> <izlazna_datoteka>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Greska: Ne mogu otvoriti ulaznu datoteku '%s'\n", argv[1]);
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Greska: Ne mogu otvoriti izlaznu datoteku '%s'\n", argv[2]);
        fclose(inputFile);
        return 1;
    }

    char longestWord[1024] = "";
    int maxLength = 0;
    char currentWord[1024];
    int wordLength = 0;
    int ch;

    // Čitanje iz ulazne datoteke
    while ((ch = fgetc(inputFile)) != EOF) {
        // Ako je trenutni karakter dio riječi (slovo)
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            currentWord[wordLength++] = ch;
        } else {
            // Ako smo dostigli kraj riječi
            if (wordLength > 0) {
                currentWord[wordLength] = '\0';
                
                // Upisujemo riječ u izlaznu datoteku
                fprintf(outputFile, "%s\n", currentWord);
                
                // Provjeravamo da li je ovo najduža riječ
                if (wordLength > maxLength) {
                    maxLength = wordLength;
                    strcpy(longestWord, currentWord);
                }
                
                wordLength = 0;
            }
        }
    }

    // Obrada zadnje riječi ako postoji
    if (wordLength > 0) {
        currentWord[wordLength] = '\0';
        fprintf(outputFile, "%s\n", currentWord);
        
        if (wordLength > maxLength) {
            maxLength = wordLength;
            strcpy(longestWord, currentWord);
        }
    }

    // Zatvoranje datoteka
    fclose(inputFile);
    fclose(outputFile);

    // Ispis najduže riječi na stdout
    if (maxLength > 0) {
        printf("%s\n", longestWord);
    }

    return 0;
}

