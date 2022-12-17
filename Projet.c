#include<stdio.h>
#include<string.h>
#include<stdlib.h>      //Gestion de la mémoire avec malloc, free, ...

//TODO : Lire le nom et prenom des formateurs avec fgets au cas ou il y aie des espaces

typedef struct etudiant {
    char nom[30];
    char prenom[30];
    char idFormationAnnee[6];
    int naissanceJour, naissanceMois, naissanceAnnee, annee;
    float montantAPayer, montantPaye, reduction;
    struct etudiant *suivant;
}etudiant;

typedef struct formateur {
    char nom[30];
    char prenom[30];    
    char titre[20][100];
    char horaireId[8][23][6];
    int naissanceJour, naissanceMois, naissanceAnnee, nbTitre;
    struct formateur *suivant;
}formateur;
 
typedef struct formation {
    char nomBase[100], nomComplete[102], idFormation[4], idFormationAnnee[6];
    char cours[20][50];
    char prerequisProf[5][81]; //Prerequis pour qu'un prof puisse enseigner dans la formation
    char prerequisEleve[5][50]; //Prerequis pour qu'un eleve puisse s'inscrire dans la formation
    int coursDejaDonne[20], nombreHeureCours[20];   //nombreHeureCours[i] est associe au cours[i]
    int maxEtudiant, nbCours, nbEtudiant, nombreAnneeFormation, numeroAnnee, horaire[8][25];
    int nombrePrerequisProf, nombrePrerequisEleve;
    float prix;
    struct formation *suivant;
}formation;

