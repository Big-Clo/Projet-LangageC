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
        if (tab[i].numero == e.numero) {
            printf("Ce numéro existe déjà.\n");
            return;
        }
    }

    printf("Nom : ");
    saisie_ligne(e.nom,sizeof(e.nom));
    printf("Prénom : ");
    saisie_ligne(e.prenom,sizeof(e.prenom));
    printf("Email : ");
    saisie_ligne(e.email,sizeof(e.email));
    printf("Date de naissance (JJ MM AAAA) : ");
    e.date_naissance.jour=saisie_entier();e.date_naissance.mois=saisie_entier();e.date_naissance.annee=saisie_entier();
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

    printf("\n=== Liste des étudiants (%d) ===\n", n);
    for (i = 0; i < n; i++) {
        printf("%d - %s %s | Email: %s | Né le %02d/%02d/%04d | Classe: %d\n",
               tab[i].numero,
               tab[i].prenom,
               tab[i].nom,
               tab[i].email,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee,
               tab[i].codeClasse);
    }
}

void rech_num_etudiant() {
    int numero, trouve = 0;
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le numéro de l'étudiant à rechercher : ");
    numero=saisie_entier();
    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
            printf("Étudiant trouvé :\n");
            printf("%d - %s %s | Email: %s | Né le %02d/%02d/%04d | Classe: %d\n",
                   tab[i].numero,
                   tab[i].prenom,
                   tab[i].nom,
                   tab[i].email,
                   tab[i].date_naissance.jour,
                   tab[i].date_naissance.mois,
                   tab[i].date_naissance.annee,
                   tab[i].codeClasse);
            trouve = 1;
            break;
        }
    }

    if (!trouve)
        printf("Aucun\n");
}

void rech_prenom_etudiant() {
    int trouve = 0;
    char prenom[30];
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le prénom à rechercher : ");
    saisie_ligne(prenom,30);
    int i;
    
    printf("Étudiants trouvés :\n");
    for (i = 0; i < n; i++) {
        if (strcmp(tab[i].prenom, prenom) == 0) {
            printf("%d - %s %s | Email: %s | Né le %02d/%02d/%04d | Classe: %d\n",
                   tab[i].numero,
                   tab[i].prenom,
                   tab[i].nom,
                   tab[i].email,
                   tab[i].date_naissance.jour,
                   tab[i].date_naissance.mois,
                   tab[i].date_naissance.annee,
                   tab[i].codeClasse);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun\n");
}

void rech_nom_etudiant() {
    int trouve = 0;
    char nom[30];
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le nom à rechercher : ");
    saisie_ligne(nom,30);
    int i;

    printf("Étudiants trouvés :\n");
    for (i = 0; i < n; i++) {
        if (strcmp(tab[i].nom,nom)==0) {
            printf("%d - %s %s | Email: %s | Né le %02d/%02d/%04d | Classe: %d\n",
                   tab[i].numero,
                   tab[i].prenom,
                   tab[i].nom,
                   tab[i].email,
                   tab[i].date_naissance.jour,
                   tab[i].date_naissance.mois,
                   tab[i].date_naissance.annee,
                   tab[i].codeClasse);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun\n");
}

void rech_mail_etudiant() {
    int trouve = 0;
    char mail[50];
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le mail à rechercher : ");
    saisie_ligne(mail,50);
    int i;

    printf("Étudiant trouvé :\n");
    for (i = 0; i < n; i++) {
        if (strcmp(tab[i].email,mail)==0) {
            printf("%d - %s %s | Email: %s | Né le %02d/%02d/%04d | Classe: %d\n",
                   tab[i].numero,
                   tab[i].prenom,
                   tab[i].nom,
                   tab[i].email,
                   tab[i].date_naissance.jour,
                   tab[i].date_naissance.mois,
                   tab[i].date_naissance.annee,
                   tab[i].codeClasse);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun\n");
}

void rech_classe_etudiant() {
    int Classe, trouve = 0;
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le code de la classe à rechercher : ");
    Classe=saisie_entier();
    int i;

    printf("Étudiants trouvés :\n");
    for (i = 0; i < n; i++) {
        if (tab[i].codeClasse == Classe) {
            printf("%d - %s %s | Email: %s | Né le %02d/%02d/%04d | Classe: %d\n",
                   tab[i].numero,
                   tab[i].prenom,
                   tab[i].nom,
                   tab[i].email,
                   tab[i].date_naissance.jour,
                   tab[i].date_naissance.mois,
                   tab[i].date_naissance.annee,
                   tab[i].codeClasse);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun\n");
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
    printf("Annee : ");
    date.annee=saisie_entier();
    int i;

    printf("Étudiant trouvé :\n");
    for (i = 0; i < n; i++) {
        if (tab[i].date_naissance.jour == date.jour && tab[i].date_naissance.mois == date.mois &&tab[i].date_naissance.annee == date.annee  ) {
            printf("%d - %s %s | Email: %s | Né le %02d/%02d/%04d | Classe: %d\n",
                   tab[i].numero,
                   tab[i].prenom,
                   tab[i].nom,
                   tab[i].email,
                   tab[i].date_naissance.jour,
                   tab[i].date_naissance.mois,
                   tab[i].date_naissance.annee,
                   tab[i].codeClasse);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun\n");
}

void menuRecherche_Etudiant(){
    
    int choix;
    do
    {   
        system("cls");
        printf("A partir de quel element voulez vous faire une recherche ? \n");
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

void modifierEtudiant() {
    int numero;
    Etudiant tab[100];
    int n = chargerEtudiants(tab, 100);

    printf("Entrez le numéro de l'étudiant à modifier : ");
    numero=saisie_entier();
    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
            printf("Nouvelle information pour l'étudiant %d :\n", numero);
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

            if (sauvegarderEtudiants(tab, n))
                printf("Étudiant modifié avec succès.\n");
            else
                printf("Erreur de sauvegarde.\n");
            return;
        }
    }

    printf("Étudiant non trouvé.\n");
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
