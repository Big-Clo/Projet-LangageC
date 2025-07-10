#include "gestion_note.h"
#include "etudiant.h"
#include <stdio.h>
// int numero;
//     char nom[30];
//     char prenom[30];
//     char email[50];
//     Date date_naissance;
//     int codeClasse;

// int numero_existe(int x){
//     char nom[30], prenom[30], email[50];
//     Date date_naissance;
//     int numero, codeClasse;
//     FILE  *fichier_classe = 
//     fopen ("etudiant.csv", "r");
//     while (fscanf(fichier_classe, "%d - %s - %s\n", &code, nom, niveau) != -1){
//         if (x == code){
//             fclose(fichier_classe);
//             return 1;
            
//         }
//     }
//     fclose(fichier_classe);
//     return 0;
// }

// int ajout_note(){
//     NOTE note;
//     int level, existe;
    
//     printf ("Ce programme vous permet d'ajouter une note a un eleve.\n Veuillez saisir:\n le numero de l'etudiant:\t");
//     scanf("%d", &note.numero);
//     existe = code_existe(classe.code);
//     while(existe == 1 ){
//         printf ("Le code que vous avez saisit est deja attribue a une classe veuillez saisir un autre code ou -1 si vous voulez annuler l'ajout:\t");
//         scanf("%d", &classe.code);
//         existe = code_existe(classe.code);
//         if (classe.code == -1){
//             break;
//         }
//     }
    
//     if (classe.code == -1){
//         printf("L'ajout a ete annule");
//         return 1;
//     }
//     printf ("\n Le nom de la classe:\t\n");
//     scanf ("%s", classe.nom);
//     printf ("\nVeuillez tapez 1 si vous etes en license et 2 si vous etes en master:\t");
//     scanf("%d", &level);
//     while (level != 1 && level != 2){
//         printf("\nVous devez entrer 1 si vous etes en license et 2 si vous etes en master. Veuillez reessayer:\t");
//         scanf("%d", &level);
//     }
//     if (level == 1){
//         classe.niveau = License;
//     }
//     else{
//         classe.niveau = Master;
//     }

//     FILE  *fichier_classe = fopen ("classe.csv", "a");
//     if (fichier_classe == NULL){
//         printf("le fichier n' a pas pu etre ouvert");
       
//         return 1;
//     }
//     if (level == 1)
//         fprintf(fichier_classe,"\n%d - %s - License",classe.code, classe.nom);
//     else
//         fprintf(fichier_classe,"\n%d - %s - Master",classe.code, classe.nom);
    

//     fclose(fichier_classe);
//     return 0;

}