#include <stdio.h>
#include <stdlib.h>
#include "etudiant.h"
#include "general.h"

void menuEtudiant() {
    int choix;
    do {
        system("cls");
        printf("\t\t\n===== MENU ÉTUDIANTS =====\n\n");
        printf("1. Ajouter un étudiant\n");
        printf("2. Modifier un étudiant\n");
        printf("3. Rechercher un étudiant\n");
        printf("4. Supprimer un étudiant\n");
        printf("5. Afficher tout les étudiants\n");
        printf("0. Menu Précédent\n\n");
        printf("Veuillez renseigner votre choix : ");
        choix=saisie_entier();
        printf("\n\n");

        switch (choix) {
            case 1:system("cls"); ajouterEtudiant(); system("pause");break;
            case 2:system("cls");printf("Entrez le numéro de l'étudiant à modifier : ");int numero=saisie_entier(); menuModifier_Etudiant(numero);break;
            case 3:system("cls"); menuRecherche_Etudiant();break;
            case 4:system("cls"); supprimerEtudiant(); system("pause");break;
            case 5:system("cls"); afficherListeEtudiants(); system("pause");break;
            case 0:printf("Menu précédent\n\n"); system("pause"); return; break;
            default: printf("Veuillez saisir une option valide\n\n");system("pause");
        }

    } while (choix != 0);
}
