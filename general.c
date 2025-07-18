#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void Maj(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

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

int classe_existe(char x[30]) {
    char nom[30], niveau[10];
    int code;
    FILE *fichier_classe = fopen("classe.csv", "r");

    if (fichier_classe == NULL) {
        printf("Erreur lors de l'ouverture du fichier classe.csv\n");
        return 0;
    }

    Maj(x); // pour rendre la recherche insensible à la casse

    while (fscanf(fichier_classe, "%d;%29[^;];%29[^\n]\n", &code, nom, niveau) == 3) {
        Maj(nom); // homogénéiser les comparaisons
        if (strcmp(x, nom) == 0) {
            fclose(fichier_classe);
            return 1; // la classe existe
        }
    }

    fclose(fichier_classe);
    return 0; // non trouvée
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
    while (getchar() != '\n'); 
    return (confirm == 'o' || confirm == 'O');
}

int numero_existe(int x){
    char ligne[200];
    char nom[30], prenom[30], email[50], date_str[15];
    int numero, codeClasse;
    int jour,mois,annee;

    FILE *fichier_etudiants= fopen("etudiants.csv", "r");
    if (fichier_etudiants== NULL){
        printf("Erreur : impossible d’ouvrir etudiants.csv\n");
        return 0;
    }

    while (fgets(ligne, sizeof(ligne), fichier_etudiants)) {
        
        if (sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%d", &numero, nom, prenom, email, date_str, &codeClasse) == 6) {
            
            sscanf(date_str, "%d/%d/%d", &jour, &mois, &annee);

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


