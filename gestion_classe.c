#include "gestion_classe.h"
#include "matiere.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "general.h"
#include "etudiant.h"


int ajout_classe(){
    CLASSE classe;
    int level, existe;
    
    printf ("Ce programme vous permet d'ajouter une classe.\n Veuillez saisir:\n le code de la classe : ");
    classe.code=saisie_entier();
    existe = code_existe(classe.code);
    while(existe == 1 ){
        printf ("Le code que vous avez saisi est déjà attribué à une classe veuillez saisir un autre code ou -1 si vous voulez annuler l'ajout:\t");
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
    printf ("\n Le nom de la classe : ");
    saisie_ligne(classe.nom,sizeof(classe.nom));
    Maj(classe.nom);
    existe=classe_existe(classe.nom);
    while(existe == 1 ){
        printf ("Le nom que vous avez saisi est déjà attribué à une classe veuillez saisir un autre nom ou q si vous voulez annuler l'ajout : ");
        saisie_ligne(classe.nom,sizeof(classe.nom));
        Maj(classe.nom);
        existe = classe_existe(classe.nom);
        if (strcmp(classe.nom,"Q")==0){
            break;
        }
    }
    if (strcmp(classe.nom,"Q")==0){
        printf("L'ajout a ete annulé");
        return 1;
    }

    printf ("\nVeuillez saisir 1 si c'est une classe de license ou 2 si c'est une classe de master : ");
    level=saisie_entier();
    while (level != 1 && level != 2){
        printf("\nVous devez saisir 1 si vous etes en license et 2 si vous etes en master. Veuillez reessayer : ");
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
        printf("le fichier n'a pas pu être ouvert");
       
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
        printf("le fichier n'a pas pu être ouvert");
        fclose(fichier_classe);
        exit(1);
    }
    int code;
    char nom[30], niveau[10];
    printf("\t+------------+-----------------+--------------+\n");
    printf("\t|   Numéro   |       Nom       |    Niveau    |\n");
    printf("\t+------------+-----------------+--------------+\n");
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){

            printf("\t| %-10d | %-15s | %-12s |\n", code,nom, niveau);
            printf("\t+------------+-----------------+--------------+\n");
    }
    fclose(fichier_classe);
}

void afficher_liste_eleve_classe(){
    Etudiant etudiant;
    int code, quitter = -1;
    int code_classe;
    char nom_classe[30], niveau_classe[10];
    FILE *fichier_etudiant = fopen("etudiants.csv", "r");
    if (fichier_etudiant == NULL){
        printf("Impossible d'ouvrir le fichier des étudiants");
        exit(1);
    }
    printf("Veuillez saisir le code de la classe dont vous voulez la liste: ");
    code = saisie_entier();
    while (!code_existe(code)){
        printf("Il n'y a pas de classe avec ce code. Voulez vous ressaisir ? Si non tapez 1 sinon tapez un autre entier : ");
        quitter = saisie_entier();
        if (quitter == 1){
            ("Annulation de la recherche");
            exit(1);
        }
        printf("Veuillez saisir un autre code");
        code = saisie_entier();
        
    }

    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe== NULL){
        printf("Impossible d'ouvrir le fichier des classes");
        exit(1);
    }
    while (fscanf(fichier_classe, "%d;%29[^;];%s\n", &code_classe, nom_classe, niveau_classe ) == 3){
        if(code == code_classe){
            break;
        }

    }
    fclose(fichier_classe);

    printf("\n===== LISTE DES ÉTUDIANTS EN %s =====\n", nom_classe);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\t+------------+--------------+--------------+--------------------------+--------------------+\n");
    printf("\t| Numéro     |     Nom      | Prénom       |          Email           |  date de naissance |\n");
    printf("\t+------------+--------------+--------------+--------------------------+--------------------+\n");

    while ((fscanf(fichier_etudiant, "%d;%29[^;];%29[^;];%49[^;];%d/%d/%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.date_naissance.jour, &etudiant.date_naissance.mois, &etudiant.date_naissance.annee, &etudiant.codeClasse)) != EOF)
    {

        if (code == etudiant.codeClasse) {
            printf("\t| %10d | %11s  | %11s  | %23s  |      %02d/%02d/%4d    |\n", etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.date_naissance.jour, etudiant.date_naissance.mois, etudiant.date_naissance.annee);
            printf("\t+------------+--------------+--------------+--------------------------+--------------------+\n");

        }
    }
    fclose(fichier_etudiant);


}

int rech_code_classe(int x){
    int code,trouve=0;
    char nom[30], niveau[10];
    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe == NULL){
        printf("le fichier n'a pas pu être ouvert");
        return 1;
    }
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if (x == code){trouve=1;}}
    if (!trouve) {
        printf("Aucun élément ne correspond à ce code\n\n");
        fclose(fichier_classe);
        return 1;
    }
    fclose(fichier_classe);
    fichier_classe = fopen("classe.csv", "r");
    printf("\t+------------+-----------------+--------------+\n");
    printf("\t|   Numéro   |       Nom       |    Niveau    |\n");
    printf("\t+------------+-----------------+--------------+\n");
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if (x == code){
            printf("\t| %-10d | %-15s | %-12s |\n", code,nom, niveau);
            printf("\t+------------+-----------------+--------------+\n");
        }
    }
    fclose(fichier_classe);
    return 0;
}

