#include <stdio.h>
#include "gestion_note.h"


void menuNotes(){
    int choix;
    do{
    
        printf("Menu de Notes\n 1. Pour ajouter les notes\n 0.Pour retourner au menu precedent\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            if(!ajout_note())
                printf ("Notes ajoutes avec succes");
            else{
                printf("Erreur d'ajout des notes");
            }
            
            
            break;
        case 0:
            printf("Menu precedent\n");
            break;
        
        default:
            printf("Nous ne pouvons pas encore faire cette option\n");
        }
    
    }while (choix != 0);
}