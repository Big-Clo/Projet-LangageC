#ifndef gestion_note_H
#define gestion_note_H

typedef struct{
    int numero;
    int reference;
    int noteCC;
    int noteDS;
}NOTE;


int ajout_note();
int numero_existe(int x);
int reference_existe(int x);
void menuNotes();
int modifier_note();
int recherche_note_eleve_matiere();
int recherche_note_eleve();
int supprimer_note();
int recherche_note_matiere();




#endif