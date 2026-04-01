#include <stdio.h>
main(){
    int a, b, c;
    printf("Unesite tri cijela broja: ");
    scanf("%d %d %d", &a, &b, &c);
    if(a > b && a > c){
        printf("Najveci broj je: %d", a);
    }
    else if(b > a && b > c){
        printf("Najveci broj je: %d", b);
    }
    else{
        printf("Najveci broj je: %d", c);
    }
}