int main() {    
    
    FILE *fres;

    /*------------------------------------------------------Declaration variable -------------------------------------------------------------------------*/
    int valeurMenu, queFaire, i, x, y, z, j, k, l, tmpAnnee, numAffiche;
    //queFaire est une variable qui est modifiée par les fonctions : on doit naviguer avec les menus, mais la lecture et l'écriture doit se faire dans le main
    //numAffiche est une variable utilisee lors de la selection d'une formation pour la supprimer.

	char temporaire[50]; // Variable temporaire pour creer nouvelleFormation->idFormationAnnee dans l'ajout formation
    char bufferNom[100];
	int test; // Variable temporaire qu'on peut utiliser quand on veut
	
    // Var des structures
    int nbFormation=0, nbEtudiant = 0, nbFormateur=0;
    formation *formationDebut, *formationCourant, *formationSuivant, *nouvelleFormation, *formationIntercale;
    etudiant *etudiantDebut,*etudiantCourant,*etudiantSuivant,*etudiantIntercale, *etudiantNouveau;
    formateur *formateurDebut,*formateurCourant,*formateurSuivant,*formateurIntercale;

    /*------------------------------------------------------Declaration fonction ------------------------------------------------------------------------*/
    void changerMenu(int *);
    void menuConsulterHoraire();
    void ecrireFormation(formation *);
    void ecrireEtudiant(etudiant *);
    int menuGererFormateur();
    void menuGestionFinanciereEtudiant(etudiant *, formation *, int, int);
    void ecrireFormateur(formateur *);
    void supprimerEspaceBlanc(char[]);
    int gestionFormation();
    int gestionFormateur();
    formation* initialisationFormation(int *);
    etudiant* initialisationEtudiant(int *);
    formateur* initialisationFormateur(int *);
    void afficherListeFormation(formation *, int);
    void afficherListeFormationBase(formation *, int);
    void afficherListeFormateur(formateur *, int);
    void afficherListeEtudiant(formation *, etudiant *, int);
    void supprimerFormationAnnee(int , int *, formation *);
    formation* supprimerFormationEntiere(int , int *, formation *);
    void reinitialiserFormationDat();
    formation* ajouterFormation(formation *, int *, int);
    formateur* ajoutFormateur(formateur *, int *, formation *, int);
    int verificationHoraire(formation *, int, formateur *, formation*, int);
    
    void afficherHoraireFormation(formation *);
    void afficherHoraireFormateur(formateur *, formation*, int);

    /*------------------------------------------------------Fin declaration des fonctions ---------------------------------------------------------------*/
    /*--------------------------------------------------------Lecture des fichiers .dat -----------------------------------------------------------------------*/
    formateurDebut = initialisationFormateur(&nbFormateur);
    etudiantDebut = initialisationEtudiant(&nbEtudiant);
	formationDebut = initialisationFormation(&nbFormation);



    //afficherHoraireFormateur(formateurDebut, formationDebut, nbFormation);

    // --------------------------------------------------------------------FIN DE LA LECTURE --------------------------------------------------------------------------
    // ---------------------------------------------------------------------LANCEMENT DU MENU -------------------------------------------------------------------------
    changerMenu(&valeurMenu);
    while(valeurMenu != 0) {

        if(valeurMenu == 1) {//  --------------------------------------------------- MENU CONSULTER ----------------------------------------------------------------------------
            // consulter horaire
            menuConsulterHoraire();
        }
    

        if(valeurMenu == 2) { //  --------------------------------------------------- MENU AJOUTER ETUDIANT ----------------------------------------------------------------------------

            // Valeur par defaut :
            etudiantNouveau = malloc(sizeof(etudiant));
            etudiantNouveau->montantPaye=0;
            etudiantNouveau->reduction=0;
            etudiantNouveau->annee = 1;

            // SELECTION DE LA FORMATION
            printf("+--------+-------------------+-----------------------------------------------------------\n");
            printf("| Numero |      Statut       |                Intitule de la formation\n");
            printf("+--------+-------------------+-----------------------------------------------------------\n");
            char matriceAffichageNomFormation[nbFormation][100]; // matrice de taille nbFormation comme maximum possible, contiendra id formation comme ca des que l'utilisateur choisis une formation on trouvera la formation avec matriceAffichageNomFormation[x]
            float prixQueDoitPayerEtudiant[nbFormation]; // on trouvera le prix selon x à payer selon ce que l'utilisateur choisis
            x=0; // x : va juste indiquer si la formation fait deja parti de la liste affiche ou non, ca evite les doublonsn, 0 par defaut car on va deja ajouter la premiere formation
            formationCourant = formationDebut;
            int nbAffichageFormation=1; // Nombre de formation dans la matrice
            while(formationCourant->numeroAnnee != 1) { // les annee > a 1 sont interdit donc le premier enregistrement doit pas etre > 1
                formationCourant=formationCourant->suivant;
            }
            for(i=2;i<nbFormation;i++) { // Pour chaque formation,   2 car on a deja fait le premier
                if(x==0) { // si pas déjà présente dans la matrice (valeur : 0) on l'ajoute et on écris
                    if(formationCourant->maxEtudiant > formationCourant->nbEtudiant) { // Si place dispo on peut add la formation à la matrice et ecrire pour l'utilisateur
                        strcpy(matriceAffichageNomFormation[nbAffichageFormation], formationCourant->idFormationAnnee); // on met idFormationAnnee dans la matrice comme ça on la rajoutera après dans etudiant.idFormationAnnee
                        prixQueDoitPayerEtudiant[nbAffichageFormation] = formationCourant->prix;
                        y = formationCourant->maxEtudiant - formationCourant->nbEtudiant; // Calcul de la place restante dans la formation
                        printf("| %02d     | Disponible (%d/%d) | %s\n", nbAffichageFormation, formationCourant->nbEtudiant, formationCourant->maxEtudiant, formationCourant->nomBase);
                        nbAffichageFormation++;   
                    }
                    else // sinon on écris quand même sans l'associer à la matrice
                    {
                        printf("| --     | Complet (%d/%d)   | %s\n", formationCourant->nbEtudiant, formationCourant->maxEtudiant, formationCourant->nomBase);
                    }
                    printf("+--------+-------------------+-----------------------------------------------------------\n");
                }
                
                formationCourant=formationCourant->suivant; // Formation suivante
                while(formationCourant->numeroAnnee != 1  && i<nbFormation) { // Tant qu'on tombe pas sur une premiere annee on skip
                    formationCourant=formationCourant->suivant;
                    i++; // Incrementation i car elle est associe a la boucle jusque nbFormation
                }
                x=0; // Nouvelle recherche de x
                for(z=1;z<=nbAffichageFormation;z++) { // Pour chaque élément dans la matrice d'affichage formation
                    if(strcmp(matriceAffichageNomFormation[z], formationCourant->nomBase) == 0) { 
                        x=1; // Si déjà présent x=1
                    }
                }
                
            }   
            printf("\nSelectionnez un numero de formation dans lequel vous souhaitez ajouter un nouvel etudiant (0 pour sortir) : ");
            scanf("%d", &x);
            if(x != 0) {
                strcpy(etudiantNouveau->idFormationAnnee, matriceAffichageNomFormation[x]);

                formationCourant = formationDebut;
                fres=fopen("listeFormation.dat", "w");
                fclose(fres);
                for(i=1;i<=nbFormation;i++) { // incrementation nbEtudiant dans la formation ou il sera ajoute
                    if(strcmp(formationCourant->idFormationAnnee, etudiantNouveau->idFormationAnnee)== 0) {
                        formationCourant->nbEtudiant= formationCourant->nbEtudiant + 1;
                    }
                    ecrireFormation(formationCourant);
                    formationCourant= formationCourant->suivant;
                }




                etudiantNouveau->montantAPayer = prixQueDoitPayerEtudiant[x]; // prix à payer de l'etudiant


                printf("\nPrix de la formation que l'etudiant devra regler : %8.2f\n", etudiantNouveau->montantAPayer);
                printf("\nVeuillez entrer le nom du nouvelle etudiant : ");
                scanf(" ");
                for(i = 0; i < 29; i++) {    
                    etudiantNouveau->nom[i] = getchar();
                    if(etudiantNouveau->nom[i] == '\n') {
                        etudiantNouveau->nom[i] = '\0';
                        break;
                    }
                }
                etudiantNouveau->nom[i] = '\0';
                etudiantNouveau->nom[29] = '\0';
                printf("\nVeuillez entrer le prenom de l'etudiant : "); scanf(" ");
                for(i = 0; i < 29; i++) {    
                    etudiantNouveau->prenom[i] = getchar();
                    if(etudiantNouveau->prenom[i] == '\n') {
                        etudiantNouveau->prenom[i] = '\0';
                        break;
                    }
                }
                etudiantNouveau->prenom[i] = '\0';
                etudiantNouveau->prenom[29] = '\0';
                

                // TODO : verification annee de naissance
                printf("\nInformation date de naissance : \n");
                printf("> Annee : "); scanf("%d", &etudiantNouveau->naissanceAnnee);
                printf("> Mois de naissance : "); scanf("%d", &etudiantNouveau->naissanceMois);
                printf("> Jour de naissance : "); scanf("%d", &etudiantNouveau->naissanceJour);

                ecrireEtudiant(etudiantNouveau);



                printf("\n=============================================\n");
                printf("Recapitulatif des informations de l'etudiant\n");
                printf("=============================================");
                printf("\n> Nom :                   %s", etudiantNouveau->nom);
                printf("\n> Prenom :                %s", etudiantNouveau->prenom);
                printf("\n> Annee :                 %d", etudiantNouveau->annee);
                printf("\n> Montant a payer  :      %8.2f", etudiantNouveau->montantAPayer);
                printf("\n> Naissance :             %02d/%02d/%4d", etudiantNouveau->naissanceJour, etudiantNouveau->naissanceMois, etudiantNouveau->naissanceAnnee);
                printf("\n> Reduction  :            %8.2f\n", etudiantNouveau->reduction);
                printf("=============================================\n");


                etudiantDebut = initialisationEtudiant(&nbEtudiant);

                /* MARCHE PAS BORDEL
                //////////////////////////////////////////////////////
                // AJOUT DE LETUDIANT A LA CHAINE                   //
                etudiantCourant=etudiantDebut;                      //
                for(i=1;i<nbEtudiant;i++) {                         //
                    etudiantCourant= etudiantCourant->suivant;      //
                }                                                   //
                etudiantCourant->suivant=etudiantNouveau;           //
                etudiantNouveau->suivant = NULL;                    //
                etudiantCourant=etudiantCourant->suivant;           //
                nbEtudiant++;                                       //
                //////////////////////////////////////////////////////
                */


                
            }
            




        }

        
        if(valeurMenu == 3) {   //Gestion formation et formateur
            // valeur possible menuGererFormation() :        1 : ajouter formation        2 : Supprimer formation      3 : afficher liste formation
            queFaire = menuGererFormation();

//S'il te plait, n'utilise pas cette methode (goto) car elle fait perdre enormement en lisibilite.
//Je l'utilise exceptionnellement car je ne pouvais pas sortir de l'ajout de formation avec un break ou un changement de condition (j'ai essaye, mais sans succes)
//C'est donc en dernier recours que j'utilise le goto. Mais j'insiste, ne l'utilise pas, s'il te plait. C'est pas une bonne pratique en general (selon internet en tout cas)
erreurID:
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
                
                //parcourir les formation deja existante et verifier leur ID. Si l'ID choisi existe deja -> redemander l'entree d'un nv ID
                formationSuivant = formationDebut;
                for(i = 1; i < nbFormation; i++) {
                    if(strcmp(formationSuivant->idFormation, formationIntercale->idFormation) == 0) {
                        printf("Erreur : cet ID est deja utilise.\n");
                        goto erreurID;
                    }
                    formationSuivant = formationSuivant->suivant;
                }

                printf("Combien d'etudiants sont autorises par annee ? : ");
                scanf("%d", &formationIntercale->maxEtudiant);

                printf("\nSur combien d'annee la formation s'etale-t-elle ? ");
                scanf("%d", &formationIntercale->nombreAnneeFormation);

                printf("\nCombien de titres seront necessaires a l'ensemble des enseignants de la formation ? ");
                scanf("%d", &formationIntercale->nombrePrerequisProf);

				//////////////////////////////////////////////////////////////////////////////////
                // VU QUON VA AJOUTER POTENTIELLEMENT PLUSIEURS ANNEE ON INITIALISE LA CHAINE   //
                // COMME CA ON AJOUTE A LA SUITE TOUTES LES ANNEES dans la boucle               //
                formationCourant=formationDebut;                                                //
                for(i=1;i< nbFormation; i++) {                                                 //
                    formationCourant= formationCourant->suivant;                                //
                }                                                                               //
                //////////////////////////////////////////////////////////////////////////////////
                if(formationIntercale->nombrePrerequisProf != 0) {
                    printf("Quel est l'ensemble des titres que les formateurs doivent avoir en possession pour enseigner dans cette formation ?\n");
                    for(i = 1; i <= formationIntercale->nombrePrerequisProf; i++) {
                        printf("Nom du prerequis %02d/%02d : ", i, formationIntercale->nombrePrerequisProf);
                        scanf(" ");
                        for(k = 0; k < 80; k++) {
                            formationIntercale->prerequisProf[i][k] = getchar();
                            if(formationIntercale->prerequisProf[i][k] == '\n') {
                                formationIntercale->prerequisProf[i][k] = '\0';
                                break;
                            }
                            formationIntercale->prerequisProf[i][80] = '\0';
                        }
                    }
                } else {
                    strcpy(formationIntercale->prerequisProf[1], "Aucun prerequis demande\0");
                }

                //Prerequis des eleves
                printf("\nCombien de titres seront necessaires a un etudiants pour s'inscire ? ");
                scanf("%d", &formationIntercale->nombrePrerequisEleve);

                if(formationIntercale->nombrePrerequisEleve != 0) {
                    printf("Quels sont-ils ?\n");
                    for(i = 1; i <= formationIntercale->nombrePrerequisEleve; i++) {
                        printf("Nom du prerequis %02d/%02d : ", i, formationIntercale->nombrePrerequisEleve);
                        scanf(" ");
                        for(k = 0; k < 49; k++) {
                            formationIntercale->prerequisEleve[i][k] = getchar();
                            if(formationIntercale->prerequisEleve[i][k] == '\n') {
                                formationIntercale->prerequisEleve[i][k] = '\0';
                                break;
                            }
                            formationIntercale->prerequisEleve[i][49] = '\0';
                        }
                    }
                } else {
                    strcpy(formationIntercale->prerequisEleve[1], "Aucun prerequis demande\0");
                }

                for(i = 1; i <= formationIntercale->nombreAnneeFormation; i++) {     //Boucle pour parcourir les annees
                	nouvelleFormation=malloc(sizeof(formation));
                	
                    //Reattribution des valeurs donnees en DEHORS de la bouche 
                    strcpy(nouvelleFormation->nomBase, formationIntercale->nomBase);
                    strcpy(nouvelleFormation->idFormation, formationIntercale->idFormation);
                    nouvelleFormation->nombreAnneeFormation = formationIntercale->nombreAnneeFormation;
                    nouvelleFormation->maxEtudiant = formationIntercale->maxEtudiant;
                    //Reattribution des prerequis prof
                    nouvelleFormation->nombrePrerequisProf = formationIntercale->nombrePrerequisProf;
                    nouvelleFormation->nombrePrerequisEleve = formationIntercale->nombrePrerequisEleve;
                    strcpy(nouvelleFormation->prerequisProf[1], formationIntercale->prerequisProf[1]);
                    strcpy(nouvelleFormation->prerequisEleve[1], formationIntercale->prerequisEleve[1]);
                    for(j = 1; j <= formationIntercale->nombrePrerequisProf; j++) {
                        strcpy(nouvelleFormation->prerequisProf[j], formationIntercale->prerequisProf[j]);
                    }
                    //Reattribution des prerequis eleves
                    for(j = 1; j <= formationIntercale->nombrePrerequisEleve; j++) {
                        strcpy(nouvelleFormation->prerequisEleve[j], formationIntercale->prerequisEleve[j]);
                    }

                    // Creation id unique
                    // concatener dans un char : sprintf(<variable char>, <formatage comme printf>, <les valeurs>)
					sprintf(temporaire, "%d_%s", i, formationIntercale->idFormation);
                    strcpy(nouvelleFormation->idFormationAnnee, temporaire);
                    //réattribution de l'idFormation non modifié (ne pas supprimer)
                    strcpy(nouvelleFormation->idFormation, formationIntercale->idFormation);

                    //Creation du nom de la formation (nomBase [espace] i)
                    strcpy(nouvelleFormation->nomComplete, formationIntercale->nomBase);
                    sprintf(nouvelleFormation->nomComplete, "%s %d", formationIntercale->nomBase, i);
                    
                    //Assignation numero annee, nbEtudiant = 0
                    nouvelleFormation->numeroAnnee = i;
                    nouvelleFormation->nbEtudiant = 0;

                    //grille horaire
                    for(k = 1; k <= 7; k ++) {
                        for(l = 0; l <= 23; l++) {
                            nouvelleFormation->horaire[k][l] = 0;
                        }
                    }

                    //Prix
                    printf("\nQuel est le prix d'inscription a cette annee de formation ? : ");
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

                        printf("Combien d'heures par semaine ce cours est-il donne ? ");
                        scanf("%d", &nouvelleFormation->nombreHeureCours[j]);
                        
                        
                        //vu que le cours est creer il est dispo donc on met 0 dans deja donne
                        nouvelleFormation->coursDejaDonne[j]=0;
                    }

                    printf("\n--------------------------------\n");
                    printf("Fin de l'encodage de l'annee : %1d\n", i);
                    printf("--------------------------------\n");
                    // Ecriture
                    ecrireFormation(nouvelleFormation);

                    ///AJOUT FORMATION A LA CHAINE////////////////////////
                                                                        //
                    formationCourant->suivant=nouvelleFormation;        //
                    nouvelleFormation->suivant = NULL;                  //
                    formationCourant=formationCourant->suivant;         //
                    nbFormation++;                                      //
                    //////////////////////////////////////////////////////


                    
                }
                printf("\nEncodage de la formation realisee avec succes.\n"); 
                printf("==============================================\n\n"); 

            }  

            if(queFaire == 2) {     //Supprimer formation
                printf("+---------------------------------------+\n");
                printf("| Menu de suppression des formations    |\n");
                printf("+---+-----------------------------------+\n");
                printf("| 1 | Supprimer une annee               |\n");
                printf("+---+-----------------------------------+\n");
                printf("| 2 | Supprimer une formation complete  |\n");
                printf("+---+-----------------------------------+\n");
                printf("| 0 | Retour                            |\n");
                printf("+---+-----------------------------------+\n");
                printf("Votre choix : ");
                scanf("%d", &test);
                while(test < 0 || test > 2) {
                    printf("Valeur incorrecte : ");
                    scanf("%d", &test);
                }
                printf("\n");

                //Cas de suppression d'une annee uniquement
                if(test == 1) {
                    //Affichage des formations
                    afficherListeFormation(formationDebut, nbFormation);
                    
                    printf("Veuillez entrer le numero correspondant a la formation que vous souhaitez supprimer : ");
                    scanf("%d", &numAffiche);
                    while(numAffiche < 0 || numAffiche > nbFormation) {
                        printf("Valeur incorrecte : ");
                        scanf("%d", &numAffiche);
                    }

                    //suppression de l'element de la liste chainee
                    formationIntercale = formationDebut;
                    for(i = 1; i < numAffiche; i++) {
                        formationIntercale = formationIntercale->suivant;
                    }
                    if(formationIntercale->nbEtudiant == 0) {
                        x = 0;
                        for(j = 1; j <= formationIntercale->nbCours; j++) {
                            if(formationIntercale->coursDejaDonne[j] != 0) {
                                x = 1;
                                break;
                            }
                        }
                        if(x == 0) {
                            supprimerFormationAnnee(numAffiche, &nbFormation, formationDebut);
                            printf("Element supprime avec succes\n");
                        } else {
                            printf("Un formateur se trouve dans cette formation. Impossible de la supprimer.\n");
                        }
                    } else {
                        printf("Un etudiant se trouve dans cette formation. Impossible de la supprimer.\n");
                    }
                    afficherListeFormation(formationDebut, nbFormation);

                    //Reecrire le Dat
                    reinitialiserFormationDat();

                    //remplir avec nouvelles donnees
                    formationCourant = formationDebut;
                    for(i = 1; i <= nbFormation; i++){
                        ecrireFormation(formationCourant);
                        formationCourant = formationCourant->suivant;
                    }
                } else {
                    //Cas de la suppression de la formation complete
                    afficherListeFormationBase(formationDebut, nbFormation);
                    printf("Veuillez entrer le numero correspondant a la formation que vous souhaitez supprimer : ");
                    scanf("%d", &numAffiche);
                    while(numAffiche < 0 || numAffiche > nbFormation) {
                        printf("Valeur incorrecte : ");
                        scanf("%d", &numAffiche);
                    }


                    //suppression
                    formationDebut = supprimerFormationEntiere(numAffiche, &nbFormation, formationDebut);
                    printf("Element supprime avec succes.\n");
                    afficherListeFormationBase(formationDebut, nbFormation);

                    //Reecrire le Dat
                    reinitialiserFormationDat();

                    //remplir avec nouvelles donnees
                    formationCourant = formationDebut;
                    for(i = 1; i <= nbFormation; i++){
                        ecrireFormation(formationCourant);
                        formationCourant = formationCourant->suivant;
                    }
                }
            }

            if(queFaire == 3) {     //Afficher les formations
                afficherListeFormation(formationDebut, nbFormation);
            }

            if(queFaire == 4) {     //Ajouter formateur
                formateurDebut = ajoutFormateur(formateurDebut, &nbFormateur, formationDebut, nbFormation);
                formateurDebut = initialisationFormateur(&nbFormateur);

            }

            if(queFaire == 5) { // supprimer formateur

                afficherListeFormateur(formateurDebut, nbFormateur);
                void supprimerFormateur(formateur*, formateur*, int);
                printf("=========================================\n");
                printf("> Quels formateur voulez-vous supprimer ?\n");
                printf("Choix : ");
                scanf("%d", &z);

                formateurCourant=formateurDebut;
                for(i=1;i<=nbFormateur;i++) {

                    if(i==z) {
                        supprimerFormateur(formateurCourant, formateurDebut, nbFormateur);
                        nbFormateur -=1;
                    }

                    formateurCourant= formateurCourant->suivant;
                }
                fres=fopen("listeFormateur.dat", "w");
                fclose(fres);
                printf("je rentre\n");
                formateurCourant=formateurDebut;
                for(i=1;i<=nbFormateur;i++) {
                    ecrireFormateur(formateurCourant);
                    formateurCourant= formateurCourant->suivant;
                }
                printf("je sors\n");
                if(nbEtudiant > 0) {
                    formateurDebut = initialisationFormateur(nbFormateur);
                }
                
            }

            if(queFaire == 6) { // afficher liste formateur

                afficherListeFormateur(formateurDebut, nbFormateur);

                printf("=========================================\n");
                printf("> Quels formateur voulez-vous consulter ?\n");
                printf("Choix : ");
                scanf("%d", &z);

                formateurCourant=formateurDebut;
                for(i=1;i<=nbFormateur;i++) {

                    if(i==z) {

                        printf("\n===== Information sur le formateur selectionne ====== \n");
                        printf("> Nom        : %-s \n", formateurCourant->nom);
                        printf("> Prenom     : %-s \n", formateurCourant->prenom);
                        printf("> Naissance  : %02d/%02d/%4d \n", formateurCourant->naissanceJour, formateurCourant->naissanceMois, formateurCourant->naissanceAnnee);
                        printf(">> ===================== <<\n");
                        printf(">> Liste de ses titres :\n");
                        for(x=1;x<=formateurCourant->nbTitre;x++) {
                            printf(" >> %s\n", formateurCourant->titre[x]);
                        }
                        printf(">> ===================== <<\n");
                        printf(">> Son horaire :\n");
                        afficherHoraireFormateur(formateurCourant, formationDebut, nbFormation);


                    }

                    formateurCourant= formateurCourant->suivant;
                }
            }
            
            // tache effectuee, on peut reset que faire
            queFaire = 0;
        }
    

        if(valeurMenu == 4) { // //  --------------------------------------------------- MENU CONSULTER ETUDIANT ----------------------------------------------------------------------------

            queFaire = 1; // osef de la valeur tant que cest different de 0
            while(queFaire != 0) {

                afficherListeFormation(formationDebut, nbFormation);
                afficherListeFormationBase(formationDebut, nbFormation);
                printf("\nSelectionnez le numero d'une formation (0 pour retourner au menu principal) : ");
                scanf("%d", &queFaire);

                while(queFaire > nbFormation || queFaire < 0) {
                    printf("\nErreur, veuillez selectionner une formation entre 1 et %2d : ", nbFormation);
                    scanf("%d", &queFaire);
                }
                if(queFaire != 0) { // si l'utilisateur a mit autre chose que 0 alors il veut selectionner une formation

                    formationCourant = formationDebut;
                    for(i=1;i<=nbFormation;i++) {

                        if(i== queFaire) { 
                            
                            afficherListeEtudiant(formationCourant, etudiantDebut, nbEtudiant);
                            


                            printf("===============================================================================================================================================\n");
                            printf("0 : Retour\n");
                            printf("1 : Supprimer un etudiant de la liste\n");
                            printf("2 : Modifier un etudiant de la liste (fonctionnalite pas encore implemente)\n");

                            scanf("%d", &x); // x : choix de l'utilisateur (retour, supprimer ou modifier)
                            if(x == 0) { // si 0 alors l'utilisateur veut quitter menu
                                queFaire=1; // osef de la valeur tant que cest different de 0
                            }
                            else // Sinon on sait que l'utilisateur veut soit supprimer ou modifier un etudiant
                            {

                                // SUPPRESSION ETUDIANT (si x=1)
                                if(x == 1) { 
                                    printf("Selectionnez le numero de l'etudiant a supprimer : \nChoix (0 pour ne rien faire) :");
                                    scanf("%d", &z); // z = numero de l'etudiant a supprimer
                                    // On repasse en revu les etudiant pour trouver celui a supprimer
                                    etudiantCourant = etudiantDebut;
                                    if(z > 1) { // L'utilisateur veut supprimer l'etudiant z
                                    
                                        for(y=1;y<= nbEtudiant; y++) {

                                            if(y == z) { // si on tombe sur l'etudiant que l'utilisateur veut supprimer alors on le supprime de la chaine

                                                

                                                printf("*********************************************INFORMATION DE L'ETUDIANT SUPPRIME******************************************************************************\n");
                                                printf("*| Numero | Date de naissance | Nom                           | Prenom                       | Montant a payer | reduction | Montant paye | Reste a payer |*\n");
                                                printf("*|   %4d |    %02d/%02d/%04d     | %-30s|%-30s| %8.2f        | %8.2f  |    %8.2f  |    %8.2f   |*\n", 
                                                y, etudiantCourant->naissanceJour, etudiantCourant->naissanceMois, etudiantCourant->naissanceAnnee, etudiantCourant->nom, etudiantCourant->prenom, etudiantCourant->montantAPayer, etudiantCourant->reduction,  etudiantCourant->montantPaye, (etudiantCourant->montantAPayer - etudiantCourant->montantPaye));
                                                printf("*************************************************************************************************************************************************************");

                                                // -1 etudiant dans la formation de l'etudiant supprime
                                                formationCourant=formationDebut;
                                                for(z=1;z<=nbFormation;z++) {
                                                    if(strcmp(formationCourant->idFormationAnnee, etudiantCourant->idFormationAnnee) == 0) {
                                                        formationCourant->nbEtudiant = formationCourant->nbEtudiant -1;
                                                        break;
                                                    }
                                                    formationCourant=formationCourant->suivant;
                                                }
                                                // mise à jour du fichier dat
                                                fres=fopen("listeFormation.dat", "w");
                                                fclose(fres);
                                                formation *formationCourant = malloc(sizeof(*formationCourant));
                                                formationCourant=formationDebut;
                                                for(i=1;i<=nbFormation;i++) {
                                                    ecrireFormation(formationCourant);
                                                    formationCourant=formationCourant->suivant;
                                                }



                                                etudiantIntercale->suivant=etudiantCourant->suivant;
                                                free(etudiantCourant);
                                                nbEtudiant--;
                                                etudiantCourant=etudiantIntercale;
                                            }
                                            etudiantIntercale = etudiantCourant;
                                            etudiantCourant=etudiantCourant->suivant; 
                                        }
                                    }

                                    if(z==1) { // Si il veut supprimer le premier etudiant (etudiantDebut) c'est pas la meme facon que si c'etait en plein milieu d'une liste
                                        etudiantIntercale=etudiantDebut;
                                        etudiantDebut=etudiantDebut->suivant;
                                        free(etudiantIntercale);
                                        nbEtudiant--;
                                    }

                                    if( z > 0 ) {// si supperieur à 0 c'est qu'il y a eu une suppression donc on met à jour la liste d'étudiant


                                        fres=fopen("listeEtudiant.dat", "w");
                                        fclose(fres);

                                        etudiantCourant=etudiantDebut;
                                        for(y=1;y<=nbEtudiant;y++) {
                                            ecrireEtudiant(etudiantCourant);
                                            etudiantCourant=etudiantCourant->suivant; 
                                        }
                                    
                                    }
                                }

                                // MODIFICATION ETUDIANT (si x = 2)
                                if( x==2 ) { 

                                }

                            }

                        }
                        formationCourant=formationCourant->suivant;
                    }
                }
            }




        }

        if(valeurMenu == 5) { // --------------------------------------------------------- MENU GESTION FINANCIERE -----------------------------------------------------------------------------
            menuGestionFinanciereEtudiant(etudiantDebut, formationDebut, nbEtudiant, nbFormation);
        }


        changerMenu(&valeurMenu);
        
    }
        
    printf("Au revoir et a bientot.\n");
}   // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_   FIN  DU  PROGRAMME MAIN -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_


