#include <stdio.h>
#include <stdlib.h>
#define EXIT_ERROR -1
#define EXIT_SUCCESS 0

typdef struct polinom* Position;
typdef struct polinom {
    int koef;
    int eksp;
    Position next;
} Polinom;

int UnosPolinoma(Position P1, Position P2, FILE* pok_na_dad);
int ZbrojPolinoma(Position P1, Position P2, Position PR);
int Ispis(Position P);

int main(){
     /*nisam sigurna je li dadoteka postoji ili je treba stvoriti, idem s 
    pretpostavkom da postoji negdje i da je ne stvaramo tokom programa*/
    FILE* pok_na_dad = NULL;
    pok_na_dad = fopen("imedadoteke.txt","r");
    if(pok_na_dad == NULL)
        printf("Dadoteka se nije otvorila!");
    
    /*citam iz dadoteke i stvaram listu tako da jedan clan liste sdrzi vrijednost
    koeficijenta i eksponenta*/
    
    Polinom head = {
        .koef = 0,
        .eksp = 0,
        .next = NULL
    };
    struct polinom *novi; /*valjda moze i Position jer je Position pokazivac tog tipa*/
    /*deklaracija head je prekopirana iz tvog koda, nisam sigurna cemu nam deklaracija
    clana novi ovjde sluzi, no ti si imao deklaraciju clana q, a ja q mijenjam u novi 
    zbog lakseg shvacanja pa sam samo to promijenila iz q u novi, inace opet tvoj kod*/
    
    Polinom Head = {
        .koef = 0,
        .eksp = 0,
        .next = NULL
    };
    struct polinom *Novi; /* umm kao valjda za dvije liste trebamo dva zasebna heada? */
    
    UnosPolinoma(&head, &Head, FILE* pok_na_dad);
    
    Polinom RHead = {
        .koef = 0,
        .eksp = 0,
        .next = NULL
    };
    struct polinom *RNovi; /*ovo r ih oznacava kao dijelove rezultante liste
    koju dobijemo zbrajanjem prethodne dvije*/
    
    ZbrojPolinoma(&head,&Head,&RHead);
    Ispis(&RHead);
    
    return EXIT_SUCCESS;
}

int UnosPolinoma(Position P1, Position P2, FILE* pok_na_dad){
    
    FILE* pok_na_dad = NULL;
    pok_na_dad = fopen("imedadoteke.txt", "r");
    if(pok_na_dad == NULL)
        printf("Dadoteka se nije otvorila!");
        return EXIT_ERROR;
    
    while(fscanf != '\n'){
        Position novi;
        novi = (Position)malloc(sizeof(Polinom));
        fscanf(pok_na_dad," %d %d", &novi->koef, &novi->eksp); /*pretpostvljam da fscanf 
        ne ce imati problem s whitespace jer ne ucitavamo string/char values, nego intigere*/
        novi->next = P->next; 
        P->next = novi;
        
    } /*ovo je valjda unos za prvi polinom*/
    
    while(fscanf != '\n'){
        Position Novi;
        Novi = (Position)malloc(sizeof(Polinom));
        fscanf(pok_na_dad," %d %d", &Novi->koef, &Novi->eksp);
        Novi->next = P->next; 
        P->next = Novi;
        
    } /*ovo je valjda unos za drugi polinom*/
    
    return EXIT_SUCCESS;
}

int ZbrojPolinoma(Position P1, Position P2, Position PR){
    
    while(P1->next != NULL OR P2->next != NULL){
        Position RNovi;
        RNovi=(Position)malloc(sizeof(Polinom));
        if(P1.eksp < P2.eksp){
            RNovi.koef = P1.koef;
            RNovi.eksp = P1.eksp;
            RNovi->next = PR->next;
            PR->next = RNovi;
        }
        else if(P1.eksp > P2.eksp){
            RNovi.koef = P2.koef;
            RNovi.eksp = P2.eksp;
            RNovi->next = PR->next;
            PR->next = RNovi;
        }
        else if(P1.eksp == P2.eksp){
            RNovi.koef = P1.koef + P2.koef;
            RNovi.eksp = P1.eksp;
            RNovi->next = PR->next;
            PR->next = RNovi;
        }
    }
    
    if(PR == NULL)
        return EXIT_ERROR;
    else
        return EXIT_SUCCESS;
}

int Ispis(Position PR)
{

    if(PR == NULL)
        printf("\nOva lista je prazna")
        return EXIT_ERROR;
    else
    {
        printf("\nIspis liste: \n");
        while (P!=NULL)
        {
            printf("\n => %s %s %d",P->ime,P->prezime,P->godRod  );
            P=P->next;
        }
        printf("\n");
        return EXIT_SUCCESS;

    }
}
