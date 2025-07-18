#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "affichage.h"

// Le module tests contient toutes les fonctions et sous-programmes servant au debug avec des affichages basiques pour verifier le fonctionnement du code de manière fiable.



// Sous-programme pour afficher les joueurs et leurs cartes
void afficher_joueurs(S_Joueur tab_joueurs[], int nb_joueurs)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n===== AFFICHAGE DES JOUEURS =====\n");

    for (int i = 0; i < nb_joueurs; i++)
    {
        printf("\nJoueur %d - Pseudo: %s", i+1, tab_joueurs[i].pseudo);
        printf(" - Pion premier joueur: %s\n",
               tab_joueurs[i].pion_premier_joueur ? "OUI" : "NON");

        // Affichage de l'en-tête des colonnes
        printf("   ");
        for (int col = 0; col < 4; col++)
        {
            printf(" Col%d  ", col);
        }
        printf("\n");

        // Affichage de la grille de cartes 4x4
        for (int ligne = 0; ligne < 4; ligne++)
        {
            printf("L%d ", ligne);

            for (int colonne = 0; colonne < 4; colonne++)
            {
                S_Carte carte = tab_joueurs[i].cartes[ligne][colonne];

                if (carte.vide == 1)
                {
                    printf("[VIDE] ");
                }
                else
                {
                    if (carte.visibilite == 1)
                    {
                        printf("[%2d V] ", carte.valeur);
                    }
                    else
                    {
                        printf("[%2d C] ", carte.valeur);
                    }
                }
            }
            printf("\n");
        }
        printf("--------------------------------\n");
    }
}



