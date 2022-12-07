#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Ce fichier sert � ecrire dans les fichiers dat et � tester la mise en forme
// il y a aussi les ordres d'�criture � copier coller
main()
{
	FILE *fres, *fres1, *fres2; 
    fres = fopen("listeEtudiant.dat","w");
    fres1 = fopen("listeFormateur.dat","w");
    fres2 = fopen("listeFormation.dat","w");
    
	int x, y, i, z;
	// ORDRE D'ECRITURE POUR ETUDIANT "e" ETUDIANT : printf("%s %s %s %2d %2d %4d %2d %8.2f %8.2f %8.2f\n", e->nom, e->prenom, e->nomDeFormation, e->naissanceJour, e->naissanceMois, e->naissanceAnnee, e->annee, e->montantAPayer, e->montantPaye, e->reduction);
	
	
	/* ECRITURE DES FORMATEURS DANS LE MAIN
	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
   // ecriture formateur
	formateurCourant=formateurDebut;
	for(i=0;i<nbFormateur;i++){
		printf(" %-30s %-30s %2d %2d %4d %2d", formateurCourant->nom, formateurCourant->prenom, formateurCourant->naissanceJour, 
		formateurCourant->naissanceMois, formateurCourant->naissanceAnnee, formateurCourant->nbTitre);
		for(x=1; x<= formateurCourant->nbTitre; x++) {
		printf("%s ", formateurCourant->titre[x]);
		}
		printf("\n");
		// Ecriture horaire formateur
		// Pas encore defini precisement chaque valeur du tableau
		// mais en principe -1 = indiponible, 0 : disponible, 1 = a d�j� cours
		for(y=1;y<=24;y++) {
			for(z=1;z<=7;z++) {
				printf("%1d", formateurCourant->horaire[z][y]);
			}
			printf("\n");
		}
		formateurCourant=formateurCourant->suivant;
	}
	
    
	/* ECRITURE DES FORMATIONS DANS LE MAIN
	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
   	formationCourant=formationDebut;
	for(i=0;i<nbFormation;i++){
		printf("%s %2d nbCours:%2d %4d %4d %8.2f\nHoraire :\n", formationCourant->nom, formationCourant->numeroAnnee, formationCourant->nbCours, 
		formationCourant->maxEtudiant, formationCourant->nbEtudiant, formationCourant->prix);	
		for(y=1;y<=24;y++){
			for(x=1;x<=7;x++) {
				printf("%1d", formationCourant->horaire[x][y]);
			}
			printf("\n");
		}
		formationCourant=formationCourant->suivant;
	}
    

    
  	--------------------------------------------------------
	VARIABLES ETUDIANT :
	--------------------------------------------------------
	char nom[30], prenom[30], nomDeFormation[100], 
	int naissanceJour, naissanceMois, naissanceAnnee, annee, 
	float montantAPayer, montantPaye, reduction;
	-------------------------------------------------------- */
	fprintf(fres,"%-30s %-30s %-100s %2d %2d %4d %2d %8.2f %8.2f %8.2f\n", "Aure", "Desp", "Info", 2, 5, 2000, 1, 4000.30, 2000.30, 500);
	fprintf(fres,"%-30s %-30s %-100s %2d %2d %4d %2d %8.2f %8.2f %8.2f\n", "Geof", "Dela", "Info", 1, 6, 1993, 1, 4100.30, 2100.30, 300);
	fprintf(fres,"%-30s %-30s %-100s %2d %2d %4d %2d %8.2f %8.2f %8.2f\n", "Nico", "Bal", "Info", 1, 6, 1991, 1, 4110.30, 2200.30, 400);
	fprintf(fres,"%-30s %-30s %-100s %2d %2d %4d %2d %8.2f %8.2f %8.2f\n", "Jean", "Carp", "Compta", 2, 6, 1921, 1, 3333.30, 2220.30, 420);
	
/*	--------------------------------------------------------
    VARIABLES FORMATION:
	--------------------------------------------------------
    char nomBase[100], nomComplete[102], idFormation[3], idFormationAnnee[5];
    char cours[20][50];
    int coursDejaDonne[20][50];
    int maxEtudiant, nbCours, nbEtudiant, nombreAnneeFormation, numeroAnnee, horaire[8][25];
    float prix;
	---------------------------------------------------------*/
	int nbCours;
	int numeroAnnee;
	
	for(i=1;i<=5;i++) {
		nbCours=i+1;
		numeroAnnee=i;
		// nom, idFormation, idFormationAnnee, numeroAnnee, nbCours, maxEtudiant, nbEtudiant, prix, nombreAnneeFormation, numeroAnnee
		fprintf(fres2,"%-100s %-102s %-3s %-5s %2d %2d %4d %4d %8.2f %2d %2d ", "gNomBaseFormation1", "NomComplete1", "CUI", "CUI_1", numeroAnnee, nbCours, 234, 32, 4321.23, 3, 1);
		
		// ecriture jour et semaine
		for(z=1;z<=7;z++) {
			for(y=1;y<=24;y++) {
				// modulo comme �a c'est pas tjr 0
				if(y%3 == 0) {
					fprintf(fres2,"%1d", 1);
				}
				else
				{
					fprintf(fres2,"%1d", 0);
				}
			}
		}

		for(x=1;x<= nbCours; x++) {
			// print 20 caract�re pour chaque cours
			fprintf(fres2," %7s%02d%41s", "UnCours", i, "");
		}

		for(x=1;x<= nbCours; x++) {
			// ecriture coursDejaDonne[20][50]
			fprintf(fres2,"%1d", 0);
		}
		
		fprintf(fres2,"\n");
		
	}



/*
	--------------------------------------------------------
	VARIABLE FORMATEUR :
	--------------------------------------------------------
    char nom[30], prenom[30], titre[10][100], nbTitre;
    int naissanceJour, naissanceMois, naissanceAnnee, niveauDiplome;
    int horaire[8][25]
	--------------------------------------------------------*/  
	
	int nbFormateur=4;
	for(x=1; x<= nbFormateur; x++) {
		int nbTitre=1+x;
		
		switch(x) {
			case 1 :
				fprintf(fres1,"%-30s %-30s %2d %2d %4d %2d %2d ", "SNomForm1", "ZPrenomForm1", 1, 4, 1990, 4, nbTitre);
				break;
			case 2 :
				fprintf(fres1,"%-30s %-30s %2d %2d %4d %2d %2d ", "AnomForm2", "RPrenomForm2", 1, 4, 1991, 2, nbTitre);
				break;
			case 3 :
				fprintf(fres1,"%-30s %-30s %2d %2d %4d %2d %2d ", "CnomForm3", "FPrenomForm3", 1, 4, 1991, 6, nbTitre);
				break;	
			case 4 :
				fprintf(fres1,"%-30s %-30s %2d %2d %4d %2d %2d ", "DnomForm4", "VPrenomForm4", 1, 4, 1995, 7, nbTitre);
				break;	
		}
		
		// ecriture jour et semaine
		for(i=1;i<=7;i++) {
			for(y=1;y<=24;y++) {
				// modulo comme �a c'est pas tjr 0
				if(y%3 == 0) {
					fprintf(fres1,"%1d", 1);
				}
				else
				{
					fprintf(fres1,"%1d", 0);
				}
			}
		}
		
		
		for(i=1;i<= nbTitre; i++) {
			// print 100 caract�re pour chaque formation
			fprintf(fres1," %7s%02d%91s", "FormationNumero", i, "");
		}
		fprintf(fres1,"\n");
		
		
	}
	
	
/* --------------------------------------------------------------- Creation d'une nvelle formation à la date du 02-12-22 -------------------------------------------*/
/*Une de nos première version, je la modifie, mais pour garder une backup, je la copie et colle ici. On pourra supprimer sans peur quand le nouveau système d'ajout
(celui basé sur notre mise en commun de l'algorithme que j'ai propose [voir OrdreDeRealisation.txt])*/

/*

queFaire = menuGererFormation();
           if(queFaire != 0) {
                if(queFaire == 1) {
                    printf("===================================\n");
                    nouvelleFormation = malloc(sizeof(formation));
                    nouvelleFormation->suivant = formationDebut->suivant;
                    formationDebut->suivant = nouvelleFormation; 
                    printf("Quel est le nom de la nouvelle formation ?");
                        scanf("%s",&nouvelleFormation->nom); // nom[100]
                    printf("Quels cours sont donnés dans la nouvelle formation ? (1 cours minimum)");
                        nouvelleFormation->nbCours = 1;
                        // On ajoute le cours dans le nouveau slot nbCours + 1
                        scanf("%s",&nouvelleFormation->cours[1]);
                        char utilisateurCours[50];
                        strcpy(utilisateurCours, "vide");
                        while(strcmp(utilisateurCours, "STOP") != 0) {
                            // On ajoute ce qu'à mit l'utilisateur dans nouvelleFormation->Cours
                            nouvelleFormation->nbCours += 1;
                            strcpy(nouvelleFormation->cours[nouvelleFormation->nbCours], utilisateurCours);
                            printf("Quels autre cours sont donnés dans la nouvelle formation ? (STOP pour arreter l'insertion)");
                            scanf("%s",&utilisateurCours);
                            // ici on peut eventuellement mettre des conditions de verif sur char utilisateurCours[50]
                        }
                        nouvelleFormation->nbCours -= 1; // enregistr en trop
                    printf("Combien d'étudiants peut acceuillir la nouvelle formation ?");
                        scanf("%d",&nouvelleFormation->maxEtudiant);
                    printf("Quel est le prix pour chaque étudiant pour cette formation ?");
                        scanf("%f",&nouvelleFormation->prix);
                    // Nouvelle formation donc première année, on fera une interface pour ajouter des années
                    nouvelleFormation->numeroAnnee=1;
                    nouvelleFormation->nbEtudiant=0;
                    // Creation de l'horaire
                    for(i=1;i<=7;i++) {
                        for(x=1;x<=24;x++) {
                            nouvelleFormation->horaire[i][x]=0;
                        }
                    }
                    printf("\nFormation ajouté : \n--------------------\nNom : %s\nAnnee : %2d\nNombre de cours :%2d\nNombre maximum d'étudiant: %4d\nNombre d'étudiant : %4d\nPrix : %8.2f\n"
                    , nouvelleFormation->nom, nouvelleFormation->numeroAnnee, nouvelleFormation->nbCours, nouvelleFormation->maxEtudiant, nouvelleFormation->nbEtudiant, nouvelleFormation->prix);	
                    printf("--------------------------\n");


                    // ***** A FAIRE: AJOUTER nouvelleFormation dans le fdat *******


                }

*/
	
	

	
	
	
	
	
	
}
