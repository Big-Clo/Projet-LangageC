#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"
#include "gestion_note.h"


char* chercher(int a, char *trouve) {
    FILE* file = fopen("matiere.csv", "r");
    if (file == NULL) {
        printf("Le fichier n'a pas pu etre ouvert");
        return NULL;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char copie[100];
        strcpy(copie, line);
        copie[strcspn(copie, "\r\n")] = 0;  

        char *valeur = strtok(line, ";");
        if (valeur != NULL && atoi(valeur) == a) {
            strcpy(trouve, copie);  
            break;
        }
    }

    fclose(file);
    return trouve;
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
        
        line[strcspn(line, "\r\n")] = 0;
        line_sup[strcspn(line_sup, "\r\n")] = 0;

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

    return trouve ? 0 : 2;
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


int modifier_matiere(char line_modif[100]){
    supprimer_matiere(line_modif);
    int a;
    matiere mat;
    printf("Veuillez saisir la nouvelle reference de la matiere : ");
    scanf("%d",&mat.reference);
    a=reference_existe(mat.reference);
    while (a==1)
    {
        printf("Cette reference a deja ete utilise\nVeuillez ressaisir une nouvelle reference : ");
        scanf("%d",&mat.reference);
        a=reference_existe(mat.reference);
    }
    
    printf("Veuillez saisir le nouveau libelle de la matiere : ");
    scanf("%s",mat.libelle);

    printf("Veuillez saisir le nouveau coefficient de la matiere : ");
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



int rech_ref(int a){
    FILE *file=fopen("matiere.csv","r");
    if(file==NULL){printf("Le fichier n'a pas pu etre ouvert");return 1;}
    char ligne[100];
    char lib[15];
    int ref, coef;
    while (fgets(ligne, sizeof(ligne), file)) {
            char copie[100];
            strcpy(copie, ligne);
            ligne[strcspn(ligne, "\n")] = '\0'; 

            char *valeur = strtok(ligne, ";");
            
            ref = atoi(valeur);

            valeur = strtok(NULL, ";");
            
            strcpy(lib, valeur);

            valeur = strtok(NULL, ";");
            
            coef = atoi(valeur);
            if (a==ref)
            {
                printf("%s",copie);
            }
       
}
fclose(file);
return 0;
}

int rech_lib(char a[15]){
    FILE *file=fopen("matiere.csv","r");
    if(file==NULL){printf("Le fichier n'a pas pu etre ouvert");return 1;}
    char ligne[100];
    char lib[15];
    int ref, coef;
    while (fgets(ligne, sizeof(ligne), file)) {
            char copie[100];
            strcpy(copie, ligne);
            ligne[strcspn(ligne, "\n")] = '\0'; 

            char *valeur = strtok(ligne, ";");
            
            ref = atoi(valeur);

            valeur = strtok(NULL, ";");
            
            strcpy(lib, valeur);

            valeur = strtok(NULL, ";");
            
            coef = atoi(valeur);
            if (strcmp(a,lib)==0)
            {
                printf("%s",copie);
            }
       
}
    fclose(file);
    return 0;
}

int rech_coef(int a){
    FILE *file=fopen("matiere.csv","r");
    if(file==NULL){printf("Le fichier n'a pas pu etre ouvert");return 1;}
    char ligne[100];
    char lib[15];
    int ref, coef;
    while (fgets(ligne, sizeof(ligne), file)) {
            char copie[100];
            strcpy(copie, ligne);
            ligne[strcspn(ligne, "\n")] = '\0'; 

            char *valeur = strtok(ligne, ";");
            
            ref = atoi(valeur);

            valeur = strtok(NULL, ";");
            
            strcpy(lib, valeur);

            valeur = strtok(NULL, ";");
            
            coef = atoi(valeur);
            if (a==coef)
            {
                printf("%s",copie);
            }
       
}
fclose(file);
    return 0;
}

void menuRecherche_matiere(){
    int option;
    do
    {
        printf("A partir de quel element voulez vous faire une recherche?\n\n\n");
        printf("1. Reference\n");
        printf("2. Libelle\n");
        printf("3. Coefficient\n");
        printf("0. Quitter\n");
        printf("Renseignez votre choix : ");
        scanf("%d",&option);
        switch (option)
        {
        case 1 :
            int a;
            printf("Quelle reference voulez vous rechercher ?");
            scanf("%d",&a);
            rech_ref(a);
            break;

         case 2 :
            char b[15];
            printf("Quelle libelle voulez vous rechercher ? ");
            scanf("%s",&b);
            rech_lib(b);
            break;
        
        case 3 :
            int c;
            printf("Quelle coefficient voulez vous rechercher ? ");
            scanf("%d",&c);
            rech_coef(c);
            break;

        default:
            break;
        }

    } while (option!=0);
    
}
