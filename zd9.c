#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR -1
#define MIN 10
#define MAX 90

struct TreeNode;
typedef struct TreeNode *Node;
struct temp;
typedef struct temp *Position;

Position CreateListElement(int X);
Position DeleteAll_(Position S);
Node DeleteAll(Node S);
Node Insert(Node S, int x);
Node AddElementIntoTree(Node S, int X);
int Replace(Node S, Position P);
int InorderIspis(Node S);
int Print(Node S);
int Suma(Node S);
int InsertIntoList(Position P, Position S);
int RandomNumGen(int X, Position P, Node S);
int FileHandling(Position P, Position P1);

typedef struct temp
{
    int element;
    Position Next;
} _temp;

struct TreeNode
{
    int element;
    Node left;
    Node right;
} _TreeNode;

int main()
{
    int i, n, odabir = 1, niz[10] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    Node root = NULL;
    _temp lista = {.element = 0, .Next = NULL};
    _temp lista1 = {.element = 0, .Next = NULL};
    Position NewEl1 = NULL;
    Position NewEl2 = NULL;
    while (odabir)
    {
        system("cls");
        printf("\n\tOdaberi nacin rada:");
        printf("\n\t\t 1 - Predefinirani niz");
        printf("\n\t\t 2 - Nasumicni niz ");
        printf("\n\t\t 0 - Izlaz\n\t ");
        scanf("%d", &odabir);

        switch (odabir)
        {
        case 1:
            for (i = 0; i < 10; i++)
                root = Insert(root, niz[i]);
            printf("\nStablo prije izmjene: \n\n");
            Print(root);
            for (i = 0; i < 10; i++)
            {
                NewEl1 = CreateListElement(niz[i]);
                InsertIntoList(&lista, NewEl1);
            }
            Replace(root, &lista1);
            printf("\n\nStablo nakon izmjene: \n\n");
            Print(root);
            for (i = 0; i < 10; i++)
            {
                NewEl2 = CreateListElement(niz[i]);
                InsertIntoList(&lista1, NewEl2);
            }
            FileHandling(&lista, &lista1);
            break;
        case 2:
            printf("\nUnesite koliko nasumicnih brojeva zelite: ");
            scanf("%d", &n);
            RandomNumGen(n, &lista, root);

            printf("\nStablo prije izmjene: \n\n");
            Print(root);
            Replace(root, &lista1);
            printf("\n\nStablo nakon izmjene: \n\n");
            Print(root);
            
            FileHandling(&lista, &lista1);
            break;
        case 0:
            if (remove("dat.txt") == 0)
            {
                printf("\n\t\tIzlaz....");
                printf("\n\t\tCiscenje memorije....\n");
                root = DeleteAll(root);
                DeleteAll_(NewEl1);
                DeleteAll_(NewEl2);
                printf("\n\t\tText file je uspjesno izbrisan!!");
            }
            else
                printf("\n\t\tText file nije uspjesno izbrisan!!\n\t\t\tNije ni postojao!!");
            return EXIT_SUCCESS;
            // break;
        default:
            printf("\n\tPogresan unos!!!");
        }
        printf("\nPause\nPress any key to continue\n");
        getch();
    }
    return EXIT_SUCCESS;
}

Node Insert(Node S, int x)
{
    if (S == NULL)
    {
        S = (Node)malloc(sizeof(struct TreeNode));
        S->left = NULL;
        S->right = NULL;
        S->element = x;
    }
    else if (x < S->element)
        S->right = AddElementIntoTree(S->right, x);
    else if (x >= S->element)
        S->left = AddElementIntoTree(S->left, x);
    return S;
}

int InsertIntoList(Position P, Position S)
{
    if (P->Next == NULL)
    {
        P->Next = S;
        S->Next = NULL;
    }
    else
    {
        while (P->Next != NULL && (P->Next->element <= S->element))
            P = P->Next;
        S->Next = P->Next;
        P->Next = S;
    }
    return EXIT_SUCCESS;
}

Node AddElementIntoTree(Node S, int x)
{
    if (S == NULL)
    {
        S = (Node)malloc(sizeof(_TreeNode));
        S->element = x;
        S->left = NULL;
        S->right = NULL;
    }
    else if (S->element >= x)
        S->left = AddElementIntoTree(S->left, x);
    else
        S->right = AddElementIntoTree(S->right, x);
    return S;
}
int InorderIspis(Node S)
{
    if (S == NULL)
        return EXIT_SUCCESS;
        
    InorderIspis(S->left);
    printf("%d ", S->element);
    InorderIspis(S->right);
    printf("\n");
    return EXIT_SUCCESS;
}

