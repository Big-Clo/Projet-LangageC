#include <stdio.h>
#include "gestion_note.h"
#include "etudiant.h"




int numero_existe(int x){
    char ligne[200];
    char nom[30], prenom[30], email[50], date_str[15];
    int numero, codeClasse;
    Date date_naissance;

    FILE *fichier_etudiants = fopen("etudiants.csv", "r");
    if (fichier_etudiants == NULL){
        printf("Erreur : impossible d’ouvrir etudiants.csv\n");
        return 0;
    }

    while (fgets(ligne, sizeof(ligne), fichier_etudiants)) {
        
        if (sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%d", &numero, nom, prenom, email, date_str, &codeClasse) == 6) {
            
            sscanf(date_str, "%d/%d/%d", &date_naissance.jour, &date_naissance.mois, &date_naissance.annee);

            if (x == numero) {
                fclose(fichier_etudiants);
                return 1;
            }
        }
    }

    fclose(fichier_etudiants);
    return 0;
}

int reference_existe(int x) {
    char ligne[100];
    char libelle[30];
    int reference, coefficient;

    FILE *fichier_matiere = fopen("matiere.csv", "r");
    if (fichier_matiere == NULL) {
        printf("Erreur : impossible d’ouvrir matiere.csv\n");
        return 0;
    }
    while (fgets(ligne, sizeof(ligne), fichier_matiere)) {
        if (sscanf(ligne, "%d;%[^;];%d", &reference, libelle, &coefficient) == 3) {
            if (x == reference) {
                fclose(fichier_matiere);
                return 1;
            }
        }
    }
    fclose(fichier_matiere);
    return 0;
}



int ajout_note(){
    NOTE note;
    printf("Veuillez saisir le numero de l'etudiant: ");
    scanf("%d", &note.numero);
    if (!numero_existe(note.numero)){
        printf("Il n'existe pas d'etudiant avec ce numero");
        return 1;
    }
    printf("Veuillez saisir la reference de la matiere: ");
    scanf ("%d", &note.reference);
    if (!reference_existe(note.reference)){
        printf("Il n'existe pas de matiere avec cette reference");
        return 1;
    }
    printf("Veuillez saisir la note de cc ");
    scanf ("%d", &note.noteCC);
    printf("Veuillez saisir la note de ds ");
    scanf ("%d", &note.noteDS);

    FILE *fichier_note = fopen("note.csv", "a");
    if (fichier_note == NULL){
        printf("le fichier n' a pas pu etre ouvert");
       
        return 1;
    }
    fprintf(fichier_note, "%d - %d - %d - %d\n", note.numero, note.reference, note.noteCC, note.noteDS);

    fclose(fichier_note);
    return 0;
}