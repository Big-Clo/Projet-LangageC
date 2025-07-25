#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"
#include "gestion_classe.h"
#include "gestion_note.h"
#include "etudiant.h"
#include "general.h"



int numero_note_existe(int x, int y){
    int numero, reference, noteCC, noteDS;

    FILE *fichier_note= fopen("note.csv", "r");
    if (fichier_note== NULL){
        printf("Erreur : impossible d'ouvrir note.csv\n");
        return 1;
    }

   while (fscanf(fichier_note, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) == 4){
        if ((x == numero) && (y == reference))    {
            fclose(fichier_note);
            return 1;
        }
    }

    fclose(fichier_note);
    return 0;
}

int classe_matiere_existe(int x, int y){

    char ligne[100];
    int reference, code;

    FILE *fichier_matiere_classe = fopen("matiere-classe.csv", "r");
    if (fichier_matiere_classe == NULL) {
        printf("Erreur : impossible d’ouvrir matiere.csv\n");
        return 0;
    }
    while (fgets(ligne, sizeof(ligne), fichier_matiere_classe)) {
        if (sscanf(ligne, "%d;%d", &reference, &code) == 2) {
            if ((x == reference) && (y == code)) {
                fclose(fichier_matiere_classe);
                return 1;
            }
        }
    }
    fclose(fichier_matiere_classe);
    return 0;

}

int ajout_note() {
    NOTE note;
    Etudiant etudiant;
    int quitter;

    do {
        quitter = 1;

        printf("Veuillez saisir le numéro de l'étudiant: ");
        note.numero = saisie_entier();

        while (!numero_existe(note.numero)) {
            printf("Il n'existe pas d'étudiant avec ce numéro. Veuillez saisir un nouveau numéro d'étudiant ou 0 pour annuler l'ajout: ");
            note.numero = saisie_entier();
            if (note.numero == 0) {
                printf("Annulation de l'ajout\n");
                return 1;
            }
        }

        FILE *fichier_etudiant = fopen("etudiants.csv", "r");
        if (fichier_etudiant == NULL) {
            printf("Erreur d'ouverture du fichier etudiants.csv\n");
            return 1;
        }

        while (fscanf(fichier_etudiant, "%d;%29[^;];%29[^;];%49[^;];%d/%d/%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email,
                      &etudiant.date_naissance.jour, &etudiant.date_naissance.mois, &etudiant.date_naissance.annee, &etudiant.codeClasse) != EOF) {
            if (note.numero == etudiant.numero) {
                break;
            }
        }
        fclose(fichier_etudiant);

        printf("Veuillez saisir la référence de la matière: ");
        note.reference = saisie_entier();

        while (!reference_existe(note.reference)) {
            printf("Il n'existe pas de matière avec cette référence.\nVeuillez saisir une nouvelle référence ou 0 pour annuler l'ajout: ");
            note.reference = saisie_entier();
            if (note.reference == 0) {
                printf("Annulation de l'ajout\n");
                return 1;
            }
        }

        if (numero_note_existe(note.numero, note.reference)) {
            printf("Cet élève a deja des notes dans cette matière.\nVeuillez entrer 0 pour annuler ou un autre chiffre pour recommencer: ");
            quitter = saisie_entier();
            if (quitter == 0) {
                printf("Annulation de l'ajout\n");
                return 1;
            }
        }

        if (!classe_matiere_existe(note.reference, etudiant.codeClasse)) {
            printf("La classe de cet élève ne fait pas cette matière.\nVeuillez entrer 0 pour annuler ou un autre chiffre pour recommencer: ");
            quitter = saisie_entier();
            if (quitter == 0) {
                printf("Annulation de l'ajout\n");
                return 1;
            }
        }

    } while (!classe_matiere_existe(note.reference, etudiant.codeClasse) || numero_note_existe(note.numero, note.reference));

    printf("Veuillez saisir la note de CC : ");
    note.noteCC = saisie_entier();
    while (note.noteCC < 0 || note.noteCC > 20) {
        printf("La note doit etre comprise entre 0 et 20. Ressaisissez la note de CC : ");
        note.noteCC = saisie_entier();
    }

    printf("Veuillez saisir la note de DS : ");
    note.noteDS = saisie_entier();
    while (note.noteDS < 0 || note.noteDS > 20) {
        printf("La note doit etre comprise entre 0 et 20. Ressaisissez la note de DS : ");
        note.noteDS = saisie_entier();
    }

    FILE *fichier_note = fopen("note.csv", "a");
    if (fichier_note == NULL) {
        printf("Erreur : le fichier des notes n'a pas pu être ouvert.\n");
        return 1;
    }

    fprintf(fichier_note, "%d;%d;%d;%d\n", note.numero, note.reference, note.noteCC, note.noteDS);
    fclose(fichier_note);

    printf("Note ajoutée avec succès.\n");
    return 0;
}

