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

    printf("\n\n\t\tBienvenue dans notre programme.\n");
    printf("1. Pour ajouter un matiere\n");
    printf("2. Pour afficher la liste des matieres\n");
    printf("3. Pour rechercher une matiere\n");
    printf("4. Pour supprimer une matiere\n");
    printf("5. Pour modifier une matiere\n");
    printf("0. Pour quitter\n");
    printf("Renseigner votre choix : ");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        a = ajout_matiere();
        if (a ==0)
            printf("\n L'ajout a réussi\n"); 
        else
            printf ("\nL'ajout a echoue\n");
        system("pause");
        break;
    case 2:
        printf("Voici la liste des matieres\n");
        lister_matiere();
        system("pause");
        break;
    case 3:
        menuRecherche_matiere();
        system("pause");
        break;
    case 4:
        printf("Veuillez saisir la reference de la matiere a supprimer\t");
        scanf("%d", &a);
        if (!reference_existe(a)){
            printf("Il n'y a pas de matiere avec cette reference");
            system("pause");
            break;
        }
        chercher(a,tab);
        supprimer_matiere(tab);
        printf("La matiere a ete supprimer avec succes.");
        system("pause");
        break;
    case 5:
        printf("Veuillez saisir la reference de la matiere a modifier\t");
        scanf("%d", &a);
        if (!reference_existe(a)){
            printf("Il n'y a pas de matiere avec cette reference");
            system("pause");
            break;
        }
        menuModifier_matiere(a);
        system("pause");
        break;
    case 0: printf("Menu precedent\n"); break; 
    
    default:
        printf("Nous ne pouvons pas encore gerer cette option\n");
        break;
    }
    
    } while (choix !=0);

}

int main(){
    menuMatiere();
    return 0;
}