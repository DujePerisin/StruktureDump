#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

struct _polinom;
typedef struct _polinom * Position;
struct _polinom {
    int koeficijent;
    int eksponent;
    Position next;
}Polinom;

int ReadPolinom(Position P,char *ime_dat);
int IspisPolinoma(Position P);
int SumaPolinoma(Position P1,Position P2,Position S);
int UmnozakPolinoma(Position P1,Position P2,Position S);


int main (void)
{
    struct _polinom P1,P2,S,P;

    P1.next = NULL;
	P2.next = NULL;
	S.next = NULL;
	P.next = NULL;
    
    ReadPolinom(&P1,"list1.txt");
    IspisPolinoma(&P1);

    ReadPolinom(&P2,"list2.txt");
    IspisPolinoma(&P2);

    printf("\n///\t///////\t//////\t/////\n");

    SumaPolinoma(P1.next,P2.next,&S);
    printf("\nSuma polinoma => \n");
    IspisPolinoma(&S);

    UmnozakPolinoma(P1.next,P2.next,&P);
    printf("\nUmnozak polinoma => \n");
    IspisPolinoma(&P);




    return EXIT_SUCCESS;
}

int ReadPolinom(Position P,char *ime_dat)
{
    FILE *dat;
    Position q,temp,prev;

    dat = fopen(ime_dat,"r");

    if(dat == NULL)
    {
        printf("\nGreska!! Datoteka ne moze biti otvorena!!\n");
        return EXIT_ERROR;
    }
    else
    {
        while(feof(dat)==0)
        {
            q = (Position)malloc(sizeof(struct _polinom));
            fscanf(dat," %d %d", &q->koeficijent, &q->eksponent);

            temp = P->next;
            prev = P;
            while(temp!=NULL && temp->eksponent > q->eksponent)
            {
                prev = temp;
                temp = temp->next;
            }

            prev->next = q;

            if(temp!=NULL)
                q->next = temp;
            else
                q->next = NULL;
        }
    }
    return EXIT_SUCCESS;
}

int IspisPolinoma(Position P)
{
    P=P->next;
    printf("\n");
    while(P!=NULL)
    {
        if(P->koeficijent > 0)
            printf("\t+%d*x^%d",P->koeficijent,P->eksponent);
        else
            printf("\t%d*x%d",P->koeficijent,P->eksponent);
        

        P=P->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int SumaPolinoma(Position P1,Position P2,Position S)
{
    Position q,temp;

    while(P1!=NULL && P2!=NULL)
    {
        q = (Position)malloc(sizeof(struct _polinom));
        q->next = NULL;
        
        if(P1->eksponent > P2->eksponent)
        {
            q->eksponent = P1->eksponent;
            q->koeficijent = P1->koeficijent;
            P1 = P1->next;
        }
        else if(P1->eksponent < P2->eksponent)
        {
            q->eksponent = P2->eksponent;
            q->koeficijent = P2->koeficijent;
            P2 = P2->next;
        }
        else            //za slucaj kad su jednaki
        {
            q->eksponent = P1->eksponent;
            q->koeficijent = P1->koeficijent + P2->koeficijent;
            P1 = P1->next;
            P2 = P2->next;
        }
        S->next = q;
        S = q;
    }
    if(P1!=NULL)
    {
        temp = P1;
    }
    else
    {
        temp = P2;
    }

    while(temp!=NULL)
    {
        q = (Position)malloc(sizeof(struct _polinom));
        q->next = NULL;
        q->eksponent = temp->koeficijent;
        S->next = q;
        S = q;
        temp = temp->next;
    }
    free(temp);                     //oslobodi memoriju kad god mozes a ne koristis je
    return EXIT_SUCCESS;
}


int UmnozakPolinoma(Position P1,Position P2,Position P)
{
    Position q,temp,prev;
    int n;

    while(P1!=NULL)
    {
        while(P2!=NULL)
        {
            temp = P->next;
            prev = P;

            n = P1->eksponent + P2->eksponent;

            while(temp!= NULL && temp->eksponent > n)
            {
                prev = temp;
                temp = temp ->next;
            }
        
        if(temp!=NULL && temp->eksponent == n)
            temp->koeficijent += P1->koeficijent * P2->koeficijent;
        else
        {
            q = (Position)malloc(sizeof(struct _polinom));

            q->eksponent = n;
            q->koeficijent = P1->koeficijent * P2->koeficijent;
            prev->next = q;
            q->next = temp;
        }

        P2 = P2->next;

        }

    P1 = P1->next;

    }

    while(P->next != NULL)
    {
        if(P->next->koeficijent == 0)
        {
            temp = P->next;
            P->next = P->next->next;
            free(temp);                             //oslobodi memoriju kad god mozes a ne koristis je
        }
        P = P->next;
    }
    return EXIT_SUCCESS;
}

