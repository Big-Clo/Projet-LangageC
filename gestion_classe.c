#include "gestion_classe.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int code_existe(int x){
    char nom[30], niveau[10];
    int code;
    FILE  *fichier_classe = 
    fopen ("classe.csv", "r");
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if (x == code){
            fclose(fichier_classe);
            return 1;
            
        }
    }
    fclose(fichier_classe);
    return 0;
}

int ajout_classe(){
    CLASSE classe;
    int level, existe;
    
    printf ("Ce programme vous permet d'ajouter une classe.\n Veuillez saisir:\n le code de la classe:\t");
    scanf("%d", &classe.code);
    existe = code_existe(classe.code);
    while(existe == 1 ){
        printf ("Le code que vous avez saisit est deja attribue a une classe veuillez saisir un autre code ou -1 si vous voulez annuler l'ajout:\t");
        scanf("%d", &classe.code);
        existe = code_existe(classe.code);
        if (classe.code == -1){
            break;
        }
    }
    
    if (classe.code == -1){
        printf("L'ajout a ete annule");
        return 1;
    }
    printf ("\n Le nom de la classe:\t\n");
    scanf ("%s", classe.nom);
    printf ("\nVeuillez tapez 1 si vous etes en license et 2 si vous etes en master:\t");
    scanf("%d", &level);
    while (level != 1 && level != 2){
        printf("\nVous devez entrer 1 si vous etes en license et 2 si vous etes en master. Veuillez reessayer:\t");
        scanf("%d", &level);
    }
    if (level == 1){
        classe.niveau = License;
    }
    else{
        classe.niveau = Master;
    }

    FILE  *fichier_classe = fopen ("classe.csv", "a");
    if (fichier_classe == NULL){
        printf("le fichier n' a pas pu etre ouvert");
       
        return 1;
    }
    if (level == 1)
        fprintf(fichier_classe,"%d;%s;License\n",classe.code, classe.nom);
    else
        fprintf(fichier_classe,"%d;%s;Master\n",classe.code, classe.nom);
    

    fclose(fichier_classe);
    return 0;
}


void afficher_classe(){
    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe == NULL){
        printf("le fichier n' a pas pu etre ouvert");
        fclose(fichier_classe);
        exit(1);
    }
    int code;
    char nom[30], niveau[10];
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        printf("code: %d, nom: %s, niveau: %s\n", code, nom, niveau);
    }
    fclose(fichier_classe);
}

int recherche_classe(int x){
    int code;
    char nom[30], niveau[10];
    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe == NULL){
        printf("le fichier n' a pas pu etre ouvert");
        fclose(fichier_classe);
        return 1;
    }
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if (x == code){
            printf("L'element est present.\n ");
            printf("code: %d, nom: %s, niveau: %s\n", code, nom, niveau);
            return 0;
        }
    }
    printf ("L'element est absent");
    return 1;
}


void supprimer_classe(int code_a_supprimer) {
    FILE *fichier = fopen("classe.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fichier == NULL || temp == NULL) {
        printf("Le fichier n' a pas pu etre ouvert,\n");
        exit(1);
    }

    char nom[30], niveau[10];
    int code;

    while (fscanf(fichier, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3) {
        if (code != code_a_supprimer) {
            fprintf(temp, "%d;%s;%s\n", code, nom, niveau);
        } 
    }

    fclose(fichier);
    fclose(temp);
    remove("classe.csv");
    rename("temp.csv", "classe.csv");
    printf("Classe supprimee avec succes.\n");
}


void modifier_classe(int code_a_modifier) {
    FILE *fichier = fopen("classe.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (fichier == NULL || temp == NULL) {
        printf("Le fichier n'a pas pu etre ouvert.\n");
        exit(1);
    }

    char nom[50], niveau[20];
    int code;


    while (fscanf(fichier, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3) {
        if (code == code_a_modifier) {
            printf("Entrez les nouvelles informations.\n");

            char nouveau_nom[30];
            int nouveau_niveau;

            printf("Nouveau nom : ");
            scanf(" %s", nouveau_nom);
            printf("Veuillez entrez 1 si tu etes en License et 2 si vous etes en Master : ");
            scanf("%d", &nouveau_niveau);
            while (nouveau_niveau != 1 && nouveau_niveau !=2){
                printf("Vous pouvez saisir que 1 pour License et 2 pour Master. Veuillez saisir");
                scanf("%d", &nouveau_niveau);
            }
            if (nouveau_niveau ==1)
            fprintf(temp, "%d;%s;License\n", code_a_modifier, nouveau_nom);
            else
            fprintf(temp, "%d;%s;Master\n", code_a_modifier, nouveau_nom);

        } else {
            fprintf(temp, "%d;%s;%s\n", code, nom, niveau);
        }
    }

    fclose(fichier);
    fclose(temp);

    remove("classe.csv");
    rename("temp.csv", "classe.csv");

    printf(" Classe modifiee avec succes.\n");
}

