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
    int naissanceJour, naissanceMois, naissanceAnnee, niveauDiplome, nbTitre, horaire[8][25];
    struct formateur *suivant;
}formateur;

typedef struct formation {
    char nom[100];
    char cours[20][50];
    char anneeCours[5][50];
    int maxEtudiant, nombreAnneeFormation, nbCours, nbAnnee, nbEtudiant;
    float prix;
    struct formation *suivant;
    
    // Ajout, plus tard faudra supprimer anneeCours
    int numeroAnnee, horaire[8][25];
}formation;



int main() {
	
    //Ouverture des fichiers *dat et *res
    FILE *fdat, *fdat1, *fdat2, *fres, *fres1, *fres2;
    fdat = fopen("listeEtudiant.dat","r");
    fdat1 = fopen("listeFormateur.dat","r");
    fdat2 = fopen("listeFormation.dat","r");

    //Declaration des variables
    int valeurMenu, queFaire, i, x, y, z;
    //queFaire est une variable qui est modifiée par les fonctions : en effet, on doit naviguer avec les menus, mais la lecture et l'écriture doit se faire dans le
    //main. (Préférence de M. Carpentier) Donc, si un menu nécessite une lecture/écriture, il faut lui faire varier la valeur de queFaire. Voir valeurMenu == 3 pour exemple

    // Var formation
    int nbFormation=0;
    formation *formationDebut, *formationCourant, *formationSuivant, *nouvelleFormation, *formationIntercale;

    // Var etudiant
    int nbEtudiant = 0;
    etudiant *etudiantDebut,*etudiantCourant,*etudiantSuivant,*etudiantIntercale;
    
    // Var formateur
    int nbFormateur=0;
    formateur *formateurDebut,*formateurCourant,*formateurSuivant,*formateurIntercale;
    
    
    /*------------------------------------------------------Fin declaration des variables----------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    
    // Declaration des fonctions
    void changerMenu(int *);
    void menuConsulterHoraire();
    int menuGererFormation();
    int gestionFormation();

    /*------------------------------------------------------Fin declaration des fonctions ---------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
   
	// LECTURE DES ETUDIANTS, VARIABLE PERTINENTE : nbEtudiant ET etudiantDebut pour les chaines
	// -----------------------------------------------------------------------------------------
	etudiantCourant=malloc(sizeof(etudiant));
	etudiantDebut=etudiantCourant;
	fscanf(fdat,"%30s", &etudiantCourant->nom);
	while(!feof(fdat)) {
		fscanf(fdat," %30s %100s %2d %2d %4d %2d %8f %8f %8f", &etudiantCourant->prenom, &etudiantCourant->nomDeFormation, 
		&etudiantCourant->naissanceJour, &etudiantCourant->naissanceMois, &etudiantCourant->naissanceAnnee, &etudiantCourant->annee, &etudiantCourant->montantAPayer, 
		&etudiantCourant->montantPaye, &etudiantCourant->reduction);
	  	etudiantSuivant=malloc(sizeof(etudiant));
	  	etudiantCourant->suivant=etudiantSuivant;
	  	nbEtudiant++;
   	  	etudiantCourant=etudiantSuivant;
		fscanf(fdat,"%30s", &etudiantCourant->nom);
	}      
	etudiantCourant=etudiantDebut;
	for(i=0;i<nbEtudiant;i++) {
		etudiantCourant=etudiantCourant->suivant;
	}   
	etudiantCourant->suivant=NULL;  // free(etudiantSuivant);
	
	
	


	// LECTURE DES FORMATEUR DANS LA VARIABLE nbFormateur ET formateurDebut
	// -------------------------------------------------------------------
	formateurCourant=malloc(sizeof(formateur));
	formateurDebut=formateurCourant;
	fscanf(fdat1,"%30s", &formateurCourant->nom);
	while(!feof(fdat1)) {
		fscanf(fdat1," %30s %2d %2d %4d %2d %2d ", &formateurCourant->prenom, 
		&formateurCourant->naissanceJour, &formateurCourant->naissanceMois, &formateurCourant->naissanceAnnee, &formateurCourant->niveauDiplome, 
		&formateurCourant->nbTitre);
		// Lecture de l'horaire
		for(i=1;i<=7;i++) {
			for(x=1;x<=24;x++) {
				
				fscanf(fdat1,"%1d", &formateurCourant->horaire[i][x]);
			}
		}
		// Passage en revu de tout les titres du formateur
		for(i=1;i<= formateurCourant->nbTitre; i++) {
			// scan 100 caract�re par nombre de titre
			fscanf(fdat1," %100s", formateurCourant->titre[i]);
		}
	  	formateurSuivant=malloc(sizeof(formateur));
	  	formateurCourant->suivant=formateurSuivant;
	  	nbFormateur++;
   	  	formateurCourant=formateurSuivant;
		fscanf(fdat1,"%30s", &formateurCourant->nom);
	}
	formateurCourant=formateurDebut;
	for(i=0;i<nbFormateur;i++){
		formateurCourant=formateurCourant->suivant;
	}
	formateurCourant->suivant=NULL;
   
   



   
	// LECTURE DES FORMATION, VARIABLE PERTINENTE : nbFormation ET formationDebut
	// -------------------------------------------------------------------
	formationCourant=malloc(sizeof(formation));
	formationDebut=formationCourant;
	fscanf(fdat2,"%100s", &formationCourant->nom);
	while(!feof(fdat2)) {
		fscanf(fdat2," %2d %2d %4d %4d %8f ", &formationCourant->numeroAnnee, &formationCourant->nbCours, &formationCourant->maxEtudiant,
		&formationCourant->nbEtudiant, &formationCourant->prix);
		// Lecture de l'horaire, 7jours * 24h
		for(i=1;i<= 7; i++) {
			for(x=1;x<=24;x++) {
				fscanf(fdat2, "%1d", &formationCourant->horaire[i][x]);
			}
		}
		// Lecture des cours
		for(i=1;i<=formationCourant->nbCours; i++) {
			fscanf(fdat2, " %50s", &formationCourant->cours[i]);
		}
	  	formationSuivant=malloc(sizeof(formation));
	  	formationCourant->suivant=formationSuivant;
	  	nbFormation++;
   	  	formationCourant=formationSuivant;
		fscanf(fdat2,"%100s", &formationCourant->nom);
	}
	formationCourant=formationDebut;
	for(i=0;i<nbFormation;i++) {
		formationCourant=formationCourant->suivant;
	}   
	formationCourant->suivant=NULL;
	
	
	
	
   
   
   	// Fin de la lecture ouverture des RES
	fclose(fdat); 
	fclose(fdat1); 
	fclose(fdat2); /*
    fres = fopen("listeEtudiant.dat","w");
    fres1 = fopen("listeFormateur.dat","w");
    fres2 = fopen("listeFormation.dat","w");*/
   
   
    //Initialisation de la valeur de valeurMenu
    changerMenu(&valeurMenu);
    while(valeurMenu != 0) {
        if(valeurMenu == 1) {
            // consulter horaire
            menuConsulterHoraire();
        }
    
        if(valeurMenu == 2) {
            // ajouter élève
        }
    
        if(valeurMenu == 3) {
            // fonction gestion formation
           queFaire = menuGererFormation();
           if(queFaire != 0) {
                //Soit lire ou écrire une formation/formateur dans un fichier
                if(queFaire == 1) {
                    //Ici on sait que l'utilisateur souhaite érire une nouvelle formation.
                    printf("===================================\n");
                    //Création d'un espace mémoire pour la nouvelleFormation
                    nouvelleFormation = malloc(sizeof(formation));
                    nouvelleFormation->suivant = formationDebut->suivant;
                    formationDebut->suivant = nouvelleFormation; 

                    //Compléter les caractéristiques de la formation
                    printf("Quel est le nom de la nouvelle formation ?");
                    scanf("%s",&nouvelleFormation->nom);
                    printf("Quels cours sont donnés dans la nouvelle formation ?"); //pour le moment on ne met que le premier cours, pour test
                    scanf("%s",&nouvelleFormation->cours[1]);
                    printf("En combien d'année se réalise la formation ?\n");
                    scanf("%d", &nouvelleFormation->nombreAnneeFormation);
                    printf("Quels cours sont donnés à chaque année ?"); //Complètement skip ca pour le moment, pas le temps de faire les boucles,
                    //scanf("%s",&nouvelleFormation->);
                    printf("Combien d'étudiants peut acceuillir la nouvelle formation ?");
                    scanf("%d",&nouvelleFormation->maxEtudiant);
                    printf("Quel est le prix pour chaque étudiant pour cette formation ?");
                    scanf("%f",&nouvelleFormation->prix);
                }
           }
        }
    
        if(valeurMenu == 4) {
            // fonction consulter etudiant
        }

         changerMenu(&valeurMenu);
        
    }
        
    //Fermeture des flux de lecture et d'écriture
    fclose(fres); fclose(fres1); fclose(fres2); printf("Au revoir et a bientot.\n");

}   //Fin du programme principal.


