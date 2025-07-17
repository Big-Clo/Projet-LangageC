#include <stdio.h>
#include <stdlib.h>
#include "gestion_note.h"
#include "general.h"


void menuNotes(){
    int choix;
    do{
        
        system("cls");
        printf("\t\t\n===== MENU NOTES =====\n\n 1. Ajouter les notes\n 2. Modifier les notes\n 3. Rechercher les notes d'un étudiant dans une matière\n 4. Afficher toutes les notes d'un étudiant\n 5. Afficher les notes dans un matière\n 6. Afficher les notes d'une classe\n 7. Supprimer les notes d'un étudiant\n 0. Menu précédent\n\n");
        printf("Renseigner votre choix : ");
        choix=saisie_entier();
        printf("\n\n");
        switch (choix)
        {
        case 1:
            system("cls");
            if(!ajout_note())
                printf ("Notes ajoutées avec succés\n");
                
                
                
            else{
                printf("Erreur d'ajout des notes\n");
                system("pause");
                return;
            }
            
            
            system("pause");
            break;

        case 2:
            system("cls");
            if(!modifier_note())
                printf("Notes modifiées avec succés\n");
                
            else{
                printf("Erreur dans la modification des notes\n");
                
            }
            system("pause");
            break;

        case 3:
            system("cls");
            if(!recherche_note_eleve_matiere()){
                printf("\n\n");
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
                printf("\n\n");
            }
            else{
                printf("Erreur dans la recherche\n\n");
            }
            system("pause");
            break;

        case 5:
            system("cls");
            if(!recherche_note_matiere()){
                printf("\n\n");
            }
            else{
                printf("Erreur dans la recherche");
            }
            system("pause");
            break;

        case 7:
            system("cls");
            if(!supprimer_note()){
                printf("\nSuppression effectuée avec succés\n\n");
            }
            else{
                printf("\nErreur dans la suppression\n\n");
            }
            system("pause");
            break;
        
        case 6:
            system("cls");
            if(!recherche_note_classe()){
                printf("\n\n");
            }
            else{
                printf("Erreur dans la recherche");
            }
            system("pause");
            break;

        case 0:
            printf("Menu précédent\n\n");
            system("pause");
            break;
        
        default:
            printf("Veuillez saisir une option valide\n\n");
        }
    
    }while (choix != 0);
}