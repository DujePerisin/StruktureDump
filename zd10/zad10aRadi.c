#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

#define MAX (1024)
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

struct _tree;
typedef struct _tree *position_tree;
typedef struct _tree
{

    char cityName[MAX];
    int population;
    position_tree left;
    position_tree right;
} tree;

struct _linkedList;
typedef struct _linkedList *position_list;
typedef struct _linkedList
{

    char stateName[MAX];
    position_tree nextTree;
    position_list next;
} linkedList;

position_tree createTreeRoot();
position_list createHeadList();
int printList(linkedList states);
int insertIntoList(position_list newElement, position_list head);
position_list createListElement(char stateName[]);
int readFromFile(char fileName[], linkedList states);
int readFromAdditionalFile(position_list head, char additionalFile[]);
int printInorder(position_tree root);
position_tree creteTreeElement(char cityName[], int peopleNumb);
position_tree insertIntoTree(position_tree root, char cityName[], int population);
position_tree findCityByName(position_tree current, char cityName[]);
int Menu(linkedList states);
position_list findStateByName(linkedList states, char stateName[]);

int main()
{

    linkedList states = {.stateName = {"\0"}, .next = NULL, .nextTree = NULL};

    states.next = createHeadList();
    states.nextTree = createTreeRoot();

    readFromFile("stateFile.txt", states);

    printf("\nLista drzava:");
    printList(states);

    printf("Ovo je states.next %p", states.next);
    Menu(states);

    return EXIT_SUCCESS;
}

position_tree createTreeRoot()
{

    position_tree root = NULL;

    root = (position_tree)malloc(sizeof(tree));

    if (!root)
    {

        printf("Memorija za root ne moze biti alocirana!\n");
        return NULL;
    }

    strcpy(root->cityName, "");
    root->left = NULL;
    root->right = NULL;
    root->population = 0;

    return root;
}

int insertIntoList(position_list newElement, position_list head)
{

    if (head->next == NULL)
    {

        head->next = newElement;
        newElement->next = NULL;
    }

    else
    {

        while (head->next != NULL && (strcmp(head->next->stateName, newElement->stateName) < 0))
            head = head->next;

        newElement->next = head->next;
        head->next = newElement;
    }

    return EXIT_SUCCESS;
}

position_list createListElement(char stateName[])
{

    position_list newElement = NULL;

    newElement = (position_list)malloc(sizeof(linkedList));

    if (!newElement)
    {

        printf("Memorija za novi element vezane liste ne moze biti alocirana!\n");
        return NULL;
    }

    strcpy(newElement->stateName, stateName);
    newElement->next = NULL;
    newElement->nextTree = createTreeRoot();

    return newElement;
}

int readFromFile(char fileName[], linkedList states)
{

    FILE *fp = NULL;
    char *buffer = NULL;
    char stateName[MAX] = {0};
    char additionalFile[MAX] = {0};
    int byteNumb = 0;
    position_list newElement = NULL;
    position_list current = states.next;

    newElement = (position_list)malloc(sizeof(linkedList));

    if (!newElement)
    {

        printf("NIje moguce alocirati memoriju za novi element vezane liste!\n");
        return EXIT_ERROR;
    }

    buffer = (char *)malloc(MAX * sizeof(char));

    if (!buffer)
    {

        printf("Memorija za buffer se ne moze alocirati!\n");
        return EXIT_ERROR;
    }

    fp = fopen(fileName, "r");

    if (!fp)
    {

        printf("File se ne moze otvoriti!\n");
        return EXIT_ERROR;
    }

    while (!feof(fp))
    {

        fgets(buffer, MAX, fp);

        if (sscanf(buffer, "%s %s %n", stateName, additionalFile, &byteNumb) == 2)
        {

            newElement = createListElement(stateName);

            insertIntoList(newElement, states.next);

            printf("\nDrzava: %s gradovi:", newElement->stateName);

            readFromAdditionalFile(newElement, additionalFile);

            buffer += byteNumb;
        }

        else
        {

            printf("Nesto nije uredu sa formatom vaseg filea!\nMolim, prmjenite format!\n");
            printf("Format: [ime drzave] [razmak] [Gradovi_[ime drzave].txt]\n");
            return EXIT_ERROR;
        }
    }

    fclose(fp);

    return 0;
}

int readFromAdditionalFile(position_list head, char additionalFile[])
{

    FILE *fp = NULL;
    char cityName[MAX] = {0};
    int population = 0;
    char *buffer = NULL;
    int byteNumb = 0;
    position_tree newElement = NULL;
    position_tree root = head->nextTree;

    buffer = (char *)malloc(MAX * sizeof(char));

    if (!buffer)
    {

        printf("Memorija za buffer se ne moze alocirati!\n");
        return EXIT_ERROR;
    }

    fp = fopen(additionalFile, "r");

    if (!fp)
    {

        printf("Fileu %s ne moze se pristupiti!\n", additionalFile);
        return EXIT_ERROR;
    }

    while (!feof(fp))
    {

        fgets(buffer, MAX, fp);

        if (sscanf(buffer, "%s %d %n", cityName, &population, &byteNumb) == 2)
        {

            newElement = createTreeRoot();

            newElement = insertIntoTree(root, cityName, population);

            buffer += byteNumb;
        }

        else
        {

            printf("Nesto nije uredu sa formatom vaseg filea!\nMolim, prmjenite format!\n");
            printf("Format: [ime grada] [razmak] [broj stanovnika]\n");
            return EXIT_ERROR;
        }
    }

    printInorder(newElement);
    puts("");

    fclose(fp);

    return EXIT_SUCCESS;
}