int modifier_note() {
    NOTE note;
    int numero, reference, noteCC, noteDS, quitter;

    do {
        printf("Veuillez saisir le numéro de l'élève dont vous voulez modifier les notes: ");
        note.numero=saisie_entier();
        while (!numero_existe(note.numero) && note.numero != -1) {
            printf("Il n'y a pas d'étudiant avec ce numéro. Veuillez ressaisir ou -1 pour annuler :\n");
            note.numero=saisie_entier();
        }
        if (note.numero == -1) {
            printf("Annulation des modifications\n");
            return 1;
        }

        printf("Veuillez saisir la référence de la matière : ");
        note.reference=saisie_entier();
        while (!reference_existe(note.reference) && note.reference != -1) {
            printf("Référence invalide. Ressaisir ou -1 pour annuler :\n");
            note.reference=saisie_entier();
        }
        if (note.reference == -1) {
            printf("Annulation des modifications\n");
            return 1;
        }

        if (!numero_note_existe(note.numero, note.reference)) {
            printf("Cet élève n'a pas de note dans cette matière. 0 pour annuler, 1 pour ressaisir :\n");
            quitter=saisie_entier();
            while (quitter != 0 && quitter != 1) {
                printf("Choix invalide. Entrez 0 ou 1 :\n");
                quitter=saisie_entier();
            }
            if(quitter == 0){
                printf("Annulation\n");
                return 1;
            }
        } else {
            quitter = 0;
        }
    } while (!(numero_note_existe(note.numero, note.reference)) || (quitter == 1));

    FILE *fichier = fopen("note.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fichier == NULL || temp == NULL) {
        printf("Le fichier n'a pas pu être ouvert.\n");
        if (fichier) fclose(fichier);
        if (temp) fclose(temp);
        return 1;
    }

    while (fscanf(fichier, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) != -1) {
        if ((note.numero == numero) && (note.reference == reference)) {
            printf("Veuillez saisir la nouvelle note de CC: ");
            note.noteCC=saisie_entier();
            printf("Veuillez saisir la nouvelle note de DS: ");
            note.noteDS=saisie_entier();
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
        printf("Veuillez saisir le saisir le numéro de l' etudiant dont vous chercher la note: ");
        note.numero=saisie_entier();
        while(!numero_existe(note.numero) && note.numero != -1){
            printf("Il n'y a pas d'étudiant avec ce numéro. Veuillez ressaisir le numéro de l'étudiant  ou -1 pour annuler la recherche.\n");
            note.numero=saisie_entier();
        }
        if(note.numero == -1){
            printf("Annulation de la recherche");
            
            return 1;
        }


        printf("Veuillez saisir la référence de la matière dont vous voulez rechercher les notes: ");
        note.reference=saisie_entier();
        while (!reference_existe(note.reference) && note.reference != -1){
            printf("Il n'y a pas de matière avec ce reference. Veuillez ressaisir la référence de la matière ou -1 pour annuler la recherche.\n ");
            note.reference=saisie_entier();
        }
        if(note.reference == -1){
            printf("Annulation de la recherche");
            
            return 1;
        }



        if (!numero_note_existe(note.numero, note.reference)){
            printf("Cette eleve n'a pas de notes dans cette matière. Veuillez entre 0 pour annuler la modification et 1 pour rentrer les informations a nouveaux");
            quitter=saisie_entier();

        }
        while(quitter != 0 && quitter != 1){
            printf("Choix invalide. Veuillez entre 1 pour annuler la modification et 0 pour rentrer les informations a nouveaux: ");
            quitter=saisie_entier();
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
        printf("Erreur : impossible d’ouvrir matière.csv\n");
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
        printf("Le fichier n'a pas pu être ouvert.\n");
        return 1;
    }

    printf(" de %s %s en %s\n ", prenom, nom, libelle);

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

int supprimer_note(){
    NOTE note;
    int numero, reference, noteCC, noteDS, quitter;

    do {
        printf("Veuillez saisir le numéro de l'élève dont vous voulez supprimer les notes: ");
        note.numero=saisie_entier();
        while (!numero_existe(note.numero) && note.numero != -1) {
            printf("Il n'y a pas d'étudiant avec ce numéro. Veuillez ressaisir ou -1 pour annuler :\n");
            note.numero=saisie_entier();
        }
        if (note.numero == -1) {
            printf("Annulation des suppressions\n");
            return 1;
        }

        printf("Veuillez saisir la référence de la matière : ");
        note.reference=saisie_entier();
        while (!reference_existe(note.reference) && note.reference != -1) {
            printf("Référence invalide. Ressaisir ou -1 pour annuler :\n");
            note.reference=saisie_entier();
        }
        if (note.reference == -1) {
            printf("Annulation des suppressions\n");
            return 1;
        }

        if (!numero_note_existe(note.numero, note.reference)) {
            printf("Cet élève n'a pas de note dans cette matière. 0 pour annuler, 1 pour ressaisir :\n");
            quitter=saisie_entier();
            while (quitter != 0 && quitter != 1) {
                printf("Choix invalide. Entrez 0 ou 1 :\n");
                quitter=saisie_entier();
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

int recherche_note_eleve(){

    NOTE note;
    int numero, reference, noteCC, noteDS, quitter;

    quitter = 0;
    printf("Veuillez saisir le saisir le numéro de l' etudiant dont vous chercher la note: ");
    note.numero=saisie_entier();
    while(!numero_existe(note.numero) && note.numero != -1){
        printf("Il n'y a pas d'étudiant avec ce numéro. Veuillez ressaisir le numéro de l'étudiant  ou -1 pour annuler la recherche.\n");
        note.numero=saisie_entier();
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
        
        if (sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%d", &num, nom, prenom, email, date_str, &codeClasse) == 6) {
            
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
        printf("Le fichier n'a pas pu être ouvert.\n");
        fclose(fichier);
        return 1;
    }

    printf("Voici les notes de %s %s :\n\n ", prenom, nom);
    printf("\t+-----------------+----------------+----------------+\n");
    printf("\t|     Matière     |    Note CC     |    Note CC     |\n");
    printf("\t+-----------------+----------------+----------------+\n");


    while (fscanf(fichier, "%d;%d;%d;%d\n", &numero, &reference, &noteCC, &noteDS) != -1) {
        if ((note.numero == numero)) {
            FILE *fichier_matiere = fopen("matiere.csv", "r");
            if (fichier_matiere == NULL) {
                printf("Erreur : impossible d’ouvrir matière.csv\n");
                return 1;
            }
            while (fgets(ligne, sizeof(ligne), fichier_matiere)) {
                if (sscanf(ligne, "%d;%[^;];%d", &ref, libelle, &coefficient) == 3) {
                    if (reference == ref) {
                        //printf("En %s:\n\tnote CC: %d \t note DS: %d\n",libelle, noteCC, noteDS); 
                        printf("\t| %-15s |       %-2d       |       %-2d       |\n", libelle,noteCC, noteDS);
                        printf("\t+-----------------+----------------+----------------+\n");
                    }
                }
            }
            fclose(fichier_matiere);           
            
            
        }
        
    }
    fclose(fichier);
    return 0;
}

int recherche_note_matiere(){
    NOTE note;
    int reference, noteCC, noteDS;

        

    printf("Veuillez saisir la référence de la matière dont vous voulez rechercher les notes: ");
    note.reference=saisie_entier();
    while (!reference_existe(note.reference) && note.reference != -1){
        printf("Il n'y a pas de matière avec cette référence. Veuillez ressaisir la référence de la matière ou -1 pour annuler la recherche.\n ");
        note.reference=saisie_entier();
    }
    
    if(note.reference == -1){
        printf("Annulation de la recherche");
            
        return 1;
    }
    int mc_ref,mc_code;
    CLASSE classe;
    matiere matiere;
    char niveau[10];
    Etudiant e;
    NOTE n;

    FILE*fichier_note=fopen("note.csv","r");
    FILE *fichier_matiere = fopen("matiere.csv", "r");
    if (!fichier_matiere) {
        printf("Erreur ouverture matiere.csv\n");
        return 1;
    }
    while (fscanf(fichier_matiere, "%d;%15[^;];%d\n", &matiere.reference, matiere.libelle, &matiere.coefficient) == 3) {
        if (matiere.reference == mc_ref) break;
    }
        fclose(fichier_matiere);
    
    printf("\t\tListe de notes en %s\n", matiere.libelle);
    printf("\t+----------------+-------------+-------------+----------------+----------------+\n");
    printf("\t|     Classe     |     Nom     |   Prénom    |    Note CC     |    Note CC     |\n");
    printf("\t+----------------+-------------+-------------+----------------+----------------+\n");
    
    
    while (fscanf(fichier_note, "%d;%d;%d;%d\n", &n.numero, &n.reference, &n.noteCC, &n.noteDS) == 4) {
    if (note.reference == n.reference) {
        FILE *fichier_matiere_classe = fopen("matiere-classe.csv", "r");
        if (!fichier_matiere_classe) {
            printf("Erreur lors de l'ouverture de matiere-classe.csv\n");
            continue;
        }

        while (fscanf(fichier_matiere_classe, "%d;%d\n", &mc_ref, &mc_code) == 2) {
            if (mc_ref != n.reference) continue;





            FILE *fichier_eleve = fopen("etudiants.csv", "r");
            if (!fichier_eleve) {
                printf("Erreur ouverture etudiants.csv\n");
                break;
            }

            while (fscanf(fichier_eleve, "%d;%29[^;];%29[^;];%49[^;];%d/%d/%d;%d\n",
                          &e.numero, e.nom, e.prenom, e.email,
                          &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee,
                          &e.codeClasse) == 8) {
                if (n.numero == e.numero) break;
            }
            fclose(fichier_eleve);

            FILE *fichier_classe = fopen("classe.csv", "r");
            if (!fichier_classe) {
                printf("Erreur ouverture classe.csv\n");
                break;
            }

            while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &classe.code, classe.nom, niveau) == 3) {
                if (classe.code == mc_code) break;
            }
            fclose(fichier_classe);

            printf("\t| %-14s | %-11s | %-11s |       %2d       |       %2d       |\n",
                   classe.nom, e.nom, e.prenom, n.noteCC, n.noteDS);
            printf("\t+----------------+-------------+-------------+----------------+----------------+\n");
        }

        fclose(fichier_matiere_classe);
    }
}

    
    fclose(fichier_note);
    return 0;
}

int recherche_note_classe() {
    int code;
    printf("Veuillez saisir le code de la classe dont vous voulez connaitre les notes : ");
    code = saisie_entier();

    while (!code_existe(code) && code != -1) {
        printf("Le code que vous avez saisi n'est attribué à aucune classe. Veuillez entrer un code valide ou -1 pour annuler la recherche : ");
        code = saisie_entier();
    }
    if (code == -1) {
        printf("Recherche annulée.\n");
        return 1;
    }

    NOTE n;
    FILE* fichier_note = fopen("note.csv", "r");
    if (!fichier_note) {
        printf("Erreur ouverture note.csv\n");
        return 1;
    }

    printf("\t+----------------+-------------+-------------+----------------+----------------+\n");
    printf("\t|    Matière     |     Nom     |   Prénom    |    Note CC     |    Note DS     |\n");
    printf("\t+----------------+-------------+-------------+----------------+----------------+\n");

    while (fscanf(fichier_note, "%d;%d;%d;%d\n", &n.numero, &n.reference, &n.noteCC, &n.noteDS) == 4) {
        FILE* fichier_matiere_classe = fopen("matiere-classe.csv", "r");
        if (!fichier_matiere_classe) continue;

        int mc_ref, mc_code;
        while (fscanf(fichier_matiere_classe, "%d;%d\n", &mc_ref, &mc_code) == 2) {
            if (mc_ref != n.reference || mc_code != code) continue;

            // Lecture matière
            matiere m;
            FILE* fichier_matiere = fopen("matiere.csv", "r");
            if (!fichier_matiere) break;

            while (fscanf(fichier_matiere, "%d;%15[^;];%d\n", &m.reference, m.libelle, &m.coefficient) == 3) {
                if (m.reference == mc_ref) break;
            }
            fclose(fichier_matiere);

            // Lecture étudiant
            Etudiant e;
            FILE* fichier_eleve = fopen("etudiants.csv", "r");
            if (!fichier_eleve) break;

            while (fscanf(fichier_eleve, "%d;%29[^;];%29[^;];%49[^;];%d/%d/%d;%d\n",
                          &e.numero, e.nom, e.prenom, e.email,
                          &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee,
                          &e.codeClasse) == 8) {
                if (e.numero == n.numero && e.codeClasse == code) break;
            }
            fclose(fichier_eleve);

            // Affichage
            printf("\t| %-14s | %-11s | %-11s |       %2d       |       %2d       |\n",
                   m.libelle, e.nom, e.prenom, n.noteCC, n.noteDS);
            printf("\t+----------------+-------------+-------------+----------------+----------------+\n");
        }

        fclose(fichier_matiere_classe);
    }

    fclose(fichier_note);
    return 0;
}

