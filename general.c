#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int code_existe(int x){
    char nom[30], niveau[10];
    int code;
    FILE  *fichier_classe = 
    fopen ("classe.csv", "r");
    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3){
        if (x == code){
            fclose(fichier_classe);
            return 1;
            
        }
    }
    fclose(fichier_classe);
    return 0;
}


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

int confirmer_modification() {
    char confirm;
    printf("Confirmer la modification ? (o/n) : ");
    scanf(" %c", &confirm);
    while (getchar() != '\n'); // Vider le buffer
    return (confirm == 'o' || confirm == 'O');
}

void Maj(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}
// gcc etudiant.c gestion_classe.c gestion_note.c general.c matiere.c menuEtudiant.c menuClasse.c menuNotes.c menuMatiere.c menuPrincipale.c -o b && b.exe