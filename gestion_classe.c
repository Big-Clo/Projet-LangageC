#include "gestion_classe.h"
#include "matiere.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "general.h"


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
    classe.code=saisie_entier();
    existe = code_existe(classe.code);
    while(existe == 1 ){
        printf ("Le code que vous avez saisit est deja attribue a une classe veuillez saisir un autre code ou -1 si vous voulez annuler l'ajout:\t");
        classe.code=saisie_entier();
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
    saisie_ligne(classe.nom,sizeof(classe.nom));
    printf ("\nVeuillez tapez 1 si c'est une classe de license et 2 si c'est une classe de master:\t");
    level=saisie_entier();
    while (level != 1 && level != 2){
        printf("\nVous devez entrer 1 si vous etes en license et 2 si vous etes en master. Veuillez reessayer:\t");
        level=saisie_entier();
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
    printf("\t+-----------+-----------------+-------------+\n");
    printf("\t| Reference |     libelle     | coefficient |\n");
    printf("\t+-----------+-----------------+-------------+\n");
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){

            printf("\t| %9d | %15s | %11s |\n", code,nom, niveau);
            printf("\t+-----------+-----------------+-------------+\n");
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

int ajouter_matiere_classe(int r, int c){
    char ligne[100];
    int code,ref;
    FILE*file=fopen("matiere-classe.csv","a+");
    if(file == NULL){
        printf("Le fichier n'a pas pu être ouvert\n");
        return 1;
    } 
    while(fgets(ligne,sizeof(ligne),file)){
        if (sscanf(ligne,"%d;%d",&ref,&code)==2)
        {
            if (r == ref && c ==code)
            {
                fclose(file);
                return 1;
            }
            
        }
        
    }  
    
    fprintf(file,"%d;%d\n",r,c);
    fclose(file);

    return 0;
}

int retirer_matiere_classe(int r, int c) {
    char ligne[100];
    int ref, code;
    int trouve = 0;

    FILE *file = fopen("matiere-classe.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (file == NULL || temp == NULL) {
        printf("Erreur : impossible d'ouvrir les fichiers.\n");
        return 1;
    }

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d;%d", &ref, &code) == 2) {
            if (ref != r || code != c) {
                fprintf(temp, "%d;%d\n", ref, code);
            } else {
                trouve = 1; 
            }
        }
    }

    fclose(file);
    fclose(temp);

    if (!trouve) {
        remove("temp.csv");
        return 2;
    }

    remove("matiere-classe.csv");
    rename("temp.csv", "matiere-classe.csv");
    return 0;
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
            saisie_ligne(nouveau_nom,sizeof(nouveau_nom));
            printf("Veuillez entrez 1 si c'est un classe de License et 2 si c'est une classe de Master : ");
            nouveau_niveau=saisie_entier();
            while (nouveau_niveau != 1 && nouveau_niveau !=2){
                printf("Vous pouvez saisir que 1 pour License et 2 pour Master. Veuillez saisir");
                nouveau_niveau=saisie_entier();
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

int afficher_matiere_classe(){

    char ligne[100];
    int ref, code_recherche=0;
    int trouve = 0;
    char lignes[100];
    char libe[15];
    int refe, co;

    printf("Veuillez saisir le code de la classe dont vous voulez afficher les matieres: ");
    code_recherche=saisie_entier();
    while (!(code_existe(code_recherche)) && code_recherche != -1  ){
        printf("Il n'y a pas de classe avec ce code. Veuillez ressaisir le code ou -1 pour annuler: ");
        code_recherche=saisie_entier();
    }


    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe == NULL){
        printf("le fichier n' a pas pu etre ouvert");
        fclose(fichier_classe);
        exit(1);
    }
    int code;
    char nom[30], niveau[10];
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if(code_recherche == code){
        printf("Voici les matieres de la classe : %s\n", nom);
        break;
        }
    }
    fclose(fichier_classe);

    printf("\t+-------------+-----------------+-------------+\n");
    printf("\t| Reference   |     libelle     | coefficient |\n");
    printf("\t+-------------+-----------------+-------------+\n");
    FILE *fichier = fopen("matiere-classe.csv", "r");
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (sscanf(ligne, "%d;%d", &ref, &code) == 2) {
           
            FILE *file = fopen("matiere.csv", "r");
            if (file != NULL) {

               

                    
             
                    while (fgets(lignes, sizeof(lignes), file)) {
                        if (sscanf(lignes, "%d;%29[^;];%d", &refe, libe, &co) == 3){
                            if (ref == refe){
                        printf("\t| %11d | %15s | %11d |\n", refe,libe, co);
                        printf("\t+-------------+-----------------+-------------+\n");
                            }
                        }
                    }
                

                
                fclose(file);
            } else {
                printf("Le fichier n'a pas pu être ouvert");
                return 1;
            }

        }
    }
}

