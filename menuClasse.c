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
    printf("1. Ajouter une classe\n");
    printf("2. Afficher la liste des classes\n");
    printf("3. Rechercher une classe\n");
    printf("4. Supprimer une classe\n");
    printf("5. Modifier une classe\n");
    printf("6. Afficher la liste d'une classe\n");
    printf("7. Gérer les matières des classes\n");
    printf("0. Menu précédent\n\n");
    printf("Renseigner votre choix: ");
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
        printf("Voici la liste des classes : \n");
        afficher_classe();
        printf("\n\n");
        system("pause");
        break;
    case 3:
        system("cls");
        menuRecherche_Classe();
        break;
    case 4:
        system("cls");
        printf("Veuillez saisir le code de la classe a supprimer : ");
        a=saisie_entier();
        if (!code_existe(a)){
            printf("Il n'y a pas de classe avec ce code");
            system("pause");
            break;
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
        afficher_liste_eleve_classe();
        system("pause");
        break;
        
    case 7:
        system("cls");
        matiere_classe();
        system("pause");
        break;
       
    case 0: printf("Menu precedent\n\n");system("pause"); break; 
    
    default:
        printf("Veuillez saisir une option valide\n\n");
        
    }
    
    } while (choix !=0);

}