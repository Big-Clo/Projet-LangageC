#ifndef ETUDIANT_H
#define ETUDIANT_H

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    int numero;
    char nom[30];
    char prenom[30];
    char email[50];
    Date date_naissance;
    int codeClasse;
} Etudiant;

void ajouterEtudiant();
void modifierEtudiant();
void supprimerEtudiant();
void rechercherEtudiant();
void afficherListeEtudiants();

int chargerEtudiants(Etudiant tab[], int max);
int sauvegarderEtudiants(Etudiant tab[], int n);

#endif
