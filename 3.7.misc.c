#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void free_for_all(){
    if(left){
        left->prev->nxt=NULL;
        for(;;){
            if(!left->nxt){
                free(left);
                right=NULL;
                left=NULL;
                ilosc_pkt = 0;
                return;
            }
            left = left -> nxt;
            free(left -> prev);
        }
    }
    ilosc_pkt = 0;
    return;
}
void points(){
    struct point *akt;
    if(!left){
        printf("Nie mam co wpisac, bo nie wczytales danych!\n");
        return;
    }
    for(akt = left;;akt=akt->nxt){
        printf("(%f,%f)",akt->x,akt->y);
        if(akt == left) printf("   <-   left");
        if(akt == right) printf("   <-   right");
        printf("\n");
        if(akt->nxt == left || akt->nxt == NULL) return;
    }
    return;
}
void blad(int n){
    int i;
    n = n+3;
    for(i=0;i<n;i++) printf(" ");
    printf("^   <-   ERROR!\n");
    return;
}
void help(){
    printf("?/HELP - wypisuje dostepne komendy\nAREA - wypisuje pole figury powstalej z wczytanych punktow\nCLEAR - czysci konsole\nDEL <a> <b> - usuwa punkt o wspolrzednych (a,b)\n");
    printf("DEL - usuwa punkty podane w kolejnych linijkach az do podania komendy STOP\nDELALL - usuwa wszystkie punkty, pyta o potwierdzenie\nLOAD <*.txt> - wczytuje dane z pliku o nazwie *.txt\n");
    printf("LOADENCR <*.txt> <PASS> - wczytuje plik o nazwie *.txt zaszyfrowany haslem PASS\nNEW <a> <b> - dodaje nowy punkt o wspolrzednych (a,b)\nNEW - dodaje nowe punkty az do podania komendy STOP\n");
    printf("PERIM - podaje obwod dla wczytanych punktow\nPOINTS - wypisuje wszystkie wczytane punkty\nSAVE <*.txt> - zapisuje punkty do pliku *.txt nadpisujac go\nSAVEENCR <*.txt> <PASS> - zapisuje punkty do pliku o nazwie *.txt z haslem PASS nadpisujac go\n");
    printf("Q - opuszcza program\n");
}
