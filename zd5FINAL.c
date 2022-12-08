#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAX 64
#define MAXL 1024
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

struct _Stog;
typedef struct _Stog* Position;
typedef struct _Stog {
	float element;
	Position next;
}stog;

int Push(Position head, float broj);
float Pop(Position head);
int IzracunOperacije(Position head, char operator);
int CitanjeFile(Position head);


int Push(Position head, float broj)
{
	Position novi_element = NULL;

	novi_element = (Position)malloc(sizeof(stog));
	if (!novi_element)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_ERROR;
	}
	novi_element->next = head->next;
	head->next = novi_element;
	novi_element->element = broj;

	return EXIT_SUCCESS;
}

float Pop(Position head)
{
	float broj = 0.0;
	Position prvi = NULL;

	prvi = head->next;

	broj = prvi->element;
	head->next = prvi->next;

	free(prvi);                                 

	return broj;
}

int IzracunOperacije(Position head, char operator)
{
	float broj1 = 0.0;
	float broj2 = 0.0;

	switch (operator)
	{
	case '+':
		broj1 = Pop(head);
		broj2 = Pop(head);
		Push(head, broj1 + broj2);
		break;

	case '-':
		broj1 = Pop(head);
		broj2 = Pop(head);
		Push(head, broj2 - broj1);
		break;

	case '*':
		broj1 = Pop(head);
		broj2 = Pop(head);
		Push(head, broj2 * broj1);
		break;

	case '/':
		broj1 = Pop(head);
		broj2 = Pop(head);
		if (broj1 == 0)
			printf("Dijeljenje sa 0 nije moguce obaviti!!!!\n\n");
		else
			Push(head, broj2 / broj1);
		break;
	}
	return EXIT_SUCCESS;
}

int CitanjeFile(Position head)
{

	char imedat[MAX] = { 0 };
	char temp01[MAXL] = { 0 };
	char* temp1 = NULL;
	float broj = 0;
	int status = 0;
	int brojac = 0;
	char operator = 0;

	printf("Unesite ime datoteke: ");
	scanf(" %s", imedat);

	FILE* fp = NULL;

	fp = fopen(imedat, "r");
	if (!fp)
	{
		printf("\nDatoteka nije pronadena!!\n");
		return EXIT_ERROR;
	}

	fgets(temp01, MAXL, fp);

	temp1 = temp01;

	while (strlen(temp1) > 0)
	{
		status = sscanf(temp1, " %f %n", &broj, &brojac);

		if (status == 1)
		{
			Push(head, broj);
			temp1 += brojac;
		}
		else
		{
			sscanf(temp1, " %c %n", &operator, &brojac);
			IzracunOperacije(head, operator);
			temp1 += brojac;
		}
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

int main() {

	stog head = { .element = 0, .next = NULL };

	Position first = &head;

	CitanjeFile(&head);

	printf("Rezultat matematickih operacija je %f\n", first->next->element);

	return 0;
}
