#include <stdio.h>
#include "gestion_classe.h"
#include <stdlib.h>

void menuClasse()
{
    int choix, a;

    do {
    printf("\t1. Pour ajouter une classe\n");
    printf("\t2. Pour afficher la liste des classes\n");
    printf("\t3. Pour rechercher une classe\n");
    printf("\t4. Pour supprimer une classe\n");
    printf("\t5. Pour modifier une classe\n");
    printf("\t0. Pour quitter\n");
    printf("\tRenseigner votre choix: ");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        a = ajout_classe();
        if (a ==0)
            printf("\n L'ajout a réussi\n"); 
        else
            printf ("\nL'ajout a echoue\n");
            break;
    case 2:
        printf("Voici la liste des classes\n");
        afficher_classe();
        break;
    case 3:
        printf("Veuillez saisir le code de la classe a rechercher\t");
        scanf("%d", &a);
        recherche_classe(a);
        break;
    case 4:
        printf("Veuillez saisir le code de la classe a supprimer\t");
        scanf("%d", &a);
        if (code_existe(a)){
            printf("Il n'y a pas de classe avec ce code");
            exit(1);
        }
        supprimer_classe(a);
        break;
    case 5:
        printf("Veuillez saisir le code de la classe a modifier\t");
        scanf("%d", &a);
        if (!code_existe(a)){
            printf("Il n'y a pas de classe avec ce code");
            exit(1);
        }
        modifier_classe(a);
        break;
    case 0: printf("Menu precedent\n"); break; 
    
    default:
        printf("Nous ne pouvons pas encore gerer cette option\n");
        
    }
    
    
    } while (choix !=0);

}