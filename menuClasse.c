#include <stdio.h>
#include "gestion_classe.h"
#include <stdlib.h>
#include "general.h"

void menuClasse()
{
    int choix, a;

    do {
    system("cls");
    printf("\t\t\n===== MENU CLASSE =====\n\n");
    printf("\t1. Pour ajouter une classe\n");
    printf("\t2. Pour afficher la liste des classes\n");
    printf("\t3. Pour rechercher une classe\n");
    printf("\t4. Pour supprimer une classe\n");
    printf("\t5. Pour modifier une classe\n");
    printf("\t6. Pour gerer les matieres des classe\n");
    printf("\t0. Pour quitter\n\n");
    printf("\tRenseigner votre choix: ");
    choix=saisie_entier();
    printf("\n\n");

    switch (choix)
    {
    case 1:
        system("cls");
        a = ajout_classe();
        if (a ==0)
            printf("\n L'ajout a réussi\n"); 
        else
            printf ("\nL'ajout a echoue\n");
            system("pause");
            break;
    case 2:
        system("cls");
        printf("Voici la liste des classes\n");
        afficher_classe();
        system("pause");
        break;
    case 3:
        system("cls");
        printf("Veuillez saisir le code de la classe a rechercher\t");
        a=saisie_entier();
        recherche_classe(a);
        system("pause");
        break;
    case 4:
        system("cls");
        printf("Veuillez saisir le code de la classe a supprimer\t");
        a=saisie_entier();
        if (code_existe(a)){
            printf("Il n'y a pas de classe avec ce code");
            exit(1);
        }
        supprimer_classe(a);
        system("pause");
        break;
    case 5:
        system("cls");
        printf("Veuillez saisir le code de la classe a modifier\t");
        a=saisie_entier();
        if (!code_existe(a)){
            printf("Il n'y a pas de classe avec ce code");
            exit(1);
        }
        modifier_classe(a);
        system("pause");
        break;
    case 6:
        system("cls");
        matiere_classe();
        system("pause");
        break;
       
    case 0: printf("Menu precedent\n\n");system("pause"); break; 
    
    default:
        printf("Nous ne pouvons pas encore gerer cette option\n");
        
    }
    
    
    } while (choix !=0);

}