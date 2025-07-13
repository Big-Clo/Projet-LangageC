#include <stdio.h>
#include "gestion_note.h"


void menuNotes(){
    int choix;
    do{
        
        system("csl");
        printf("\n\nMenu de Notes\n 1. Ajouter les notes\n 2. Modifier les notes\n 3. RechercheR notes etudiant dans une matiere\n 4. Afficher toutes les notes d'un eleve\n 5. Afficher les notes dans un matiere\n 6. Supprimer les notes d'un eleves\n 0. Retourner au menu precedent\n");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            system("cls");
            if(!ajout_note())
                printf ("Notes ajoutes avec succes\n");
                
                
                
            else{
                printf("Erreur d'ajout des notes\n");
                return;
            }
            
            
            system("pause");
            break;

        case 2:
            system("cls");
            if(!modifier_note())
                printf("Notes modifiees avec succes\n");
                
            else{
                printf("Erreur dans la modification des notes\n");
                
            }
            system("pause");
            break;

        case 3:
            system("cls");
            if(!recherche_note_eleve_matiere()){
                printf("Recherche effectuee avec succees\n");
                system("pause");
                break;
                
            }
            else{
                printf("Erreur dans la recherche");
                
            }
            system("pause");
            break;

        case 4:
            system("cls");
            if(!recherche_note_eleve()){
                printf("Recherche effectuee avec succees\n");
            }
            else{
                printf("Erreur dans la recherche");
            }
            system("pause");
            break;

        case 5:
            system("cls");
            if(!recherche_note_matiere()){
                printf("Recherche effectuee avec succees\n");
            }
            else{
                printf("Erreur dans la recherche");
            }
            system("pause");
            break;

        case 6:
            system("cls");
            if(!supprimer_note()){
                printf("Suppression effectuee avec succes");
            }
            else{
                printf("Erreur dans la suppression");
            }
            system("pause");
            break;
        
        case 0:
            printf("Menu precedent\n");
            system("pause");
            break;
        
        default:
            printf("Nous ne pouvons pas encore faire cette option\n");
        }
    
    }while (choix != 0);
}