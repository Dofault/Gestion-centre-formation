#include<stdio.h>
#include<string.h>
#include<stdlib.h>      //Gestion de la mémoire avec malloc, free, ...

//TODO : Fixer le probleme de idFormation qui se deforme (??)
//TODO : Avec la nouvelle ecriture, quand un element est dans le formation.dat, ca fait planter à la lecture enclencée par les lignes 141 à 171

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
    char nomBase[100], nomComplete[102], idFormation[4], idFormationAnnee[6];
    char cours[20][50];
    int coursDejaDonne[20];
    int maxEtudiant, nbCours, nbEtudiant, nombreAnneeFormation, numeroAnnee, horaire[8][25];
    float prix;
    struct formation *suivant;
}formation;


int main() {
	
    //Ouverture des fichiers *dat et *res
    FILE *fdat, *fdat1, *fdat2, *fres, *fres1, *fres2;
    fdat = fopen("listeEtudiant.dat","r");
    fdat1 = fopen("listeFormateur.dat","r");
    fdat2 = fopen("listeFormation.dat","r");

    //Decl variables
    int valeurMenu, queFaire, i, x, y, z, j, k, l, tmpAnnee;
    //queFaire est une variable qui est modifiée par les fonctions : on doit naviguer avec les menus, mais la lecture et l'écriture doit se faire dans le main

	
	char temporaire[50]; // Variable temporaire pour creer nouvelleFormation->idFormationAnnee dans l'ajout formation
    char bufferNom[100];
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
    void ecrireFormation(formation *);
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

                //nomBase
                printf("\nVeuillez entrer le nom de la formation : ");
                //PAS SUPPRIMER : scanf(" ") permet de se debarasser des restes des precedents inputs des menus
                scanf(" ");
                //boucle qui permet de parcourir 100 caractères
                for(i = 0; i < 99; i++) {    
                    formationIntercale->nomBase[i] = getchar();
                    if(formationIntercale->nomBase[i] == '\n') {
                        formationIntercale->nomBase[i] = '\0';
                        break;
                    }
                }
                formationIntercale->nomBase[i] = '\0';
                formationIntercale->nomBase[99] = '\0';

                //idFormation
                //Entree de l'idFormation avec 3 caracteres max
                printf("\nVeuillez entrer l'ID de la formation (3 lettres). Notez que les caracteres excedents ne seront pas pris en compte. : ");
                i = 0;
                while(1==1) {
                    temporaire[i] = getchar();
                    if(temporaire[i] == '\n') {
                        break;
                    }
                    i++;
                }
                
                //gestion des excedents : Note que si l'utilisateur entre + de 50 caracteres (limite de temporaire[]), alors ca plante quand meme...
                for(i = 0; i < 3; i++) {
                    formationIntercale->idFormation[i] = temporaire[i];
                }

                formationIntercale->idFormation[3] = '\0';
                //TODO : parcourir les formation deja existante et verifier leur ID. Si l'ID choisi existe deja -> redemander l'entree d'un nv ID

                printf("Combien d'etudiants sont autorises par annee ? : ");
                scanf("%d", &formationIntercale->maxEtudiant);

                printf("\nSur combien d'annee la formation s'etale-t-elle ? ");
                scanf("%d", &formationIntercale->nombreAnneeFormation);
				
                for(i = 1; i <= formationIntercale->nombreAnneeFormation; i++) {     //Boucle pour parcourir les annees
                	nouvelleFormation=malloc(sizeof(formation));
                	
                    //Reattribution des valeurs donnees en DEHORS de la bouche 
                    strcpy(nouvelleFormation->nomBase, formationIntercale->nomBase);
                    strcpy(nouvelleFormation->idFormation, formationIntercale->idFormation);
                    nouvelleFormation->nombreAnneeFormation = formationIntercale->nombreAnneeFormation;
                    nouvelleFormation->maxEtudiant = formationIntercale->maxEtudiant;

                    // Creation id unique
                    // concatener dans un char : sprintf(<variable char>, <formatage comme printf>, <les valeurs>)
					sprintf(temporaire, "%d_%s", i, formationIntercale->idFormation);
                    strcpy(nouvelleFormation->idFormationAnnee, temporaire);
                    //réattribution de l'idFormation non modifié (ne pas supprimer)
                    strcpy(nouvelleFormation->idFormation, formationIntercale->idFormation);

                    //Creation du nom de la formation (nomBase [espace] i)
                    strcpy(nouvelleFormation->nomComplete, formationIntercale->nomBase);
                    sprintf(nouvelleFormation->nomComplete, "%s %d", formationIntercale->nomBase, i);
                    
                    //Assignation numero annee, nbEtudiant = 0, Max etudiant
                    nouvelleFormation->numeroAnnee = i;
                    nouvelleFormation->nbEtudiant = 0;

                    //grille horaire
                    for(k = 1; k <= 7; k ++) {
                        for(l = 1; l <= 24; l++) {
                            nouvelleFormation->horaire[k][l] = 0;
                        }
                    }

                    //Prix
                    printf("Quel est le prix d'inscription a cette annee de formation ? : ");
                    scanf("%f", &nouvelleFormation->prix);

                    //Gestion des cours
                    printf("\nCombien de cours sont donnes dans la formation pour l'annee %d ? ", i);
                    
                    // Passage par la variable test car sinon ca marche pas (?)
                    scanf("%d", &test);
                    nouvelleFormation->nbCours = test;
                    
                    for(j = 1; j <= nouvelleFormation->nbCours; j++) {
                    	
                        printf("\nQuel est le nom du cours numero %d/%2d ? : ", j, nouvelleFormation->nbCours);
                        scanf(" ");
                        for(k = 0; k < 49; k++) {
                            nouvelleFormation->cours[j][k] = getchar();
                            if(nouvelleFormation->cours[j][k] == '\n') {
                                nouvelleFormation->cours[j][k]  = '\0';
                                break;
                            }
                            nouvelleFormation->cours[j][49] = '\0'; 
                        }
                        
                        
                        // vu que le cours est creer il est dispo donc on met 0 dans deja donne
                        nouvelleFormation->coursDejaDonne[j]=0;
                    }

                    printf("\n--------------------------------\n");
                    printf("Fin de l'encodage de l'annee : %1d\n", i);
                    printf("--------------------------------\n");
                    // Ecriture
                    ecrireFormation(nouvelleFormation);
                    
                }

                printf("\nEncodage de la formation realisee avec succes.\n"); 
                printf("==============================================\n\n"); 

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
    printf("1 : Acceder aux formations (ajouter, modifier, supprimer, afficher la liste)\n");
    printf("2 : Acceder aux formateurs (ajouter, modifier, supprimer, afficher la liste)\n");
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


void ecrireFormation(formation *f) {

    FILE *fres;
    fres=fopen("listeFormation.dat", "a");

    printf("\nFormation en cours d'ajout : %s \n", f->nomBase);
    int z, y, x;

    // nom, idFormation, idFormationAnnee, numeroAnnee, nbCours, maxEtudiant, nbEtudiant, prix, nombreAnneeFormation, numeroAnnee
    fprintf(fres,"%-100s %-102s %-3s %-5s %2d %2d %4d %4d %8.2f %2d %2d ", f->nomBase, f->nomComplete, f->idFormation, f->idFormationAnnee, 
    f->numeroAnnee, f->nbCours, f->maxEtudiant, f->nbEtudiant, f->prix, f->nombreAnneeFormation, f->numeroAnnee);
    
    // ecriture jour et semaine horaire
    for(z=1;z<=7;z++) {
        for(y=1;y<=24;y++) {
                fprintf(fres,"%1d", f->horaire[z][y]);
        }
    }

    for(x=1;x<= f->nbCours; x++) {
        // print 50 caractere pour chaque cours
        fprintf(fres," %50s", f->cours[x]);
    }

    for(x=1;x<= f->nbCours; x++) {
        // ecriture coursDejaDonne[20][50]
        fprintf(fres,"%1d", f->coursDejaDonne[x]);
    }
    
    fprintf(fres,"\n");

    fclose(fres);
}