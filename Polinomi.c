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

int UnosPolinoma_1(Position P, FILE* pok_na_dad);
int UnosPolinoma_2(Position P, FILE* pok_na_dad);

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
    
    UnosPolinoma_1(&head, FILE* pok_na_dad);
    
    Polinom Head = {
        .koef = 0,
        .eksp = 0,
        .next = NULL
    };
    struct polinom *Novi; /* umm kao valjda za dvije liste trebamo dva zasebna heada? */
    
    UnosPolinoma_2(&Head, FILE* pok_na_dad);
    
    return EXIT_SUCCESS;
}

int UnosPolinoma_1(Position P, FILE* pok_na_dad){
    
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
    
    return EXIT_SUCCESS;
}

int UnosPolinoma_2(Position P, FILE* pok_na_dad){
    
    FILE* pok_na_dad = NULL;
    pok_na_dad = fopen("imedadoteke.txt", "r");
    if(pok_na_dad == NULL)
        printf("Dadoteka se nije otvorila!");
        return EXIT_ERROR;
    
    while(fscanf != '\n'){
        Position Novi;
        Novi = (Position)malloc(sizeof(Polinom));
        fscanf(pok_na_dad," %d %d", &Novi->koef, &Novi->eksp);
        Novi->next = P->next; 
        P->next = Novi;
        
    } /*ovo je valjda unos za drugi polinom*/
    
    return EXIT_SUCCESS;
}
