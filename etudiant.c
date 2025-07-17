#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"
#include "general.h"

int chargerEtudiants(Etudiant tab[], int max) {
    FILE *f = fopen("etudiants.csv", "r");
    if (!f) return 0;
    int i = 0;
    while (i < max && fscanf(f, "%d;%29[^;];%29[^;];%49[^;];%d/%d/%d;%d\n",
           &tab[i].numero,
           tab[i].nom,
           tab[i].prenom,
           tab[i].email,
           &tab[i].date_naissance.jour,
           &tab[i].date_naissance.mois,
           &tab[i].date_naissance.annee,
           &tab[i].codeClasse) == 8) {
        i++;
    }
    fclose(f);
    return i;
}

int sauvegarderEtudiants(Etudiant tab[], int n) {
    FILE *f = fopen("etudiants.csv", "w");
    if (!f) return 0;

    int i;

    for (i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%s;%s;%02d/%02d/%04d;%d\n",
                tab[i].numero,
                tab[i].nom,
                tab[i].prenom,
                tab[i].email,
                tab[i].date_naissance.jour,
                tab[i].date_naissance.mois,
                tab[i].date_naissance.annee,
                tab[i].codeClasse);
    }
    fclose(f);
    return 1;
}

void ajouterEtudiant() {
    Etudiant e;
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Numéro étudiant : ");
    e.numero=saisie_entier();
    int i;

    for (i = 0; i < n; i++) {
        while (tab[i].numero == e.numero) {
            printf("Ce numéro existe déjà. Veuillez saisir un autre numéro ou -1 pour quitter\n");
            e.numero=saisie_entier();
            if(e.numero == -1){
                printf("\tAnnulation\n");
                return;
            }
        }
    }

    printf("Nom : ");
    saisie_ligne(e.nom,sizeof(e.nom));
    printf("Prénom : ");
    saisie_ligne(e.prenom,sizeof(e.prenom));
    printf("Email : ");
    saisie_ligne(e.email,sizeof(e.email));
    printf("Jour de naissance  : ");
    e.date_naissance.jour=saisie_entier();
    while((e.date_naissance.jour > 31) || (e.date_naissance.jour < 0)){
        printf("Le jour ne peut pas etre negatif ou superieur a 31. Veuillez ressaisir le jour de naissance: ");
        e.date_naissance.jour=saisie_entier();
    }
    printf("Mois de naissance  : ");
    e.date_naissance.mois=saisie_entier();
    while((e.date_naissance.mois > 31) || (e.date_naissance.mois < 0)){
        printf("Le mois ne peut pas etre negatif ou superieur 12. Veuillez ressaisir le mois de naissance: ");
        e.date_naissance.mois=saisie_entier();
    }
    printf("Annee de naissance  : ");
    printf("Année de naissance  : ");
    e.date_naissance.annee=saisie_entier();
    printf("Code classe : ");
    e.codeClasse=saisie_entier();

    tab[n++] = e;
    if (sauvegarderEtudiants(tab, n))
        printf("Étudiant ajouté avec succès.\n");
    else
        printf("Erreur de sauvegarde.\n");
}

void afficherListeEtudiants() {
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);
    if (n == 0) {
        printf("Aucun étudiant trouvé.\n");
        return;
    }
    int i;

    printf("\n\t\t\t\t\t     ====== Liste des étudiants (%d) ======\n", n);
    printf("\t----------------------------------------------------------------------------------------------------------------\n");
    printf("\t+------------+--------------+------------------+-----------------+-------------------------+-----------------------+\n");
    printf("\t|   Numéro   |     Nom      |     Prénom       |     Classe      |          Email          |   Date de naissance   |\n");
    printf("\t+------------+--------------+------------------+-----------------+-------------------------+-----------------------+\n");

    int code, nom, niveau;

    for (i = 0; i < n; i++) {
        FILE *fichier_classe = fopen("classe.csv", "r");
        if (fichier_classe == NULL){
            printf("le fichier n'a pas pu être ouvert");
            exit(1);
        }
        int code;
        char nom[30], niveau[10];
        while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
            if(tab[i].codeClasse == code){;
            fclose (fichier_classe);
            break;
            }
        }
        printf("\t| %-10d | %-11s  | %-15s  | %-14s  | %-23s |       %02d/%02d/%0004d      |\n",
               tab[i].numero,
               tab[i].nom,
               tab[i].prenom,
               nom,
               tab[i].email,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee);
    }
    printf("\t+------------+--------------+------------------+-----------------+-------------------------+-----------------------+\n");
    printf("\n");
}

