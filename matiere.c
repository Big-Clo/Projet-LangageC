#include <stdio.h>
#include "matiere.h"

int reference_existe(int x){
    char libelle[15];
    int reference,coefficient;
    FILE  *file = 
    fopen ("matiere.csv", "r");
    while (fscanf(file, "%d - %s - %d\n", &reference,libelle,&coefficient) != -1){
        if (x == reference){
            fclose(file);
            return 1;
            
        }
    }
    fclose(file);
    return 0;
}

int ajout_matiere(){
    int a;
    matiere mat;
    printf("Veuillez saisir la reference de la matiere :\n");
    scanf("%d",&mat.reference);
    a=reference_existe(mat.reference);
    while (a==1)
    {
        printf("Cette reference a deja ete utilise\nVeuillez ressaisir une nouvelle reference :");
        scanf("%d",&mat.reference);
        a=reference_existe(mat.reference);
    }
    
    printf("Veuillez saisir le libelle de la matiere :\n");
    scanf("%s",mat.libelle);

    printf("Veuillez saisir le coefficient de la matiere :\n");
    scanf("%d",&mat.coefficient);

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu etre ouvert");
        return 1;
    }
    fprintf(file,"%d - %s - %d\n",mat.reference,mat.libelle,mat.coefficient);
    fclose(file);
    return 0;
}