void menuGestionFinanciereEtudiant(etudiant *etudiantDebut, formation *formationDebut, int nbEtudiant, int nbFormation) {

    void afficherListeFormation(formation *, int);
    void afficherListeEtudiant(formation *, etudiant *, int);
    void ecrireEtudiant(etudiant *);


    afficherListeFormation(formationDebut, nbFormation);
    printf("Selectionnez la formation de l'etudiant qui doit recevoir une modification financiere : \n");
    int form, i, y, numEtudiant, choix;
    int modif; // si il y a eu modif on met a jour la liste etudiant
    int pourcentage, exit=1;
    float montant, reste;
    int choixTypeMontant;
    scanf("%d", &form);

    formation *formationCourant = malloc(sizeof(*formationCourant));
    etudiant *etudiantCourant = malloc(sizeof(*etudiantCourant));
    formationCourant = formationDebut;

    for(i=1;i<=nbFormation;i++) {
        if(form == i) {

            
            
            afficherListeEtudiant(formationCourant, etudiantDebut, nbEtudiant);
            printf("Selectionnez l'etudiant qui doit recevoir une modification financiere : ");
            printf("Choix : ");
            scanf("%d", &numEtudiant);
            etudiantCourant = etudiantDebut;
            for(y=1;y<=nbEtudiant; y++) {

                if(numEtudiant == y) {

                    while(exit != 0) {
                        printf("==============================================\n");
                        printf(" > Situation financiere de     : %-s %-s\n", etudiantCourant->nom, etudiantCourant->prenom);
                        printf("==============================================\n");
                        printf("| Montant a payer              : %8.2f e |\n", etudiantCourant->montantAPayer);
                        printf("---------------------------------------------\n");
                        printf("| Montant paye par l'etudiant  : %8.2f e |\n", etudiantCourant->montantPaye);
                        printf("---------------------------------------------\n");

                        if(etudiantCourant->reduction == 0) {
                            printf("| > Aucune reduction                        |\n", etudiantCourant->montantPaye);
                        }
                        else
                        {
                            printf("| Reduction                    : %8.2f e |\n", etudiantCourant->reduction);
                        }


                        reste = (etudiantCourant->montantAPayer - etudiantCourant->montantPaye - etudiantCourant->reduction);
                        printf("=============================================\n");
                        printf("| Reste a payer                : %8.2f e |\n", reste);
                        printf("---------------------------------------------\n");
                        printf("0 : Retour\n");

                        if(reste > 0) {


                            if(etudiantCourant->reduction == 0) {
                                printf("1 : Appliquer une reduction sur le montant a payer (%8.2f euros)\n", etudiantCourant->montantAPayer);
                            }
                            else
                            {
                                printf("1 : Redefinir la reduction sur le montant a payer (%8.2f euros)\n", etudiantCourant->montantAPayer);
                            }
                            
                            printf("2 : L'etudiant a paye un montant\n");
                            printf("Votre choix : ");
                            scanf("%d", &choix);

                            if(choix == 1) {
                                printf("0 : Retour\n");
                                printf("1 : Appliquer une reduction par pourcentage\n");
                                printf("2 : Appliquer une reduction par montant\n");
                                printf("Votre choix : ");
                                scanf("%d", &choixTypeMontant);
                                if(choixTypeMontant == 1) {
                                    printf("Entrez le pourcentage accorde pour l'etudiant (sans entrer le %c): ", '%');
                                    scanf("%d", &pourcentage);
                                    etudiantCourant->reduction = etudiantCourant->montantAPayer * (((float)pourcentage)/100);
                                    modif=1; // on sait quon devra ouvrir le dat et modifier
                                }

                                if(choixTypeMontant == 2) {
                                    printf("Entrez le montant de la reduction pour l'etudiant: \n");
                                    scanf("%f", &montant);

                                    while(montant > etudiantCourant->montantAPayer) {
                                    printf("Erreur d'encodage, la reduction ne peut pas etre superieur a %8.2f e: \n", etudiantCourant->montantAPayer);
                                    scanf("%f", &montant);
                                    }
                                    etudiantCourant->reduction = montant;
                                    modif=1; // on sait quon devra ouvrir le dat et modifier
                                }


                            }

                            
                            if(choix == 2) {
                                printf("Entrez le montant paye par l'etudiant (0 pour sortir): ");
                                scanf("%f", &montant);
                                etudiantCourant->montantPaye = etudiantCourant->montantPaye + montant;
                                modif=1; // on sait quon devra ouvrir le dat et modifier
                            }


                        }
                        else
                        {
                            
                            if(reste < 0) {
                                printf(">>> L'etudiant est en ordre mais doit etre rembourse de %8.2f euros\n", (reste * (-1)));
                                printf("1 : Cet etudiant a ete rembourse\n");
                                printf("0 : Retour");
                                scanf("%d", &choix);

                                if(choix == 1) {
                                    etudiantCourant->montantPaye = etudiantCourant->montantAPayer - etudiantCourant->reduction;
                                    modif=1; // on sait quon devra ouvrir le dat et modifier
                                }
                            }
                            else
                            {
                                printf("> L'etudiant est en ordre\n");
                                scanf("%d", &choix);
                            }

                        }

                        if(choix == 0) {
                            exit = 0; 
                        }


                    }


                }

                etudiantCourant=etudiantCourant->suivant;
            }


        }

        formationCourant = formationCourant->suivant;
    }

    if(modif == 1) {
        FILE *fres;
        fres=fopen("listeEtudiant.dat", "w");
        fclose(fres);

        etudiantCourant = etudiantDebut;
        for(i=1;i<=nbEtudiant;i++) {
            ecrireEtudiant(etudiantCourant);
            etudiantCourant = etudiantCourant->suivant;
        }
    }



}

