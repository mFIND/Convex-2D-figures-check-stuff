/**

Autor: Mateusz Findeisen G2I3/1I3

*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "3.7.main.h"
#include "3.7.files.c"
#include "3.7.szyfr.c"
#include "3.7.math.oper.c"
#include "3.7.struct.oper.c"
#include "3.7.misc.c"

int main (){
    char s[100], __delall_pomocnicza[4];
    int temp,i;
    for(;;){
        printf("$> ");
        fgets(s,99,stdin);
        if(tolower(s[0])=='q' && (s[1]=='\n' || s[1]==' ')){
/** QUIT */
            puts("Konczenie pracy programu...");
            free_for_all();
            puts("Dziekujemy i zapraszamy ponownie.");
            break;
        }
        if(s[0]=='?'){
            if(s[1]!='\n' && s[1]!=' '){blad(i); continue;}
/** ? */
            help();
            continue;
        }
        for(i=0;i<1;i++){
/** TUTAJ UMIESZCZAM SPRAWDZANIE KOMENDY JAKA WPISAL UZYTKOWNIK */
            if(tolower(s[0])=='h'){
                if(tolower(s[++i])!='e'){blad(i); break;}
                if(tolower(s[++i])!='l'){blad(i); break;}
                if(tolower(s[++i])!='p'){blad(i); break;}
                if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** HELP */
                help();
                break;
            }
            if(tolower(s[0])=='c'){
                if(tolower(s[++i])!='l'){blad(i); break;}
                if(tolower(s[++i])!='e'){blad(i); break;}
                if(tolower(s[++i])!='a'){blad(i); break;}
                if(tolower(s[++i])!='r'){blad(i); break;}
                if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** CLEAR */
                #ifdef __linux__
                system("clear");
                #elif defined(_WIN32) || defined(WIN32)
                system("cls");
                #else
                puts("OS not supported!");
                #endif
                break;
            }
            if(tolower(s[0])=='d'){
                if(tolower(s[++i])!='e'){blad(i); break;}
                if(tolower(s[++i])!='l'){blad(i); break;}
                if(tolower(s[++i])!='a'){
                    if(s[i]!='\n' && s[i]!=' '){blad(i); break;}
/** DEL */
                    usun_pkt(&(s[i+1]));
                    break;
                }
                if(tolower(s[++i])!='l'){blad(i); break;}
                if(tolower(s[++i])!='l'){blad(i); break;}
                if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** DELLALL */
                puts("Czy na pewno chcesz usunac wszystkie punkty z pamieci programu?");
                for(temp=0;temp<4;temp++)
                    __delall_pomocnicza[temp] = 0;
                for(;tolower(__delall_pomocnicza[0])!='n' && __delall_pomocnicza[1]!='\n' && __delall_pomocnicza[1]!=' ';){
                    puts("Kontynuowac?:   t/n");
                    fgets(__delall_pomocnicza,3,stdin);
                    if(tolower(__delall_pomocnicza[0])=='t' && (__delall_pomocnicza[1]=='\n' || __delall_pomocnicza[1]==' ')){
                        puts("Usuwam...");
                        free_for_all();
                        break;
                    }
                }
                break;
            }
            if(tolower(s[0])=='a'){
                if(tolower(s[++i])!='r'){blad(i); break;}
                if(tolower(s[++i])!='e'){blad(i); break;}
                if(tolower(s[++i])!='a'){blad(i); break;}
                if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** AREA */
                area();
                break;
            }
            if(tolower(s[0])=='p'){
                if(tolower(s[++i])!='o'){
                        if(tolower(s[i]=='e')){
                            if(tolower(s[++i])!='r'){blad(i); break;}
                            if(tolower(s[++i])!='i'){blad(i); break;}
                            if(tolower(s[++i])!='m'){blad(i); break;}
                            if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** PERIMETER */
                            perim();
                            break;
                        }else{
                            blad(i); break;
                        }
                }
                if(tolower(s[++i])!='i'){blad(i); break;}
                if(tolower(s[++i])!='n'){blad(i); break;}
                if(tolower(s[++i])!='t'){blad(i); break;}
                if(tolower(s[++i])!='s'){blad(i); break;}
                if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** POINTS */
                points();
                break;
            }
            if(tolower(s[0])=='n'){
                if(tolower(s[++i])!='e'){blad(i); break;}
                if(tolower(s[++i])!='w'){blad(i); break;}
                if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** NEW */
                dodaj_pkt(&(s[i+1]));
                break;
            }
            if(tolower(s[0])=='s'){
                if(tolower(s[++i])!='a'){blad(i); break;}
                if(tolower(s[++i])!='v'){blad(i); break;}
                if(tolower(s[++i])!='e'){blad(i); break;}
                if(s[++i]!='\n' && s[i]!=' '){
                    if(tolower(s[i]=='e')){
                        if(tolower(s[++i])!='n'){blad(i); break;}
                        if(tolower(s[++i])!='c'){blad(i); break;}
                        if(tolower(s[++i])!='r'){blad(i); break;}
                        if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** SAVE ENCRYPTED */
                        save_encrypted(&(s[i+1]));
                        break;
                    }else{
                        blad(i); break;
                    }
                }
/** SAVE */
                save(&(s[i+1]));
                break;
            }
            if(tolower(s[0])=='l'){
                if(tolower(s[++i])!='o'){blad(i); break;}
                if(tolower(s[++i])!='a'){blad(i); break;}
                if(tolower(s[++i])!='d'){blad(i); break;}
                if(s[++i]!='\n' && s[i]!=' '){
                    if(tolower(s[i]=='e')){
                        if(tolower(s[++i])!='n'){blad(i); break;}
                        if(tolower(s[++i])!='c'){blad(i); break;}
                        if(tolower(s[++i])!='r'){blad(i); break;}
                        if(s[++i]!='\n' && s[i]!=' '){blad(i); break;}
/** LOAD ENCRYPTED */
                        load_encrypted(&(s[i+1]));
                        break;
                    }else{
                        blad(i); break;
                    }
                }
/** LOAD */
                load(&(s[i+1]));
                break;
            }
            printf("Jesli nie wiesz co mozesz zrobic, wpisz '?'\n");
        }
    }
    return 0;
}
