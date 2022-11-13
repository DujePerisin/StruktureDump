#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1
#define C_MAX 1000

typedef struct _stog* Position;
typedef struct _stog{
    char uneseno[C_MAX];
    Position next;
}Stog;

int Push(Position P, char [C_MAX]);
int Add(Position P);
int Minus(Position P);
int Multiply(Position P);
int Ispis(Position P); /*pročitat će konačni rezultat tj. jednin preostali element stoga te testirati je li sve ok*/

int main(){

    printf("Ovo je program koji iz dadoteke(koja se već nalazi na računalu u istom folderu kao i program) učitava postfix i izračunava ga.");

    Position head;
    head = (Position)malloc(sizeof(Stog));
    head->next = NULL;

    FILE* pok = NULL;
    pok = fopen("Postfix.txt", "r");
    if(pok == NULL){
        printf("Dadoteka se nije otvorila!");
    }
    
    char string[C_MAX] = {0};
    if(fscanf(pok, "\n %[^\n]", string)){
        printf("Ovo je string %s",string); /* Success */
    }
    else{
        printf("Greška sa fscanf!");
    }

    if(string == NULL) printf("Greška pri čitanju iz dadoteke!");

    char provjera[C_MAX] = {0}; /*mjesto u memoriji gdje je iščitani podatak iz dadotke privremeno spremljen kako bi mogli odrediti što s tim podatkom treba dalje raditi-koju funkciju zvati*/
 
    while(sscanf(string, "%s", provjera)){

        printf("\n Ovo je provjera %s", provjera); /*success*/

        if(strcmp(provjera, "+") == 0 && head->next != NULL && head->next->next != NULL && strcmp(head->next->uneseno,"0") ){ /*drugi uvjet osigurava da operator ne dolazi na prazan stog, treći da imamo 2 operanda, četvrti da prvi operand nije nula*/
            Add(head);
        }
        else if(strcmp(provjera, "-") == 0 && head->next != NULL && head->next->next != NULL && strcmp(head->next->uneseno,"0")){
            Minus(head);
        }
        else if(strcmp(provjera, "*") == 0 && head->next != NULL && head->next->next != NULL && strcmp(head->next->uneseno,"0")){
            Multiply(head);
        }
        else /*if(strcmp(provjera,"\t") == 0)*/{ /*uvjet da ignorira razmake?*/
            Push(head, provjera);
        }
    }
    



    return EXIT_SUCCESS;
}

int Push(Position P, char provjera[C_MAX]){

    Position temp; /*Position P je povezana s head, a position temp je privremena varijabla koju mozemo korisiti ako zelimo osigurati da uvijek imamo dirketan pristup headu preko Position P*/
    temp = (Position)malloc(sizeof(Stog));

    strcpy(temp->uneseno, provjera);
    temp->next = P->next;
    P->next = temp;
    

    printf("\n %s", temp->uneseno);
    Ispis(P->next);

    return EXIT_SUCCESS;
}

int Add(Position P){

    Position D; /*D kao desni operand od operatora, onaj na dnu stoga*/
    Position L; /*L kao lijevi operand, onaj na vrhu stoga*/
    D = (Position)malloc(sizeof(Stog));
    L = (Position)malloc(sizeof(Stog));
    D = P->next->next;
    L = P->next;

    strcpy(D->uneseno, D->uneseno + (int)L->uneseno);
    P->next = D;
    free(L);

    Ispis(P->next);

    return EXIT_SUCCESS;
}

int Minus(Position P){

    Position D; /*D kao desni operand od operatora, onaj na dnu stoga*/
    Position L; /*L kao lijevi operand, onaj na vrhu stoga*/
    D = (Position)malloc(sizeof(Stog));
    L = (Position)malloc(sizeof(Stog));
    D = P->next->next;
    L = P->next;

    strcpy(D->uneseno, D->uneseno - (int)L->uneseno);
    P->next = D;
    free(L);

    Ispis(P->next);

    return EXIT_SUCCESS;
}

int Multiply(Position P){

    Position D; /*D kao desni operand od operatora, onaj na dnu stoga*/
    Position L; /*L kao lijevi operand, onaj na vrhu stoga*/
    D = (Position)malloc(sizeof(Stog));
    L = (Position)malloc(sizeof(Stog));
    D = P->next->next;
    L = P->next;

    /*strcpy(D->uneseno, D->uneseno × (int)L->uneseno); problem s množenjem*/
    P->next = D;
    free(L);

    return EXIT_SUCCESS;
}

int Ispis(Position P)
{

    if(P == NULL){
        printf("\nOva lista je prazna\n");
		return EXIT_ERROR;
	}
    else
    {
        printf("\nIspis liste: \n");
        while (P!=NULL)
        {
            printf("%s", P->uneseno );
            P=P->next;
        }
        printf("\n");

		return EXIT_SUCCESS;
    }
}