void afficherListeEtudiant(formation *formationCourant, etudiant *etudiantDebut, int nbEtudiant) {

    // si une formation est egal à ce que l'utilisateur a entree comme information
    // Generation de la liste des etudiants sur base de formationCourant

    if(formationCourant->nbEtudiant > 0) {

        printf("\nVous avez selectionne %s\n", formationCourant->nomBase);
        printf("\n===============================================================================================================================================\n");
        printf("                                              Liste des etudiants de la formation %s \n", formationCourant->nomComplete);
        printf("+--------+-------------------+-------------------------------+------------------------------+-----------------+-----------+--------------+---------------+\n");
        printf("| Numero | Date de naissance | Nom                           | Prenom                       | Montant a payer | reduction | Montant paye | Reste a payer |\n");
        printf("+--------+-------------------+-------------------------------+------------------------------+-----------------+-----------+--------------+---------------+\n");
        // Affichage de la liste des etudiants de la formation selectionne00
        etudiant *etudiantCourant = malloc(sizeof(*etudiantCourant));
        etudiantCourant=etudiantDebut;
        int y;
        for(y=1;y<= nbEtudiant; y++) {
            if(strcmp(etudiantCourant->idFormationAnnee, formationCourant->idFormationAnnee) == 0) { // si on tombe sur un etudiant qui a la meme id formation que la formation selectionne alors on lecris
                printf("|   %4d |    %02d/%02d/%04d     | %-30s|%-30s| %8.2f        | %8.2f  |    %8.2f  |    %8.2f   |\n", 
                y,
                etudiantCourant->naissanceJour, 
                etudiantCourant->naissanceMois, 
                etudiantCourant->naissanceAnnee,
                etudiantCourant->nom, 
                etudiantCourant->prenom, 
                etudiantCourant->montantAPayer,
                etudiantCourant->reduction, 
                etudiantCourant->montantPaye, 
                (etudiantCourant->montantAPayer - etudiantCourant->montantPaye));
                printf("+--------+-------------------+-------------------------------+------------------------------+-----------------+-----------+--------------+---------------+\n");
            }
            etudiantCourant=etudiantCourant->suivant;
        }
    }
    else
    {
        printf("\n===============================================================================================================================================\n");
        printf("                                              >>> Aucun etudiant dans la formation %s <<<\n", formationCourant->nomComplete);
        printf("===============================================================================================================================================\n");
    }
}


//ChangerMenu
void changerMenu(int *valeurMenu) {

    printf("-+--------------------------------------------------------------+\n");
    printf(" | Veuillez entrer la valeur correspondante au menu souhaite    |\n");
    printf("-+---+----------------------------------------------------------+\n");
    printf(" | 0 | Quitter                                                  |\n");
    printf("-+---+----------------------------------------------------------+\n");
    printf(" | 1 | Acceder aux horaires                                     |\n");
    printf("-+---+----------------------------------------------------------+\n");
    printf(" | 2 | Ajouter un etudiant                                      |\n");
    printf("-+---+----------------------------------------------------------+\n");
    printf(" | 3 | Gerer les formations ou les formateurs                   |\n");
    printf("-+---+----------------------------------------------------------+\n");
    printf(" | 4 | Consulter les etudiants                                  |\n");
    printf("-+---+----------------------------------------------------------+\n");
    printf(" | 5 | Gestion financiere des etudiants                         |\n");
    printf("-+---+----------------------------------------------------------+\n");
    printf("Votre choix : ");
    scanf("%d", &*valeurMenu);

    //Gestion d'erreur
    while(*valeurMenu < 0 || *valeurMenu > 5) {
        printf("Valeur incorrecte.\n");
        printf("Votre choix : ");
        scanf("%d", &*valeurMenu);
    }
    printf("\n");

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

    printf("+--------------------------------+\n");
    printf("| Choix de la formation          |\n");
    printf("+--------------------------------+\n");
    printf("| 1 | Acceder aux formations     |\n");
    printf("+--------------------------------+\n");
    printf("| 2 | Acceder aux formateurs     |\n");
    printf("+--------------------------------+\n");
    printf("| 0 | Quitter                    |\n");
    printf("+--------------------------------+\n");
    printf("Votre choix : ");

    scanf("%d", &valeurMenuFormation);

    //Gestion d'erreur
    while(valeurMenuFormation < 0 || valeurMenuFormation > 2) {
        printf("Valeur incorrecte.\n");
        printf("Votre choix : ");
        scanf("%d", &valeurMenuFormation);
    }

    printf("\n");

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
        queFaire = gestionFormateur();
        return queFaire;

        // ******* A FAIRE : Creer fonction gestionFormateur et renvoyer queFaire 3 valeurs différente (ajouter, modifier, supprimer formateur)
    }
}


//Est appelée depuis menuGererFormation()
//Les valeurs possibles sont :
// 1 : ajouter un formateur
// 2 : supprimer un formateur
// 3 : afficher la liste des formateurs
int gestionFormateur() {

    int queFaire = 0;
    int menu;
    
    printf("+---+-----------------------------------+\n");
    printf("| 1 | Ajouter un formateur              |\n");
    printf("+---+-----------------------------------+\n");
    printf("| 2 | Supprimer un formateur            |\n");
    printf("+---+-----------------------------------+\n");
    printf("| 3 | Afficher la liste des formateurs  |\n");
    printf("+---+-----------------------------------+\n");
    printf("| 0 | Quitter                           |\n");
    printf("+---+-----------------------------------+\n");

    printf("Votre choix : ");
    scanf("%d", &menu);

    while(menu < 0 || menu > 3) {
        printf("Valeur incorrecte.\n");
        printf("Votre choix : ");
        scanf("%d", &menu);
    }

    printf("\n");
    queFaire = menu + 3;
    return queFaire;

}



