#include <stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_NAME (1024)
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1   

struct _osoba;
typedef struct _osoba* Position;
typedef struct _osoba {
    char ime[MAX_NAME];
    char prezime[MAX_NAME];
    int godRod;
    Position next;
} Osoba;

void UnosP(Position P);
void UnosK(Position P);
void Ispis(Position P);
Position TraziPoPrez(Position P);
Position TraziPret(Position P);
int Brisi(Position P);
int UnosIza(Position P);
int UnosIspred(Position P);
int Sort(Position P);
int BrisiSve(Position P); 
int UnosDad(Position P, imedad);
int CitaDad(Position P, imedad);




int main(void)
{
    Osoba head = {
        .ime = {0},
        .prezime = {0},
        .godRod = 0,
        .next = NULL
    };
    struct _osoba *q;

    int odabir;

    char imedad[MAX_NAME];
    FILE* pok_na_dad = NULL;
    while(pok_na_dad==NULL){ 
    printf("Upisite ime datoteke.\n");
    scanf("%s", imedad); }
    /*pok_na_dad = fopen(imedad, "r+");
   
   if(pok_na_dad==NULL){
       printf("Greska, dadoteka nije otvorena."); }*/
      

    while(odabir != 0 )
    {
        printf("Unesite ispravan broj za odabir opcije: \n\n");
        printf("1 - Dodavanje novog elementa na pocetak liste\n");
        printf("2 - Ispis liste\n");
        printf("3 - Dodavanje novog elementa na kraj liste\n");
        printf("4 - Pronalazak elementa u listi (po prezimenu)\n");
        printf("5 - Brisanje odredenog elementa iz liste\n");
        printf("6 - Dodavanje novog elementa iza odredenog elementa\n");
        printf("7 - Dodavanje novog elementa ispred odredenog elementa\n");
        printf("8 - Sortiranje liste po prezimenima\n");
        printf("9 - Upis liste u datoteku\n");
        printf("10 - Citanje liste iz datoteke\n");
        printf("\n0 - Izlazak iz programa\n \n");

        scanf("%d",&odabir);

        switch(odabir)
        {
            case 1: 
                printf("Odabir 1\n");
                UnosP(&head);
                break;
            case 2:
                printf("Odabir 2\n");
                Ispis(head.next);
                break;
            case 3:
                printf("Odabir 3\n");
                UnosK(&head);
                break;
            case 4:
                printf("Odabir 4\n");
                q=TraziPoPrez(head.next);
                if(q==NULL)
                    printf("\n Osoba ne postoji u listi!");
			    else
				    printf("\nOsoba je: %s %s, %d\n", q->ime, q->prezime,q->godRod);
                break;
            case 5: 
                printf("Odabir 5\n");
                Brisi(&head);
                break;
            case 6:
                printf("Odabir 6\n");
                UnosIza(&head);
                break;
            case 7:
                printf("Odabir 7\n");
                UnosIspred(&head);
                break;
            case 8:
                printf("Odabir 8\n");
                Sort(&head);
                break;
            case 9:
                printf("Odabir 9\n");
                UnosDad(head.next, imedad);
                break;
            case 10:
                printf("Odabir 10\n");
                CitaDad(head.next, imedad);
                break;
        } 

        
    }

    /*UnosP(&head);
    UnosP(&head);
    UnosP(&head);
    //Ispis(head.next);
    UnosK(head.next);
    Ispis(head.next);*/


    printf("\n \n \n----OSLOBADANJE MEMORIJE----\n");
	BrisiSve(&head);

    return EXIT_SUCCESS;
}


void UnosP(Position P)
{
    
    Position q;
    q = (Position)malloc(sizeof(struct _osoba));

    printf("\nUnesite podatke o novoj osobi: ");
    scanf("%s %s %d",q->ime,q->prezime,&q->godRod);
    //q->El.x;
    q->next = P->next;
    P->next = q;
}

void Ispis(Position P)
{

    if(P == NULL)
        printf("\nOva lista je prazna");
    else
    {
        printf("\nIspis liste: \n");
        while (P!=NULL)
        {
            printf("\n => %s %s %d",P->ime,P->prezime,P->godRod  );
            P=P->next;
        }
        printf("\n");


    }
}

void UnosK(Position P)
{
    Position q;
    q = (Position)malloc(sizeof(struct _osoba));
    printf("\nUnesite podatke o novoj osobi: ");
    scanf("%s %s %d",q->ime,q->prezime,&q->godRod);
    
    while(P->next!=NULL)
    {
            P=P->next;
    }
    //q->ime = 
    q->next = P->next;
    P->next =q;
    //q->next=NULL;
   

}

Position TraziPoPrez(Position P)
{
    char temp_p[MAX_NAME];
    printf("\nUnesi prezime osobe koju zelis pronaci: ");
	scanf(" %s", temp_p);

    while(P != NULL && strcmpi(P->prezime, temp_p)!= 0) 
    P = P->next;
    //while(P!=NULL && P->prezime!=temp_p)
	//	P = P->next;

	return P;
}

