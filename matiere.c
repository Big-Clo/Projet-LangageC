#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"

int reference_existe(int x){
    char libelle[15];
    int reference,coefficient;
    FILE  *file = 
    fopen ("matiere.csv", "r");
    while (fscanf(file, "%d;%s;%d\n", &reference,libelle,&coefficient) != -1){
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
    printf("Veuillez saisir la reference de la matiere : ");
    scanf("%d",&mat.reference);
    a=reference_existe(mat.reference);
    while (a==1)
    {
        printf("Cette reference a deja ete utilise\nVeuillez ressaisir une nouvelle reference : ");
        scanf("%d",&mat.reference);
        a=reference_existe(mat.reference);
    }
    
    printf("Veuillez saisir le libelle de la matiere : ");
    scanf("%s",mat.libelle);

    printf("Veuillez saisir le coefficient de la matiere : ");
    scanf("%d",&mat.coefficient);

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu etre ouvert");
        return 1;
    }
    fprintf(file,"%d;%s;%d\n",mat.reference,mat.libelle,mat.coefficient);
    fclose(file);
    return 0;
}

int supprimer_matiere(char line_sup[100]) {
    FILE *file = fopen("matiere.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (file == NULL || temp == NULL) {
        printf("Le fichier n'a pas pu etre ouvert");
        return 1;
    }

    char line[100];
    int trouve = 0;

    while (fgets(line, sizeof(line), file)) {
        
        line[strcspn(line, "\n")] = 0;
        line_sup[strcspn(line_sup, "\n")] = 0;

        if (strcmp(line, line_sup) != 0) {
            fprintf(temp, "%s\n", line);
        } else {
            trouve = 1; 
        }
    }

    fclose(file);
    fclose(temp);

    remove("matiere.csv");
    rename("temp.csv", "matiere.csv");

    return trouve ? 0 : 2;;
}

int lister_matiere() {
    FILE *file = fopen("matiere.csv", "r");
    if (file != NULL) {
        char ligne[100];
        char lib[15];
        int ref, coef;

        while (fgets(ligne, sizeof(ligne), file)) {
            ligne[strcspn(ligne, "\n")] = '\0'; 

            char *valeur = strtok(ligne, ";");
            
            ref = atoi(valeur);

            valeur = strtok(NULL, ";");
            
            strcpy(lib, valeur);

            valeur = strtok(NULL, ";");
            
            coef = atoi(valeur);

            printf("Reference : %d, Libelle : %s, Coefficient : %d\n", ref, lib, coef);
        }

        fclose(file);
        return 0;
    } else {
        printf("Le fichier n'a pas pu etre ouvert");
        return 1;
    }
}


int modifier_matiere(){

    return 0;
}



int chercher_matiere(){
    return 0;
}