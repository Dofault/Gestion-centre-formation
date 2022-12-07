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
    char nomBase[100], nomComplete[102], idFormation[3], idFormationAnnee[5];
    char cours[20][50];
    int coursDejaDonne[20][5];
    int maxEtudiant, nbCours, nbEtudiant, nombreAnneeFormation, numeroAnnee, horaire[8][25];
    float prix;
    struct formation *suivant;
}formation;



void ecrireFormation(struct formation f) {

    FILE *fres;
    fres=fopen("listeFormation.dat", "w");

    printf("\nFormation en cours d'ajout : %s \n", f.nomBase);
    int z, y, x;

    // nom, idFormation, idFormationAnnee, numeroAnnee, nbCours, maxEtudiant, nbEtudiant, prix, nombreAnneeFormation, numeroAnnee
    fprintf(fres,"%-100s %-102s %-3s %-5s %2d %2d %4d %4d %8.2f %2d %2d ", f.nomBase, f.nomComplete, f.idFormation, f.idFormationAnnee, 
    f.numeroAnnee, f.nbCours, f.maxEtudiant, f.nbEtudiant, f.prix, f.nombreAnneeFormation, f.numeroAnnee);
    
    // ecriture jour et semaine horaire
    for(z=1;z<=7;z++) {
        for(y=1;y<=24;y++) {
                fprintf(fres,"%1d", f.horaire[z][y]);
        }
    }

    for(x=1;x<= f.nbCours; x++) {
        // print 50 caractere pour chaque cours
        fprintf(fres," %50s", f.cours[x]);
    }

    for(x=1;x<= f.nbCours; x++) {
        // ecriture coursDejaDonne[20][50]
        fprintf(fres,"%1d", f.coursDejaDonne[x]);
    }
    
    fprintf(fres,"\n");

    fclose(fres);
}