void matiere_classe(){
    int choix;
    do
    {
        //system("cls");
        printf("Quelle action voulez vous effectuer ?\n");
        printf("1. Ajouter une matiere a une classe\n");
        printf("2. Retirer une matiere a une classe\n");
        printf("3. Afficher les classes associees a une matiere\n");
        printf("4. Afficher les matieres d'une classe\n");

        printf("Renseignez votre choix : ");
        choix = saisie_entier();

        int code,ref,existe;
        char ligne[20];
        
        switch (choix)
        {
        case 1 :
            printf("Quel est la référence de la matière que vous voulez ajouter ? ");
            ref = saisie_entier();
            existe = reference_existe(ref);
            while(existe == 0){
                printf("Cette référence n'existe pas. Entrez une référence valide ou entrez -1 pour annuler l'operation : ");
                ref = saisie_entier();
                if (ref == -1) break;
                existe= reference_existe(ref);
            }
            
            if (ref == -1){
                printf("L'operation a été annulé.");
                break;
            }

            printf("Entrez le code de la classe a laquelle vous voulez ajouter la matiere : ");
            code = saisie_entier();
            existe = code_existe(code);
            while(existe == 0){
                printf("Ce code n'existe pas. Entrez un code valide ou entrez -1 pour annuler l'operation : ");
                code = saisie_entier();
                if (code == -1) break;
                existe= code_existe(code);
            }
            
            if (code == -1){
                printf("L'operation a été annulé.");
                break;
            }
            ajouter_matiere_classe(ref,code);
            break;
        
        case 2 :
            printf("Quel est la référence de la matière que vous voulez retirer ? ");
            ref = saisie_entier();
            existe = reference_existe(ref);
            while(existe == 0){
                printf("Cette référence n'existe pas. Entrez une référence valide ou entrez -1 pour annuler l'operation : ");
                ref = saisie_entier();
                if (ref == -1) break;
                existe= reference_existe(ref);
            }

            if (ref == -1){
                printf("L'operation a été annulé.");
                break;
            }

            printf("Entrez le code de la classe a laquelle vous voulez retirer la matiere : ");
            code = saisie_entier();
            existe = code_existe(code);
            while(existe == 0){
                printf("Ce code n'existe pas. Entrez un code valide ou entrez -1 pour annuler l'operation : ");
                code = saisie_entier();
                if (code == -1) break;
                existe= code_existe(code);
            }

            if (code == -1){
                printf("L'operation a été annulé.");
                break;
            }
            retirer_matiere_classe(ref,code);
            break;
        
        case 3 :
            printf("Quel est la classe dont vous voulez connaitre les matieres ? ");
            existe=saisie_entier();
            FILE*file=fopen("matiere-classe.csv","r");
            printf("\t+-----------+-----------------+-------------+\n");
            printf("\t| Référence |     Libellé     | Coefficient |\n");
            printf("\t+-----------+-----------------+-------------+\n");
            while(fgets(ligne,sizeof(ligne),file))
            {
                sscanf(ligne,"%d;%d",&ref,&code);
                if (code == existe)
                {
                    rech_ref(ref);
                }
                
            }
            
            break;

        case 4 :
            afficher_matiere_classe();
            break;

        default:
            break;
        }

    } while (choix!=0);
    
}