int Print(Node S)
{
    static int n = 0;
    int i;
    if (n == -1)
        n = 0;
    if (NULL != S)
    {
        n++;
        Print(S->right);
        printf("\n");
        for (i = 0; i < n; i++)
            printf("\t");
        printf(" %d", S->element);
        printf("\n");
        n++;
        Print(S->left);
    }
    n--;
    return EXIT_SUCCESS;
}

Node DeleteAll(Node S)
{
    if (S != NULL)
    {
        DeleteAll(S->left);
        DeleteAll(S->right);
        free(S);
    }
    return NULL;
}

Position DeleteAll_(Position S)
{
    if (S != NULL)
    {
        DeleteAll_(S->Next);
        free(S);
    }
    return NULL;
}

int Replace(Node S, Position P)
{
    Position newEl = NULL;
    newEl = (Position)malloc(sizeof(_temp));

    if (!S)
        return 0;

    S->element = Suma(S->right) + Suma(S->left);
    newEl = CreateListElement(S->element);
    InsertIntoList(P, newEl);

    Replace(S->left, P);
    Replace(S->right, P);
    return EXIT_SUCCESS;
}

int Suma(Node S)
{
    if (S == NULL)
        return 0;
    else
        return (S->element + Suma(S->left) + Suma(S->right));
}

Position CreateListElement(int x)
{
    Position tm = NULL;
    tm = (Position)malloc(sizeof(_temp));
    if (tm == NULL)
    {
        printf("Memorija nije alocirana\n");
        return NULL;
    }
    tm->element = x;
    tm->Next = NULL;
    return tm;
}

int FileHandling(Position P, Position P1)
{
    FILE *fp = NULL;

    fp = fopen("dat.txt", "w");

    if (!fp) {
        printf("File nije moguce otvoriti!\n");
        return EXIT_ERROR;
    }

    fprintf(fp, "\nPrije izmjene: \n");
    do
    {
        if (P->element != 0)
            fprintf(fp, "%d ", P->element);
        P = P->Next;
    } while (P->Next != NULL);
    fprintf(fp, "%d ", P->element);


    fprintf(fp, "\nNakon izmjene: \n");
    do
    {
        if (P1->element != 0)
            fprintf(fp, "%d ", P1->element);
        P1 = P1->Next;
    } while (P1->Next != NULL);
    fprintf(fp, "%d ", P1->element);

    fclose(fp);
    return EXIT_SUCCESS;
}

int RandomNumGen(int X, Position P, Node S)
{
    int *Pomocni = NULL;
    int Pomocni_[100];
    int cnt = 0;
    Position newEl = NULL;
    Node newEl1 = NULL;
    int i = 0;

    newEl = (Position)malloc(sizeof(_temp));
    newEl1 = (Node)malloc(sizeof(_TreeNode));

    if (!newEl)
    {
        printf("Mem not allocated!\n");
        return EXIT_ERROR;
    }

    // Pomocni = (int *)malloc(X * sizeof(int));

    printf("%d random brojeva:\n", X);

    for (i = 0; i < X; i++)
    {

        Pomocni_[i] = MIN + (rand() % (MAX - MIN + 1));
        printf("%d \n", Pomocni_[i]);
    }
    // nakon ovog
    for (i = 0; i < X; i++)
    {
        // printf("%d ", Pomocni_[i]);
        newEl = CreateListElement(Pomocni_[i]);
        InsertIntoList(P, newEl);
        // printf("%d ",newEl->element); works
    }
    /*
    //printf("USO SAM");
    for (i = 0; i < X; i++)
    {
        //printf("%d ", Pomocni[i]); works
        newEl1 = AddElementIntoTree(S, Pomocni[i]);
    }*/
    for (i = 0; i < X; i++)
    {
        // printf("-%d ", Pomocni_[i]);
        S = Insert(S, Pomocni_[i]);
    }

    return EXIT_SUCCESS;
}



/*int Replace(Node S)
{
    //Node newEl = NULL;
    //newEl = (Node)malloc(sizeof(TreeNode));


    if(S == NULL)
        return 0;
    S->element = Suma(S->left) + Suma(S->right);
    Insert(S,S->element);
    //puca
    Replace(S->left);
    printf("USO SAM"); //ne puca
    Replace(S->right);

    return 0;
}*/