//Est appelée depuis menuGererFormation()
// Les valeurs possible de retour :
// 1 : ajouter formation
// 2 : Supprimer formation
// 3 : afficher liste formation
int gestionFormation() {
    int queFaire = 0;
    int menu;
    
    printf("+---+-----------------------------------+\n");
    printf("| 1 | Ajouter une formation             |\n");
    printf("+---+-----------------------------------+\n");
    printf("| 2 | Supprimer une formation           |\n");
    printf("+---+-----------------------------------+\n");
    printf("| 3 | Afficher la liste des formations  |\n");
    printf("+---+-----------------------------------+\n");
    printf("| 0 | Quitter                           |\n");
    printf("+---+-----------------------------------+\n");

    printf("Votre choix : ");
    scanf("%d", &menu);

    while(menu < 0 || menu > 3) {
        printf("Valeur incorrecte.\n");
        printf("Votre choix : ");
        scanf("%d", &menu);
    }

    printf("\n");
    queFaire = menu;
    return queFaire;
}


void ecrireEtudiant(etudiant *e) {
   FILE *fres;
   fres=fopen("listeEtudiant.dat", "a");
   fprintf(fres,"%-30s %-30s %5s %2d %2d %4d %2d %8.2f %8.2f %8.2f\n", 
   e->nom, e->prenom, e->idFormationAnnee, e->naissanceJour, e->naissanceMois, e->naissanceAnnee, e->annee, e->montantAPayer, e->montantPaye, e->reduction);
   fclose(fres);
}

void ecrireFormation(formation *f) {

    FILE *fres;
    fres=fopen("listeFormation.dat", "a");

    //printf("\nFormation en cours d'ajout : %s \n", f->nomBase);
    int z, y, x;

    // nom, idFormation, idFormationAnnee, numeroAnnee, nbCours, maxEtudiant, nbEtudiant, prix, nombreAnneeFormation, numeroAnnee
    fprintf(fres,"%-99s %-101s %-3s %-5s %2d %2d %4d %4d %8.2f %2d ", f->nomBase, f->nomComplete, f->idFormation, f->idFormationAnnee, 
    f->numeroAnnee, f->nbCours, f->maxEtudiant, f->nbEtudiant, f->prix, f->nombreAnneeFormation);
    
    // ecriture jour et semaine horaire
    for(z=1;z<=7;z++) {
        for(y=0;y<=23;y++) {
                fprintf(fres,"%02d", f->horaire[z][y]);
        }
    }

    for(x=1; x <= f->nbCours; x++) {
        // print 50 caractere pour chaque cours
        fprintf(fres," %-50s", f->cours[x]);
    }

    for(x=1; x<= f->nbCours; x++) {
        fprintf(fres,"%1d", f->coursDejaDonne[x]);
    }

    //Ecriture des prerequis eleve
    //Si nombrePrerequisEleve vaut 0, prerequisEleve[1] contient ce qui doit être ecrit
    fprintf(fres,"%1d", f->nombrePrerequisEleve);
    if(f->nombrePrerequisEleve == 0) {
        fprintf(fres,"%-49s", f->prerequisEleve[1]);
    } else {
        for(x = 1; x <= f->nombrePrerequisEleve; x++) {
            fprintf(fres,"%-49s", f->prerequisEleve[x]);
        }
    }

    //Ecriture des prerequis prof
    //Si nombrePrerequisProf vaut 0, prerequisProf[1] contient ce qui doit être ecrit
    fprintf(fres,"%1d", f->nombrePrerequisProf);
    if(f->nombrePrerequisProf == 0) {
        fprintf(fres,"%-80s", f->prerequisProf[1]);
    } else {
        for(x = 1; x <= f->nombrePrerequisProf; x++){
            fprintf(fres,"%-80s", f->prerequisProf[x]);
        }
    }

    //Ecriture des nombres d'heures de cours
    for(x = 1; x <= f->nbCours; x++) {
        fprintf(fres, "%02d", f->nombreHeureCours[x]);
    }
    
    fprintf(fres,"\n");

    fclose(fres);
}


void afficherListeFormateur(formateur *formateurDebut, int nbFormateur) {


    int i, j;
    formateur *formateurCourant = malloc(sizeof(*formateurCourant));
    formateurCourant = formateurDebut;
    printf("==================================================================================================================\n");
    printf("                                          LISTE DES FORMATEURS  \n");
    printf("+--------+--------------------------------+--------------------------------+-------------------+-----------------+\n");
    printf("| Numero | Nom                            | Prenom                         | Date de naissance | Nombre de titre |\n");
    printf("+--------+--------------------------------+--------------------------------+-------------------+-----------------+\n");
    if(nbFormateur > 0) {
        for(i=1;i<=nbFormateur;i++) {
            


            printf("|   %2d   | %-30s | %-30s |    %02d/%02d/%4d     |        %2d       |\n", i, formateurCourant->nom, formateurCourant->prenom, formateurCourant->naissanceJour, formateurCourant->naissanceMois, formateurCourant->naissanceAnnee, formateurCourant->nbTitre);
        printf("+--------+--------------------------------+--------------------------------+-------------------+-----------------+\n");




            formateurCourant= formateurCourant->suivant;
        }
    }
    else
    {
        printf("\n===========================================================\n");
        printf("\n            AUCUN FORMATEUR DANS LE CENTRE                 \n");
        printf("\n===========================================================\n");
    }
}



void supprimerEspaceBlanc(char *str)
{
    int index, i;

    /* Index par défaut */
    index = -1;

    /* Trouver dernier index du character non espace blanc */
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }
        i++;
    }
    str[index + 1] = '\0';
}



void afficherHoraireFormateur(formateur *formateurCourant, formation *formationDebut, int nbFormation) {
    

    formation *formationCourant = malloc(sizeof(*formationCourant));

    int i, j, x, y, z, id;


    char coursPresentGrille[20][50];
    char nomFormationPresentGrille[20][102];
    int nbCoursGrille = 0;
    int verifDoublon;

    printf("|----------+----------+----------+----------+----------+----------+----------+----------|\n");
    printf("|  Heure   |  Lundi   |   Mardi  |  Mecredi |  Jeudi   | Vendredi |  Samedi  | Dimanche |\n");
    printf("|----------+----------+----------+----------+----------+----------+----------+----------|");


    for(j=8;j<= 22; j++) { // Pour chaque heure
        printf("\n|   %02dh00  |", j);
        for(i=1;i<=7;i++) { // Pour chaque jour
            
            if(strcmp(formateurCourant->horaireId[i][j], "AUCUN") == 0) { // Si rien dans la case
                printf("    --    |");
            }
            else
            {
                if(strcmp(formateurCourant->horaireId[i][j], "INDSP") == 0) { // Si indisponible dans la case
                    printf("    //    |");
                }
                else // si id du cours présent
                {
                    formationCourant=formationDebut;
                    for(x=1;x<=nbFormation;x++) { // Passage en revu des formations pour trouver l'id de la formation de la cellule du formateur
                        if(strcmp(formateurCourant->horaireId[i][j], formationCourant->idFormationAnnee) == 0) { // si idFormationAnnee de formation est egal à la cellule de l'horaire du formateur

                            verifDoublon=0; // Aucun doublon par defaut (0)



                            for(y=1;y<=nbCoursGrille;y++) { // Pour chaque cours qui sont deja affiche
                                if (strcmp(coursPresentGrille[y], formationCourant->cours[formationCourant->horaire[i][j]]) == 0) { // si deja present dans la liste affiche
                                    verifDoublon = 1; // doublon deja present
                                    id= y;
                                    break;
                                }
                            }

                            if(verifDoublon == 0) { // si pas de doublon ajout dans la liste qui va etre affiche en legende
                                nbCoursGrille +=1;
                                id=nbCoursGrille;
                                strcpy(coursPresentGrille[nbCoursGrille], formationCourant->cours[formationCourant->horaire[i][j]]); // ajout cours de la formation
                                strcpy(nomFormationPresentGrille[nbCoursGrille], formationCourant->nomComplete); // Ajout nom formation
                                break;
                            }

                        }

                        formationCourant= formationCourant->suivant;

                    }

                    printf("    %02d    |", id);



                }
            }
        }
    }

    printf("\n|----------+----------+----------+----------+----------+----------+----------+----------|\n");

    printf("-- : Vide\n", i, coursPresentGrille[i]);
    printf("// : Empechement\n", i, coursPresentGrille[i]);
    printf("> Nom du cours (formation)\n", i, coursPresentGrille[i]);
    for(i=1;i<= nbCoursGrille; i++) {
        printf("%02d : %s (%s)\n", i, coursPresentGrille[i], nomFormationPresentGrille[i]);
    }

    printf("\n");
}

void afficherHoraireFormation(formation *formationCourant){
    
    int i, j, x;



    printf("|----------+----------+----------+----------+----------+----------+----------+----------|\n");
    printf("|  Heure   |  Lundi   |   Mardi  |  Mecredi |  Jeudi   | Vendredi |  Samedi  | Dimanche |\n");
    printf("|----------+----------+----------+----------+----------+----------+----------+----------|");

    for(j=0;j<= 23; j++) {
        
        printf("\n|   %02dh00  |", j);
        for(i=1;i<=7;i++) {
            if(formationCourant->horaire[i][j] != 0) {
                printf("    %02d    |", formationCourant->horaire[i][j]);
            }
            else
            {
                printf("    --    |", formationCourant->horaire[i][j]);
            }
            
        }
    }
    printf("\n|----------+----------+----------+----------+----------+----------+----------+----------|");

    for(j=1;j<=formationCourant->nbCours; j++) {
        if((j-1) %3 == 0) { // 3 enregistrement par ligne
            printf("\n");
        }
        printf("%2d : %-s, ", j, formationCourant->cours[j]);
    }
    printf("\n");

}

