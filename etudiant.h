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
void rech_num_etudiant();
void rech_prenom_etudiant();
void rech_nom_etudiant();
void rech_mail_etudiant();
void rech_date_etudiant();
void rech_classe_etudiant();
void menuRecherche_Etudiant();
void afficherListeEtudiants();
void menuEtudiant();

int chargerEtudiants(Etudiant tab[], int max);
int sauvegarderEtudiants(Etudiant tab[], int n);

#endif
