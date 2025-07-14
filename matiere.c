#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"
#include "gestion_note.h"
#include "general.h"

char* chercher(int a, char *trouve) {
    FILE* file = fopen("matiere.csv", "r");
    if (file == NULL) {
        printf("Le fichier n'a pas pu être ouvert");
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
    printf("Veuillez saisir la référence de la matière : ");
    mat.reference = saisie_entier();
    a=reference_existe(mat.reference);
    while (a==1)
    {
        printf("Cette référence a déjà été utilisé\nVeuillez ressaisir une nouvelle référence : ");
        mat.reference=saisie_entier();
        a=reference_existe(mat.reference);
    }
    
    printf("Veuillez saisir le libellé de la matière : ");
    saisie_ligne(mat.libelle,sizeof(mat.libelle));

    printf("Veuillez saisir le coefficient de la matière : ");
    mat.coefficient = saisie_entier();

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu être ouvert");
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
        printf("Le fichier n'a pas pu être ouvert");
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
        printf("\t| Référence |     Libellé     | Coefficient |\n");
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
        printf("Le fichier n'a pas pu être ouvert");
        return 1;
    }
}


int modifier_matiere(char line_modif[100]){
    supprimer_matiere(line_modif);
    int a;
    matiere mat;
    printf("Veuillez saisir la nouvelle référence de la matière : ");
    mat.reference = saisie_entier();
    a=reference_existe(mat.reference);
    while (a==1)
    {
        printf("Cette référence a déjà été utilisé\nVeuillez ressaisir une nouvelle référence : ");
        mat.reference = saisie_entier();
        a=reference_existe(mat.reference);
    }
    
    printf("Veuillez saisir le nouveau libellé de la matière : ");
    saisie_ligne(mat.libelle,sizeof(mat.libelle));

    printf("Veuillez saisir le nouveau coefficient de la matière : ");
    mat.coefficient = saisie_entier();

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu être ouvert");
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
    printf("Veuillez saisir la nouvelle référence de la matière : ");
    mat.reference = saisie_entier();
    a=reference_existe(mat.reference);
    while (a==1)
    {
        printf("Cette référence a déjà été utilisé\nVeuillez ressaisir une nouvelle référence : ");
        mat.reference = saisie_entier();
        a=reference_existe(mat.reference);
    }
    
    strcpy(mat.libelle,lib);
    mat.coefficient = coef;

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu être ouvert");
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
    
    printf("Veuillez saisir le nouveau libellé de la matiere : ");
    saisie_ligne(mat.libelle,sizeof(mat.libelle));

    mat.coefficient = coef;

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu être ouvert");
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

    printf("Veuillez saisir le nouveau coefficient de la matière : ");
    mat.coefficient = saisie_entier(); 

    FILE *file=fopen("matiere.csv","a");
    if(file==NULL){
        printf("Le fichier n'a pas pu être ouvert");
        return 1;
    }
    fprintf(file,"%d;%s;%d\n",mat.reference,mat.libelle,mat.coefficient);
    fclose(file);
    return 0;
}

void menuModifier_matiere(int a)
    {int choix;
    
        char ligne_modif[100];
        system("cls");
        printf("Quel élément voulez vous modifier ?\n\n\n");
        printf("1. Référence\n");
        printf("2. Libellé\n");
        printf("3. Coefficient\n");
        printf("4. Tout\n");
        printf("0. Annuler\n\n");
        printf("Renseignez votre choix : ");
        choix = saisie_entier();
        printf("\n\n");
        system("cls");

        switch (choix)
        {
        case 1 :
            chercher(a,ligne_modif);
            modifier_ref(ligne_modif); 
            break;
        case  2 :
            chercher(a,ligne_modif);
            modifier_lib(ligne_modif); 
            break;
        case 3 :
            chercher(a,ligne_modif);
            modifier_coef(ligne_modif); 
            break;
        case 4 :
            chercher(a,ligne_modif);
            modifier_matiere(ligne_modif); 
            break;
        case 0:
            printf("Menu précédent\n\n");
            break;
        default:
            printf("Nous ne pouvons pas encore gérer cette option\n"); 
            break;
        }
        printf("\n\n");
    
}

int rech_ref(int a){
    FILE *file=fopen("matiere.csv","r");
    if(file==NULL){printf("Le fichier n'a pas pu être ouvert");return 1;}
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
    if(file==NULL){printf("Le fichier n'a pas pu être ouvert");return 1;}
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
    if(file==NULL){printf("Le fichier n'a pas pu être ouvert");return 1;}
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
        printf("1. Référence\n");
        printf("2. Libellé\n");
        printf("3. Coefficient\n");
        printf("0. Quitter\n\n");
        printf("Renseignez votre choix : ");
        option = saisie_entier();
        printf("\n");
        switch (option)
        {
        case 1 :
            int a;
            system("cls");
            printf("Quelle référence voulez vous rechercher ?");
            a = saisie_entier();
            printf("\t+-----------+-----------------+-------------+\n");
            printf("\t| Référence |     Libellé     | Coefficient |\n");
            printf("\t+-----------+-----------------+-------------+\n");
            rech_ref(a);
            system("pause");
            break;

         case 2 :
            char b[15];
            system("cls");
            printf("Quelle libellé voulez vous rechercher ? ");
            saisie_ligne(b,sizeof(b));
            printf("\t+-----------+-----------------+-------------+\n");
            printf("\t| Référence |     Libellé     | Coefficient |\n");
            printf("\t+-----------+-----------------+-------------+\n");
            rech_lib(b);
            system("pause");
            break;
        
        case 3 :
            int c;
            system("cls");
            printf("Quelle coefficient voulez vous rechercher ? ");
            c = saisie_entier();
            printf("\t+-----------+-----------------+-------------+\n");
            printf("\t| Référence |     Libellé     | Coefficient |\n");
            printf("\t+-----------+-----------------+-------------+\n");
            rech_coef(c);
            system("pause");
            break;
        
        case 0:
            printf("Menu précédent\n\n");
            break;
        default:
            printf("Nous ne pouvons pas encore gérer cette option\n");
            system("pause");
            break;
        }

    } while (option!=0);
    
}