int Brisi(Position P)
{
    char tempPrezime[MAX_NAME] = { 0 };
	Position temp = NULL;

	printf("Unesite prezime trazene osobe: ");
	scanf("%s", tempPrezime);

	while (P->next != NULL && strcmp(tempPrezime, P->next->prezime) != 0) {
		P = P->next;
	}
	if (strcmp(tempPrezime, P->next->prezime) == 0) {
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
	else {
		printf("Trazena osoba nije upisana u strukturu");
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

Position TraziPret(Position P)
{
    char temp_p[MAX_NAME] = {0};

     if(P->next == NULL)
        P==NULL;
    else{
        printf("Unesite prezime osobe koju zelite izbrisati/pronaci: ");  //dio starog koda kad san priko ove funkcije brisa
        scanf(" %s",temp_p);
    while(P->next->next!=NULL && strcmpi(P->next->prezime,temp_p)!=0)
        P=P->next; 
    }
        return P;
}

int UnosIza(Position P) 
{
	Position q;
	char trazenoPrezime[MAX_NAME] = { 0 };

	q = (Position)malloc(sizeof(struct _osoba));

	if (q == NULL) {
		printf("Pogreska prilikom alokacije!!!\n");
		return EXIT_ERROR;
	}

	printf("Unesite prezime osobe koju zelite pronaci: ");
	scanf("%s", trazenoPrezime);

	while (P != NULL && strcmp(trazenoPrezime, P->prezime) != 0) {
		P = P->next;
	}

	if (strcmp(trazenoPrezime, P->prezime) == 0) {
		//UnosP(q);                                         //zbog nove dek. memorije ne zeli ?
        printf("\nUnesite podatke o novoj osobi: ");
        scanf("%s %s %d",q->ime,q->prezime,&q->godRod);
		q->next = P->next;
		P->next = q;
	}
	else {
		printf("Nije pronadena trazena osoba!");
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

int UnosIspred(Position P) 
{
	Position q;
	char trazenoPrezime[MAX_NAME] = { 0 };

	q = (Position)malloc(sizeof(struct _osoba));

	if (q == NULL) {
		printf("Pogreska prilikom alokacije!!!\n");
		return EXIT_ERROR;
	}

	printf("Unesite prezime osobe koju zelite pronaci: ");
	scanf("%s", trazenoPrezime);

	while (P->next != NULL && strcmp(trazenoPrezime, P->next->prezime) != 0) {
		P = P->next;
	}

	if (strcmp(trazenoPrezime, P->next->prezime) == 0) {
		//UnosP(q);                                                 //zbog nove dek. memorije ne zeli ?
        printf("\nUnesite podatke o novoj osobi: ");
        scanf("%s %s %d",q->ime,q->prezime,&q->godRod);
		q->next = P->next;
		P->next = q;
	}
	else {
		printf("Nije pronadena trazena osoba!");
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

int Sort(Position P) //mjehuric sort - inace se ne koristi
{																
	Position q, prev_q, temp, end;
	
	q = (Position)malloc(sizeof(struct _osoba));

	if (q == NULL) {
		printf("Pogreska prilikom alokacije!!!\n");
		return EXIT_ERROR;
	}
	
	end = NULL;

	while (P->next != end) {
		prev_q = P;
		q = P->next;
		while (q->next != end) {
			if (strcmp(q->prezime, q->next->prezime) > 0) {
				temp = q->next;
				prev_q->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}
			prev_q = q;
			q = q->next;
		}
		end = q;
	}
	return EXIT_SUCCESS;
}

int BrisiSve(Position P) 
{
	Position temp;
	while (P->next != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int UnosDad(Position P, char imedad[MAXC]){
    FILE* pok_na_dad = NULL;
    pok_na_dad = fopen(imedad,"w");
    if(pok_na_dad==NULL){
       printf("Greska, dadoteka nije otvorena.");
       return EXIT_ERROR; }

    while(P != NULL){
    fprintf(imedad, "\nIme: %s \t Prezime: %s \t GodRod: %d \n", P->ime, P->prezime,P->godRod);
    P = P->next;
    }

    return EXIT_SUCCESS;
}

int CitaDad(Position P, imedad){
    FILE* pok_na_dad = NULL;
    pok_na_dad = fopen(imedad,"r");
    if(pok_na_dad == NULL){
        printf("Greska u otvaranju dadoteke");
        return EXIT_ERROR;
        }
    printf("Ispis liste:"); 
    while ( P!= NULL) { 
      printf(fscanf(imedad," %s \n", P->ime));
      printf(fscanf(imedad," %s \n", P->prezime));
      printf(fscanf(imedad," %d \n",&P->godRod));

      return EXIT_SUCCESS;
      
}
