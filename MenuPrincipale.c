#include <stdio.h>
#include <stdlib.h>
#include "etudiant.h"
#include "matiere.h"
#include "gestion_classe.h"
#include "gestion_note.h"
#include "general.h"

int main () {
    int menu;
    do {
        system("cls");
        printf("MINI-LOGIECIEL DE GESTION DES NOTES\n\n\n");
        printf("1. Gestion des Étudiants\n");
        printf("2. Gestions des Classes\n");
        printf("3. Gestions des Matières\n");
        printf("4. Gestion des Notes\n");
        printf("0. Quitter\n\n");
        printf("Veuillez renseigner votre choix : ");
        menu=saisie_entier();
        printf("\n\n");

        switch (menu) {
            case 1:system("cls"); menuEtudiant(); break;
            case 2:system("cls"); menuClasse(); break;
            case 3:system("cls"); menuMatiere(); break;
            case 4:system("cls"); menuNotes(); break;
            case 0:printf("Au revoir!!!\n\n");break; 
            default: printf("Veuillez saisir une option valide\n\n");system("pause");
        }


    } while(menu !=0 );

    return 0;
}