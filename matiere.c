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
        printf("\t+-----------+-----------------+-------------+\n");
        printf("\t| Reference |     Libelle     | Coefficient |\n");
        printf("\t+-----------+-----------------+-------------+\n");
        while (fgets(ligne, sizeof(ligne), file)) {
            ligne[strcspn(ligne, "\n")] = '\0'; 

            char *valeur = strtok(ligne, ";");
            
            ref = atoi(valeur);

            valeur = strtok(NULL, ";");
            
            strcpy(lib, valeur);

            valeur = strtok(NULL, ";");
            
            coef = atoi(valeur);

            
            printf("\t| %9d | %15s | %11d |\n",ref,lib,coef);      
            printf("\t+-----------+-----------------+-------------+\n");
        }

        printf("\n\n");
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
    fprintf(file,"%d;%s;%d\n",mat.reference,mat.libelle,mat.coefficient);
    fclose(file);
    return 0;
}

int modifier_ref(char ligne_modif[100]){
    supprimer_matiere(ligne_modif);
    char copie[100],lib[15];
    int ref,coef;
    strcpy(copie, ligne_modif);
    ligne_modif[strcspn(ligne_modif, "\n")] = '\0'; 

    char *valeur = strtok(ligne_modif, ";");
    
    ref = atoi(valeur);

    valeur = strtok(NULL, ";");
    
    strcpy(lib, valeur);

    valeur = strtok(NULL, ";");
    
    coef = atoi(valeur);
    
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
    
    strcpy(mat.libelle,lib);
    mat.coefficient = coef;

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu etre ouvert");
        return 1;
    }
    fprintf(file,"%d;%s;%d\n",mat.reference,mat.libelle,mat.coefficient);
    fclose(file);
    return 0;
}

int modifier_lib(char ligne_modif[100]){
    supprimer_matiere(ligne_modif);
    char copie[100],lib[15];
    int ref,coef;
    strcpy(copie, ligne_modif);
    ligne_modif[strcspn(ligne_modif, "\n")] = '\0'; 

    char *valeur = strtok(ligne_modif, ";");
    
    ref = atoi(valeur);

    valeur = strtok(NULL, ";");
    
    strcpy(lib, valeur);

    valeur = strtok(NULL, ";");
    
    coef = atoi(valeur);
    
    int a;
    matiere mat;

    mat.reference = ref;    
    
    printf("Veuillez saisir le nouveau libelle de la matiere : ");
    scanf("%s",mat.libelle);

    mat.coefficient = coef;

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu etre ouvert");
        return 1;
    }
    fprintf(file,"%d;%s;%d\n",mat.reference,mat.libelle,mat.coefficient);
    fclose(file);
    return 0;
}

int modifier_coef(char ligne_modif[100]){
    supprimer_matiere(ligne_modif);
    char copie[100],lib[15];
    int ref,coef;
    strcpy(copie, ligne_modif);
    ligne_modif[strcspn(ligne_modif, "\n")] = '\0'; 

    char *valeur = strtok(ligne_modif, ";");
    
    ref = atoi(valeur);

    valeur = strtok(NULL, ";");
    
    strcpy(lib, valeur);

    valeur = strtok(NULL, ";");
    
    coef = atoi(valeur);
    
    int a;
    matiere mat;

    mat.reference = ref;

    strcpy(mat.libelle,lib);

    printf("Veuillez saisir le nouveau coefficient de la matiere : ");
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

void menuModifier_matiere(int a)
    {int choix;
    do{
        char ligne_modif[100];
        system("cls");
        printf("Quel element voulez vous modifier ?\n\n\n");
        printf("1. Reference\n");
        printf("2. Libelle\n");
        printf("3. Coefficient\n");
        printf("4. Tout\n");
        printf("0. Annuler\n");
        printf("Renseignez votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1 :
            chercher(a,ligne_modif);
            modifier_ref(ligne_modif);
            system("pause"); 
            break;
        case  2 :
            chercher(a,ligne_modif);
            modifier_lib(ligne_modif);
            system("pause"); 
            break;
        case 3 :
            chercher(a,ligne_modif);
            modifier_coef(ligne_modif);
            system("pause"); 
            break;
        case 4 :
            chercher(a,ligne_modif);
            modifier_matiere(ligne_modif);
            system("pause"); 
            break;
        case 0:
            printf("Menu precedent\n");
            break;
        default:
            printf("Nous ne pouvons pas encore gerer cette option\n");
            system("pause"); 
            break;
        }
    }while(choix!=0);
}

int rech_ref(int a){
    FILE *file=fopen("matiere.csv","r");
    if(file==NULL){printf("Le fichier n'a pas pu etre ouvert");return 1;}
    char ligne[100];
    char lib[15];
    int ref, coef;
    printf("\t+-----------+-----------------+-------------+\n");
    printf("\t| Reference |     Libelle     | Coefficient |\n");
    printf("\t+-----------+-----------------+-------------+\n");
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
                printf("\t| %9d | %15s | %11d |\n",ref,lib,coef);      
                printf("\t+-----------+-----------------+-------------+\n");
            }
       
}
printf("\n\n");
fclose(file);
return 0;
}

int rech_lib(char a[15]){
    FILE *file=fopen("matiere.csv","r");
    if(file==NULL){printf("Le fichier n'a pas pu etre ouvert");return 1;}
    char ligne[100];
    char lib[15];
    int ref, coef;
    printf("\t+-----------+-----------------+-------------+\n");
    printf("\t| Reference |     Libelle     | Coefficient |\n");
    printf("\t+-----------+-----------------+-------------+\n");
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
                printf("\t| %9d | %15s | %11d |\n",ref,lib,coef);      
                printf("\t+-----------+-----------------+-------------+\n");
            }
       
}
    printf("\n\n");
    fclose(file);
    return 0;
}

int rech_coef(int a){
    FILE *file=fopen("matiere.csv","r");
    if(file==NULL){printf("Le fichier n'a pas pu etre ouvert");return 1;}
    char ligne[100];
    char lib[15];
    int ref, coef;
    printf("\t+-----------+-----------------+-------------+\n");
    printf("\t| Reference |     Libelle     | Coefficient |\n");
    printf("\t+-----------+-----------------+-------------+\n");
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
                printf("\t| %9d | %15s | %11d |\n",ref,lib,coef);      
                printf("\t+-----------+-----------------+-------------+\n");
            }
       
}
printf("\n\n");
fclose(file);
    return 0;
}

void menuRecherche_matiere(){
    int option;
    do
    {
        system("cls");
        printf("A partir de quel element voulez vous faire une recherche?\n\n\n");
        printf("1. Reference\n");
        printf("2. Libelle\n");
        printf("3. Coefficient\n");
        printf("0. Annuler\n");
        printf("Renseignez votre choix : ");
        scanf("%d",&option);
        switch (option)
        {
        case 1 :
            int a;
            printf("Quelle reference voulez vous rechercher ?");
            scanf("%d",&a);
            rech_ref(a);
            system("pause");
            break;

         case 2 :
            char b[15];
            printf("Quelle libelle voulez vous rechercher ? ");
            scanf("%s",&b);
            rech_lib(b);
            system("pause");
            break;
        
        case 3 :
            int c;
            printf("Quelle coefficient voulez vous rechercher ? ");
            scanf("%d",&c);
            rech_coef(c);
            system("pause");
            break;
        
        case 0:
            printf("Menu precedent\n");
            break;
        default:
            printf("Nous ne pouvons pas encore gerer cette option\n");
            break;
        }

    } while (option!=0);
    
}
