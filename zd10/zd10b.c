#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

#define MAX (1024)
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

struct _linkedList;
typedef struct _linkedList* position_list;
typedef struct _linkedList {

    char cityName[MAX];
    int population;
    position_list next;
}linkedList;

struct _tree;
typedef struct _tree* position_tree;
typedef struct _tree {

    char stateName[MAX];
    position_tree left;
    position_tree right;
    position_list nextList;
}tree;

position_tree createTreeRoot();
position_list createHeadList();
int insertIntoList(position_list newElement, position_list head);
position_list createListElement(char cityName[], int population);
int printInorder(position_tree root);
position_tree creteTreeElement(char stateName[]);
position_tree insertIntoTree(position_tree root, position_tree newElement);
position_tree readFromFile(char fileName[]);
int readFromAdditionalFile(position_tree root, char additionalFile[]);
int printList(position_list head);
position_tree findStateByName(position_tree current, char stateName[]);
position_list findCityByName(position_list current, char cityName[]);
int Menu(position_tree states);

int main() {

   
    position_tree current = createTreeRoot();
    current = readFromFile("stateFile.txt");

    printf("\nLista drzava: ");
    printInorder(current);

    Menu(current);

    return EXIT_SUCCESS;
}

position_tree createTreeRoot() {

    position_tree root = NULL;

    root = (position_tree)malloc(sizeof(tree));

    if(!root) {

        printf("Memorija za root ne moze biti alocirana!\n");
        return NULL;
    }

    strcpy(root->stateName, "");
    root->left = NULL;
    root->right = NULL;
    root->nextList = createHeadList();

    return	root;
}   

position_list createHeadList() {

    position_list head = NULL;

    head = (position_list)malloc(sizeof(linkedList));

    if(!head) {

        printf("Memorija za head element vezane liste se ne moze alocirati!\n");
        return NULL;
    }

    strcpy(head->cityName, "");
    head->population = 0;
    head->next = NULL;

    return head;
}

int insertIntoList(position_list newElement, position_list head) {

    if(head->next == NULL) {

        newElement->next = head->next;
        head->next = newElement;
        return 0;
    }


    while (head->next != NULL && (strcmp(head->next->cityName, newElement->cityName) < 0))
            head = head->next;

        newElement->next = head->next;
        head->next = newElement;       
    

    return EXIT_SUCCESS;
}

position_list createListElement(char cityName[], int population) {

    position_list newElement = NULL;

    newElement = (position_list)malloc(sizeof(linkedList));

    if(!newElement) {

        printf("Memorija za novi element vezane liste ne moze biti alocirana!\n");
        return NULL;
    }

    strcpy(newElement->cityName, cityName);
    newElement->population = population;
    newElement->next = NULL;

    return newElement;
}

int printInorder(position_tree root) {

    if(root == NULL) 
        return 0;

    printInorder(root->left);
    printf("\n\t%s", root->stateName);
    printInorder(root->right);

    return EXIT_SUCCESS;
}

position_tree creteTreeElement(char stateName[]) {

    position_tree newElement = NULL;

    newElement = (position_tree)malloc(sizeof(tree));

    if(!newElement) {

        printf("Memorija za novi element stabla ne moze se alocirati!\n");
        return NULL;
    }

    strcpy(newElement->stateName, stateName);
    newElement->left = NULL;
    newElement->right = NULL;
    newElement->nextList = createHeadList();

    return newElement;
}

position_tree insertIntoTree(position_tree root, position_tree newElement) {

    if(!root) {

        return newElement;
    }

    else if(strcmp(root->stateName, newElement->stateName) >= 0)
        root->left = insertIntoTree(root->left, newElement);
    
    else if(strcmp(root->stateName, newElement->stateName) < 0)
        root->right = insertIntoTree(root->right, newElement);
    
    return root;
}

position_tree readFromFile(char fileName[]) {

    FILE* fp = NULL;
    char* buffer = NULL;
    char stateName[MAX] = { 0 };
    char additionalFile[MAX] = { 0 };
    int byteNumb = 0;
    position_tree newElement = NULL;
    position_tree root = NULL;

    buffer = (char*)malloc(MAX * sizeof(char));

    if(!buffer) {

        printf("Memorija za buffer se ne moze alocirati!\n");
        return NULL;
    }

    fp = fopen(fileName, "r");

    if(!fp) {

        printf("File se ne moze otvoriti!\n");
        return NULL;
    }

    while(!feof(fp)) {

        fgets(buffer, MAX, fp);

        if(sscanf(buffer, "%s %s %n", stateName, additionalFile, &byteNumb) == 2) {

            newElement = creteTreeElement(stateName);

            if(!newElement) {

                printf("NIje moguce alocirati memoriju za novi element vezane liste!\n");
                return NULL;
            }

            printf("\nDrzava: %s gradovi:", newElement->stateName);

            root = insertIntoTree(root, newElement);

            readFromAdditionalFile(newElement, additionalFile);

            buffer += byteNumb;
        }

        else {

            printf("Nesto nije uredu sa formatom vaseg filea!\nMolim, prmjenite format!\n");
            printf("Format: [ime drzave] [razmak] [Gradovi_[ime drzave].txt]\n");
            return NULL;
        }
    }
    
    fclose(fp);

    return root;
}