int main() {
	
    //Ouverture des fichiers *dat et *res
    FILE *fdat, *fdat1, *fdat2, *fres, *fres1, *fres2;
    fdat = fopen("listeEtudiant.dat","r");
    fdat1 = fopen("listeFormateur.dat","r");
    fdat2 = fopen("listeFormation.dat","r");

    //Decl variables
    int valeurMenu, queFaire, i, x, y, z, j, k, l, tmpAnnee;
    //queFaire est une variable qui est modifiée par les fonctions : on doit naviguer avec les menus, mais la lecture et l'écriture doit se faire dans le main

	
	char temporaire[5]; // Variable temporaire pour creer nouvelleFormation->idFormationAnnee dans l'ajout formation
	int test; // Variable temporaire qu'on peut utiliser quand on veut
	
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
    /*------------------------------------------------------Debut declaration fonction ------------------------------------------------------------------*/
    
    void changerMenu(int *);
    void menuConsulterHoraire();
    void ecrireFormation(struct formation);
    int menuGererFormation();
    int gestionFormation();

    /*------------------------------------------------------Fin declaration des fonctions ---------------------------------------------------------------*/
    /*--------------------------------------------------------Debut de la lecture -----------------------------------------------------------------------*/
   
	// LECTURE DES ETUDIANTS, VARIABLE PERTINENTE : nbEtudiant ET etudiantDebut pour les chaines
	// -----------------------------------------------------------------------------------------
	etudiantCourant=malloc(sizeof(etudiant));
	etudiantDebut=etudiantCourant;
	fscanf(fdat,"%30s", etudiantCourant->nom);
	while(!feof(fdat)) {
		fscanf(fdat," %30s %100s %2d %2d %4d %2d %8f %8f %8f", etudiantCourant->prenom, etudiantCourant->nomDeFormation, 
		&etudiantCourant->naissanceJour, &etudiantCourant->naissanceMois, &etudiantCourant->naissanceAnnee, &etudiantCourant->annee, &etudiantCourant->montantAPayer, 
		&etudiantCourant->montantPaye, &etudiantCourant->reduction);
	  	etudiantSuivant=malloc(sizeof(etudiant));
	  	etudiantCourant->suivant=etudiantSuivant;
	  	nbEtudiant++;
   	  	etudiantCourant=etudiantSuivant;
		fscanf(fdat,"%30s", etudiantCourant->nom);
	}      
	etudiantCourant=etudiantDebut;
	for(i=0;i<nbEtudiant;i++) {
		etudiantCourant=etudiantCourant->suivant;
	}   
	etudiantCourant->suivant=NULL;  // free(etudiantSuivant);
	
	
	


	// LECTURE DES FORMATEUR VARIABLE PERTINENTE : nbFormateur ET formateurDebut
	// -------------------------------------------------------------------
	formateurCourant=malloc(sizeof(formateur));
	formateurDebut=formateurCourant;
	fscanf(fdat1,"%30s", formateurCourant->nom);
	while(!feof(fdat1)) {
		fscanf(fdat1," %30s %2d %2d %4d %2d %2d ", formateurCourant->prenom, 
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
			// scan 100 caractere par nombre de titre
			fscanf(fdat1," %100s", formateurCourant->titre[i]);
		}
	  	formateurSuivant=malloc(sizeof(formateur));
	  	formateurCourant->suivant=formateurSuivant;
	  	nbFormateur++;
   	  	formateurCourant=formateurSuivant;
		fscanf(fdat1,"%30s", formateurCourant->nom);
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
	fscanf(fdat2,"%100s", formationCourant->nomBase);
	while(!feof(fdat2)) {
		fscanf(fdat2," %102s %3s %5s %2d %2d %4d %4d %8f %2d %2d ", &formationCourant->nomComplete, &formationCourant->idFormation, &formationCourant->idFormationAnnee, &formationCourant->numeroAnnee, &formationCourant->nbCours, &formationCourant->maxEtudiant,
		&formationCourant->nbEtudiant, &formationCourant->prix, &formationCourant->nombreAnneeFormation, &formationCourant->numeroAnnee);
		// Lecture de l'horaire, 7jours * 24h
		for(i=1;i<= 7; i++) {
			for(x=1;x<=24;x++) {
				fscanf(fdat2, "%1d", &formationCourant->horaire[i][x]);
			}
		}
		// Lecture des cours
		for(i=1;i<=formationCourant->nbCours; i++) {
			fscanf(fdat2, " %50s", formationCourant->cours[i]);
		}
        // Lecture des cours deja donnee
        for(i=1;i<=formationCourant->nbCours; i++) {
			fscanf(fdat2, "%1d", &formationCourant->coursDejaDonne[i]);
		}
	  	formationSuivant=malloc(sizeof(formation));
	  	formationCourant->suivant=formationSuivant;
	  	nbFormation++;
   	  	formationCourant=formationSuivant;
		fscanf(fdat2,"%100s", formationCourant->nomBase);
	}
    //Attribution de NULL pour la dernière formation->suivant
	formationCourant=formationDebut;
	for(i=0;i<nbFormation;i++) {

		formationCourant=formationCourant->suivant;
	}   
	formationCourant->suivant=NULL;
	
	
	
	
   
   
	fclose(fdat); 
	fclose(fdat1); 
	fclose(fdat2); /*
    fres = fopen("listeEtudiant.dat","w");
    fres1 = fopen("listeFormateur.dat","w");
    fres2 = fopen("listeFormation.dat","w");*/
   
    // --------------------------------------------------------------------FIN DE LA LECTURE --------------------------------------------------------------------------
    // ---------------------------------------------------------------------LANCEMENT DU MENU -------------------------------------------------------------------------
    changerMenu(&valeurMenu);
    while(valeurMenu != 0) {
        if(valeurMenu == 1) {
            // consulter horaire
            menuConsulterHoraire();
        }
    

        if(valeurMenu == 2) {
            // ajouter élève
        }
    
        
        if(valeurMenu == 3) {   //Gestion formation et formateur
            // valeur possible menuGererFormation() :        1 : ajouter formation        2 : modifier formation      3 : afficher liste formation
            queFaire = menuGererFormation();
            if(queFaire == 1) {     //Ajouter formation
                //allouer la mémoire
                formationIntercale = malloc(sizeof(formation));

                printf("\nVeuillez entrer le nom de la formation : ");
                scanf("%s", formationIntercale->nomBase);
                printf("\nVeuillez entrer l'ID de la formation (3 lettres) : ");
                scanf("%s", formationIntercale->idFormation);
                //TODO : parcourir les formation deja existante et verifier leur ID. Si l'ID choisi existe deja -> redemander l'entree d'un nv ID

                printf("\nSur combien d'annee la formation s'etale-t-elle ? ");
                scanf("%d", &formationIntercale->nombreAnneeFormation);
                
				
                for(i = 1; i <= formationIntercale->nombreAnneeFormation; i++ ) {     //Boucle pour parcourir les annees
                	nouvelleFormation=malloc(sizeof(formation));
                	
                    // Creation id unique
                    // concatener dans un char : sprintf(<variable char>, <formatage comme printf>, <les valeurs>)
					sprintf(temporaire, "%d_%s", i, formationIntercale->idFormation);
                    strcpy(nouvelleFormation->idFormationAnnee, temporaire);

                    //Creation du nom de la formation (nomBase [espace] i)
                    strcpy(nouvelleFormation->nomComplete, formationIntercale->nomBase);
                    sprintf(nouvelleFormation->nomComplete, "%s %d", formationIntercale->nomBase, i);
                    
                    //grille horaire
                    for(k = 1; k <= 7; k ++) {
                        for(l = 1; l <= 24; l++) {
                            nouvelleFormation->horaire[k][l] = 0;
                        }
                    }

                    //Gestion des cours
                    printf("\nCombien de cours sont donnes dans la formation pour l'annee %d ?", i);
                    
                    // Passage par la variable test car sinon ea marche pas (?)
                    scanf("%d", &test);
                    nouvelleFormation->nbCours = test;
                    
                    for(j = 1; j <= nouvelleFormation->nbCours; j++) {
                    	
                        printf("\nQuel est le nom du cours numero %d/%02d ? : ", j, nouvelleFormation->nbCours);
                        scanf("%s", nouvelleFormation->cours[j]);
                        
                        // vu que le cours est creer il est dispo donc on met 0 dans deja donne
                    }

                    printf("\nFin de l'encodage de l'annee : %1d", i);
                    // Ecriture
                    ecrireFormation(*nouvelleFormation);
                    
                }

                printf("\nEncodage de la formation realisee avec succes.\n"); 


                //Enregistrement de la formation dans le .dat
                //TODO : Voir si c'est possible de le faire avec un fonction -> plus facile de gerer l'ouverture et la fermeture des flux d'ecriture et lecture 

            }  


            if(queFaire == 2) {

                // ****** A FAIRE : MENU POUR MODIFIER UNE FORMATION ET DONC MODIFIER formationDAT ********
            }

            if(queFaire == 3) {

                // ********* A FAIRE : AFFICHER LA LISTE DES FORMATIONS + POSSIBILITE D'EN SUPPRIMER *********
            }
            
            // tache effectuee, on peut reset que faire
            queFaire = 0;
        }
    

        if(valeurMenu == 4) {
            // fonction consulter etudiant
        }

        changerMenu(&valeurMenu);
        
    }
        
    fclose(fres); fclose(fres1); fclose(fres2); printf("Au revoir et a bientot.\n");
}   // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_   FIN  DU  PROGRAMME MAIN -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_


//ChangerMenu
void changerMenu(int *valeurMenu) {
    
    printf("Veuillez entrer la valeur correspondante au menu souhaite :\n");
    printf("0 : Quitter\n");
    printf("1 : Acceder aux horaires\n");
    printf("2 : Ajouter un etudiant\n");
    printf("3 : Gerer les formations ou les formateurs\n");
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
    printf("1 : \n");
    printf("2 : \n");

    // ***** A FAIRE : AFFICHER LA LISTE DES FORMATIONS ET DES QUE L'UTILISATEUR SELECTIONNE UNE FORMATION CA AFFICHE L'HORAIRE ************

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

// Les valeurs possible de retour :
// 1 : ajouter formation
// 2 : modifier formation
// 3 : afficher liste formation
int menuGererFormation() {
    int valeurMenuFormation=-1;
    int queFaire = 0; //0 signifie ne rien faire.
        
    printf("Choix de la formation\n");
    printf("0 : Quitter\n");
    printf("1 : Accéder aux formations (ajouter, modifier, supprimer, afficher la liste)\n");
    printf("2 : Accéder aux formateurs (ajouter, modifier, supprimer, afficher la liste)\n");
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

        // ******* A FAIRE : Creer fonction gestionFormateur et renvoyer queFaire 3 valeurs différente (ajouter, modifier, supprimer formateur)
    }
}


//Est appelée depuis menuGererFormation()
// Les valeurs possible de retour :
// 1 : ajouter formation
// 2 : modifier formation
// 3 : afficher liste formation
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

