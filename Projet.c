#include<stdio.h>
#include<string.h>
#include<stdlib.h>      //Gestion de la mémoire avec malloc, free, ...

int main() {
//Ouverture des fichiers *dat et *res


//Declaration des variables
int valeurMenu = 0;

/*------------------------------------------------------Fin declaration des variables----------------------------------------------------------------*/
void changerMenu(int *);


changerMenu(&valeurMenu);
    
}   //Fin du programme principal.


//ChangerMenu
void changerMenu( int *valeurMenu) {
    /*La valeur du menu principal est 0. Donc, si *valeurMenu est déjà à 0, on propose un affichage pour 0 qui s'appelle 'Retour'.*/
    if(*valeurMenu == 0) {
        printf("Veuillez entrer la valeur correspondante au menu souhaite :\n");
        printf("0 : Retour\n");
        printf("1 : Consulter un horaire\n");
        printf("2 : Ajouter un etudiant\n");
        printf("3 : Gerer les formations\n");
        printf("4 : Consulter les etudiants\n");

        scanf("%d", &*valeurMenu);

        //Gestion d'erreur
        while(*valeurMenu < 0 || *valeurMenu > 4) {
            printf("Valeur incorrecte.\n");
            scanf("%d", &*valeurMenu);
        }

    } else {
        /*On est déjà dans un autre menu. Selon la valeur (1 à 4), Faire appel à une fonction propre à ce menu.
          Car, par exemple, Gérer les formations débouche sur 2 sous menu + possibilités de revenir au menu principal. Donc ce serait le bordel si on met tout en brute ici
          --> Faire des fonctions sera plus clair
          !! Ne pas utiliser 2 fois le même chiffre pour un menu différent car chaque sous menu à son chiffre qui lui sert d'ID en quelque sorte !!
        */

        //pas encore d'autre menu réalisé
    }

    //Appel des fonctions d'affichage correspondant
    /*Pas encore mise en place pour le moment*/
}

