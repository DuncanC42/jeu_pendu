#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#define SIZE 40
#define NUM_ERREURS_MIN 8
#define NUM_ERREURS_MAX 12

// Fonction pour afficher l'ASCII art en fonction du nombre d'erreurs
void afficher_pendu(int erreurs_actuelles, int erreurs_max) {
    // Calcul du taux d'erreur en pourcentage
    int taux_erreur = (erreurs_actuelles * 100) / erreurs_max;
    // Ajout de la barre supérieure (30%)
    if (taux_erreur >= 30) {
        printf("_______\n"); // Barre supérieure (transversale)
    }
    // Ajout de la corde (40%)
    if (taux_erreur >= 40) {
        printf(" |/|\n"); // Corde accrochée
    } else if (taux_erreur >= 30) {
        printf(" |/\n"); // Barre sans corde
    }
    if (taux_erreur>=50){
        printf(" |(_)\n"); // Tête du pendu
    }
    else if(taux_erreur>=20){
        printf(" |\n"); // Pilier complet (à 20%)
    }

    // Ajout des bras (60%)
    if (taux_erreur >= 60) {
        printf(" |\\|/\n"); // Bras complets
    } 
    else if (taux_erreur >= 20) {
        printf(" |\n"); // Pas de bras, mais espace sous le torse
    }
    
        // Ajout du torse (80%)
    if (taux_erreur >= 80) {
        printf(" ||\n"); // Torse
    } 
    else if (taux_erreur >= 20) {
        printf(" |\n"); // Pas de torse, mais espace sous la tête
    }

    // Ajout des jambes (100%)
    if (taux_erreur >= 100) {
        printf(" |/ \\\n"); // Jambes complètes
    } 
    else if (taux_erreur >= 10) {
        printf(" |\n"); // Pas de jambes, mais espace sous les bras
    }

    if (taux_erreur>=10){// Affichage de la base du pilier
        printf("__|__\n");
    }
}

void displayIntro(){
printf("·······························································································\n");
printf(":     ██╗███████╗██╗   ██╗    ██████╗ ██╗   ██╗    ██████╗ ███████╗███╗   ██╗██████╗ ██╗   ██╗:\n");
printf(":     ██║██╔════╝██║   ██║    ██╔══██╗██║   ██║    ██╔══██╗██╔════╝████╗  ██║██╔══██╗██║   ██║:\n");
printf(":     ██║█████╗  ██║   ██║    ██║  ██║██║   ██║    ██████╔╝█████╗  ██╔██╗ ██║██║  ██║██║   ██║:\n");
printf(":██   ██║██╔══╝  ██║   ██║    ██║  ██║██║   ██║    ██╔═══╝ ██╔══╝  ██║╚██╗██║██║  ██║██║   ██║:\n");
printf(":╚█████╔╝███████╗╚██████╔╝    ██████╔╝╚██████╔╝    ██║     ███████╗██║ ╚████║██████╔╝╚██████╔╝:\n");
printf(": ╚════╝ ╚══════╝ ╚═════╝     ╚═════╝  ╚═════╝     ╚═╝     ╚══════╝╚═╝  ╚═══╝╚═════╝  ╚═════╝ :\n");
printf(":                                                                                             :\n");
printf("·······························································································\n");

}

// Proposer un mot et un nombre de chances
// Afficher le mot en _ _ _ _ _ _
// Tant que le nombre de chance > 0 et que le mot affiché contient "_" :
    // Proposer une lettre qui pourrait être présente
        // Si le caractère est présent :
            // On l'affiche à la place des "_"
        // Sinon 
            // On retire une chance
            // On affiche l'état du pendu
            // Si chance = 0 :
                // On indique que la personne a perdu
                // On précise le mot cherché
                // On indique où elle en était
            // Sinon : 
                // Sauvegarder la lettre proposée dans une liste


bool estPresent(char caractereCherche, char motSujet[]){
    bool res = false;
    for (int i = 0; i < strlen(motSujet) && res == false; i++){
        if (motSujet[i] == caractereCherche){
            res = true;
        }
    }
    return res;
}

void majChaineProposition(char *chaineProposition, const char *motRecherche, char caractereTrouve){
    for (int i = 0 ; i < strlen(motRecherche); i++){
        if (motRecherche[i] == caractereTrouve){
            chaineProposition[i] = caractereTrouve;
        }
    }
}

void ajouterLettreErreur(char *tabErreurs, int *nbErreursActuelles, int tailleMax, char mauvaisCaractere){
    if (*nbErreursActuelles < tailleMax) {
        tabErreurs[*nbErreursActuelles] = mauvaisCaractere;
        (*nbErreursActuelles)++;
    }
}