formateur* initialisationFormateur(int *nbFormateur) {

    FILE *fdat1;
    fdat1=fopen("listeFormateur.dat", "r");

    formateur *fSuivant;
    formateur *debut=malloc(sizeof(*debut));
    formateur *courant=malloc(sizeof(*courant));
    debut = courant;

    int i, x;

    //Dans l'odre : nom, prenom, jour naissance, mois naissance, annee naissance, nombre de titre
    //fgets(courant->nomBase, 99, fdat2);
    fgets(courant->nom, 30, fdat1);
    
        char tmp[6];
    fscanf(fdat1, " ");
	while(!feof(fdat1)) {
        fgets(courant->prenom, 30, fdat1);
		fscanf(fdat1," %2d %2d %4d %2d ", &courant->naissanceJour, &courant->naissanceMois, &courant->naissanceAnnee, &courant->nbTitre);
		// Lecture de l'horaire

		for(i=1;i<=7;i++) {
			for(x=1;x<=22;x++) {
                fgets(courant->horaireId[i][x], 6, fdat1);

			}
		}


		// Passage en revue de tout les titres du formateur
		for(i=1;i<= courant->nbTitre; i++) {
			// scan 100 caractere par nombre de titre
            fgets(courant->titre[i], 100, fdat1);
		}

        fscanf(fdat1, " "); // passage à la ligne
	  	fSuivant=malloc(sizeof(formateur));
	  	courant->suivant=fSuivant;
	  	*nbFormateur= *nbFormateur+1;
   	  	courant=fSuivant;
		fgets(courant->nom, 30, fdat1);
	}

	courant=debut;
	for(i=0;i<*nbFormateur;i++){
		courant=courant->suivant;
	}
	courant->suivant=NULL;
    fclose(fdat1);
    return debut;
}


etudiant* initialisationEtudiant(int *nbEtudiant) {

    FILE *fdat;
    fdat=fopen("listeEtudiant.dat", "r");

    etudiant *eSuivant;
    etudiant *debut = malloc(sizeof(*debut));
    etudiant *courant = malloc(sizeof(*courant));
    debut = courant;

    int i, x;


	fscanf(fdat,"%30s", courant->nom);
	while(!feof(fdat)) {
		fscanf(fdat," %30s %5s %2d %2d %4d %2d %8f %8f %8f", courant->prenom, courant->idFormationAnnee, 
		&courant->naissanceJour, &courant->naissanceMois, &courant->naissanceAnnee, &courant->annee, &courant->montantAPayer, 
		&courant->montantPaye, &courant->reduction);
	  	eSuivant=malloc(sizeof(etudiant));
	  	courant->suivant=eSuivant;
	  	*nbEtudiant = *nbEtudiant + 1;
   	  	courant=eSuivant;
		fscanf(fdat,"%30s", courant->nom);
	}      
	courant=debut;
	for(i=0;i<*nbEtudiant;i++) {
		courant=courant->suivant;
	}   
	courant->suivant=NULL;  // free(eSuivant);

    fclose(fdat);
    return debut;
}


formation* initialisationFormation(int *nbFormation) {
    FILE *fdat2;
    fdat2 = fopen("listeFormation.dat","r");

    formation *fSuivant;
    formation *debut = malloc(sizeof(*debut));
    formation *courant = malloc(sizeof(*courant));
    debut = courant;

    int i, x;

    fgets(courant->nomBase, 99, fdat2);
    supprimerEspaceBlanc(courant->nomBase);

	while(!feof(fdat2)) {
        fscanf(fdat2, " ");

        fgets(courant->nomComplete, 101, fdat2);
        supprimerEspaceBlanc(courant->nomComplete);

		fscanf(fdat2," %3s %5s %2d %2d %4d %4d %8f %2d ", &courant->idFormation, &courant->idFormationAnnee, &courant->numeroAnnee, &courant->nbCours, &courant->maxEtudiant, &courant->nbEtudiant, &courant->prix, &courant->nombreAnneeFormation);

        // Lecture de l'horaire, 7jours * 24h
		for(i=1;i<= 7; i++) {
			for(x=0;x<=23;x++) {
				fscanf(fdat2, "%2d", &courant->horaire[i][x]);
			}
		}
        
		// Lecture des cours
		for(i=1;i<=courant->nbCours; i++) {
            fscanf(fdat2, " ");
            fgets(courant->cours[i], 50, fdat2);
            supprimerEspaceBlanc(courant->cours[i]);
		}

        // Lecture des cours deja donnee
        for(i=1;i<=courant->nbCours; i++) {
			fscanf(fdat2, "%1d", &courant->coursDejaDonne[i]);
		}

        //Lecture des prerequis eleve
        fscanf(fdat2,"%1d", &courant->nombrePrerequisEleve);
        if(courant->nombrePrerequisEleve == 0) {
            fgets(courant->prerequisEleve[1], 50, fdat2);
            supprimerEspaceBlanc(courant->prerequisEleve[1]);
        } else {
            for(x = 1; x <= courant->nombrePrerequisEleve; x++) {
                fgets(courant->prerequisEleve[x], 50, fdat2);
                supprimerEspaceBlanc(courant->prerequisEleve[x]);
            }
        }


        //Lecture des prerequis prof
        fscanf(fdat2,"%1d", &courant->nombrePrerequisProf);
        if(courant->nombrePrerequisProf == 0) {
            fgets(courant->prerequisProf[1], 81, fdat2);
            supprimerEspaceBlanc(courant->prerequisProf[1]);
        } else {
            for(x = 1; x <= courant->nombrePrerequisProf; x++){
                fgets(courant->prerequisProf[x], 81, fdat2);
                supprimerEspaceBlanc(courant->prerequisProf[x]);
            }
        }


        //Lecture des nombres d'heures de cours
        for(x = 1; x <= courant->nbCours; x++) {
            fscanf(fdat2, "%2d", &courant->nombreHeureCours[x]);
        }

        //lecture des 
        fSuivant = malloc(sizeof(*fSuivant));
        courant->suivant=fSuivant;
        *nbFormation = *nbFormation + 1;

   	  	courant=fSuivant;
        fscanf(fdat2, " "); // Lecture du saut de ligne
        fgets(courant->nomBase, 99, fdat2);

	}

    //Attribution de NULL pour la dernière formation->suivant
	courant=debut;
	for(i = 1; i < *nbFormation; i++) {
		courant=courant->suivant;
	}   
	courant->suivant=NULL;

    fclose(fdat2);
    return debut;
}

//Affiche les formations sans indiquer les annees
void afficherListeFormationBase(formation *courant, int nombreFormation) {
    formation *debut = malloc(sizeof(*debut));
    formation *fSuite = malloc(sizeof(*fSuite));

    debut = courant;

    if(courant == NULL) {
        exit(EXIT_FAILURE);
    }

    int i, j, nombreFormationBase = 1, numero = 1, tmp;

    //compter formation base differentes
    for(i = 1; i < nombreFormation; i++) {
        fSuite = courant->suivant;
        if(strcmp(courant->idFormation, fSuite->idFormation) != 0) {
            nombreFormationBase = nombreFormationBase + 1;
        }
        courant = fSuite;
    }

    courant = debut;    
    printf("\n=========================================================================================================================\n");
    printf("                                            Liste des formations disponibles\n");
    printf("+--------+-------+------------------------------------------------------------------------------------------------------+\n");
    printf("| Numero | ID    |  Nom                                                                                                 |\n");
    printf("+--------+-------+------------------------------------------------------------------------------------------------------+\n");

    //ecriture des formations bases
    for(j = 0; j < nombreFormationBase; j++) {
        
        
        printf("|   %02d   |  %-3s  | %-100s | \n", numero, courant->idFormation, courant->nomBase);
        numero++;
        tmp = courant->nombreAnneeFormation;
        for(i = 0; i < tmp; i++) {
            //avancer dans la liste
            if(courant->suivant != NULL) {
                courant = courant->suivant;
            }
        }
    }
    printf("+--------+-------+------------------------------------------------------------------------------------------------------+\n");
    printf("\n=========================================================================================================================\n");

}

//Affiche les formations et toutes les annees qui les composent
void afficherListeFormation(formation *courant, int nombreFormation) {

    formation *debut = malloc(sizeof(*debut));
    formation *fSuite = malloc(sizeof(*fSuite));

    debut = courant;

    if(courant == NULL) {
        exit(EXIT_FAILURE);
    }

    int i, j, nombreFormationBase = 1, numero = 1, tmp;

    //compter formation base differentes
    for(i = 1; i < nombreFormation; i++) {
        fSuite = courant->suivant;
        if(strcmp(courant->idFormation, fSuite->idFormation) != 0) {
            nombreFormationBase = nombreFormationBase + 1;
        }
        courant = fSuite;
    }

    courant = debut;

    //Presentation
    printf("\n\nNotre centre vous propose %02d formations differentes", nombreFormationBase);
    printf("\n==================================================================================================================================================\n");
    printf("                                                             Liste des formations");

    //ecriture des formations bases
    for(j = 0; j < nombreFormationBase; j++) {
        printf("\n==================================================================================================================================================\n");
        printf("ID de la formation complete : %-3s     Nom : %-100s\n", courant->idFormation, courant->nomBase);
        printf("+--------+-------+------------------------------------------------------------------------------------------------------+-----------+------------+\n");
        printf("| Numero | ID    |  Nom                                                                                                 | Etudiants |    Prix    |\n");
        printf("+--------+-------+------------------------------------------------------------------------------------------------------+-----------+------------+\n");
        tmp = courant->nombreAnneeFormation;
        for(i = 0; i < tmp; i++) {
            printf("|   %02d   | %-5s | %-100s |   %02d/%02d   |   %6.2f   |\n", numero, courant->idFormationAnnee, courant->nomComplete, courant->nbEtudiant, courant->maxEtudiant, courant->prix);
            numero++;
            //avancer dans la liste
            if(courant->suivant != NULL) {
                courant = courant->suivant;
            }
        }
        printf("+--------+-------+------------------------------------------------------------------------------------------------------+-----------+------------+\n");
    }
}



void supprimerFormateur(formateur *asupprimer, formateur *formateurDebut, int nbFormateur) {
    int i;


    formateur *formateurCourant=malloc(sizeof(*formateurCourant));
    formateur *formateurIntercale=malloc(sizeof(*formateurIntercale));
    formateurCourant=formateurDebut;
    for(i=1;i<=nbFormateur;i++) {

        


        if(
            formateurCourant->naissanceAnnee == asupprimer->naissanceAnnee &&
            formateurCourant->naissanceJour == asupprimer->naissanceJour &&
            formateurCourant->naissanceMois == asupprimer->naissanceMois &&
            (strcmp(formateurCourant->nom, asupprimer->nom)== 0) &&
            (strcmp(formateurCourant->prenom, asupprimer->prenom)== 0)
        ) {

            if(i==1) {
                asupprimer = asupprimer->suivant;
                free(asupprimer);
            }
            else
            {
                formateurIntercale->suivant = formateurCourant->suivant;
                free(formateurCourant);
                break;
            }

        }
        formateurIntercale = formateurCourant;
        formateurCourant=formateurCourant->suivant;
    }
}