int rech_nom_classe(char *x){
    int code,trouve=0;
    char nom[30], niveau[10];
    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe == NULL){
        printf("le fichier n'a pas pu être ouvert");
        return 1;
    }
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if (strcmp(x,nom)==0){trouve=1;}}
    if (!trouve) {
        printf("Aucun élément ne correspond à ce nom\n\n");
        fclose(fichier_classe);
        return 1;
    }
    fclose(fichier_classe);
    fichier_classe = fopen("classe.csv", "r");
    printf("\t+------------+-----------------+--------------+\n");
    printf("\t|   Numéro   |       Nom       |    Niveau    |\n");
    printf("\t+------------+-----------------+--------------+\n");
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if (strcmp(x,nom)==0){
            printf("\t| %-10d | %-15s | %-12s |\n", code,nom, niveau);
            printf("\t+------------+-----------------+--------------+\n");
        }
    }
    fclose(fichier_classe);
    return 0;
}

int rech_niveau_classe(char *x) {
    int code;
    char maj[10], nom[30], niveau[10];
    int trouve = 0;

    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe == NULL){
        printf("Le fichier n'a pas pu être ouvert\n");
        return 1;
    }
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        strcpy(maj, niveau);
        Maj(maj);
        if (strcmp(x, maj) == 0){trouve=1;}}
    if (!trouve) {
        printf("Aucun élément ne correspond à ce niveau\n\n");
        fclose(fichier_classe);
        return 1;
    }
    fclose(fichier_classe);
    fichier_classe = fopen("classe.csv", "r");
    printf("\t+------------+-----------------+--------------+\n");
    printf("\t|   Numéro   |       Nom       |    Niveau    |\n");
    printf("\t+------------+-----------------+--------------+\n");
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3) {
        strcpy(maj, niveau);
        Maj(maj);
        if (strcmp(x, maj) == 0) {
            printf("\t| %-10d | %-15s | %-12s |\n", code,nom, niveau);
            printf("\t+------------+-----------------+--------------+\n");
        }
    }

    fclose(fichier_classe);
    return 0;
}

void menuRecherche_Classe(){
    int choix;
    do
    {
        system("cls");
        printf("A partir de quel element voulez vous faire une recherche?\n\n");
        printf("1. Code\n");
        printf("2. Nom\n");
        printf("3. Niveau\n");
        printf("0. Quitter\n\n");
        printf("Renseignez votre choix : ");
        choix = saisie_entier();
        printf("\n\n");

        switch (choix)
        {
        case 1:
            system("cls");
            printf("Veuillez saisir le code de la classe à rechercher : ");
            int a=saisie_entier();
            rech_code_classe(a);
            printf("\n");
            system("pause");
            break;
        case 2:
            char nom[30];
            system("cls");
            printf("Veuillez saisir le nom à rechercher : ");
            saisie_ligne(nom,30);
            Maj(nom);
            rech_nom_classe(nom);
            printf("\n");
            system("pause");
            break;
        case 3:
            system("cls");
            char cls[10];
            while (1) {
                printf("Veuillez saisir le niveau à rechercher (MASTER ou LICENSE, q pour annuler) : ");
                saisie_ligne(cls, 10);
                Maj(cls);

                if (strcmp(cls, "Q") == 0) {
                    printf("Opération annulée\n\n");
                    break;
                }

                if (strcmp(cls, "MASTER") != 0 && strcmp(cls, "LICENSE") != 0) {
                    printf("Ce niveau n'existe pas.\n\n");
                    continue;
                }

                rech_niveau_classe(cls);
                break;
            }
            printf("\n");
            system("pause");
            break;

        case 0:
            printf("Menu précédent\n\n");
            system("pause");
            break;
        default:
            printf("Renseignez une option valide\n");
            system("pause");
            break;
        }
    } while (choix!=0);
    
}

