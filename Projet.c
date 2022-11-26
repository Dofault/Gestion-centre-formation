#include<stdio.h>
#include<string.h>
#include<stdlib.h>      //Gestion de la mémoire avec malloc, free, ...

typedef struct etudiant {
    char nom[30];
    char prenom[30];
    char nomDeFormation[100];
    int naissanceJour, naissanceMois, naissanceAnnee, annee;
    float montantAPayer, montantPaye, reduction;
    struct etudiant *suivant;
}etudiant;

typedef struct formateur {
    char nom[30];
    char prenom[30];
    char titre[10][100];
    int naissanceJour, naissanceMois, naissanceAnnee, niveauDiplome;
    struct formateur *suivant;
}formateur;

typedef struct formation {
    char nom[100];
    char cours[50];
    char anneeCours[5][50];
    int maxEtudiant;
    float prix;
    struct formation *suivant;
}formation;

int main() {
//Ouverture des fichiers *dat et *res


//Declaration des variables
int valeurMenu = 0;

/*------------------------------------------------------Fin declaration des variables----------------------------------------------------------------*/
void changerMenu(int *);

while(valeurMenu != 0) {
		
		if(valeurMenu == 1) {
	        // fonction consulter horaire
	        printf("Chargement du menu ""consulter un horaire"" ...");
	        menuConsulterHoraire();
	        printf("\nJe quitte la fonction horaire\n");
	    }
	
	    if(valeurMenu == 2) {
	        // fonction ajouter élève
	    }
	
	    if(valeurMenu == 3) {
	        // fonction gestion formation
	    }
	
	    if(valeurMenu == 4) {
	        // fonction consulter etudiant
	    }
	    
	    
    	menuPrincipal(&valeurMenu);
	}
    
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



void menuConsulterHoraire() {
    /*La valeur du menu principal est 0. Donc, si *valeurMenu est déjà à 0, on propose un affichage pour 0 qui s'appelle 'Retour'.*/

    int valeurMenuHoraire=-1;

    while(valeurMenuHoraire != 0) {
        
        printf("Choix de la formation\n");
        printf("0 : Quitter\n");
        printf("1 : Formation x\n");
        printf("2 : Formation y\n");

        scanf("%d", &valeurMenuHoraire);

        //Gestion d'erreur
        while(valeurMenuHoraire < 0 || valeurMenuHoraire > 2) {
            printf("Valeur incorrecte.\n");
            scanf("%d", valeurMenuHoraire);
        }

        if(valeurMenuHoraire == 1) {
            //Bloc d'instruction pour la formation
        }

        //Et ainsi de suite
    }
}

