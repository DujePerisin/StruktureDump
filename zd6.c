#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

struct direktorij;
typedef struct direktorij dir;
typedef struct direktorij *Node;

struct Stog_Sim;
typedef struct Stog_Sim *Stog;

struct direktorij
{
	char ime[10];
	Node next;
	Node child;
};

struct Stog_Sim
{
	Node element;
	Stog next;
};

int Ispis_Dir(Node, char *);
Node Izadi_Dir(Node, char *, Stog);
Node Udi_Dir(Node, char *, char *, Stog);
int Stvori_Dir(Node, char *);
int Push(Stog, Node);
Node Pop(Stog);


int main(void)
{ 
	char instrukcija[20], ime[10], naredba[10], path[100];
	char *i, *j;
	dir root;
	struct Stog_Sim S;

	Node UpDir = &root;
	S.next = NULL;

	printf("Unesi ime root direktorija: ");
	scanf("%s", root.ime);
	root.child = NULL;
	root.next = NULL;
	//printf("%s",path);
	path[0] = 0;				
	strcat(path, root.ime);
	strcat(path, ":\\");
	
	printf("Unesite neku naredbu:");
	printf("\n\tdir");
	printf("\n\tcd..");
	printf("\n\tcd ime_dir");
	printf("\n\tmk ime_dir");
	printf("\n\n\texit - za kraj");
	printf("\n\n\t");

	fgets(instrukcija, 20,stdin);
	
	while(strcmp(naredba, "exit")!=0)
	{
		printf("\n\n\t%s",path);
		
		strset(ime, 0);
		strset(naredba, 0);

		fgets(instrukcija, 20,stdin);

		i = strchr(instrukcija, ' ');	//pamti koji smo direktorij zadnji zadnji napravili/usli u njega
		//printf("%s",i);
		if (i == NULL)
		{
			strncpy(naredba, instrukcija, sizeof(instrukcija));
			j = strchr(naredba, 10);
			*j = 0;
		}
		else
		{
			strncpy(naredba, instrukcija, i - instrukcija);
			naredba[i-instrukcija] = 0;
			strcpy(ime, i+1);
			//printf("%s",i);
		}

		if(strcmp(naredba, "dir")==0)
			Ispis_Dir(UpDir, path);
		else if(strcmp(naredba, "cd..")==0)
			UpDir = Izadi_Dir(UpDir, path, &S);
		else if(strcmp(naredba, "cd")==0)
			if(ime[0] == 0)
				printf("Pogresan upis naredbe!\n Trebao bi bit: cd ime_dir");
			else
				UpDir = Udi_Dir(UpDir, ime, path, &S);
		else if(strcmp(naredba, "mk")==0)
			if(ime[0] == 0)
				printf("Pogresan upis naredbe!\n Trebao bi bit: mk ime_dir");
			else
				Stvori_Dir(UpDir, ime);
		else if(strcmp(naredba, "exit")!=0)
			printf("\nNe postoji ta mogucnost!!\nUnesi neku od gore navednih opcija!!\n");

	}
	return EXIT_SUCCESS;
}


int Ispis_Dir(Node N, char * path)
{
	int i = 0;
	printf("\nDirektorij od %s", path);
	
	N = N->child;
	while(N != NULL)
	{
		printf("\n\t\t %s", N->ime);
		N = N->next;
		i++;
	}
	printf("\n\t\t %d Dir(s)", i);
	return EXIT_SUCCESS;
}


Node Izadi_Dir(Node N, char *path, Stog S)
{
	Node temp;
	char *a;

	temp = Pop(S);
	if(NULL == temp)
	{
		printf("Nalazimo se u root-u (pocetni direktorij)!!");
		return N;
	}
	else
	{
		a = strrchr(path, '\\');
		*a = 0;

		a = strrchr(path, '\\');
		*(a+1) = 0;
	
		return temp;
	}
}


Node Udi_Dir(Node N, char *ime, char *path, Stog S)
{
	Node temp = N->child;
	char *a;

	while(temp != NULL && strcmp(temp->ime, ime)!= 0)
		temp = temp->next;
	if (NULL == temp)
		printf("\nNe postoji taj pod-direktorij!!!");
	else
	{
		Push(S, N);
		strcat(path, temp->ime);
		a = strchr(path, 10);
		*a = '\\';
		return temp;
	}
	return N;
}


int Stvori_Dir(Node N, char *ime)
{
	Node q;
	q = (Node)malloc(sizeof(dir));
	q->child = NULL;
	q->next = NULL;

	strcpy(q->ime, ime);

	if(NULL == q)
	{
		printf("\nNeuspjesna alokacija memorije!");
		return EXIT_ERROR;
	}
	else
	{
		if ( NULL == N->child)
			N->child = q;
		else
		{
			q->next = N->child;
			N->child = q;
		}
		return EXIT_SUCCESS;
	}
}

int Push(Stog head, Node T)
{
	Stog novi_element;
	novi_element = (Stog)malloc(sizeof(struct Stog_Sim));

	if( novi_element==NULL)
	{
		printf("\nNeuspjesna alokacija memorije!\n");
		return EXIT_ERROR;
	}
	else
	{
		novi_element->element = T;
		novi_element->next = head->next;
		head->next = novi_element;
		return EXIT_SUCCESS;
	}
}


Node Pop(Stog head)
{
	Node q;
	Stog prvi;

	if(NULL == head->next)
		return NULL;
	else
	{
		q = head->next->element;
		prvi = head->next;
		head->next = prvi->next;

		free(prvi);
		return q;
	}
}