int printInorder(position_tree root)
{

    if (root == NULL)
        return 0;

    printInorder(root->left);

    if (root->population != 0)
        printf("\n\tGrad: %s    Populacija: %d", root->cityName, root->population);

    printInorder(root->right);

    return EXIT_SUCCESS;
}

position_tree creteTreeElement(char cityName[], int peopleNumb)
{

    position_tree newElement = NULL;

    newElement = (position_tree)malloc(sizeof(tree));

    if (!newElement)
    {

        printf("Memorija za novi element stabla ne moze se alocirati!\n");
        return NULL;
    }

    strcpy(newElement->cityName, cityName);
    newElement->population = peopleNumb;
    newElement->left = NULL;
    newElement->right = NULL;

    return newElement;
}

position_list findStateByName(linkedList states, char stateName[])
{

    position_list current = NULL;

    current = (position_list)malloc(sizeof(linkedList));

    if (!current)
    {

        printf("Memorija za current [pretrazivanje] nije alocirana!\n");
        return NULL;
    }

    current = states.next;
    //printf("Ovo je states.next %p", states.next);
    //printf("Ovo je current->next %s", current->next);
    if(!(strcmp(stateName, current->next))){
        return current->next;

    while (current->next != NULL && (strcmp(current->stateName, stateName))){
        current = current->next;
       // printf("Ovo je current %s", current);
        //printf("Ovo je current->next %s", current->next);

    if (!(strcmp(stateName, current->next->stateName)))
    {

        //printf("Ovo je stateName %s", stateName);
        //printf("Ovo je current->next->stateName %s", current->next->stateName);
        return current->next;
    } 
    }
   // printf("Ovo je states.next %p", states.next);
    //printf("Ovo je current->next", current->next);
    current = current->next;
    //printf("Ovo je current->next", current->next);
    return NULL;
}

position_tree findCityByName(position_tree current, char cityName[])
{

    int i = 0;

    for (i = 0; i < 1; i++)
    {

        if (current == NULL)
            return NULL;

        else if (strcmp(current->cityName, cityName) > 0)
            return findCityByName(current->left, cityName);

        else if (strcmp(current->cityName, cityName) < 0)
            return findCityByName(current->right, cityName);

        else
            return current;
    }

    return current;
}

int Menu(linkedList states)
{

    int key = 111;
    char stateName[MAX] = {0};
    char cityName[MAX] = {0};
    position_list currentList = NULL;
    position_tree currentTree = NULL;
    position_tree temp = NULL;

    currentList = (position_list)malloc(sizeof(linkedList));

    if (!currentList)
    {

        printf("Memorija za listu [pretrazivanje] ne moze biti alocirana!\n");
        return EXIT_ERROR;
    }

    currentTree = (position_tree)malloc(sizeof(tree));

    if (!currentTree)
    {

        printf("Memorija za stablo [pretrazivanje] ne moze biti alocirana!\n");
        return EXIT_ERROR;
    }
    printf("\n");
    temp = (position_tree)malloc(sizeof(tree));
        while (key)
        {
            key = 0;
            //system("cls");
            printf("\n\tOdaberite:");
            printf("\n\t\t 1 - Pretraga drzave");
            printf("\n\t\t 0 - Izlaz\n\t ");
            scanf("%d", &key);

            switch (key)
            {
            case 1:
                 printf("\n\nUnesite ime drzave: ");
            scanf(" %s", stateName);

            currentList = findStateByName(states, stateName);
            //printf("Ovo je currentList %s", currentList);
            if (!currentList)
                printf("\n\tTa drzava ne postoji!\n");

            else
            {
                printf("\n\tDrzava: %s je pronadjena!", currentList->stateName);
                printf("\n\tGradovi drzave su:\n");
                printInorder(currentList->nextTree);

                printf("\n\n\tUnesite ime grada: ");
                scanf(" %s", cityName);

                temp = currentList->nextTree;

                currentTree = findCityByName(temp, cityName);

                if (!currentTree)
                    printf("\n\tGrada nema!\n");

                else
                    printf("\n\tGrad: %s    Populacija: %d", currentTree->cityName, currentTree->population);
            }
                break;
            case 0:
                    printf("\n\t\tIzlaz....");
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

position_tree insertIntoTree(position_tree root, char cityName[], int population)
{

    if (root == NULL)
    {

        root = (position_tree)malloc(sizeof(tree));
        strcpy(root->cityName, cityName);
        root->population = population;
        root->left = NULL;
        root->right = NULL;
    }

    if (root->population > population)
        root->left = insertIntoTree(root->left, cityName, population);

    else if (root->population < population)
        root->right = insertIntoTree(root->right, cityName, population);

    return root;
}

position_list createHeadList()
{

    position_list head = NULL;

    head = (position_list)malloc(sizeof(linkedList));

    if (!head)
    {

        printf("Memorija za head element vezane liste se ne moze alocirati!\n");
        return NULL;
    }

    strcpy(head->stateName, "");
    head->next = NULL;
    head->nextTree = NULL;
    head->next = NULL;

    return head;
}

int printList(linkedList states)
{

    position_list current = states.next;

    while (current->next != NULL)
    {

        current = current->next;
        printf("\n\t%s", current->stateName);
    }
    return EXIT_SUCCESS;
}

//neke drzave zeli pronaci npr. Njemacku ne zeli ali Austriju zeli
//kada otvori drzavu tada sve gradove uspjesno pronalazi


//update prva 2 zeli ostale ne zeli
//findStatebyName funkcija zaj***je
