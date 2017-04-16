#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void dodaj_pkt(char *s){
    char tab[50], *pEnd;
    double x,y;
    int i=0;
    for(i=0;i<45;i++){
        if(s[i]=='\n' || s[i]==' ') s[i]=0;
        tab[i] = 0;
    }
    if(strlen(s)<1){
        for(;;){
            printf("Podaj wspolrzedne nowego punktu, lub wpisz 'STOP' aby zakonczyc wpisywanie:\n");
            fgets(tab,45,stdin);
            if(tolower(tab[0])=='s'){
                if(tolower(tab[1])!='t'){blad(-2); continue;}
                if(tolower(tab[2])!='o'){blad(-1); continue;}
                if(tolower(tab[3])!='p'){blad(0); continue;}
                if(tab[4]!='\n' && tab[4]!=' '){;blad(1); continue;}
                return;
            }
            x = strtod(tab, &pEnd);
            i = pEnd-tab+1;
            if((isdigit(tab[0]) || tab[0] == '.' || tab[0] == '-' || tab[0] == '+') && (isdigit(tab[i]) || tab[i] == '.' || tab[i] == '-' || tab[i] == '+')){
                y = strtod(&tab[i], &pEnd);
                struktura_punktow_dodaj(x,y);
                continue;
            }
            puts("Upewnij sie, ze podales 2 liczby!");
        }
    }
    x = strtod(s, &pEnd);
    i = pEnd-s+1;
    if((isdigit(s[0]) || s[0] == '.' || s[0] == '-' || s[0] == '+') && (isdigit(s[i]) || s[i] == '.' || s[i] == '-' || s[i] == '+')){
        y = strtod(&s[i], &pEnd);
        struktura_punktow_dodaj(x,y);
        return;
    }
    puts("Upewnij sie, ze podales 2 liczby!");
    return;
}
void struktura_punktow_dodaj(double x, double y){
double a,b;
    short int temp=0, temp_more_3, czy_po_right = 0;
    struct point *akt,*tmp;
    akt = (struct point*)malloc(sizeof(struct point));
    ilosc_pkt++;
    if(!akt){
        puts("Nie udalo sie wczytac wiecej punktow. Brak miejsca na stosie pamieci. (?)");
        return;
    }else{
        akt->x = x;
        akt->y = y;
        tmp = left;
        if(ilosc_pkt < 3){
            if(!left){
                left = akt;
                right = akt;
                akt->prev = akt;
                akt->nxt = akt;
                tmp = left;
                akt->pionowa=0;
                return;
            }
            if(akt->x == tmp->x){
                if(akt->y == tmp->y){
                    printf("Taki punkt ( (%f,%f) ) juz istnieje! Wczytam nastepny.\n",akt->x,akt->y);
                    free(akt);
                    ilosc_pkt--;
                    return;
                }
                if(akt->y > tmp->y){
                    wstaw_za(tmp,akt);
                    right = akt;
                    akt->pionowa=1;
                    tmp->pionowa=1;
                    return;
                }
                wstaw_za(tmp,akt);
                left = akt;
                akt->pionowa=1;
                tmp->pionowa=1;
                return;
            } /* ENDOF: akt->x == tmp->x */
            if(akt->x > tmp->x){
                wstaw_za(tmp,akt);
                right = akt;
                akt->pionowa=0;
                tmp->pionowa=0;
                return;
            } /* ENDOF: akt->x > tmp->x */
            wstaw_za(tmp,akt);
            left = akt;
            akt->pionowa=0;
            tmp->pionowa=0;
            return;
            /* ENDOF: akt->x < tmp->x */
        }
        if(ilosc_pkt == 3){
            temp = polozenie_pkt_a_prosta(akt->x,akt->y, tmp->a, tmp->b, tmp->pionowa);
            if((akt->x == tmp->x && akt->y == tmp->y) || (akt->x == right->x && akt->y == right->y)){
                printf("Taki punkt ( (%f,%f) ) juz istnieje! Wczytam nastepny.\n",akt->x,akt->y);
                free(akt);
                ilosc_pkt--;
                return;
            }

            if(temp == 0){
                printf("Ten punkt ( (%f,%f) ) lezy na prostej przechodzacej przez pierwsze 2 punkty! Wczytam nastepny.\n",akt->x,akt->y);;
                free(akt);
                ilosc_pkt--;
                return;
            }
            prosta(tmp->x, tmp->y, akt->x, akt->y, &a, &b);
            if(akt->x < tmp->x){
                if(temp == 1){
                    wstaw_za(tmp,akt);
                    left = akt;
                    akt->pionowa = 0;
                    return;
                }
                if(temp == -1){
                    wstaw_za(tmp->nxt,akt);
                    left = akt;
                    akt->pionowa = 0;
                    return;
                }
            }
            if(akt->x == tmp->x){
                if(temp == 1){ /** powyzej */
                    wstaw_za(tmp,akt);
                    tmp->pionowa = 1;
                    return;
                }
                if(temp == -1){ /** ponizej */
                    wstaw_za(tmp->nxt,akt);
                    left = akt;
                    akt->pionowa = 1;
                    return;
                }
            }
            if(akt->x > tmp->x && akt->x < right->x){
                if(temp == -1){
                    wstaw_za(tmp->nxt,akt);
                    akt->pionowa = 0;
                    return;
                }
                if(temp == 1){
                    wstaw_za(tmp,akt);
                    akt->pionowa = 0;
                    return;
                }
            }
            if(akt->x == right->x){
                if(temp == 1){
                    wstaw_za(tmp,akt);
                    akt->pionowa = 1;
                    right = akt;
                    return;
                }
                if(temp == -1){
                    wstaw_za(tmp->nxt,akt);
                    akt->prev->pionowa=1;
                    return;
                }
            } /** ENDOF akt->x == right->x */
    /**
    polozenie_pkt_a_prosta(double x, double y, double a, double b, short int pionowa){
    1 nad, -1 pod, 0 na ORAZ na lewo od x=a -> 1, na prostej x=a -> 0, na prawo od x=a -> -1
    */
            if(temp == -1){
                wstaw_za(tmp->nxt,akt);
                right = akt;
                akt->pionowa = 0;
                return;
            }
            if(temp == 1){
                wstaw_za(tmp,akt);
                right = akt;
                akt->pionowa = 0;
                return;
            }

            printf("Uwaga, punkt nr %d nie zostal wczytany z powodu bledu w kodzie! Prosze przeslac wyczerpujace informacje o okolicznosciach bledu na maila mfindeis@mion.elka.pw.edu.pl\n",ilosc_pkt+1);
        }
        if(ilosc_pkt > 3){
            for(;;tmp = tmp->nxt){
                if(tmp == right)
                    czy_po_right = 1;
                temp_more_3 = is_valid(x,y,tmp,czy_po_right);
                if(temp_more_3 == 0){
                    puts("Punktu nie wczytuje, bo lezy na ktoryms z odcinkow lub jego przedluzeniu!");
                    free(akt);
                    ilosc_pkt--;
                    return;
                }
                if(temp_more_3 == 1){
                    continue;
                }
                if(temp_more_3 == 2){
                    puts("Punktu nie wczytuje, bo figura przestalaby byc wypukla!");
                    printf("Minimalny punkt ktory lezalby w srodku: (%f,%f)\n",tmp->x,tmp->y);
                    free(akt);
                    ilosc_pkt--;
                    return;
                }
                if(temp_more_3 == 3){
                    wstaw_za(tmp,akt);
                    return;
                }
                if(temp_more_3 == 4){
                    puts("FATAL ERROR! Blad w funkcji 'is_valid'! Prosze o wyslanie szczegolowych informacji odnosnie okolicznosci na adres fin_mat@interia.eu");
                    free(akt);
                    ilosc_pkt--;
                    return;
                }
                if(tmp->nxt == left){
                    printf("Punktu (%f,%f) nie wczytuje, bo lezalby w srodku figury!",akt->x,akt->y);
                    free(akt);
                    ilosc_pkt--;
                    return;
                }
            }
        }
        puts("FATAL ERROR! Jesli czytasz nie numer punktu <2, nie ==2 i nie >2 to nie masz prawa tego napisu widziec. Prosze o wyslanie szczegolowych informacji odnosnie okolicznosci na adres fin_mat@interia.eu");
    }
}
int is_valid(double x, double y, struct point* tmp, short int czy_po_right){
    short int temp;
    temp = polozenie_pkt_a_prosta(x,y,tmp->a,tmp->b,tmp->pionowa);
    if(czy_po_right == 0){
        if(temp == 0) return 0; /** na prostej */
        if(temp == -1) return 1; /** continue */
        if(temp == 1){
            temp = polozenie_pkt_a_prosta(x,y,tmp->prev->a,tmp->prev->b,tmp->prev->pionowa);
            if(tmp == left){
                if(temp == -1) return 2; /** blad od razu */
                if(temp == 0) return 0; /** na prostej */
                if(temp == 1){
                    temp = polozenie_pkt_a_prosta(x,y,tmp->nxt->a,tmp->nxt->b,tmp->nxt->pionowa);
                    if(tmp == right->prev){
                        if(temp == -1) return 1; /** continue */
                        if(temp == 0) return 0; /** na prostej */
                        if(temp == 1) return 3; /** dobry pkt */
                    }
                    if(temp == -1) return 3; /** DOBRY PUNKT */
                    if(temp == 0) return 0; /** na prostej */
                    if(temp == 1) return 1;
                }
            }
            if(temp == 0) return 0; /** na prostej */
            if(temp == 1) return 2;
            if(temp == -1){
                temp = polozenie_pkt_a_prosta(x,y,tmp->nxt->a,tmp->nxt->b,tmp->nxt->pionowa);
                if(tmp == right->prev){
                    if(temp == -1) return 1; /** continue */
                    if(temp == 0) return 0; /** na prostej */
                    if(temp == 1) return 3; /** dobry pkt */
                }
                if(temp == -1) return 3;
                if(temp == 0) return 0; /** na prostej */
                if(temp == 1) return 1;
            }
        }
    }

    if(temp == 0) return 0; /** na prostej */
    if(temp == 1) return 1; /** continue */
    if(temp == -1){
        temp = polozenie_pkt_a_prosta(x,y,tmp->prev->a,tmp->prev->b,tmp->prev->pionowa);
        if(tmp == right){
            if(temp == 1) return 2; /** continue */
            if(temp == 0) return 0; /** na prostej */
            if(temp == -1){
                temp = polozenie_pkt_a_prosta(x,y,tmp->nxt->a,tmp->nxt->b,tmp->nxt->pionowa);
                if(tmp == left->prev){
                    if(temp == -1) return 3; /** continue */
                    if(temp == 0) return 0; /** na prostej */
                    if(temp == 1) return 1; /** dobry pkt */
                }
                if(temp == -1) return 1;
                if(temp == 0) return 0; /** na prostej */
                if(temp == 1) return 3; /** DOBRY PUNKT */
            }
        }
        if(temp == 0) return 0; /** na prostej */
        if(temp == -1) return 2; /** ten punkt bylby w srodku*/
        if(temp == 1){
            temp = polozenie_pkt_a_prosta(x,y,tmp->nxt->a,tmp->nxt->b,tmp->nxt->pionowa);
            if(tmp == left->prev){
                if(temp == -1) return 3; /** dobry punkt */
                if(temp == 0) return 0; /** na prostej */
                if(temp == 1) return 1; /** continue */
            }
            if(temp == -1) return 1;
            if(temp == 0) return 0; /** na prostej */
            if(temp == 1) return 3;
        }
    }
    return 4;
}
void wstaw_za(struct point *tmp, struct point *akt){
    akt->prev = tmp;
    akt->nxt = tmp->nxt;
    tmp->nxt = akt;
    akt->nxt->prev = akt;
    akt->pionowa = prosta(akt->x, akt->y, akt->nxt->x, akt->nxt->y, &(akt->a), &(akt->b));
    tmp->pionowa = prosta(tmp->x, tmp->y, akt->x, akt->y, &(tmp->a), &(tmp->b));
    if(akt->x > right->x){
        right = akt;
    }else{
        if(akt->x == right->x && akt->y > right->y)
            right = akt;
    }
    if(akt->x < left->x){
        left = akt;
    }else{
        if(akt->x == left->x && akt->y < left->y)
            left = akt;
    }
    return;
}
void usun_pkt(char *s){
    char tab[50], *pEnd;
    double x,y;
    int i=0;
    for(i=0;i<45;i++){
        if(s[i]=='\n' || s[i]==' ') s[i]=0;
        tab[i] = 0;
    }
    if(strlen(s)<1){
        for(;;){
            printf("Podaj wspolrzedne punktu do usuniecia, lub wpisz 'STOP' aby zakonczyc usuwanie:\n");
            fgets(tab,45,stdin);
            if(tolower(tab[0])=='s'){
                if(tolower(tab[1])!='t'){blad(-2); continue;}
                if(tolower(tab[2])!='o'){blad(-1); continue;}
                if(tolower(tab[3])!='p'){blad(0); continue;}
                if(tab[4]!='\n' && tab[4]!=' '){blad(1); continue;}
                return;
            }
            x = strtod(tab, &pEnd);
            i = pEnd-tab+1;
            y = strtod(&tab[i], &pEnd);
            struktura_punktow_usun(x,y);
        }
    }
    x = strtod(s, &pEnd);
    i = pEnd-s+1;
    y = strtod(&s[i], &pEnd);
    struktura_punktow_usun(x,y);
    return;
}
void struktura_punktow_usun(double x, double y){
    if(left){
        struct point *tmp;
        if(left == right && left->x == x && left->y == y){
            free(left);
            printf("Usuwam punkt (%f,%f)\n",x,y);
            ilosc_pkt--;
            left = right = NULL;
            return;
        }
        for(tmp = left; !(tmp->nxt == left); tmp = tmp->nxt){
            if(left->prev->x == x && left->prev->y == y)
                tmp = left->prev;
            if(tmp->x == x && tmp->y == y){
                if(tmp == left){
                    if(tmp->nxt->x < tmp->prev->x) left = tmp->nxt;
                    if(tmp->nxt->x > tmp->prev->x) left = tmp->prev;
                    if(tmp->nxt->x == tmp->prev->x) left = tmp->prev;
                }
                if(tmp == right){
                    if(tmp->nxt->x < tmp->prev->x) right = tmp->prev;
                    if(tmp->nxt->x > tmp->prev->x) right = tmp->nxt;
                    if(tmp->nxt->x == tmp->prev->x) right = tmp->nxt;
                }
                if((tmp->nxt == tmp && tmp->prev != tmp) || (tmp->prev == tmp && tmp->nxt != tmp)){
                    puts("Bardzo przepraszam, mialem niestety blad krytyczny w funkcji void struktura_punktow_usun(double,double);");
                    return;
                }
                tmp->prev->nxt = tmp->nxt;
                tmp->nxt->prev = tmp->prev;
                tmp->prev->pionowa = prosta(tmp->prev->x, tmp->prev->y, tmp->nxt->x, tmp->nxt->y, &(tmp->prev->a), &(tmp->prev->b));
                free(tmp);
                printf("Usuwam punkt (%f,%f)\n",x,y);
                ilosc_pkt--;
                return;
            }
        }
    }else{
        puts("Nie mam co usuwac, bo nie sa wczytane zadne punkty!");
        return;
    }
    puts("Taki punkt nie istnieje.");
    return;
}
void perim(){
    struct point *akt;
    double obwod = 0;
    if(!left || left->nxt == left->prev){
        puts("Za malo punktow, by mowic o obwodzie!");
        return;
    }
    for(akt = left;;akt=akt->nxt){
        obwod = obwod + odleglosc_dwoch_pkt(akt->x,akt->y,akt->nxt->x,akt->nxt->y);
        if(akt->nxt == left || akt->nxt == NULL) break;
    }
    printf("Obwod wczytanej figury to: %.10f\n",obwod);
    return;
}
void area(){
    struct point *tmp1, *tmp2;
    double area = 0, y;
    if(!left || left->nxt == left->prev){
        puts("Za malo punktow, by mowic o polu!");
        return;
    }
    y = left->y;
    for(tmp2 = left->prev;tmp2 != right->prev;tmp2 = tmp2->prev){
        if(tmp2->y < y) y = tmp2->y;
    }
    if(left->pionowa == 1){
        tmp1 = left->nxt;
        tmp2 = left;
    }else{
        if(left->prev->pionowa == 1){
            tmp1 = left;
            tmp2 = left->prev;
        }else{
            tmp1 = tmp2 = left;
        }
    }
    for(;;){
        if(tmp1->nxt->x <= tmp2->prev->x){
            if(tmp1->nxt != right){
                tmp1 = tmp1->nxt;
            }else{
                tmp2 = tmp2->prev;
            }
        }else{
            if(tmp1->nxt->x > tmp2->prev->x){
                tmp2 = tmp2->prev;
            }else{
                puts("Niezrozumialy blad programu w funkcji area! Report to fin_mat@interia.eu!");
            }
        }
        if(tmp1 == tmp2) break;
        if(tmp1->prev->x > tmp2->x){
            area = area + pow_trap(tmp1->x,tmp1->prev->x,tmp1->prev->a,tmp1->prev->b,y) - pow_trap(tmp1->x,tmp1->prev->x,tmp2->prev->a,tmp2->prev->b,y);
        }else{
            if(tmp2->nxt->x > tmp1->x){
                area = area + pow_trap(tmp2->x,tmp2->nxt->x,tmp1->a,tmp1->b,y) - pow_trap(tmp2->x,tmp2->nxt->x,tmp2->a,tmp2->b,y);
            }else{
                if(tmp1->x > tmp2->x){
                    area = area + pow_trap(tmp1->x,tmp2->x,tmp1->prev->a,tmp1->prev->b,y) - pow_trap(tmp1->x,tmp2->x,tmp2->prev->a,tmp2->prev->b,y);
                }
                if(tmp1->x < tmp2->x){
                    area = area + pow_trap(tmp1->x,tmp2->x,tmp1->a,tmp1->b,y) - pow_trap(tmp1->x,tmp2->x,tmp2->a,tmp2->b,y);
                }
                if(tmp1->x == tmp2->x){
                    continue;
                }
            }
        }
        /**
            printf("Aktualna powierzchnia: %f\n",area);
        */
    }
    printf("Powierzchnia wczytanej figury to: %.10f\n",area);
    return;
}