int readFromAdditionalFile(position_tree root, char additionalFile[]) {

    FILE* fp = NULL;
    char cityName[MAX] = { 0 };
    int population = 0;
    char* buffer = NULL;
    int byteNumb = 0;
    position_list newElement = NULL;
    position_list head = root->nextList; 

    buffer = (char*)malloc(MAX * sizeof(char));

    if(!buffer) {

        printf("Memorija za buffer se ne moze alocirati!\n");
        return EXIT_ERROR;
    }

    fp = fopen(additionalFile, "r");

    if(!fp) {

        printf("Fileu %s ne moze se pristupiti!\n", additionalFile);
        return EXIT_ERROR;
    }

    while(!feof(fp)) {

        fgets(buffer, MAX, fp);
        

        if(sscanf(buffer, "%s %d %n", cityName, &population, &byteNumb) == 2) {

            newElement = createListElement(cityName, population);

            insertIntoList(newElement, root->nextList);

            buffer += byteNumb;
        }

        else {

            printf("Nesto nije uredu sa formatom vaseg filea!\nMolim, prmjenite format!\n");
            printf("Format: [ime grada] [razmak] [broj stanovnika]\n");
            return EXIT_ERROR;           
        }
    }

    printList(root->nextList);  
    puts("");

    fclose(fp);

    return EXIT_SUCCESS;
}

int printList(position_list head) {

    while (head->next != NULL) {

        head = head->next;
        printf("\n\tGrad: %s    Populacija: %d", head->cityName, head->population);        
    }

    return EXIT_SUCCESS;
}

position_tree findStateByName(position_tree current, char *stateName) {



        if(current == NULL)
            return NULL;

        else if(strcmp(current->stateName, stateName) == 0)   
            return current;

        else if(strcmp(current->stateName, stateName) > 0)
            return findStateByName(current->left, stateName);

        else if(strcmp(current->stateName, stateName) < 0)
            return findStateByName(current->right, stateName);

        else
    return current;
}

position_list findCityByName(position_list current, char cityName[]) {

    while (current->next != NULL && (strcmp(current->next->cityName, cityName))){
        current = current->next;
    
    if((strcmp(cityName, current->next->cityName))) 
    {

        printf("Grad ne postoji!\n");
        return NULL;
    }
    }
    current = current->next;

    return current;
}

int Menu(position_tree states) {

    int key = 11;
    char stateName[MAX] = { 0 };
    char cityName[MAX] = { 0 };
    position_list currentList = NULL;
    position_tree currentTree = NULL;
    position_list temp = NULL;

    currentList = (position_list)malloc(sizeof(linkedList));

    if(!currentList) {

        printf("Memorija za listu [pretrazivanje] ne moze biti alocirana!\n");
        return EXIT_ERROR;
    }
    
    currentTree = (position_tree)malloc(sizeof(tree));

    if(!currentTree) {

        printf("Memorija za stablo [pretrazivanje] ne moze biti alocirana!\n");
        return EXIT_ERROR;
    }

    temp = (position_list)malloc(sizeof(linkedList));
    printf("\n");

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

            currentTree = findStateByName(states, stateName);

            if (!currentTree)
                printf("\n\tTa drzava ne postoji!\n");

            else
            {
                printf("\n\tDrzava: %s je pronadjena!", currentTree->stateName);
                printf("\n\tGradovi drzave su:\n");
                printList(currentTree->nextList);

                printf("\n\n\tUnesite ime grada: ");
                scanf(" %s", cityName);

                temp = currentTree->nextList;

                currentList = findCityByName(temp, cityName);

                if (!currentTree)
                    printf("\n\tGrada nema!\n");

                else
                    printf("\n\tGrad: %s    Populacija: %d", currentList->cityName, currentList->population);
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


//neke gradove drzava ne zeli pronaci a neke zeli npr. Cork u Irskoj ne zeli ali Arklow zeli

//update prva 2 zeli ostale ne zeli
//findCitybyName funkcija zaj***je