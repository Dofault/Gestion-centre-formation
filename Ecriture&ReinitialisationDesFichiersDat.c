#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Ce fichier sert à ecrire dans les fichiers dat et à tester la mise en forme
// il y a aussi les ordres d'écriture à copier coller
main()
{
	FILE *fres, *fres1, *fres2; 
    fres = fopen("listeEtudiant.dat","w");
    fres1 = fopen("listeFormateur.dat","w");
    fres2 = fopen("listeFormation.dat","w");
    
	// ORDRE D'ECRITURE POUR ETUDIANT "e" ETUDIANT : printf("%s %s %s %2d %2d %4d %2d %8.2f %8.2f %8.2f\n", e->nom, e->prenom, e->nomDeFormation, e->naissanceJour, e->naissanceMois, e->naissanceAnnee, e->annee, e->montantAPayer, e->montantPaye, e->reduction);
	
	/* ORDRE D'ECRITURE FORMATEUR
	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
	formateurCourant=formateurDebut;
	for(i=0;i<nbFormateur;i++){
		printf(" %-30s %-30s %2d %2d %4d %2d", formateurCourant->nom, formateurCourant->prenom, formateurCourant->naissanceJour, 
		formateurCourant->naissanceMois, formateurCourant->naissanceAnnee, formateurCourant->nbTitre);
		for(x=1; x<= formateurCourant->nbTitre; x++) {
		printf("%s ", formateurCourant->titre[x]);
		}
		printf("\n");
		formateurCourant=formateurCourant->suivant;
	}
	*/
    
    
    
    
    
/*	--------------------------------------------------------
	ECRITURE DES VARIABLES D'ETUDIANT :
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
    ECRITURE DES VARIABLES DE FORMATION PAS FINIS :
	--------------------------------------------------------
    char nom[100], cours[20][50], anneeCours[5][50];
    int maxEtudiant, nombreAnneeFormation, nbCours, nbAnnee;
    float prix;
	---------------------------------------------------------
	int nbCours=4;
	int nbAnnee;
	fprintf(fres2,"%-100s %2d %2d", "gNomFormation1", nbCours, nbAnnee);
	int i;
	for(i=1;i<= nbCours; i++) {
		// print 20 caractère pour chaque cours
		fprintf(fres2,"%7s%02d%11s ", "UnCours", i, "          ");
	}
	
	for(i=1;i<= nbAnnee; i++) {
		// print 20 caractère pour chaque cours
		fprintf(fres2,"%7s%02d%11s ", "UnCours", i, "          ");
	}
*/

/*
	--------------------------------------------------------
	ECRITURE DES VARIABLES DE FORMATEUR :
	--------------------------------------------------------
    char nom[30], prenom[30], titre[10][100], nbTitre;
    int naissanceJour, naissanceMois, naissanceAnnee, niveauDiplome;
	--------------------------------------------------------*/  
	
	int nbFormateur=4;
	int i, x;
	for(x=1; x<= nbFormateur; x++) {
		int nbTitre=1+x;
		
		switch(x) {
			case 1 :
				fprintf(fres1,"%-30s %-30s %2d %2d %4d %2d %2d", "SNomForm1", "ZPrenomForm1", 1, 4, 1990, 4, nbTitre);
				break;
			case 2 :
				fprintf(fres1,"%-30s %-30s %2d %2d %4d %2d %2d", "AnomForm2", "RPrenomForm2", 1, 4, 1991, 2, nbTitre);
				break;
			case 3 :
				fprintf(fres1,"%-30s %-30s %2d %2d %4d %2d %2d", "CnomForm3", "FPrenomForm3", 1, 4, 1991, 6, nbTitre);
				break;	
			case 4 :
				fprintf(fres1,"%-30s %-30s %2d %2d %4d %2d %2d", "DnomForm4", "VPrenomForm4", 1, 4, 1995, 7, nbTitre);
				break;	
		}
		
		for(i=1;i<= nbTitre; i++) {
			// print 100 caractère pour chaque formation
			fprintf(fres1," %7s%02d%91s", "FormationNumero", i, "");
		}
		fprintf(fres1,"\n");
		
		
	}
	
	

	
	

	
	
	
	
	
	
}
