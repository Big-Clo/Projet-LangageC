#include "gestion_classe.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int code_existe(int x){
    char nom[30], niveau[10];
    int code;
    FILE  *fichier_classe = 
    fopen ("classe.csv", "r");
    while (fscanf(fichier_classe, "%d - %s - %s\n", &code, nom, niveau) != -1){
        if (x == code){
            fclose(fichier_classe);
            return 1;
            
        }
    }
    fclose(fichier_classe);
<<<<<<< HEAD


=======
>>>>>>> 21bece1b00fbf1674b2b36a704c4451e490f7610
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
        fprintf(fichier_classe,"\n%d - %s - License",classe.code, classe.nom);
    else
        fprintf(fichier_classe,"\n%d - %s - Master",classe.code, classe.nom);
    

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
    while (fscanf(fichier_classe, "%d - %s - %s\n", &code, nom, niveau) != -1){
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
    while (fscanf(fichier_classe, "%d - %s - %s\n", &code, nom, niveau) != -1){
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
    int code, trouve = 0;

    while (fscanf(fichier, "%d - %s - %s\n", &code, nom, niveau) != -1) {
        if (code != code_a_supprimer) {
            fprintf(temp, "%d - %s - %s\n", code, nom, niveau);
        } else {
            trouve = 1;
        }
    }

    fclose(fichier);
    fclose(temp);
    remove("classe.csv");
    rename("temp.csv", "classe.csv");
    printf("Classe supprimee avec succes.\n");
}
