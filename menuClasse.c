#include <stdio.h>
#include "gestion_classe.h"
#include <stdlib.h>

void menuClasse()
{
    int choix, a;

    do {
    printf("\t\tBienvenue dans notre programme.\n");
    printf("1. Pour ajouter un classe\n");
    printf("2. Pour afficher la liste des classe\n");
    printf("0. Pour quitter\n");
    printf("Renseigner votre choix\n");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        a = ajout_classe();
        if (a ==0)
            printf("\n L'ajout a reussi\n"); 
        else
            printf ("\nL'ajout a echoue\n");
            break;
    case 2:
        printf("Voici la liste des classes\n");
        afficher_classe();
        break;
    
    default:
        printf("Nous ne pouvons pas encore gerer cette option\n");
        break;
    }
    
    
    } while (choix !=0);

}