//ChangerMenu
void changerMenu(int *valeurMenu) {
    
    printf("Veuillez entrer la valeur correspondante au menu souhaite :\n");
    printf("0 : Quitter\n");
    printf("1 : Acceder aux horaires\n");
    printf("2 : Ajouter un etudiant\n");
    printf("3 : Gerer les formations\n");
    printf("4 : Consulter les etudiants\n");
    printf("Votre choix : ");

    scanf("%d", &*valeurMenu);

    //Gestion d'erreur
    while(*valeurMenu < 0 || *valeurMenu > 4) {
        printf("Valeur incorrecte.\n");
        printf("Votre choix : ");
        scanf("%d", &*valeurMenu);
    }

}


void menuConsulterHoraire() {
    int valeurMenuHoraire=-1;
        
    printf("Choix de la formation\n");
    printf("0 : Quitter\n");
    printf("1 : Formation x\n");
    printf("2 : Formation y\n");

    scanf("%d", &valeurMenuHoraire);

    //Gestion d'erreur
    while(valeurMenuHoraire < 0 || valeurMenuHoraire > 2) {
        printf("Valeur incorrecte.\n");
        scanf("%d", &valeurMenuHoraire);
    }

    if(valeurMenuHoraire == 1) {
        //Bloc d'instruction pour la formation
        printf("Vous avez choisi 1\n");
    }

    //Et ainsi de suite
}