//Supprime l'annee de formation indique.
void supprimerFormationAnnee(int numIdASupprimer, int *nombreFormation, formation *debut) {
    int i, nb;
    formation *aSupprimer = malloc(sizeof(*aSupprimer));
    formation *courant = malloc(sizeof(*courant));

    aSupprimer = debut;

    //3 caracteres de la formation
    char id[4];

    //recherche de l'id
    aSupprimer = debut;
    for(i = 1; i < numIdASupprimer; i++) {
        aSupprimer = aSupprimer->suivant;
    }
    strcpy(id, aSupprimer->idFormation);
    nb = aSupprimer->nombreAnneeFormation;


    if(numIdASupprimer >= 1 && numIdASupprimer <= *nombreFormation) {

        if(numIdASupprimer == 1) {
            debut = debut->suivant;
            free(aSupprimer);
        } else {
            courant = debut;
            //On se deplace jusqu a la bonne adresse
            for(i = 1; i < numIdASupprimer - 1; i++) {
                courant = courant->suivant;
            }

            if(numIdASupprimer != *nombreFormation) {
                aSupprimer = courant->suivant;
                courant->suivant = aSupprimer->suivant;
                free(aSupprimer);
            } else {
                aSupprimer = courant->suivant;
                courant->suivant = NULL;
                free(aSupprimer);
            } 
            *nombreFormation = *nombreFormation - 1;
        }
        //diminuer le nombre d'annee de formation
        //recherche de la premiere annee de la formation a supprimer
        aSupprimer = debut;
        for(i = 1; i <= *nombreFormation; i++) {
            if(strcmp(aSupprimer->idFormation, id) == 0) {
                aSupprimer->nombreAnneeFormation = aSupprimer->nombreAnneeFormation - 1;
            }
            aSupprimer = aSupprimer->suivant;
        }
    }
    courant = debut;
}


//Supprimer une formation entiere : toutes les annees qui la composent
formation* supprimerFormationEntiere(int numIdASupprimer, int *nombreFormation, formation *debut) {

    int i, j, positionAvantFormation, nb;
    formation *aSupprimer = malloc(sizeof(*aSupprimer));
    formation *courant = malloc(sizeof(*courant));
    formation *avant = malloc(sizeof(*avant));

    //3 caracteres de la formation
    char id[4];

    //recherche de l'id
    aSupprimer = debut;
    courant = debut;
    i = 1;
    while(i != numIdASupprimer) {
        aSupprimer = courant->suivant;
        if(strcmp(courant->idFormation, aSupprimer->idFormation) != 0) {
            i++;
        }
        courant = aSupprimer;
    }

    strcpy(id, aSupprimer->idFormation);
    nb = aSupprimer->nombreAnneeFormation;

    //Cas ou la formation est la premiere
    if(strcmp(id, debut->idFormation) == 0) {
        //Nouveau debut
        for(i = 1; i <= nb; i++) {
            aSupprimer = aSupprimer->suivant;
        }

        
        avant = aSupprimer;     //Placement de la formation aSupprimer dans avant     
        aSupprimer = debut;
        for(i = 1; i <= nb; i++) {
            courant = aSupprimer->suivant;
            for(j = 1; j <= aSupprimer->nbCours; j++) {
                if(aSupprimer->coursDejaDonne[j] != 0) {    //Verification que aucun formateur ne soit dans la formation
                    printf("Suppression impossible : un formateur est present dans une annee\n");
                    return debut;
                }
            }

            if(aSupprimer->nbEtudiant != 0) {   //verification que aucun etudiant ne soit inscrit
                printf("Suppression impossible : un eleve est present dans une annee\n");
                return debut;
            }
            aSupprimer = courant;
        } 

        aSupprimer = debut;
        for(i=1; i <= nb; i++) {
            courant = aSupprimer->suivant;
            printf("Suppression de %-101s\n", aSupprimer->nomComplete);
            free(aSupprimer);
            aSupprimer = courant;
            *nombreFormation = *nombreFormation - 1;
        }

        debut = avant;  //Nouveau debut


    } else {
        //Cas ou la formation n'est pas la premiere
        //recherche de la premiere annee de la formation a supprimer
        aSupprimer = debut;
        i = 1;
        while(strcmp(aSupprimer->idFormation, id) != 0) {
            aSupprimer = aSupprimer->suivant;
            i++;
        }
        i--;
        positionAvantFormation = i;

        //controle de suppression
        courant = debut;    //remise au debut
        for(i = 1; i < positionAvantFormation; i++) {
            courant = courant->suivant;     //se positionner a la formation juste avant la premiere annee visee
        }    

        for(j = 1; j <= nb; j++) {
            aSupprimer = courant->suivant;
            printf("%-5s %02d\n", aSupprimer->idFormationAnnee, aSupprimer->nbEtudiant);
            if(aSupprimer->nbEtudiant != 0) {
                printf("Impossible de supprimer cette formation car un etudiant y est inscrit.\n");
                return debut;
            }
            for(i = 1; i <= aSupprimer->nbCours; i++) {
                if(aSupprimer->coursDejaDonne[i] != 0) {
                    printf("Impossible de supprimer cette formation car un formateur y est inscrit.\n");
                    return debut;
                }
            }
            courant = courant->suivant;
        }


        //suppression
        courant = debut;    //remise au debut
        for(i = 1; i < positionAvantFormation; i++) {
            courant = courant->suivant;     //se positionner a la formation juste avant la premiere annee visee
        }   

        for(j = 1; j <= nb; j++) {
            aSupprimer = courant->suivant;
            courant->suivant = aSupprimer->suivant;
            free(aSupprimer);
            *nombreFormation = *nombreFormation - 1;
        }
    }

    //S'assure que le dernier maillon soit NULL (si la derniere formation etait ciblee)
    courant = debut;
    for(i = 1; i < *nombreFormation; i++) {
        courant = courant->suivant;
    }
    courant->suivant = NULL;

    return debut;

}

void reinitialiserFormationDat() {
    FILE *fres;
    fres = fopen("listeFormation.dat","w");
    fclose(fres);
}


