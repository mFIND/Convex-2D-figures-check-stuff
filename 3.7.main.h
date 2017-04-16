FILE *pFile;
void reset_pliku(char*);
void pisz(char*,char*);
void czytaj(char*,char*);
void save(char*);
void save_encrypted(char*);
void load(char*);
void load_encrypted(char*);

void zahasluj_mnie(char*,char*);
void odhasluj_mnie(char*,char*);

int prosta(double,double,double,double,double*,double*);
int polozenie_pkt_a_prosta(double,double,double,double,short int);
double odleglosc_dwoch_pkt(double,double,double,double);
double pow_trap(double,double,double,double,double);

struct point{
    double x,y,a,b;
    short int pionowa;
    struct point *prev, *nxt;
};
struct point *right = NULL;
struct point *left = NULL;
int ilosc_pkt=0;

void dodaj_pkt(char*);
void struktura_punktow_dodaj(double,double);
int is_valid(double,double,struct point*,short int);
void wstaw_za(struct point*, struct point*);
void usun_pkt(char*);
void struktura_punktow_usun(double,double);
void perim();
void area();

void free_for_all();
void points();
void blad(int);
void help();