int menuGererFormation() {
    int valeurMenuFormation=-1;
    int queFaire = 0; //0 signifie ne rien faire. Cette valeur est retournée si l'utilisateur n'a pas besoin de lire/ecrire dans un fichier
        
    printf("Choix de la formation\n");
    printf("0 : Quitter\n");
    printf("1 : Accéder aux formations\n");
    printf("2 : Accéder aux Formateurs y\n");
    printf("Votre choix : ");

    scanf("%d", &valeurMenuFormation);

    //Gestion d'erreur
    while(valeurMenuFormation < 0 || valeurMenuFormation > 2) {
        printf("Valeur incorrecte.\n");
        printf("Votre choix : ");
        scanf("%d", &valeurMenuFormation);
    }

    if(valeurMenuFormation == 1) {
        queFaire = gestionFormation(); 
        return queFaire;
        /*
		 Regarde avec gestionFormation() : 
          Si l'utilisateur a choisi l'option 1, on sait qu'il veut ajouter une formation. Ca implique qu'il doive écrire dans un fichier.
          On return ici 1 et dans le main on fait écrire toutes les parties d'une structure Formation.
        */
    }

    if(valeurMenuFormation == 2) {
        //TODO : prévoir ce cas
        //Note : queFaire devra être différent de 0,1,2 et 3 car ces options sont déjà reprises dans le cas 1 et il faut que queFaire soit différent pour chaque
        //option regroupée dans le main -->
        //if(valeurMenu == X) {}
    }
}

//Est appelée depuis menuGererFormation()
int gestionFormation() {
    int queFaire = 0;
    int menu;
    printf("0 : Quitter\n");
    printf("1. Ajouter une formation\n");
    printf("2. Modifier une formation\n");
    printf("3. Afficher la liste des formations");

    printf("Votre choix : ");
    scanf("%d", &menu);

    while(menu < 0 || menu > 3) {
        printf("Valeur incorrecte.\n");
        printf("Votre choix : ");
        scanf("%d", &menu);
    }

    queFaire = menu;
    return queFaire;
}

