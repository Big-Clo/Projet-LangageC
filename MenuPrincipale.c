#include <stdio.h>
#include "etudiant.h"
#include "matiere.h"
#include "gestion_classe.h"
#include "gestion_note.h"

int main () {
    int menu;
    do {
        printf("MINI-LOGIECIEL DE GESTION DES NOTES\n");
        printf("\t1. Gestion des Etudiants\n");
        printf("\t2. Gestions des Classes\n");
        printf("\t3. Gestions des matieres\n");
        printf("\t4. Gestion des Notes\n");
        printf("\t0. Quitter\n\n");
        printf("\tVeuillez renseigner votre choix : \n");
        scanf("%d", &menu);

        switch (menu) {
            case 1: menuEtudiant(); break;
            case 2: menuClasse(); break;
            case 3: menuMatiere(); break;
            case 4: menuNotes(); break;
            case 0: printf("Au revoir!!!\n"); break; 
            default: printf("Choix Invalide");
        }


    } while(menu !=0 );

    return 0;
}