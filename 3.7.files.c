#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void reset_pliku(char *s){
    int i;
    for(i=0;s[i];i++){
        if(s[i]=='\n') s[i]=0;
    }
    pFile = fopen(s,"r");
    if(pFile){
        fclose(pFile);
        pFile = fopen (s,"w");
        if (pFile!=NULL){
            fclose (pFile);
        }
    }
}
void pisz(char *tab, char *s){
    pFile = fopen (s,"a");
    tab[strlen(tab)] = '\n';
    if (pFile!=NULL){
        fputs (tab,pFile);
        fclose (pFile);
    }
}
void czytaj(char *tab, char *s){
    pFile = fopen (s,"r");
    if (pFile!=NULL){
        fscanf (pFile,"%[255]",tab);
        fclose (pFile);
    }
    tab[strlen(tab)-1] = 0;
}
void save(char *s){
    char tab[50];
    int i;
    struct point *akt;
    if(!left){
        printf("Nie mam co wpisac, bo nie wczytales danych!\n");
        return;
    }
    if(strlen(s)<1){
        printf("Podales za malo argumentow!\n");
        return;
    }
    for(i=0;s[i];i++){
        if(s[i]==' ' || s[i] == '\n') s[i]=0;
    }
    reset_pliku(s);
    for(akt = left;akt;akt=akt->nxt){
        for(i=0;i<50;i++)
            tab[i]=0;
        sprintf (tab, "%f %f", akt->x, akt->y);
        pisz(tab,s);
        if(akt->nxt == left){
            puts("Wszystkie punkty zostaly zapisane pomyslnie!");
            return;
        }
    }
    return;
}
void save_encrypted(char *s){
    struct point *akt;
    char pass[64],tab[55];
    int i,j=0;
    if(!left){
        printf("Nie mam co wpisac, bo nie wczytales danych do programu!\n");
        return;
    }
    for(i=0;s[i];i++){
        if(j){
            pass[j-1] = s[i];
            if(pass[j-1] == ' ') pass[j-1]='+';
            if(pass[j-1] == '\n') pass[j-1]=0;
            s[i]=0;
            j++;
        }
        if(s[i]==' ') {
            s[i]=0;
            j=1;
        }
    }
    reset_pliku(s);
    for(i=0;i<50;i++)
        tab[i]=0;
    sprintf (tab, "%s", pass);
    zahasluj_mnie(tab, pass);
    pisz(tab,s);
    for(akt = left;akt;akt=akt->nxt){
        for(i=0;i<50;i++)
            tab[i]=0;
        sprintf (tab, "%f %f", akt->x, akt->y);
        zahasluj_mnie(tab, pass);
        pisz(tab,s);
        if(akt->nxt == left){
            puts("Wszystkie punkty zostaly zapisane pomyslnie!");
            return;
        }
    }
    return;
}
void load(char *s){
    double x,y;
    int i=0;
    if(left){
        puts("ERROR nie wczytuje pliku, poniewaz sa juz wczytane punkty! Zastosuj SAVE jesli chcesz je zachowac, a nastepnie DELALL jesli chcesz wczytac nowe punkty z pliku");
        return;
    }
    if(strlen(s)<1){
        printf("Podales za malo argumentow!\n");
        return;
    }
    for(i=0;s[i];i++){
        if(s[i]==' ' || s[i] == '\n') s[i]=0;
    }
    i=0;
    pFile = fopen (s,"r");
    if (pFile!=NULL){
        while(fscanf (pFile,"%lf %lf",&x,&y) == 2){
            i++;
            struktura_punktow_dodaj(x,y);
        }
        if(feof(pFile)){
            printf("Wczytalem punktow: %d\n",i);
            fclose (pFile);
            return;
        }else{
            printf("Blad w pliku w %d linijce! (+/- 1)\n",i+1);
            fclose (pFile);
            return;
        }
    }
    puts("Taki plik nie istnieje!");
    return;
}
void load_encrypted(char *s){
    char pass[64],tab[55],pass_check[55], *pEnd;
    double x,y;
    int i,j=0;
    if(left){
        puts("ERROR nie wczytuje pliku, poniewaz sa juz wczytane punkty! Zastosuj SAVE jesli chcesz je zachowac, a nastepnie DELALL jesli chcesz wczytac nowe punkty z pliku");
        return;
    }
    for(i=0;s[i];i++){
        if(j){
            pass[j-1] = s[i];
            if(pass[j-1] == ' ') pass[j-1]='+';
            if(pass[j-1] == '\n') pass[j-1]=0;
            s[i]=0;
            j++;
        }
        if(s[i]==' ') {
            s[i]=0;
            j=1;
        }
    }
    i=0;
    pFile = fopen (s,"r");
    sprintf (pass_check, "%s", pass);
    if (pFile!=NULL){
        for(i=0;i<50;i++){
            tab[i]=0;
            pass_check[i]=0;
        }
        strcpy(pass_check,pass);
        fgets(tab,50,pFile);
        zahasluj_mnie(pass_check, pass);
        for(i=0;i<50;i++){
            if(tab[i] == '\n') tab[i]=0;
            if(tab[i] != pass_check[i]){
                puts("Error, zle haslo!");
                return;
            }
        }
        for(i=0;i<50;i++){
            tab[i]=0;
        }
        i=0;
        while(fgets(tab,50,pFile)){
            odhasluj_mnie(tab, pass);
            x = strtod(tab, &pEnd);
            j = pEnd-tab+1;
            y = strtod(&tab[j], &pEnd);
            struktura_punktow_dodaj(x,y);
            i++;
            for(j=0;j<50;j++)
                tab[j]=0;
        }
        if(feof(pFile)){
            printf("Wczytalem punktow: %d\n",i);
            fclose (pFile);
            return;
        }else{
            printf("Blad w pliku w %d linijce! (+/- 1)\n",i+1);
            fclose (pFile);
            return;
        }
    }
    puts("Taki plik nie istnieje!");
    return;
}
