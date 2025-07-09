#include <stdio.h>
#include "etudiant.h"

void menuEtudiant() {
    int choix;
    do {
        printf("\t\t\n===== MENU ÉTUDIANTS =====\n");
        printf("\n");
        printf("\t1. Ajouter un étudiant\n");
        printf("\t2. Modifier un étudiant\n");
        printf("\t3. Rechercher un étudiant\n");
        printf("\t4. Supprimer un étudiant\n");
        printf("\t5. Afficher tous les étudiants\n");
        printf("\t0. Quitter\n\n");
        printf("\tVeuillez renseigner votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterEtudiant(); break;
            case 2: modifierEtudiant(); break;
            case 3: rechercherEtudiant(); break;
            case 4: supprimerEtudiant(); break;
            case 5: afficherListeEtudiants(); break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 0);
}
