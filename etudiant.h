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
void modif_num_Etudiant(int numero);
void modif_nom_Etudiant(int numero);
void modif_prenom_Etudiant(int numero);
void modif_mail_Etudiant(int numero);
void modif_Date_Etudiant(int numero);
void modif_classe_Etudiant(int numero);
void modifier_Etudiant(int numero);
void menuModifier_Etudiant(int numero);


int chargerEtudiants(Etudiant tab[], int max);
int sauvegarderEtudiants(Etudiant tab[], int n);

#endif
