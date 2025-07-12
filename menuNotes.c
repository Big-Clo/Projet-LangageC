#include <stdio.h>
#include "gestion_note.h"


void menuNotes(){
    int choix;
    do{
    
        printf("\n\nMenu de Notes\n 1. Ajouter les notes\n 2. Modifier les notes\n 3.Recherche notes etudiant dans une matiere\n 4.Pour affichicher toutes les notes d'un eleve\n 5.Pour supprimer les notes d'un eleves\n 0.Pour retourner au menu precedent\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            if(!ajout_note())
                printf ("Notes ajoutes avec succes\n");
                
                
                
            else{
                printf("Erreur d'ajout des notes\n");
                return;
            }
            
            
            break;

        case 2:
            if(!modifier_note())
                printf("Notes modifiees avec succes\n");
                
            else{
                printf("Erreur dans la modification des notes\n");
                
            }
            break;

        case 3:
            if(!recherche_note_eleve_matiere()){
                printf("Recherche effectuee avec succees\n");
                
            }
            else{
                printf("Erreur dans la recherche");
                
            }
            break;

        case 4:
            if(!recherche_note_eleve()){
                printf("Recherche effectuee avec succees\n");
            }
            else{
                printf("Erreur dans la recherche");
            }

        case 5:
            if(!supprimer_note()){
                printf("Suppression effectuee avec succes");
            }
            else{
                printf("Erreur dans la suppression");
            }
        case 0:
            printf("Menu precedent\n");
            break;
        
        default:
            printf("Nous ne pouvons pas encore faire cette option\n");
        }
    
    }while (choix != 0);
}