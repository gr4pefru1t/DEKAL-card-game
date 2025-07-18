#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "declarations.h"
#include "initialisation.h"
#include "affichage.h"
#include "tests.h"
#include "partie.h"
int main() {
    plein_ecran();

    S_Carte tab_cartes[100]; // Paquet de 100 cartes
    S_Carte cartes_posees[6]; // Pour stocker les cartes posées par les joueurs (max 6 joueurs)
    S_Joueur tab_joueurs[6]; // Tableau des joueurs (max 6 joueurs)
    int nb_joueurs, type_partie, gagnant;

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    printf("=== BIENVENUE DANS LE JEU DEKAL ===\n\n");

    // Initialisation des joueurs et distribution des cartes
    nb_joueurs = demarrage_jeu(tab_joueurs, tab_cartes);

    choix_partie(&type_partie);

    // Selon le type de partie choisi
    if (type_partie == 1) {
        // Partie rapide : un seul round
        printf("\nDébut de la partie rapide...\n");

        // Jouer une partie rapide
        gagnant = jouer_partie_rapide(tab_joueurs, tab_cartes, cartes_posees, nb_joueurs);

        printf("\n\nFin de la partie ! Le gagnant est %s !\n", tab_joueurs[gagnant].pseudo);
    }
    else {
        // Partie longue : plusieurs rounds jusqu'à ce qu'un joueur atteigne 100 points
        printf("\nDébut de la partie longue...\n");

        // Jouer une partie longue
        gagnant = jouer_partie_longue(tab_joueurs, tab_cartes, cartes_posees, nb_joueurs);

        printf("\n\nFin de la partie ! Le gagnant est %s !\n", tab_joueurs[gagnant].pseudo);
    }

    printf("\nMerci d'avoir joué à DEKAL !\n");
    return 0;
}