void rech_num_etudiant() {
    int numero, trouve = 0;
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le numéro de l'étudiant à rechercher : ");
    numero=saisie_entier();
    int i;

    for (i = 0; i < n; i++){if (numero==tab[i].numero)
    {trouve=1;}}

    if (!trouve)
            {printf("Aucun étudiant né correspond à ce numéro\n");return;}

    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
    printf("\t|   Numéro   |     Nom      | Prénom       |     Classe      |          Email          |   Date de naissance   |\n");
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");   
    for (i = 0; i < n; i++) {
        FILE *fichier_classe = fopen("classe.csv", "r");
        if (fichier_classe == NULL){
            printf("le fichier n'a pas pu être ouvert");
            exit(1);
        }
        int code;
        char nom[30], niveau[10];
        while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
            if(tab[i].codeClasse == code){;
            fclose (fichier_classe);
            break;
            }
        }if(numero==tab[i].numero){
        printf("\t| %-10d | %-11s  | %-11s  | %-14s  | %-23s |       %02d/%02d/%0004d      |\n",
               tab[i].numero,
               tab[i].nom,
               tab[i].prenom,
               nom,
               tab[i].email,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee);}
    }
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
    
}

void rech_prenom_etudiant() {
    int trouve = 0;
    char prenom[30];
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le prénom à rechercher : ");
    saisie_ligne(prenom,30);
    int i;
    
    for (i = 0; i < n; i++){if (strcmp(prenom,tab[i].prenom)==0)
    {trouve=1;}}

    if (!trouve)
            {printf("Aucun étudiant ne correspond à ce prénom\n");return;}

    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
    printf("\t|   Numéro   |     Nom      | Prénom       |     Classe      |          Email          |   Date de naissance   |\n");
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");   
    for (i = 0; i < n; i++) {
        FILE *fichier_classe = fopen("classe.csv", "r");
        if (fichier_classe == NULL){
            printf("le fichier n'a pas pu être ouvert");
            exit(1);
        }
        int code;
        char nom[30], niveau[10];
        while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
            if(tab[i].codeClasse == code){;
            fclose (fichier_classe);
            break;
            }
        }if(strcmp(prenom,tab[i].prenom)==0){
        printf("\t| %-10d | %-11s  | %-11s  | %-14s  | %-23s |       %02d/%02d/%0004d      |\n",
               tab[i].numero,
               tab[i].nom,
               tab[i].prenom,
               nom,
               tab[i].email,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee);}
    }
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
}

void rech_nom_etudiant() {
    int trouve = 0;
    char nom[30];
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le nom à rechercher : ");
    saisie_ligne(nom,30);
    int i;

    for (i = 0; i < n; i++){if (strcmp(nom,tab[i].nom)==0)
    {trouve=1;}}

    if (!trouve)
            {printf("Aucun étudiant ne correspond à ce nom\n");return;}

    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
    printf("\t|   Numéro   |     Nom      | Prénom       |     Classe      |          Email          |   Date de naissance   |\n");
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");   
    for (i = 0; i < n; i++) {
        FILE *fichier_classe = fopen("classe.csv", "r");
        if (fichier_classe == NULL){
            printf("le fichier n'a pas pu être ouvert");
            exit(1);
        }
        int code;
        char nomc[30], niveau[10];
        while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nomc, niveau) == 3){
            if(tab[i].codeClasse == code){;
            fclose (fichier_classe);
            break;
            }
        }if(strcmp(nom,tab[i].nom)==0){
        printf("\t| %-10d | %-11s  | %-11s  | %-14s  | %-23s |       %02d/%02d/%0004d      |\n",
               tab[i].numero,
               tab[i].nom,
               tab[i].prenom,
               nomc,
               tab[i].email,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee);}
    }
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
}

void rech_mail_etudiant() {
    int trouve = 0;
    char mail[50];
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le mail à rechercher : ");
    saisie_ligne(mail,50);
    int i;

    for (i = 0; i < n; i++){if (strcmp(mail,tab[i].email)==0)
    {trouve=1;}}

    if (!trouve)
            {printf("Aucun étudiant ne correspond à ce mail\n");return;}

    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
    printf("\t|   Numéro   |     Nom      | Prénom       |     Classe      |          Email          |   Date de naissance   |\n");
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");   
    for (i = 0; i < n; i++) {
        FILE *fichier_classe = fopen("classe.csv", "r");
        if (fichier_classe == NULL){
            printf("le fichier n'a pas pu être ouvert");
            exit(1);
        }
        int code;
        char nom[30], niveau[10];
        while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
            if(tab[i].codeClasse == code){;
            fclose (fichier_classe);
            break;
            }
        }if(strcmp(mail,tab[i].email)==0){
        printf("\t| %-10d | %-11s  | %-11s  | %-14s  | %-23s |       %02d/%02d/%0004d      |\n",
               tab[i].numero,
               tab[i].nom,
               tab[i].prenom,
               nom,
               tab[i].email,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee);}
    }
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
}

