# Projet de Gestion de Formations, Formateurs et Étudiants

## Description

Ce projet est un programme de gestion d'un centre de formation. Il permet de gérer les **formations**, les **formateurs** et les **étudiants**, en prenant en compte divers aspects comme les prérequis pour suivre une formation, les horaires de cours, les coûts, et la gestion budgétaire.

Le projet enregistre les données dans des fichiers `.dat` :
- ```DesplanqueCDelattre01.dat``` : Liste des élèves
- ```DesplanqueCDelattre02.dat``` : Liste des formateurs
- ```DesplanqueCDelattre03.dat``` : Liste des formations de chaque année

Ce projet contient également un executable pour reinitialiser ces même fichiers `.dat` (`ResetEcritureFichierListeEtudiant.exe`)

## Fonctionnalités Principales

### Gestion des Formations
- Ajouter, supprimer et modifier des formations.
- Chaque formation a un coût pour les étudiants et peut avoir des réductions appliquées.
- Suivi des cours proposés dans chaque formation et des prérequis pour les étudiants et les formateurs.
- Chaque formation est divisée en années, permettant de gérer les étudiants inscrits dans différentes années d'une même formation.

### Gestion des Formateurs
- Les formateurs peuvent être assignés à plusieurs formations et cours.
- Chaque formateur a un ensemble de titres requis pour donner des cours.
- Gestion des horaires et des indisponibilités pour chaque formateur.

### Gestion des Étudiants
- Inscription des étudiants à différentes formations.
- Suivi des paiements des étudiants avec possibilité d'accorder des réductions.
- Limite sur le nombre d'étudiants par formation.

### Aspect Budgétaire
- Calcul du coût par étudiant pour chaque formation.
- Gestion des réductions et des montants payés par les étudiants.
- Calcul du bénéfice ou de la perte pour chaque formation, en tenant compte des coûts des formateurs.

## Installation et Compilation

1. Clonez le dépôt dans votre environnement local :
   ```bash
   git clone https://github.com/Dofault/Gestion-centre-formation
   cd Gestion-centre-formation
2. Compilez le programme avec la commande suivante :
   ```bash
    gcc Projet.c -o Projet
3. Exécutez le programme :
   ```bash
    ./Projet
## Améliorations Futures (Options)
- Système de palier de prix selon le titre requis du formateur.
- Gestion automatique des augmentations de salaire pour les formateurs en fonction de leur ancienneté.
- Calcul automatique des bénéfices et des pertes du centre de formation.
- Affichage de la liste complète des étudiants inscrits par formation ou par année.

## Table des Variables

| Nom                  | Description                                                                 |
| -------------------- | --------------------------------------------------------------------------- |
| `nomBase[100]`        | Nom de la formation                                                         |
| `nomComplete[102]`    | Nom complet avec le numéro de l'année                                       |
| `cours[20][50]`       | Noms des cours de l'année                                                   |
| `maxEtudiant`         | Nombre maximum d'étudiants pour une année                                   |
| `nombreAnneeFormation`| Nombre d'années sur lesquelles s'étale la formation                         |
| `nbCours`             | Nombre de cours dans l'année                                                |
| `nbEtudiant`          | Nombre d'étudiants inscrits pour l'année                                    |
| `prix`                | Prix de la formation (hors réduction)                                       |
| `numeroAnnee`         | Numéro de l'année de la formation                                           |
| `horaire[8][25]`      | Grille horaire des cours (8 jours, 25 heures par jour)                      |
| `idFormation[3]`      | Identifiant de base de la formation (3 lettres)                             |
| `idFormationAnnee[5]` | Identifiant unique pour chaque année de la formation (année + idFormation)  |
| `coursDejaDonne[20]`  | Liste des cours déjà assignés à un formateur                                |

## Credits

Merci à [Tilthood](https://github.com/Tilthood) pour sa contribution !