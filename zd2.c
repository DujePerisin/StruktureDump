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
void Brisi(Position P);

void UnosIza(Position P);

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

    while(odabir != 0 )
    {
        printf("Unesite ispravan broj za odabir opcije: \n\n");
        printf("1 - Dodavanje novog elementa na pocetak liste\n");
        printf("2 - Ispis liste\n");
        printf("3 - Dodavanje novog elementa na kraj liste\n");
        printf("4 - Pronalazak elementa u listi (po prezimenu)\n");
        printf("5 - Brisanje odredenog elementa iz liste\n");
        printf("\n0 - Izlazak iz programa\n \n");

        scanf("%d",&odabir);

        switch(odabir)
        {
            case 1: 
                UnosP(&head);
                break;
            case 2:
                Ispis(head.next);
                break;
            case 3:
                UnosK(&head);
                break;
            case 4:
                q=TraziPoPrez(head.next);
                if(q==NULL)
                    printf("\n Osoba ne postoji u listi!");
			    else
				    printf("\nOsoba je: %s %s, %d\n", q->ime, q->prezime,q->godRod);
                break;
            case 5: 
                Brisi(&head);
                break;
        } 

        
    }

    /*UnosP(&head);
    UnosP(&head);
    UnosP(&head);
    //Ispis(head.next);
    UnosK(head.next);
    Ispis(head.next);*/


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

void Brisi(Position P)
{
    Position prev,temp;

    prev = TraziPret(P);

    if(NULL==prev)
    {
        printf("Nema ga\n");
        //return EXIT_ERROR;
    }
    else{
        temp=prev->next;
        temp=prev->next;
        temp=temp->next;
        free(temp);
        //return EXIT_SUCCESS;
    }
}

Position TraziPret(Position P)
{
    char temp_p[MAX_NAME];

     if(P->next == NULL)
        P==NULL;
    else{
        printf("Unesite prezime osobe koju zelite izbrisati: ");
        scanf(" %s",temp_p);
    while(P->next->next!=NULL && strcmpi(P->next->prezime,temp_p)!=0)
        P=P->next; 
    }
        return P;
}

void UnosIza(Position P)
{
    Position q;

    printf("");

}


