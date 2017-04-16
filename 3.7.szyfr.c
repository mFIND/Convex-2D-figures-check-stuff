#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void zahasluj_mnie(char * tab, char * haslo){
    int i,j,temp;
    for(i=0,j=0;haslo[i];i++,j++){
        haslo[i] = tolower(haslo[i]);
        if(haslo[i]==' ') haslo[i]='+';
        if(haslo[i]=='\n') haslo[i]=0;
        if(i>63)i=0;
    }
    for(i=0, j=0;tab[i];i++, j++){
        if(!haslo[j]) j = 0;
        temp = haslo[j] + (tab[i] - 32);
        if(temp>126) temp -= 95;
        tab[i] = temp;
    }
}
void odhasluj_mnie(char * tab, char * haslo){
    int i,j;
    for(i=0,j=0;haslo[i];i++,j++){
        haslo[i] = tolower(haslo[i]);
        if(haslo[i]==' ') haslo[i]='+';
        if(haslo[i]=='\n') haslo[i]=0;
        if(i>63) i=0;
    }
    for(i=0, j=0;tab[i];i++, j++){
        if(!haslo[j]) j=0;
        tab[i] = tab[i] - (haslo[j] - 32);
        if(tab[i]<32) tab[i] += 95;
    }
}
