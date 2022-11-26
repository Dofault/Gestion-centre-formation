#include<stdio.h>
#include<string.h>
#include<stdlib.h>      //Gestion de la mémoire avec malloc, free, ...

int main() {
//Ouverture des fichiers *dat et *res


//Declaration des variables
int valeurMenu = -1;

/*------------------------------------------------------Fin declaration des variables----------------------------------------------------------------*/
void menuPrincipal(int *);
void menuConsulterHoraire();

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
void menuPrincipal( int *valeurMenu) {
    /*La valeur du menu principal est 0. Donc, si *valeurMenu est déjà à 0, on propose un affichage pour 0 qui s'appelle 'Retour'.*/

        printf("Veuillez entrer la valeur correspondante au menu souhaite :\n");
        printf("0 : Quitter\n");
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
	        while(valeurMenuHoraire < 0 || valeurMenuHoraire > 4) {
	            printf("Valeur incorrecte.\n");
	            scanf("%d", valeurMenuHoraire);
	        }
		}

}


