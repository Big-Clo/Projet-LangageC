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
        printf("MINI-LOGIECIEL DE GESTION DES NOTES\n");
        printf("\t1. Gestion des Etudiants\n");
        printf("\t2. Gestions des Classes\n");
        printf("\t3. Gestions des matieres\n");
        printf("\t4. Gestion des Notes\n");
        printf("\t0. Quitter\n\n");
        printf("\tVeuillez renseigner votre choix : \n");
        menu=saisie_entier();

        switch (menu) {
            case 1:system("cls"); menuEtudiant(); system("pause");break;
            case 2:system("cls"); menuClasse(); system("pause");break;
            case 3:system("cls"); menuMatiere(); system("pause");break;
            case 4:system("cls"); menuNotes(); system("pause");break;
            case 0:printf("Au revoir!!!\n"); system("pause");break; 
            default: printf("Choix Invalide");
        }


    } while(menu !=0 );

    return 0;
}