void rech_classe_etudiant() {
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100), trouve = 0;
    char classe[30]; 
    int codeRecherche = -1;
    char nom[30], niveau[10];

    printf("Entrez le nom de la classe à rechercher : ");
    saisie_ligne(classe, 30);
    Maj(classe);

    FILE *fichier_classe = fopen("classe.csv", "r");
    if (fichier_classe == NULL) {
        printf("Le fichier classe.csv n'a pas pu être ouvert\n");
        return;
    }

    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &codeRecherche, nom, niveau) == 3) {
        Maj(nom);
        if (strcmp(classe, nom) == 0) {
            break;
        }
        codeRecherche = -1;
    }
    fclose(fichier_classe);

    if (codeRecherche == -1) {
        printf("Classe non trouvée\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (tab[i].codeClasse == codeRecherche) {
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Aucun étudiant n'est dans cette classe\n");
        return;
    }

    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
    printf("\t|   Numéro   |     Nom      | Prénom       |     Classe      |          Email          |   Date de naissance   |\n");
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");

    for (int i = 0; i < n; i++) {
        if (tab[i].codeClasse == codeRecherche) {
            printf("\t| %-10d | %-11s  | %-11s  | %-14s  | %-23s |       %02d/%02d/%0004d      |\n",
                   tab[i].numero,
                   tab[i].nom,
                   tab[i].prenom,
                   classe,
                   tab[i].email,
                   tab[i].date_naissance.jour,
                   tab[i].date_naissance.mois,
                   tab[i].date_naissance.annee);
        }
    }

    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
}

void rech_date_etudiant() {
    int trouve = 0;
    Etudiant tab[100];
    Date date;
    int n = chargerEtudiants(tab, 100);

    printf("Jour : ");
    date.jour=saisie_entier();
    printf("Mois : ");
    date.mois=saisie_entier();
    printf("Année : ");
    date.annee=saisie_entier();
    int i;

    for (i = 0; i < n; i++){if (tab[i].date_naissance.jour == date.jour && tab[i].date_naissance.mois == date.mois && tab[i].date_naissance.annee == date.annee)
    {trouve=1;}}

    if (!trouve)
            {printf("Aucun étudiant né correspond à ce numéro\n");return;}

    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
    printf("\t|   Numéro   |     Nom      | Prénom       |     Classe      |          Email          |   Date de naissance   |\n");
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");   
    for (i = 0; i < n; i++) {
        FILE *fichier_classe = fopen("classe.csv", "r");
        if (fichier_classe == NULL){
            printf("le fichier n'a pas pu être ouvert");
            exit(1);
        }
        int code;
        char nom[30], niveau[10];
        while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
            if(tab[i].codeClasse == code){;
            fclose (fichier_classe);
            break;
            }
        }if(tab[i].date_naissance.jour == date.jour && tab[i].date_naissance.mois == date.mois && tab[i].date_naissance.annee == date.annee){
        printf("\t| %-10d | %-11s  | %-11s  | %-14s  | %-23s |       %02d/%02d/%0004d      |\n",
               tab[i].numero,
               tab[i].nom,
               tab[i].prenom,
               nom,
               tab[i].email,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee);}
    }
    printf("\t+------------+--------------+--------------+-----------------+-------------------------+-----------------------+\n");
}

