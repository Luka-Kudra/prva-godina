/*
 * ZADATAK 2 - L04
 * 
 * KAKO POKRENUTI:
 *   gcc 2-zadatak.c -o 2-zadatak
 *   2-zadatak KRUGOVI.TXT
 * 
 * OČEKIVANI ISPIS:
 *   - Na stdout: koordinate i polupročnik kruga s najvećom površinom
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

int main(int argc, char *argv[]) {
    // Provjera broja argumenata
    if (argc != 2) {
        fprintf(stderr, "Upotreba: %s <datoteka_sa_krugovima>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Greska: Ne mogu otvoriti datoteku '%s'\n", argv[1]);
        return 1;
    }

    double x, y, r;
    double maxArea = 0;
    double maxX, maxY, maxR;
    int foundCircle = 0;

    // Čitanje krugova iz datoteke
    while (fscanf(file, "(%lf,%lf,%lf)", &x, &y, &r) == 3) {
        // Izračunavanje površine kruga: P = π * r²
        double area = M_PI * r * r;
        
        // Provjera je li ovo najveća površina dosad
        if (area > maxArea) {
            maxArea = area;
            maxX = x;
            maxY = y;
            maxR = r;
            foundCircle = 1;
        }
    }

    fclose(file);

    // Ispis rezultata
    if (foundCircle) {
        printf("Najvecu povrsinu (P=%.3f) ima krug: (%.3f,%.3f,%.3f)\n", 
               maxArea, maxX, maxY, maxR);
    } else {
        printf("Datoteka ne sadrzi krugove.\n");
    }

    return 0;
}
