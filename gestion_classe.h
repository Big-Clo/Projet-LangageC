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
#endif 