void menuRecherche_Etudiant(){
    
    int choix;
    do
    {   
        system("cls");
        printf("A partir de quel element voulez vous faire une recherche ? \n\n");
        printf("1. Numéro\n");
        printf("2. Nom\n");
        printf("3. Prénom\n");
        printf("4. Email\n");
        printf("5. Date de naissance\n");
        printf("6. Classe\n");
        printf("0. Annuler\n\n");
        printf("Veuillez renseigner votre choix : ");

        choix=saisie_entier();

        switch (choix)
        {
        case 1:
            system("cls");
            rech_num_etudiant();
            printf("\n\n");
            system("pause");
            break;

        case 2:
            system("cls");
            rech_nom_etudiant();
            printf("\n\n");
            system("pause");
            break;

        case 3:
            system("cls");
            rech_prenom_etudiant();
            printf("\n\n");
            system("pause");
            break;

        case 4:
            system("cls");
            rech_mail_etudiant();
            printf("\n\n");
            system("pause");
            break;

        case 5:
            system("cls");
            printf("Entrez la date à rechercher :\n\n");
            rech_date_etudiant();
            printf("\n\n");
            system("pause");
            break;

        case 6:
            system("cls");
            rech_classe_etudiant();
            printf("\n\n");
            system("pause");
            break;

        case 0:
            printf("\nMenu précédent");
            printf("\n\n");
            system("pause");
            break;
        
        default:
            printf("\nVeuillez entrer une option valide.\n\n");
            system("pause");
            break;
        }
    } while (choix!=0);
}

void supprimerEtudiant() {
    int numero, index = -1;
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le numéro de l'étudiant à supprimer : ");
    numero=saisie_entier();
    int i;
    
    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Étudiant non trouvé.\n");
        return;
    }

    for (i = index; i < n - 1; i++)
        tab[i] = tab[i + 1];

    if (sauvegarderEtudiants(tab, n - 1))
        printf("Étudiant supprimé avec succès.\n");
    else
        printf("Erreur de sauvegarde.\n");
}

void modif_num_Etudiant(int numero) {
    int num;
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
        printf("Voici l'ancien numéro : %d\n\n",numero);
        printf("Veuillez saisir le nouveau numéro : ");
        num=saisie_entier();
        int j;
        for (j = 0; j < n; j++) {
        if (tab[j].numero == num) {
            printf("Ce numéro existe déjà.\n\n");
            return;
            }
        }

        if (!confirmer_modification()) {
            printf("Modification annulée.\n\n");
            return;
        }


        tab[i].numero=num;

        if (sauvegarderEtudiants(tab, n))
            printf("Étudiant modifié avec succès.\n\n");
        else
            printf("Erreur de sauvegarde.\n\n");
        return;
        }
    }

    printf("Étudiant non trouvé.\n\n");
}

void modif_nom_Etudiant(int numero) {
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
            printf("Voici l'ancien nom : %s\n\n",tab[i].nom);
            printf("Veuillez saisir le nouveau nom : ");
            saisie_ligne(tab[i].nom,sizeof(tab[i].nom));

            if (!confirmer_modification()) {
            printf("Modification annulée.\n\n");
                return;
            }


            if (sauvegarderEtudiants(tab, n))
                printf("Étudiant modifié avec succès.\n\n");
            else
                printf("Erreur de sauvegarde.\n\n");
            return;
        }
    }

    printf("Étudiant non trouvé.\n\n");
}

void modif_prenom_Etudiant(int numero) {
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {

            printf("Voici l'ancien prénom : %s\n\n",tab[i].prenom);
            printf("Veuillez saisir le nouveau prénom : ");
            saisie_ligne(tab[i].prenom,sizeof(tab[i].prenom));
            
            if (!confirmer_modification()) {
            printf("Modification annulée.\n\n");
                return;
            }


            if (sauvegarderEtudiants(tab, n))
                printf("Étudiant modifié avec succès.\n\n");
            else
                printf("Erreur de sauvegarde.\n\n");
            return;
        }
    }

    printf("Étudiant non trouvé.\n\n");
}

void modif_mail_Etudiant(int numero) {
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
            printf("Voici l'ancien mail : %s\n\n",tab[i].email);
            printf("Veuillez saisir le nouvel Email : ");
            saisie_ligne(tab[i].email,sizeof(tab[i].email));

            if (!confirmer_modification()) {
            printf("Modification annulée.\n\n");
                return;
            }


            if (sauvegarderEtudiants(tab, n))
                printf("Étudiant modifié avec succès.\n\n");
            else
                printf("Erreur de sauvegarde.\n\n");
            return;
        }
    }

    printf("Étudiant non trouvé.\n\n");
}

void modif_Date_Etudiant(int numero) {
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
            printf("Voici l'ancienne date de naissance : %d/%d/%d\n\n",tab[i].date_naissance.jour,tab[i].date_naissance.mois,tab[i].date_naissance.annee);
            printf("Veuillez saisir la nouvelle date de naissance \n\n");
            printf("Jour : ");tab[i].date_naissance.jour=saisie_entier();
            printf("Mois : ");tab[i].date_naissance.mois=saisie_entier();
            printf("Année : ");tab[i].date_naissance.annee=saisie_entier();

            if (!confirmer_modification()) {
                printf("Modification annulée.\n\n");
                return;
            }

            
            if (sauvegarderEtudiants(tab, n))
                printf("Étudiant modifié avec succès.\n\n");
            else
                printf("Erreur de sauvegarde.\n\n");
            return;
        }
    }

    printf("Étudiant non trouvé.\n\n");
}

