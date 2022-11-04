void UnosDad(Position P, imedad);
void CitaDad(Position P, imedad);

void UnosP(Position P){
     Position q;
     q=(Position)malloc(sizeof(struct _osoba)); 
     printf("\nUnesite podatke o novoj osobi: ");
     scanf("%s %s %d",q->ime,q->prezime,&q->godRod);
       
     q->next = P->next; 
     P->next = q;}

/*u main dodati 
char imedad[MAXC];
FILE* pok_na_dad = NULL;
while(pok_na_dad==NULL){ 
   printf("Upisite ime datoteke.\n");
   scanf("%s", imedad);
   pok_na_dad = fopen(imedad, "r+");
   
   if(pok_na_dad==NULL){
       printf("Greska, dadoteka nije otvorena."); }
      
*/

/*u main dodaj switch case za ovu opciju poziva UnosDad(&head,imedad); */
void UnosDad(Position P, char imedad[MAXC]){
    FILE* pok_na_dad = NULL;
    pok_na_dad = fopen(imedad,"w");
    if(pok_na_dad==NULL){
       printf("Greska, dadoteka nije otvorena."); }
    Position novi_clan;
    novi_clan = (Position)malloc(sizeof(struct _osoba));
    printf("Zapocnite unos u dadoteku");
    scanf("%s %s %d",novi_clan->ime,novi_clan->prezime,&novi_clan->godRod);
    novi_clan->next = P->next;
    P->next = novi_clan;
    
    fputs(novi_clan->ime,imedad);
    /* ili treba staviti pok_na_dad umjesto imedad */
    fputc("\n",imedad);
    fputs(novi_clan->prezime,imedad);
    fputc("\n",imedad);
    fputc(novi_clan->godRod,imedad);
    fputc("\n",imedad);
    fputc("\n",imedad);
}

void CitaDad(Position P, imedad){
    FILE* pok_na_dad = NULL;
    pok_na_dad = fopen(imedad,"r");
    if(pok_na_dad == NULL){
        printf("Greska u otvaranju dadoteke");}
    printf("Ispis liste:"); 
    while (fgetc!=NULL) { 
      printf(fscanf(imedad," %s \n", P->ime));
      printf(fscanf(imedad," %s \n", P->prezime));
      printf(fscanf(imedad," %d \n",&P->godRod));
      
}