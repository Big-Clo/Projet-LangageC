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
int recherche_classe(int x);
void modifier_classe(int code_a_modifier);
void supprimer_classe(int code_a_supprimer);






#endif 