void modif_classe_Etudiant(int numero) {
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {

            FILE *fichier_classe = fopen("classe.csv", "r");
            if (fichier_classe == NULL){
                printf("le fichier n'a pas pu être ouvert");
                exit(1);
            }
            int code;
            char nom[30], niveau[10];
            while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
                if(tab[i].codeClasse == code){;
                fclose (fichier_classe);
                break;
                }
            }
            printf("Voici l'ancienne classe de l'élève : %s\n\n",nom);
            printf("Veuillez saisir le code de la nouvelle classe : ");
            tab[i].codeClasse=saisie_entier();

            if (!confirmer_modification()) {
                printf("Modification annulée.\n\n");
                return;
            }


            if (sauvegarderEtudiants(tab, n))
                printf("Étudiant modifié avec succès.\n\n");
            else
                printf("Erreur de sauvegarde.\n\n");
            return;
        }
    }

    printf("Étudiant non trouvé.\n\n");
}

void modifier_Etudiant(int numero) {
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
            FILE *fichier_classe = fopen("classe.csv", "r");
            if (fichier_classe == NULL){
                printf("le fichier n'a pas pu être ouvert");
                exit(1);
            }
            int code;
            char nom[30], niveau[10];
            while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
                if(tab[i].codeClasse == code){;
                fclose (fichier_classe);
                break;
                }
            }
            printf("Voici les anciennes informations :\nNuméro : %d - %s %s | Email: %s | Né le %02d/%02d/%04d | Classe: %s\n\n",
               tab[i].numero,
               tab[i].prenom,
               tab[i].nom,
               tab[i].email,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee,
               nom);
            printf("Veuillez saisir les nouvelles information pour l'étudiant %d :\n", numero);
            printf("Nom : ");
            saisie_ligne(tab[i].nom,sizeof(tab[i].nom));
            printf("Prénom : ");
            saisie_ligne(tab[i].prenom,sizeof(tab[i].prenom));
            printf("Email : ");
            saisie_ligne(tab[i].email,sizeof(tab[i].email));
            printf("Date de naissance (JJ MM AAAA) : ");
            tab[i].date_naissance.jour=saisie_entier();
            tab[i].date_naissance.mois=saisie_entier();
            tab[i].date_naissance.annee=saisie_entier();
            printf("Code classe : ");
            tab[i].codeClasse=saisie_entier();

            if (!confirmer_modification()) {
                printf("Modification annulée.\n\n");
                return;
            }


            if (sauvegarderEtudiants(tab, n))
                printf("Étudiant modifié avec succès.\n\n");
            else
                printf("Erreur de sauvegarde.\n\n");
            return;
        }
    }

    printf("Étudiant non trouvé.\n\n");
}

void menuModifier_Etudiant(int numero){
    int choix;
    system("cls");
    printf("Quel element voulez vous modifier ? \n\n");
    printf("1. Numéro\n");
    printf("2. Nom\n");
    printf("3. Prénom\n");
    printf("4. Email\n");
    printf("5. Date de naissance\n");
    printf("6. Classe\n");
    printf("7. Tout\n");
    printf("0. Annuler\n\n");
    printf("Veuillez renseigner votre choix : ");
    printf("\n\n");

    choix=saisie_entier();
    
    switch (choix)
    {
    case 1:
        system("cls");
        modif_num_Etudiant(numero);
        system("pause");
        break;
    case 2:
        system("cls");
        modif_nom_Etudiant(numero);
        system("pause");
        break;
    case 3:
        system("cls");
        modif_prenom_Etudiant(numero);
        system("pause");
        break;
    case 4:
        system("cls");
        modif_mail_Etudiant(numero);
        system("pause");
        break;
    case 5:
        system("cls");
        modif_Date_Etudiant(numero);
        system("pause");
        break;
    case 6:
        system("cls");
        modif_classe_Etudiant(numero);
        system("pause");
        break;
    case 7:
        system("cls");
        modifier_Etudiant(numero);
        system("pause");
        break;
    case 0:
        printf("Menu précédent\n\n");
        system("pause");
        break;
    default:
        printf("Cette option n'est pas prise en charge\n\n");
        system("pause");
        break;
    }
}