void supprimer_classe(int code_a_supprimer) {
    FILE *fichier = fopen("classe.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fichier == NULL || temp == NULL) {
        printf("Le fichier n'a pas pu être ouvert,\n");
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
            printf("Voici les anciennes informations de la classe :\nNom : %s, Niveau : %s",nom,niveau);
            printf("\nEntrez les nouvelles informations.\n");

            char nouveau_nom[30];
            int nouveau_niveau,existe;

            printf("Nouveau nom : ");
            saisie_ligne(nouveau_nom,sizeof(nouveau_nom));
            Maj(nouveau_nom);
            existe=classe_existe(nouveau_nom);
            while(existe == 1 ){
                printf ("Le nom que vous avez saisit est deja attribue a une classe veuillez saisir un autre nom ou q si vous voulez annuler la modification : ");
                saisie_ligne(nouveau_nom,sizeof(nouveau_nom));
                Maj(nouveau_nom);
                existe = classe_existe(nouveau_nom);
                if (strcmp(nouveau_nom,"Q")==0){
                    break;
                }
            }
            if (strcmp(nouveau_nom,"Q")==0){
                printf("La modification à été annulé");
                return ;
            }
            printf("Veuillez saisir 1 si c'est un classe de License ou 2 si c'est une classe de Master : ");
            nouveau_niveau=saisie_entier();
            while (nouveau_niveau != 1 && nouveau_niveau !=2){
                printf("Vous ne pouvez saisir que 1 pour License ou 2 pour Master. Veuillez saisir");
                nouveau_niveau=saisie_entier();
            }
            if (!confirmer_modification()) {
                printf("Modification annulée.\n\n");
                return;
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

    printf("\nClasse modifiée avec succes.\n");
}

int afficher_matiere_classe(){

    char ligne[100];
    int ref, code_recherche=0;
    int trouve = 0;
    char lignes[100];
    char libe[15];
    int refe, co;

    printf("Veuillez saisir le code de la classe dont vous voulez afficher les matières: ");
    code_recherche=saisie_entier();
    while (!(code_existe(code_recherche)) && code_recherche != -1  ){
        printf("Il n'y a pas de classe avec ce code. Veuillez ressaisir le code ou -1 pour annuler: ");
        code_recherche=saisie_entier();
    }


    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe == NULL){
        printf("le fichier n'a pas pu être ouvert");
        fclose(fichier_classe);
        exit(1);
    }
    int code;
    char nom[30], niveau[10];
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if(code_recherche == code){
        printf("Voici les matières de la classe : %s\n", nom);
        break;
        }
    }
    fclose(fichier_classe);

    printf("\t+-------------+-----------------+-------------+\n");
    printf("\t| Référence   |     Libellé     | Coefficient |\n");
    printf("\t+-------------+-----------------+-------------+\n");
    FILE *fichier = fopen("matiere-classe.csv", "r");
    
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (sscanf(ligne, "%d;%d", &ref, &code) == 2) {
           if (code == code_recherche){
                FILE *file = fopen("matiere.csv", "r");
                if (file != NULL) {
                        while (fgets(lignes, sizeof(lignes), file)) {
                            if (sscanf(lignes, "%d;%29[^;];%d", &refe, libe, &co) == 3){
                                if (ref == refe){
                                printf("\t| %-11d | %-15s | %-11d |\n", refe,libe, co);
                                printf("\t+-------------+-----------------+-------------+\n");
                                    }
                            }
                        }
                    

                    
                    
                } else {
                    printf("Le fichier n'a pas pu être ouvert");
                    fclose(file);
                    fclose(fichier);
                    return 1;
                }
                fclose(file);
           }
        }
    }
    
    fclose(fichier);
}

