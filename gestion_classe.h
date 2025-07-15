#ifndef gestion_classe_H
#define gestion_classe_H

typedef enum{
    License,
    Master
} NIVEAU;

typedef struct {
    int code;
    char nom[30];
    NIVEAU niveau;
} CLASSE;

int ajout_classe();
int code_existe(int x);
void afficher_classe();
void menuClasse();
void modifier_classe(int code_a_modifier);
void supprimer_classe(int code_a_supprimer);
void matiere_classe();
int rech_code_classe(int x);
int rech_nom_classe(char *x);
int rech_niveau_classe(char *x);
void menuRecherche_Classe();
void afficher_liste_eleve_classe();
int afficher_classe_matiere();




#endif 
