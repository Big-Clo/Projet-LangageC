#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"

void saisie_ligne(char *dest, int taille) {
    while (1) {
        if (fgets(dest, taille, stdin) != NULL) {
            size_t len = strlen(dest);
            if (len > 0 && dest[len - 1] == '\n') {
                dest[len - 1] = '\0';
            } else {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }

            if (strchr(dest, ';') != NULL) {
                printf("Le caractère ';' est interdit. Veuillez ressaisir :\n");
                continue;
            }

            break;
        }
    }
}

int saisie_entier() {
    int valeur;
    char buffer[100];

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &valeur) == 1) {
                return valeur;
            } else {
                printf("Entrée invalide. Veuillez saisir un entier valide : \n");
            }
        }
    }
}


// gcc etudiant.c gestion_classe.c gestion_note.c matiere.c menuEtudiant.c menuClasse.c menuNotes.c menuMatiere.c menuPrincipale.c -o b && b.exe