#include <stdio.h>
#include "gestion_classe.h"
#include <stdlib.h>

int main(){
    int choix, a;
    printf("Bienvenue dans notre programme. \n Pour ajouter un classe tapez 1, \nPour afficher la liste des classe tapez 2\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        a = ajout_classe();
        if (a ==0)
            printf("\n L'ajout a reussi");
            
        else
            printf ("\nL'ajout a echoue");
            break;
    case 2:
        printf("Voici la liste des classes\n");
        afficher_classe();
        break;
    
    default:
        printf("Nous ne pouvons pas encore gerer cette option");
        break;
    }
    
}