#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"

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
    scanf("%d", &e.numero);
    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == e.numero) {
            printf("Ce numéro existe déjà.\n");
            return;
        }
    }

    printf("Nom : ");
    scanf("%s", e.nom);
    printf("Prénom : ");
    scanf("%s", e.prenom);
    printf("Email : ");
    scanf("%s", e.email);
    printf("Date de naissance (JJ MM AAAA) : ");
    scanf("%d %d %d", &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee);
    printf("Code classe : ");
    scanf("%d", &e.codeClasse);

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
    scanf("%d", &numero);
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
    scanf("%d", &numero);
    int i;

    for (i = 0; i < n; i++) {
        if (tab[i].numero == numero) {
            printf("Nouvelle information pour l'étudiant %d :\n", numero);
            printf("Nom : ");
            scanf("%s", tab[i].nom);
            printf("Prénom : ");
            scanf("%s", tab[i].prenom);
            printf("Email : ");
            scanf("%s", tab[i].email);
            printf("Date de naissance (JJ MM AAAA) : ");
            scanf("%d %d %d",
                  &tab[i].date_naissance.jour,
                  &tab[i].date_naissance.mois,
                  &tab[i].date_naissance.annee);
            printf("Code classe : ");
            scanf("%d", &tab[i].codeClasse);

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
    scanf("%d", &numero);
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