int afficher_classe_matiere(){

    char ligne[100];
    int ref, ref_cherche=0;
    int trouve = 0;
    char lignes[100];
    char nom[15], niv[15];
    int cod, code;

    printf("Veuillez saisir la référence de la matière dont vous voulez afficher les classes associées: ");
    ref_cherche=saisie_entier();
    while (!(reference_existe(ref_cherche)) && ref_cherche != -1  ){
        printf("Il n'y a pas de matière avec cette référence. Veuillez ressaisir la référence ou -1 pour annuler: ");
        ref_cherche=saisie_entier();
    }


    FILE *fichier_matiere = fopen("matiere.csv", "r");
    if (fichier_matiere == NULL){
        printf("le fichier n'a pas pu être ouvert");
        fclose(fichier_matiere);
        exit(1);
    }
    int reference, coef;
    char libelle[30];
    while (fscanf(fichier_matiere, "%d;%29[^;];%29[^\n]\n", &reference, libelle, &coef) == 3){
        if(ref_cherche == reference){
        printf("Voici les classes faisant la matière : %s\n", libelle);
        break;
        }
    }
    fclose(fichier_matiere);

    printf("\t+-------------+-----------------+-------------+\n");
    printf("\t|    Code     |       Nom       |   Niveau    |\n");
    printf("\t+-------------+-----------------+-------------+\n");
    FILE *fichier = fopen("matiere-classe.csv", "r");
    FILE *file = fopen("classe.csv", "r");
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (sscanf(ligne, "%d;%d", &ref, &code) == 2) {
            if (ref == ref_cherche){
                
                if (file != NULL) {
                        while (fgets(lignes, sizeof(lignes), file)) {
                            if (sscanf(lignes, "%d;%29[^;];%s", &cod, nom, &niv) == 3){
                                if (code == cod){
                                printf("\t| %-11d | %-15s | %-11s |\n", cod,nom, niv);
                                printf("\t+-------------+-----------------+-------------+\n");}
                                }
                            }
                        }
                

                
                fclose(file);
            } 
            else {
                printf("Le fichier n'a pas pu être ouvert");
                fclose(file);
                return 1;
            }

        }
    }


}

void matiere_classe(){
    int choix;
    do
    {
        system("cls");
        printf("Quelle action voulez vous effectuer ?\n\n");
        printf("1. Ajouter une matière à une classe\n");
        printf("2. Retirer une matière à une classe\n");
        printf("3. Afficher les classes associées à une matiere\n");
        printf("4. Afficher les matières d'une classe\n");
        printf("0. Menu précédent\n");

        printf("Renseignez votre choix : ");
        choix = saisie_entier();

        int code,ref,existe;
        char ligne[20];
        
        switch (choix)
        {
        case 1 :
            system("cls");
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
                printf("L'operation à été annulé.");
                system("pause");
                break;
            }

            printf("Entrez le code de la classe a laquelle vous voulez ajouter la matière : ");
            code = saisie_entier();
            existe = code_existe(code);
            while(existe == 0){
                printf("Ce code n'existe pas. Entrez un code valide ou entrez -1 pour annuler l'operation : ");
                code = saisie_entier();
                if (code == -1) break;
                existe= code_existe(code);
            }
            
            if (code == -1){
                printf("L'operation à été annulé.");
                system("pause");
                break;
            }
            ajouter_matiere_classe(ref,code);
            system("pause");
            break;
        
        case 2 :
            system("cls");
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
                printf("L'operation à été annulé.");
                system("pause");
                break;
            }

            printf("Entrez le code de la classe a laquelle vous voulez retirer la matière : ");
            code = saisie_entier();
            existe = code_existe(code);
            while(existe == 0){
                printf("Ce code n'existe pas. Entrez un code valide ou entrez -1 pour annuler l'operation : ");
                code = saisie_entier();
                if (code == -1) break;
                existe= code_existe(code);
            }

            if (code == -1){
                printf("L'operation à été annulé.");
                system("pause");
                break;
            }
            retirer_matiere_classe(ref,code);
            system("pause");
            break;
        
        case 3 :
            system("cls");
            afficher_classe_matiere();
            system("pause");
            break;

        case 4 :
            system("cls");
            afficher_matiere_classe();
            system("pause");
            break;

        default:
            break;
        }

    } while (choix!=0);
    
}