#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int prosta(double x, double y, double z, double t, double *a, double *b){
    if(x==z){
        if(y==t) return 0;
        *a=*b=x;
        return 1;
    }
    *a = (y-t) / (x-z);
    *b = y - (*a) * x;
    return 0;
}
int polozenie_pkt_a_prosta(double x, double y, double a, double b, short int pionowa){
    /** 1 nad, -1 pod, 0 na ORAZ na lewo od x=a -> 1, na prostej x=a -> 0, na prawo od x=a -> -1 */
    double temp;
    if(pionowa == 0){
        temp = a * x + b;
        if(temp > y) return -1;
        if(temp == y) return 0;
        if(temp < y) return 1;
    }else{
        if(x < a && x < b) return 1;
        if(x == a && x == b) return 0;
        if(x > a && x > b) return -1;
        printf("ERROR, *pionowa zostala zle obsluzona!\n");
        return -1;
    }
    return -1;
}
double odleglosc_dwoch_pkt(double x, double y, double z, double t){
    return sqrt((x-z)*(x-z) + (y-t)*(y-t));
}
double pow_trap(double x1, double x2, double a, double b, double OX){
    if(x1 == x2) return 0;
    if(x1 > x2)
        return ((a * x1+b-OX)+(a * x2+b-OX)) * (x1-x2) / 2;
    return ((a * x1+b-OX)+(a * x2+b-OX)) * (x2-x1) / 2;
}