formateur* ajoutFormateur(formateur *debut, int *nb, formation *formationDebut, int nombreFormation) {

    formateur *nouveauFormateur;
    formateur *courant;
    nouveauFormateur = malloc(sizeof(formateur));
    courant = malloc(sizeof(courant));
    formation *fSuite;
    fSuite = malloc(sizeof(fSuite));
    void afficherHoraireFormateur(formateur *, formation*, int);
    void ecrireFormateur(formateur *);

    int i, j, x, choixDeFormation = 1, reponse, heureDebutIndisponibilite, heureFinIndisponibilite, jour, heure, nbHeure, accord = 0, envie = 1;
    int tmpJourN, tmpMoisN, tmpAnneeN;

    printf("Quel est votre nom ? ");
    scanf(" "); //Absorbtion de newline
    for(i = 0; i < 29; i++) {
        nouveauFormateur->nom[i] = getchar();
        if(nouveauFormateur->nom[i] == '\n') {
            nouveauFormateur->nom[i] = '\0';
            break;
        }
    }
    nouveauFormateur->nom[29] = '\0';

    printf("\nQuel est votre prenom ? ");
    //scanf(" "); //Absorbtion de newline
    for(i = 0; i < 29; i++) {
        nouveauFormateur->prenom[i] = getchar();
        if(nouveauFormateur->prenom[i] == '\n') {
            nouveauFormateur->prenom[i] = '\0';
            break;
        }
    }

    //Date de naissance
    printf("\nInformation date de naissance : \n");
    //Entree de annee + controle de donnees
    printf("> Annee : "); 
    scanf(" %d", &tmpAnneeN);
    while(tmpAnneeN < 1932 || tmpAnneeN > 2004) {
        printf("Annee incorrecte : ");
        scanf(" %d", &tmpAnneeN);
    }
    //Entree du mois + controle de donnees
    printf("> Mois de naissance : "); 
    scanf(" %d", &tmpMoisN);
    while(tmpMoisN < 1 || tmpMoisN > 12) {
        printf("Mois incorrect : ");
        scanf(" %d", &tmpMoisN);
    }
    //Entree du jour + controle de donnees
    printf("> Jour de naissance : "); 
    scanf(" %d", &tmpJourN);
    while(tmpJourN < 1 || tmpJourN > 31) {
        printf("Annee incorrecte : ");
        scanf(" %d", &tmpJourN);
    }

    //Gestion des indisponibilites
    printf("Avez-vous des indisponibilites ? \n");
    printf("1 : Oui\n");
    printf("0 : Non\n");
    printf("Votre reponse : ");
    scanf(" %d", &reponse);
    while(reponse < 0 || reponse > 2) {
        printf("\nReponse incorrecte. Essayez à nouveau : %d", &reponse);
    }

    //Initialisation de son horaire (disponible tout le temps dans un premier temps) 
    for(i = 1; i <= 7; i++) {
        for(j = 0; j <= 22; j++) {
            //nouveauFormateur->horaire[i][j] = 0;
            strcpy(nouveauFormateur->horaireId[i][j], "AUCUN");

        }
    }

    //Selection du jour et ensuite des heures. Quand une indisponibilite est remplie
    //on repropose la liste des jours. L'utilisateur peut choisir retour pour sortir de la boucle
    while(reponse != 0) {
        afficherHoraireFormateur(nouveauFormateur, formationDebut, nombreFormation);
        
        //Jour
        printf("1 : Lundi\n");
        printf("2 : Mardi\n");
        printf("3 : Mercredi\n");
        printf("4 : Jeudi\n");
        printf("5 : Vendredi\n");
        printf("6 : Samedi\n");
        printf("7 : Dimanche\n");
        printf("0 : Retour\n");
        printf("Quel jour etes-vous indisponible ? ");
        scanf(" %d", &jour);

        //printf("%d", jour);

        //Controle de donnees
        while(jour < 0 || jour > 7) {
            printf("Numero incorrect : ");
            scanf(" %d", &jour);
        }
        
        //debut de l'indisponibilite
        printf("\nA partir de quelle heure etes-vous indisponible ? ");
        scanf(" %d", &heureDebutIndisponibilite);
        while(heureDebutIndisponibilite < 0 || heureDebutIndisponibilite > 23) {
            printf("\nHeure incorrecte, essayez a nouveau : ");
            scanf(" %d", &heureDebutIndisponibilite);
        }

        //fin de l'indisponibilite.
        //NOTE : Si l'utilisateur entre 10, alors on considere qu'il peut donner cours a 10h. Donc c'est [heureDeb, heureFin[
        printf("\nA partir de quelle heure pourriez-vous reprendre votre activite ? ");
        scanf(" %d", &heureFinIndisponibilite);
        while(heureFinIndisponibilite <= heureDebutIndisponibilite || heureFinIndisponibilite > 23 ) {
            printf("\nHeure incorrecte, essayez a nouveau : ");
            scanf(" %d", &heureFinIndisponibilite);
        }

        //Remplissage des indisponibilites
        for(i = heureDebutIndisponibilite; i < heureFinIndisponibilite; i++) {
            //nouveauFormateur->horaire[jour][i] = -1;
            strcpy(nouveauFormateur->horaireId[jour][i], "INDSP");
        }


        afficherHoraireFormateur(nouveauFormateur, formationDebut, nombreFormation);
        //Avancer ou sortir de la boucle while
        printf("Avez-vous d'autres indisponibilites ?\n");
        printf("1 : Oui\n");
        printf("0 : Non\n");
        printf("Votre reponse : ");
        scanf(" %d", &reponse);
        while(reponse < 0 || reponse > 2) {
            printf("\nReponse incorrecte. Essayez à nouveau : %d", &reponse);
        }
    }

    nouveauFormateur->nbTitre=0; ;

    //Rentrera toujours au moins une fois dans cette boucle car choixDeFormation est initialise a 1.
    //Dans ce while, on s'occupe de lui attribuer une (ou plusieurs) formation ainsi que des cours (qu'il choisit) au sein de ces formations
    while(choixDeFormation != 0 ) {

        printf("Voici la liste des formations : \n");
        afficherListeFormation(formationDebut, nombreFormation);
        printf("0 : RETOUR\n");

        //Prevention de mauvaise valeur
        printf("\nVeuillez entrer le numero de la formation dans laquelle vous souhaitez enseigner : ");
        scanf(" %d", &choixDeFormation);
        while(choixDeFormation < 0 || choixDeFormation > nombreFormation) {
            printf("Valeur invalide.");
            printf("\nVotre choix : ");
            scanf(" %d", &choixDeFormation);
        }

        //Si l'utilisateur a choisi RETOUR
        if(choixDeFormation == 0) {
            //TEST
            printf("Vous avez choisi : %1d. Retour\n", choixDeFormation);
            break;
        }

        //recuperation de la formation ciblee
        fSuite = formationDebut;
        for(i = 1; i < choixDeFormation; i++) {
            fSuite = fSuite->suivant;
        }

        //Verification des prerequis
        if(fSuite->nombrePrerequisProf > 0) {
            printf("La formation necessite %1d prerequis pour y enseigner. \nVeuillez repondre a ces questions : ", fSuite->nombrePrerequisProf);
            for(i = 1; i <= fSuite->nombrePrerequisProf; i++) {
                printf("\nPossedez-vous : %-80s ?", fSuite->prerequisProf[i]);
                printf("\n0 : Non");
                printf("\n1 : Oui");
                printf("\nVotre reponse : ");
                scanf(" %d", &reponse);
                while(reponse < 0 || reponse > fSuite->nombrePrerequisProf) {
                    printf("Reponse invalide.\n");
                    printf("Votre reponse : ");
                    scanf(" %d", &reponse);
                }

                //reponse positive, on copie
                if(reponse == 1) {
                    nouveauFormateur->nbTitre = nouveauFormateur->nbTitre + 1;
                    strcpy(nouveauFormateur->titre[nouveauFormateur->nbTitre], fSuite->prerequisProf[i]);
                } else {
                    //Reponse negative, fin de la fonction et annulation de l'inscription du formateur
                    printf("Vous ne remplissez pas les conditions d'inscription en tant que formateur.\n");
                    printf("Nous vous souhaitons une bonne continuation.\n\n\n");
                    free(nouveauFormateur);
                    return;
                }
            }
        }

        //Choix des cours donnes
        //Affichage des cours pas encore donne
        //envie est le numero du cours choisi. Si c'est a 0, c'est qu'on souhaite sortir de cette formation
        envie = 1;
        while(envie != 0 || envie == 999) {
            printf("Voici les cours disponibles pour cette formation : \n");
            for(i = 1; i <= fSuite->nbCours; i++) {
                if(fSuite->coursDejaDonne[i] == 0) {
                    printf("%02d : %-49s\n", i, fSuite->cours[i]);
                }
            }

            printf("0 : Retour\n");
            printf("Votre choix : ");
            scanf(" %d", &envie);
            while(envie < 0 || envie > fSuite->nbCours) {
                printf("Choix incorrect. Essayer a nouveau : ");
                scanf(" %d", &envie);
            }
            //verification que l'utilisateur n'aie pas entre le numero d'un cours indisponible
            if(envie != 0) {    //Une condition pour eviter d'iterer inutilement si l'utilisateur souhaite sortir de ce menu
                for(j = 1; j <= fSuite->nbCours; j++) {
                    if(fSuite->coursDejaDonne[j] == 1) {
                        if(envie == j) {        //Si le cours numero J est deja pris et que l'utilisateur a entre le cours numero J, on change la valeur de envie
                            printf("Cours indisponible !\n");
                            envie = 999;        //Avec envie a 999, on ne rentre pas dans la gestion de l'horaire, mais on recommence la boucle du choix du cours.
                        }
                    }
                }
            }

            if(envie != 0 && envie != 999) {
                //Gestion de l'horaire
                accord = 0;
                while(accord == 0)  {
                    accord = verificationHoraire(fSuite, envie, nouveauFormateur, formationDebut, nombreFormation);
                }
            }
        }
    }
    
    //Pour une raison que je ne comprends pas, si on attribue tout de suite les valeurs à la structure, elles se perdent. Donc intermediaire
    nouveauFormateur->naissanceAnnee = tmpAnneeN;
    nouveauFormateur->naissanceMois = tmpMoisN;
    nouveauFormateur->naissanceJour = tmpJourN;
    ecrireFormateur(nouveauFormateur);

    ///AJOUT FORMATEUR A LA CHAINE////////////////////////  
    courant = debut;
    for(i = 1; i < *nb; i++) {
       courant = courant->suivant; 
    }
    courant->suivant=nouveauFormateur;        
    nouveauFormateur->suivant = NULL;                         
    *nb = *nb + 1;
    //////////////////////////////////////////////////////

    return debut;
}

//fonction appelee dans ajouterFormateur
//Le but de cette fonction est de demander a l'utilisateur un jour, une heure et une periode (1h, 2h, 3h, ...) pendant laquelle
//il donne son cours.
//S'en suit une comparaison avec l'horaire de la formation entree en argument
//Si les plages horaires de la formation sont libres, alors on renvoie 1, sinon, 0
//NOTE : Quand on renvoie 0, cette fonction est a nouveau appelee
int verificationHoraire(formation *fSuite, int numeroCoursChoisi, formateur *nouveau, formation *formationDebut, int nbFormation) {
    int heureRestante, heureDonnee = 0, jour, heure, i;

    //Initialisation du nombre d'heure restante
    heureRestante = fSuite->nombreHeureCours[numeroCoursChoisi];
    void afficherHoraireFormateur(formateur*, formation*, int);
    while(heureRestante > 0) {

        afficherHoraireFormateur(nouveau, formationDebut, nbFormation);
        printf("\nHeure(s) restante(s) pour ce cours : %02d\n", heureRestante);
        //Demander le jour et heures pendant lesquelles il donne cours.


        printf("1 : Lundi\n");
        printf("2 : Mardi\n");
        printf("3 : Mercredi\n");
        printf("4 : Jeudi\n");
        printf("5 : Vendredi\n");
        printf("6 : Samedi\n");
        printf("7 : Dimanche\n");
        printf("0 : Retour\n");
        printf("Quel jour souhaiteriez-vous donne ce cours ? ");
        scanf("%d", &jour);
        while(jour < 0 || jour > 7) {
            printf("\nJour incorrect, essayez a nouveau : ");
            scanf("%d", &jour);
        }

        printf("A quelle heure souhaitez-vous commencer votre cours ? ");
        scanf("%d", &heure);
        while(heure < 0 || heure > 23 || fSuite->horaire[jour][heure] != 0) {   //3e condition : Verification qu'aucun cours ne soit deja donne ce jours, a cette heure la
            printf("\nHeure incorrecte, essayez a nouveau : ");
            scanf("%d", &heure);
        }

        printf("Pendant combien d'heure(s) durera votre session ? ");
        scanf("%d", &heureDonnee);

        while(heureDonnee < 0 || heureDonnee > heureRestante || heure + heureDonnee > 23) {
            printf("Le nombre d'heure est incorrect");
            scanf("%d", &heureDonnee);
        }

        //Verification horaire formation
        for(i = heure; i < heure + heureDonnee; i++) {
            if(fSuite->horaire[jour][i] != 0) {
                printf("Erreur : conflit d'horaire dans la formation !\n");
                return 0;
            }
        }

        //Verification indisponibilite du formateur
        for(i = heure; i < heure + heureDonnee; i++) {
            if(strcmp(nouveau->horaireId[jour][i], "INDSP") == 0) {
                printf("Erreur : heure pendant une indisponibilite !\n");
                return 0;
            }
        }

        //Modification de l'horaire et du nombre d'heure restante
        for(i = heure; i < heure + heureDonnee; i++) {
            //nouveau->horaire[jour][i] = numeroCoursChoisi;
            
            fSuite->horaire[jour][i] = numeroCoursChoisi;
            strcpy(nouveau->horaireId[jour][i], fSuite->idFormationAnnee);
        }
        fSuite->coursDejaDonne[numeroCoursChoisi] = 1;
        heureRestante = heureRestante - heureDonnee;
        printf("Horaire mis a jour !\n");
    }
    

    // Vu qu'on a aussi modifier formation on reecris toutes les formations
    void ecrireFormation(formation*);
    FILE *fres;
    fres=fopen("listeFormation.dat", "w");
    fclose(fres);
    formation *formationCourant = malloc(sizeof(*formationCourant));
    formationCourant=formationDebut;
    for(i=1;i<=nbFormation;i++) {
        ecrireFormation(formationCourant);
        formationCourant=formationCourant->suivant;
    }


    afficherHoraireFormateur(nouveau, formationDebut, nbFormation);
    return 1;

}

void ecrireFormateur(formateur *courant) {

    FILE *fres;
    fres = fopen("listeFormateur.dat", "a");

    int i, j;

    //Dans l'odre : nom, prenom, jour naissance, mois naissance, annee naissance, nombre de titre
    fprintf(fres,"%-30s%-30s %02d %02d %4d %02d ", courant->nom, courant->prenom, courant->naissanceJour, courant->naissanceMois, courant->naissanceAnnee, courant->nbTitre);    

    //ecriture de l'horaire
    for(i = 1; i <= 7; i++) {
        for(j = 1; j <= 22; j++) {      //On commence a 1, pas 0. ->Simplifie le sens : en 9eme position, c'est la 9eme heure. Pas de decalage
            fprintf(fres,"%5s", courant->horaireId[i][j]);
        }
    }

    for(i = 1; i <= courant->nbTitre; i++) {
        fprintf(fres,"%-100s", courant->titre[i]);
    }    

    fprintf(fres,"\n");
    fclose(fres);    

}