
PRVI

`#include <stdio.h>

int main() 
{
    int broj;

    printf("Unesite cijeli broj: ");
    scanf("%d", &broj);

    if (broj > 0) 
    {
        printf("Broj je pozitivan\n");
    } 
    else if (broj < 0) 
    {
        printf("Broj je negativan\n");
    } 
    else 
    {
        printf("Broj je nula\n");
    }

    return 0;
}`


DRUGI 

`#include <stdio.h>

int main() 
{
    int a, b;

    printf("Unesite prvi broj (a): ");
    scanf("%d", &a);
    printf("Unesite drugi broj (b): ");
    scanf("%d", &b);

    if (a > b) 
    {
        printf("Veci broj je: %d\n", a);
    } 
    else if (b > a) 
    {
        printf("Veci broj je: %d\n", b);
    } 
    else 
    {
        printf("Brojevi su jednaki\n");
    }

    return 0;
}`

TRECI 

`#include <stdio.h>

int main() 
{
    int bodovi;

    printf("Unesite broj bodova (0-100): ");
    scanf("%d", &bodovi);

    // Prvo provjeravamo da li je unos van dozvoljenog opsega
    if (bodovi < 0 || bodovi > 100) 
    {
        printf("Nevazeci unos!\n");
    } 
    else if (bodovi < 55) 
    {
        printf("Ocjena: 5 (Nije polozio)\n");
    } 
    else if (bodovi <= 64) 
    {
        printf("Ocjena: 6\n");
    } 
    else if (bodovi <= 74) 
    {
        printf("Ocjena: 7\n");
    } 
    else if (bodovi <= 84) 
    {
        printf("Ocjena: 8\n");
    } 
    else if (bodovi <= 94) 
    {
        printf("Ocjena: 9\n");
    } 
    else 
    {
        printf("Ocjena: 10\n");
    }

    return 0;
}`