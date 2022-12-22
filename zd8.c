#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

struct TreeNode;
typedef struct TreeNode *Node;

Node Delete(Node S, int x);
Node DeleteAll(Node S);
Node PronadiMin(Node S);
Node PronadiMax(Node S);
Node Insert(Node S, int x);
Node Pronadi(Node S, int x);
int InorderIspis(Node S);
int PreorderIspis(Node S);
int PostorderIspis(Node S);
int LevelorderIspis(Node S);
int Visina(Node S);
int TrenutnaRazina(Node S, int level);
int Print(Node S);

struct TreeNode
{
    int element;
    Node left;
    Node right;
};
int main(void)
{

    Node root = NULL, temp;
    int odabir = 1 , x;

    while (odabir)
    {
        system("cls");
        printf("\n\tOdaberi akciju:");
        printf("\n\t\t 1 - Unos elementa");
        printf("\n\t\t 2 - Trazenje elementa");
        printf("\n\t\t 3 - Brisanje elementa");
        printf("\n\t\t 4 - Inorder ispis");
        printf("\n\t\t 5 - Preorder ispis");
        printf("\n\t\t 6 - Postorder ispis");
        printf("\n\t\t 7 - Levelorder ispis");
        printf("\n\t\t 8 - Pregled stabla");
        printf("\n\t\t 0 - Izlazak iz programa\n\t");
        scanf(" %d", &odabir);

        switch (odabir)
        {
        case 1:
            printf("\n\tUnesi element: ");
            scanf(" %d", &x);
            root = Insert(root, x);
            break;
        case 2:
            printf("\n\tKoji element trazis? ");
            scanf(" %d", &x);
            temp = Pronadi(root, x);
            if (temp != NULL)
                printf("Element %d se nalazi na adresi %d", temp->element, temp);
            break;
        case 3:
            printf("\n\tKoji element zelis izbrisat? ");
            scanf(" %d", &x);
            root = Delete(root, x);
            break;
        case 4:
            InorderIspis(root);
            break;
        case 5:
            PreorderIspis(root);
            break;
        case 6:
            PostorderIspis(root);
            break;
        case 7:
            LevelorderIspis(root);
            break;
        case 8:
            Print(root);
            break;
        case 0:
            printf("\n\t\tIzlaz...\n");
            printf("\t\tCleaning memory....\n");
            root = DeleteAll(root);
            return EXIT_SUCCESS;
            break;
        default:
            printf("\n\tKrivi unos!!!");
        }
        printf("\nPause\nPress any key to continue!");
        getch();
    }
}
Node Pronadi(Node S, int x)
{
    if (S == NULL)
    {
        printf("\n\tElement ne postoji!!");
        return NULL;
    }
    else if (x < S->element)
        return Pronadi(S->left, x);
    else if (x > S->element)
        return Pronadi(S->right, x);
    return S;
}
Node PronadiMin(Node S)
{
    while (S->left != NULL)
        S = S->left;
    return S;
}
Node PronadiMax(Node S)
{
    while (S->right != NULL)
        S = S->right;
    return S;
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
    else if (x > S->element)
        S->right = Insert(S->right, x);
    else if (x < S->element)
        S->left = Insert(S->left, x);
    return S;
}
Node Delete(Node S, int x)
{
    Node temp;
    if (S == NULL)
        printf("Taj element ne postoji!!!\n");
    else if (x > S->element)
        S->right = Delete(S->right, x);
     else if (x < S->element)
        S->left = Delete(S->left, x);
    else
    {
        if (S->left)
        {
            temp = PronadiMax(S->left);
            S->element = temp->element;
            S->left = Delete(S->left, S->element);
        }
        else if(S->right)
        {
            temp = PronadiMin(S->right);
            S->element = temp->element;
            S->right = Delete(S->right, S->element);
        }
        else
        {
            free(temp);
            return NULL;
        }
    }
    return S;
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

int InorderIspis(Node S)
{
    if (S == NULL)
    {
        return EXIT_SUCCESS;
    }
    InorderIspis(S->left);
    printf("%d ", S->element);
    InorderIspis(S->right);
    printf("\n");
    return EXIT_SUCCESS;
}

int PreorderIspis(Node S)
{
    if (S == NULL)
    {
        return EXIT_SUCCESS;
    }
    printf("%d ", S->element);
    PreorderIspis(S->left);
    PreorderIspis(S->right);
    printf("\n");
    return EXIT_SUCCESS;
}

int PostorderIspis(Node S)
{
    if (S == NULL)
    {
        return EXIT_SUCCESS;
    }
    PostorderIspis(S->left);
    PostorderIspis(S->right);
    printf("%d ", S->element);
    printf("\n");
    return EXIT_SUCCESS;
}
int LevelorderIspis(Node S)
{
    int h = Visina(S);
    int i = 0;
    for (i = h; i > 0; i--)
        TrenutnaRazina(S, i);
}

int Visina(Node S)
{
    if (S == NULL)
        return EXIT_SUCCESS;
    else
    {
        int lvisina = Visina(S->left);
        int rvisina = Visina(S->right);

        if (lvisina > rvisina)
            return (lvisina + 1);
        else
            return (rvisina + 1);
    }
}

int TrenutnaRazina(Node S, int level)
{
    if (S == NULL)
        return EXIT_SUCCESS;
    if (level == 1)
        printf("%d ", S->element);
    else if (level > 1)
    {
        TrenutnaRazina(S->left, level - 1);
        TrenutnaRazina(S->right, level - 1);
    }
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
