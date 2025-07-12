#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matiere.h"

void menuMatiere()
{
    int choix, a;
    char tab[100];

    do {

    system("cls");

    printf("\n\n\t\tMenu matière\n");
    printf("1. Pour ajouter un matière\n");
    printf("2. Pour afficher la liste des matières\n");
    printf("3. Pour rechercher une matière\n");
    printf("4. Pour supprimer une matière\n");
    printf("5. Pour modifier une matière\n");
    printf("0. Pour quitter\n\n");
    printf("Renseigner votre choix : ");
    choix = saisie_entier();
    printf("\n\n");

    switch (choix)
    {
    case 1:
        system("cls");
        a = ajout_matiere();
        if (a ==0)
            printf("\n L'ajout a réussi\n\n"); 
        else
            printf ("\nL'ajout a échoué\n\n");
        system("pause");
        break;
    case 2:
        system("cls");
        printf("Voici la liste des matières\n");
        lister_matiere();
        system("pause");
        break;
    case 3:
        system("cls");
        menuRecherche_matiere();
        system("pause");
        break;
    case 4:
        system("cls");
        printf("Veuillez saisir la référence de la matière à supprimer : ");
        a = saisie_entier();
        if (!reference_existe(a)){
            printf("Il n'y a pas de matière avec cette référence\n\n");
            system("pause");
            break;
        }
        chercher(a,tab);
        supprimer_matiere(tab);
        printf("La matière a été supprimé avec succès\n\n");
        system("pause");
        break;
    case 5:
        system("cls");
        printf("Veuillez saisir la référence de la matière a modifier : ");
        a = saisie_entier();
        if (!reference_existe(a)){
            printf("Il n'y a pas de matière avec cette référence\n\n");
            system("pause");
            break;
        }
        menuModifier_matiere(a);
        system("pause");
        break;
    case 0: printf("Menu précédent\n\n"); break; 
    
    default:
        printf("Cette option n'existe pas\n\n");
        system("pause");
        break;
    }
    
    } while (choix !=0);

}