bool dejaPropose(char *tab,int taille,char caractereCherche){
    for (int i = 0; i < taille; i++){
        if (tab[i] == caractereCherche){
            return true;
        }
    }
    return false;
}

void afficherLettresErreurs(char *tabErreurs, int nbErreursActuelles) {
    printf("Lettres déjà proposées : ");
    for (int i = 0; i < nbErreursActuelles; i++) {
        printf("%c ", tabErreurs[i]);
    }
    printf("\n");
}



void ecranPerdu(char *etatRecherche, char *motRecherche){
    printf("PERDU !\n");
    printf("Etat de tes recherches : %s\n", etatRecherche);
    printf("Le mot recherché était %s\n", motRecherche);

}

bool estGagne(char *etatRecherche){
    for (int i = 0; i < strlen(etatRecherche); i++){
        if (etatRecherche[i] == '_'){
            return false;
        }
    }
    return true;
}

char choisirCaractere(){
    srand(time(NULL));
    int index = 97 + rand() % 26;
    char caractere = (char)index;
    return caractere;
}


int main(){

    displayIntro();

    char* liste_mots[] = { "bonjour", "maison", "papillon", "artisan",
    "ruelle", "ordinateur", "chocolat", "fromage", "jardin", "etoile",
    "nuages", "cyclone", "robotique", "escargot", "chameau", "probleme",
    "terrasse", "bonsoir", "biscuit", "catastrophe" };

    int nb_mots = 20; //Nombre de mots dans liste_mots.

    // Proposer un mot et un nombre de chances
    char* motRecherche = malloc(SIZE);
    int nbErreursMax, nbErreur;
    int nbLettresErreurs = 0; // Compteur pour les lettres d'erreur stockées
    nbErreur = 0;
    
    srand(time(NULL));

    nbErreursMax = rand()%((NUM_ERREURS_MAX+1)-NUM_ERREURS_MIN) + NUM_ERREURS_MIN;
    int indexMotCherche = rand()% nb_mots;

    strcpy(motRecherche, liste_mots[indexMotCherche]);

    printf("le mot est %s\n", motRecherche); // A supprimer plus tard
    printf("Vous avez le droit à %d erreurs\n", nbErreursMax);

    char tabLettresErreurs[nbErreursMax];
    for (int i = 0; i < nbErreursMax; i++) {
        tabLettresErreurs[i] = ' '; // Initialise chaque case à un espace
    }
    // Afficher le mot en _ _ _ _ _ _
    char etatPropositionMot[strlen(motRecherche)];
    for (int i = 0; i < strlen(motRecherche); i++){
        etatPropositionMot[i] = '_';
    }

    // Tant que le nombre de chance > 0 et que le mot affiché contient "_" :
    while ( nbErreur < nbErreursMax && !estGagne(etatPropositionMot)){

        // Proposer une lettre qui pourrait être présente
        char caracterePropose;
        sleep(5);
        printf("Proposez une lettre : \n");
        caracterePropose = choisirCaractere();
        // Si le caractère est présent OU qu'on a déjà fait cette erreur:
        if (estPresent(caracterePropose, motRecherche) || dejaPropose(tabLettresErreurs, nbErreursMax, caracterePropose)){
            majChaineProposition(etatPropositionMot, motRecherche, caracterePropose);
        }
        // sinon
        else {
            // On retire une chance
            nbErreur++;
            // On affiche l'état du pendu
            afficher_pendu(nbErreur, nbErreursMax);
            // Si chance = 0 :
            if (nbErreur >= nbErreursMax){
                // On indique que la personne a perdu
                // On précise le mot cherché
                // On indique où elle en était
                ecranPerdu(etatPropositionMot, motRecherche);
            }
            // Sinon : 
            else {
                // Sauvegarder la lettre proposée dans une liste
                ajouterLettreErreur(tabLettresErreurs, &nbLettresErreurs, nbErreursMax, caracterePropose);
                printf("Cette lettre n'est pas dans le mot ! Il te reste %d erreurs possibles\n", nbErreursMax - nbErreur);
            }

            afficherLettresErreurs(tabLettresErreurs, nbLettresErreurs);
        }

        printf("Etat des recherches : %s\n", etatPropositionMot);

    }
    
    if (estGagne(etatPropositionMot)){
        printf("GAGNÉ ! Le mot était bien %s\n", motRecherche);
    }
        
}