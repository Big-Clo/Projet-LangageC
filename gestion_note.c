#include <stdio.h>
#include <stdlib.h>
#include "gestion_note.h"
#include "etudiant.h"




int numero_existe(int x){
    char ligne[200];
    char nom[30], prenom[30], email[50], date_str[15];
    int numero, codeClasse;
    Date date_naissance;

    FILE *fichier_etudiants= fopen("etudiants.csv", "r");
    if (fichier_etudiants== NULL){
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

int numero_note_existe(int x, int y){
    int numero, reference, noteCC, noteDS;

    FILE *fichier_note= fopen("note.csv", "r");
    if (fichier_note== NULL){
        printf("Erreur : impossible d'ouvrir note.csv\n");
        return 1;
    }

   while (fscanf(fichier_note, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) != -1){
        if ((x == numero) && (y = reference))    {
            fclose(fichier_note);
            return 1;
        }
    }

    fclose(fichier_note);
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
        printf("Il n'existe pas de matiere avec cette reference\n");
        return 1;
    }
    if (numero_note_existe(note.numero, note.reference)){
        printf("Cette eleve a deja des notes dans cette matiere vous pouvez les modifier\n");
        return 1;
    }
    printf("Veuillez saisir la note de CC ");
    scanf ("%d", &note.noteCC);
    while(note.noteCC < 0 || note.noteCC > 20){
        printf("La note doit etre comprise entre 0 et 20. Veuillez ressaisir la note de CC");
        scanf ("%d", &note.noteCC);
    }
    printf("Veuillez saisir la note de DS ");
    scanf ("%d", &note.noteDS);
    while(note.noteDS < 0 || note.noteDS > 20){
        printf("La note doit etre comprise entre 0 et 20. Veuillez ressaisir la note de DS");
        scanf ("%d", &note.noteDS);
    }

    FILE *fichier_note = fopen("note.csv", "a");
    if (fichier_note == NULL){
        printf("le fichier n' a pas pu etre ouvert");
       
        return 1;
    }
    fprintf(fichier_note, "%d;%d;%d;%d\n", note.numero, note.reference, note.noteCC, note.noteDS);

    fclose(fichier_note);
    return 0;
}

int modifier_note() {
    NOTE note;
    int numero, reference, noteCC, noteDS, quitter;

    do {
        printf("Veuillez saisir le numero de l'eleve dont vous voulez modifier les notes: ");
        scanf("%d", &note.numero);
        while (!numero_existe(note.numero) && note.numero != -1) {
            printf("Il n'y a pas d'etudiant avec ce numero. Veuillez ressaisir ou -1 pour annuler :\n");
            scanf("%d", &note.numero);
        }
        if (note.numero == -1) {
            printf("Annulation des modifications\n");
            return 1;
        }

        printf("Veuillez saisir la reference de la matiere : ");
        scanf("%d", &note.reference);
        while (!reference_existe(note.reference) && note.reference != -1) {
            printf("Reference invalide. Ressaisir ou -1 pour annuler :\n");
            scanf("%d", &note.reference);
        }
        if (note.reference == -1) {
            printf("Annulation des modifications\n");
            return 1;
        }

        if (!numero_note_existe(note.numero, note.reference)) {
            printf("Cet eleve n'a pas de note dans cette matiere. 0 pour annuler, 1 pour ressaisir :\n");
            scanf("%d", &quitter);
            while (quitter != 0 && quitter != 1) {
                printf("Choix invalide. Entrez 0 ou 1 :\n");
                scanf("%d", &quitter);
            }
        } else {
            quitter = 0;
        }
    } while ((!numero_note_existe(note.numero, note.reference)) || (quitter == 1));

    FILE *fichier = fopen("note.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fichier == NULL || temp == NULL) {
        printf("Le fichier n'a pas pu être ouvert.\n");
        if (fichier) fclose(fichier);
        if (temp) fclose(temp);
        return 1;
    }

    while (fscanf(fichier, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) != -1) {
        if (note.numero == numero && note.reference == reference) {
            printf("Veuillez saisir la nouvelle note de CC: ");
            scanf("%d", &note.noteCC);
            printf("Veuillez saisir la nouvelle note de DS: ");
            scanf("%d", &note.noteDS);
            fprintf(temp, "%d;%d;%d;%d\n", note.numero, note.reference, note.noteCC, note.noteDS);
        } else {
            fprintf(temp, "%d;%d;%d;%d\n", numero, reference, noteCC, noteDS);
        }
    }

    fclose(fichier);
    fclose(temp);

    remove("note.csv");
    rename("temp.csv", "note.csv");

    

    
    return 0;
}



int recherche_note_eleve_matiere(){



    NOTE note;
    int numero, reference, noteCC, noteDS, quitter;

    quitter = 0;
    do{
        printf("Veuillez saisir le saisir le numero de l' etudiant dont vous chercher la note: ");
        scanf("%d", &note.numero);
        while(!numero_existe(note.numero) && note.numero != -1){
            printf("Il n'y a pas d'etudiant avec ce numero. Veuillez ressaisir le numero de l'etudiant  ou -1 pour annuler la recherche.\n");
            scanf("%d" ,&note.numero);
        }
        if(note.numero == -1){
            printf("Annulation de la recherche");
            
            return 1;
        }


        printf("Veuillez saisir la reference de la matiere dont vous voulez rechercher les notes: ");
        scanf("%d" ,&note.reference);
        while (!reference_existe(note.reference) && note.reference != -1){
            printf("Il n'y a pas de matiere avec ce reference. Veuillez ressaisir la reference de la matiere ou -1 pour annuler la recherche.\n ");
            scanf("%d" ,&note.reference);
        }
        if(note.reference == -1){
            printf("Annulation de la recherche");
            
            return 1;
        }



        if (!numero_note_existe(note.numero, note.reference)){
            printf("Cette eleve n'a pas de notes dans cette matiere. Veuillez entre 0 pour annuler la modification et 1 pour rentrer les informations a nouveaux");
            scanf("%d", &quitter);

        }
        while(quitter != 0 && quitter != 1){
            printf("Choix invalide. Veuillez entre 1 pour annuler la modification et 0 pour rentrer les informations a nouveaux: ");
            scanf("%d", &quitter);
        }
    }while (!(numero_note_existe(note.numero, note.reference)) || (quitter == 1));

    char ligne[200];
    char nom[30], prenom[30], email[50], date_str[15];
    int num, codeClasse;
    Date date_naissance;

    FILE *fichier_etudiants= fopen("etudiants.csv", "r");
    if (fichier_etudiants== NULL){
        printf("Erreur : impossible d’ouvrir etudiants.csv\n");
        
        fclose(fichier_etudiants);
        return 1;
    }

    while (fgets(ligne, sizeof(ligne), fichier_etudiants)) {
        
        if (sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%d", &num, nom, prenom, email, date_str, &codeClasse) == 6) {
            
            sscanf(date_str, "%d/%d/%d", &date_naissance.jour, &date_naissance.mois, &date_naissance.annee);

            if (note.numero == num) {
                fclose(fichier_etudiants);
                
                break;
            }
        }
    }

    fclose(fichier_etudiants);

    char libelle[30];
    int ref, coefficient;

    FILE *fichier_matiere = fopen("matiere.csv", "r");
    if (fichier_matiere == NULL) {
        printf("Erreur : impossible d’ouvrir matiere.csv\n");
        fclose(fichier_matiere);
        return 1;
    }
    while (fgets(ligne, sizeof(ligne), fichier_matiere)) {
        if (sscanf(ligne, "%d;%[^;];%d", &ref, libelle, &coefficient) == 3) {
            if (note.reference == ref) {
                fclose(fichier_matiere);
                
                break;
            }
        }
    }
    fclose(fichier_matiere);
    FILE *fichier = fopen("note.csv", "r");
    if (fichier == NULL) {
        printf("Le fichier n'a pas pu etre ouvert.\n");
        return 1;
    }

    printf("Voici les notes de %s %s en %s\n ", prenom, nom, libelle);

    while (fscanf(fichier, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) != -1) {
        if ((note.numero == numero) && (note.reference == reference)) {
            printf("note CC: %d \t note DS: %d\n", noteCC, noteDS);
            fclose(fichier);
            return 0;
            
        }
        
    }
    fclose(fichier);
    return 1;
}

int recherche_note_eleve(){

    NOTE note;
    int numero, reference, noteCC, noteDS, quitter;

    quitter = 0;
    printf("Veuillez saisir le saisir le numero de l' etudiant dont vous chercher la note: ");
    scanf("%d", &note.numero);
    while(!numero_existe(note.numero) && note.numero != -1){
        printf("Il n'y a pas d'etudiant avec ce numero. Veuillez ressaisir le numero de l'etudiant  ou -1 pour annuler la recherche.\n");
        scanf("%d" ,&note.numero);
    }
    if(note.numero == -1){
        printf("Annulation de la recherche");
        return 1;
    }

    char ligne[200];
    char nom[30], prenom[30], email[50], date_str[15];
    int num, codeClasse;
    Date date_naissance;

    FILE *fichier_etudiants= fopen("etudiants.csv", "r");
    if (fichier_etudiants== NULL){
        printf("Erreur : impossible d’ouvrir etudiants.csv\n");
        
        fclose(fichier_etudiants);
        return 1;
    }

    while (fgets(ligne, sizeof(ligne), fichier_etudiants)) {
        
        if (sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%d", &num, nom, prenom, email, date_str, &codeClasse) == 6) {
            
            sscanf(date_str, "%d/%d/%d", &date_naissance.jour, &date_naissance.mois, &date_naissance.annee);

            if (note.numero == num) {
                fclose(fichier_etudiants);
                
                break;
            }
        }
    }

    fclose(fichier_etudiants);

    char libelle[30];
    int ref, coefficient;


    FILE *fichier = fopen("note.csv", "r");
    if (fichier == NULL) {
        printf("Le fichier n'a pas pu etre ouvert.\n");
        fclose(fichier);
        return 1;
    }

    printf("Voici les notes de %s %s :\n ", prenom, nom, libelle);

    while (fscanf(fichier, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) != -1) {
        if ((note.numero == numero)) {
            FILE *fichier_matiere = fopen("matiere.csv", "r");
            if (fichier_matiere == NULL) {
                printf("Erreur : impossible d’ouvrir matiere.csv\n");
                return 1;
            }
            while (fgets(ligne, sizeof(ligne), fichier_matiere)) {
                if (sscanf(ligne, "%d;%[^;];%d", &ref, libelle, &coefficient) == 3) {
                    if (reference == ref) {
                        printf("En %s:\n\tnote CC: %d \t note DS: %d\n",libelle, noteCC, noteDS); 
                    }
                }
            }
            fclose(fichier_matiere);           
            
            
        }
        
    }
    fclose(fichier);
    return 0;
}

int supprimer_note(){
    NOTE note;
    int numero, reference, noteCC, noteDS, quitter;

    do {
        printf("Veuillez saisir le numero de l'eleve dont vous voulez supprimer les notes: ");
        scanf("%d", &note.numero);
        while (!numero_existe(note.numero) && note.numero != -1) {
            printf("Il n'y a pas d'etudiant avec ce numero. Veuillez ressaisir ou -1 pour annuler :\n");
            scanf("%d", &note.numero);
        }
        if (note.numero == -1) {
            printf("Annulation des suppressions\n");
            return 1;
        }

        printf("Veuillez saisir la reference de la matiere : ");
        scanf("%d", &note.reference);
        while (!reference_existe(note.reference) && note.reference != -1) {
            printf("Reference invalide. Ressaisir ou -1 pour annuler :\n");
            scanf("%d", &note.reference);
        }
        if (note.reference == -1) {
            printf("Annulation des suppressions\n");
            return 1;
        }

        if (!numero_note_existe(note.numero, note.reference)) {
            printf("Cet eleve n'a pas de note dans cette matiere. 0 pour annuler, 1 pour ressaisir :\n");
            scanf("%d", &quitter);
            while (quitter != 0 && quitter != 1) {
                printf("Choix invalide. Entrez 0 ou 1 :\n");
                scanf("%d", &quitter);
            }
        } else {
            quitter = 0;
        }
    } while ((!numero_note_existe(note.numero, note.reference)) || (quitter == 1));

    FILE *fichier = fopen("note.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fichier == NULL || temp == NULL) {
        printf("Le fichier n'a pas pu être ouvert.\n");
        if (fichier) fclose(fichier);
        if (temp) fclose(temp);
        return 1;
    }

    while (fscanf(fichier, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) != -1) {
        if ((note.numero != numero) || (note.reference != reference)) {
            fprintf(temp, "%d;%d;%d;%d\n", numero, reference, noteCC, noteDS);
        } 
    }

    fclose(fichier);
    fclose(temp);

    remove("note.csv");
    rename("temp.csv", "note.csv");

    

    
    return 0;
}

int recherche_note_matiere(){
    NOTE note;
    int reference, noteCC, noteDS, quitter;

    quitter = 0;
        

    printf("Veuillez saisir la reference de la matiere dont vous voulez rechercher les notes: ");
    scanf("%d" ,&note.reference);
    while (!reference_existe(note.reference) && note.reference != -1){
        printf("Il n'y a pas de matiere avec ce reference. Veuillez ressaisir la reference de la matiere ou -1 pour annuler la recherche.\n ");
        scanf("%d" ,&note.reference);
    }
    if(note.reference == -1){
        printf("Annulation de la recherche");
            
        return 1;
    }



    char ligne[200];
    char nom[30], prenom[30], email[50], date_str[15];
    int numero, codeClasse;
    Date date_naissance;

    char libelle[30];
    int coefficient;

    FILE *fichier_matiere = fopen("matiere.csv", "r");
    if (fichier_matiere == NULL) {
        printf("Erreur : impossible d’ouvrir matiere.csv\n");
        fclose(fichier_matiere);
        return 1;
    }
    while (fgets(ligne, sizeof(ligne), fichier_matiere)) {
        if (sscanf(ligne, "%d;%[^;];%d", &reference, libelle, &coefficient) == 3) {
            if (note.reference == reference) {
                fclose(fichier_matiere);
                
                break;
            }
        }
    }
    fclose(fichier_matiere);

    FILE *fichier = fopen("note.csv", "r");
    if (fichier == NULL) {
        printf("Le fichier n'a pas pu etre ouvert.\n");
        return 1;
    }

    printf("Voici les notes de %s\n ", libelle);

    while (fscanf(fichier, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) != -1) {
        if (note.reference == reference) {
            
            FILE *fichier_etudiants= fopen("etudiants.csv", "r");
            if (fichier_etudiants== NULL){
                printf("Erreur : impossible d’ouvrir etudiants.csv\n");
                
                fclose(fichier_etudiants);
                return 1;
            }

            while (fgets(ligne, sizeof(ligne), fichier_etudiants)) {
                
                if (sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%d", &numero, nom, prenom, email, date_str, &codeClasse) == 6) {
                    
                    sscanf(date_str, "%d/%d/%d", &date_naissance.jour, &date_naissance.mois, &date_naissance.annee);

                    if (note.numero == numero) {
                        fclose(fichier_etudiants);
                        
                        break;
                    }
                }
            }

            fclose(fichier_etudiants);
            printf("%s %s:\tnote CC: %d note DS: %d\n", prenom, nom, noteCC, noteDS);
            fclose(fichier);
            return 0;
            
        }
        
    }
    fclose(fichier);
    return 1;
}

