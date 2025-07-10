#ifndef matiere_H
#define matiere_H

typedef struct 
{
    int reference;
    char libelle[15];
    short coefficient;
}matiere;
int reference_existe(int x);
int ajout_matiere();
int lister_matiere();
char* chercher(int a,char *trouve);
int supprimer_matiere(char line_sup[100]);
int rech_ref(int a);
int rech_lib(char a[15]);
int rech_coef(int a);
void menuRecherche_matiere();
int chercher_matiere();
void menuMatiere();
int modifier_matiere(char line_modif[100]);

#endif
