#include <stdio.h>
#include "gestion_note.h"


void menuNotes(){
    int choix;
    do{
    
        printf("\n\nMenu de Notes\n 1. Ajouter les notes\n 2. Modifier les notes\n 3. RechercheR notes etudiant dans une matiere\n 4. Afficher toutes les notes d'un eleve\n 5. Afficher les notes dans un matiere\n 6. Supprimer les notes d'un eleves\n 0. Retourner au menu precedent\n");
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
                break;
                
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
            break;

        case 5:
            if(!recherche_note_matiere()){
                printf("Recherche effectuee avec succees\n");
            }
            else{
                printf("Erreur dans la recherche");
            }
            break;

        case 6:
            if(!supprimer_note()){
                printf("Suppression effectuee avec succes");
            }
            else{
                printf("Erreur dans la suppression");
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