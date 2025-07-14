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

void rechercherEtudiant() {
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
        printf("Aucun étudiant avec ce numéro.\n");
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
