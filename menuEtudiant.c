#include <stdio.h>
#include <stdlib.h>
#include "etudiant.h"
#include "general.h"

void menuEtudiant() {
    int choix;
    do {
        system("cls");
        printf("\t\t\n===== MENU ÉTUDIANTS =====\n\n");
        printf("\t1. Ajouter un étudiant\n");
        printf("\t2. Modifier un étudiant\n");
        printf("\t3. Rechercher un étudiant\n");
        printf("\t4. Supprimer un étudiant\n");
        printf("\t5. Afficher tous les étudiants\n");
        printf("\t0. Quitter\n\n");
        printf("\tVeuillez renseigner votre choix : ");
        choix=saisie_entier();
        printf("\n\n");

        switch (choix) {
            case 1:system("cls"); ajouterEtudiant(); system("pause");break;
            case 2:system("cls"); modifierEtudiant(); system("pause");break;
            case 3:system("cls"); menuRecherche_Etudiant();break;
            case 4:system("cls"); supprimerEtudiant(); system("pause");break;
            case 5:system("cls"); afficherListeEtudiants(); system("pause");break;
            case 0:printf("Menu précédent\n\n"); system("pause");break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 0);
}
