#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "declarations.h"
#include "affichage.h"
#include "initialisation.h"
#include "partie.h"

// Zone de message commune pour tous les affichages
#define ZONE_MESSAGE_Y 10

#define DECALAGE_X_BASE 2
#define DECALAGE_Y_BASE 2

// Cherche le premier joueur, si il n'a pas �t� d�sign�, renvoie -1.
int premier_joueur(int nb_joueurs, S_Joueur tab_joueurs[])
{
    int index_premier_joueur = -1; // Initialisation � -1 au cas o� aucun joueur n'est trouv�
    int existe = 0; // Variable qui indique si le pion premier joueur a �t� distribu�

    printf("\nRecherche du premier joueur parmi %d joueurs :\n", nb_joueurs);

    for(int i = 0; i < nb_joueurs; i++) // Recherche du pion premier joueur
    {
        printf("Verification du joueur %d (%s): ", i+1, tab_joueurs[i].pseudo);

        if (tab_joueurs[i].pion_premier_joueur == 1)
        {
            index_premier_joueur = i;
            existe = 1;
            printf("possede le pion premier joueur!\n");
            break; // On sort de la boucle d�s qu'on trouve le premier joueur
        }
        else
        {
            printf("n'a pas le pion premier joueur.\n");
        }
    }

    if (existe == 0)
    {
        printf("\nLe premier joueur n'a pas ete designe.\n");
        // index_premier_joueur est d�j� � -1
    }
    else
    {
        printf("\nLe joueur %d (%s) est le premier joueur.\n",index_premier_joueur+1, tab_joueurs[index_premier_joueur].pseudo);
    }

    return index_premier_joueur;
}



int calculer_score(S_Joueur *joueur)
{
    int score = 0;

    // Parcourir la grille 4x4 du joueur
    for (int ligne = 0; ligne < 4; ligne++)
    {
        for (int colonne = 0; colonne < 4; colonne++)
        {
            // Si la carte est pr�sente (non vide) et visible, ajouter sa valeur au score
            if (joueur->cartes[ligne][colonne].vide == 0 &&
                    joueur->cartes[ligne][colonne].visibilite == 1)
            {
                score += joueur->cartes[ligne][colonne].valeur;
            }
        }
    }

    return score;
}


S_Carte poser_carte(S_Joueur *joueur, int zone_message_y)
{
    S_Carte carte_posee;
    int ligne, colonne;
    int choix_valide = 0;
    char message[100];

    sprintf(message, "%s, choisissez une carte � poser", joueur->pseudo);

    do
    {
        demander_coordonnees(&ligne, &colonne, message, zone_message_y);

        // V�rifier si les coordonn�es sont valides
        if (ligne >= 0 && ligne < 4 && colonne >= 0 && colonne < 4)
        {
            // V�rifier si la carte n'a pas d�j� �t� jou�e
            if (joueur->cartes[ligne][colonne].vide == 0)
            {
                // Si la carte n'est pas visible, la r�v�ler d'abord
                if (joueur->cartes[ligne][colonne].visibilite == 0)
                {
                    joueur->cartes[ligne][colonne].visibilite = 1;

                    sprintf(message, "Carte en [%d][%d] r�v�l�e : valeur %d",
                            ligne, colonne, joueur->cartes[ligne][colonne].valeur);
                    afficher_message(message, zone_message_y + 3);

                }

                // Copier la carte dans la carte pos�e
                carte_posee = joueur->cartes[ligne][colonne];

                // Marquer la position comme vide dans la grille du joueur
                joueur->cartes[ligne][colonne].vide = 1;

                choix_valide = 1;
            }
            else
            {
                afficher_message("Cette carte a d�j� �t� jou�e. Choisissez-en une autre.", zone_message_y + 3);
            }
        }
        else
        {
            afficher_message("Coordonn�es invalides. Veuillez entrer des valeurs entre 0 et 3.", zone_message_y + 3);
        }
    }
    while (!choix_valide);

    // Effacer les messages
    afficher_message("", zone_message_y + 3);

    return carte_posee;
}


void remettre_dans_grille(S_Joueur *joueur, S_Carte carte, int zone_message_y)
{
    int choix_mode, ligne, colonne, direction;
    int choix_valide = 0;
    int case_vide_trouvee = 0;
    int ligne_vide = -1, colonne_vide = -1;
    char message[100];
    S_Carte carte_temporaire; // Pour stocker une carte temporairement lors du d�calage

    // Localiser d'abord la position de la case vide
    for (int i = 0; i < 4 && !case_vide_trouvee; i++)
    {
        for (int j = 0; j < 4 && !case_vide_trouvee; j++)
        {
            if (joueur->cartes[i][j].vide == 1)
            {
                ligne_vide = i;
                colonne_vide = j;
                case_vide_trouvee = 1;
            }
        }
    }

    // V�rifier si une case vide a �t� trouv�e
    if (!case_vide_trouvee)
    {
        sprintf(message, "Erreur: Aucune case vide trouv�e dans la grille de %s.", joueur->pseudo);
        afficher_message(message, zone_message_y);
        return;
    }

    sprintf(message, "%s, choisissez o� placer la carte de valeur %d",
            joueur->pseudo, carte.valeur);
    afficher_message(message, zone_message_y);

    do
    {
        // Demander le mode d'insertion
        positionner_curseur(zone_message_y + 1, DECALAGE_X_BASE);
        printf("Choisissez le mode d'insertion : 1) Pousser une ligne ou 2) Pousser une colonne ? ");
        scanf("%d", &choix_mode);

        if (choix_mode == 1)    // Pousser une ligne
        {
            // Demander quelle ligne pousser
            positionner_curseur(zone_message_y + 2, DECALAGE_X_BASE);
            printf("Quelle ligne pousser (0-3) ? ");
            scanf("%d", &ligne);

            // V�rifier si la ligne est valide et contient la case vide
            if (ligne >= 0 && ligne < 4 && ligne == ligne_vide)
            {
                // Demander la direction
                positionner_curseur(zone_message_y + 3, DECALAGE_X_BASE);
                printf("Depuis quelle direction ? 1) Gauche ou 2) Droite ? ");
                scanf("%d", &direction);

                if (direction == 1)    // Pousser depuis la gauche
                {
                    // Cas sp�cial : si la case vide est � l'extr�me gauche, simplement remplacer la case vide
                    if (colonne_vide == 0)
                    {
                        joueur->cartes[ligne][colonne_vide] = carte;
                        joueur->cartes[ligne][colonne_vide].visibilite = 1;
                        joueur->cartes[ligne][colonne_vide].vide = 0;
                    }
                    else
                    {
                        // Marquer la case qui �tait vide comme non-vide et mettre les donn�es de la carte adjacente
                        joueur->cartes[ligne][colonne_vide] = joueur->cartes[ligne][colonne_vide-1];
                        joueur->cartes[ligne][colonne_vide].vide = 0;

                        // D�caler les cartes de la ligne vers la droite
                        for (int c = colonne_vide - 1; c > 0; c--)
                        {
                            joueur->cartes[ligne][c] = joueur->cartes[ligne][c-1];
                        }

                        // Ins�rer la nouvelle carte � gauche
                        joueur->cartes[ligne][0] = carte;
                        joueur->cartes[ligne][0].visibilite = 1;
                        joueur->cartes[ligne][0].vide = 0;
                    }

                    choix_valide = 1;
                }
                else if (direction == 2)    // Pousser depuis la droite
                {
                    // Cas sp�cial : si la case vide est � l'extr�me droite, simplement remplacer la case vide
                    if (colonne_vide == 3)
                    {
                        joueur->cartes[ligne][colonne_vide] = carte;
                        joueur->cartes[ligne][colonne_vide].visibilite = 1;
                        joueur->cartes[ligne][colonne_vide].vide = 0;
                    }
                    else
                    {
                        // Marquer la case qui �tait vide comme non-vide et mettre les donn�es de la carte adjacente
                        joueur->cartes[ligne][colonne_vide] = joueur->cartes[ligne][colonne_vide+1];
                        joueur->cartes[ligne][colonne_vide].vide = 0;

                        // D�caler les cartes de la ligne vers la gauche
                        for (int c = colonne_vide + 1; c < 3; c++)
                        {
                            joueur->cartes[ligne][c] = joueur->cartes[ligne][c+1];
                        }

                        // Ins�rer la nouvelle carte � droite
                        joueur->cartes[ligne][3] = carte;
                        joueur->cartes[ligne][3].visibilite = 1;
                        joueur->cartes[ligne][3].vide = 0;
                    }

                    choix_valide = 1;
                }
                else
                {
                    afficher_message("Direction invalide. Veuillez choisir 1 ou 2.", zone_message_y + 4);

                }
            }
            else if (ligne != ligne_vide)
            {
                afficher_message("Cette ligne ne contient pas la case vide. Veuillez choisir la ligne contenant la case vide.", zone_message_y + 4);

            }
            else
            {
                afficher_message("Ligne invalide. Veuillez entrer une valeur entre 0 et 3.", zone_message_y + 4);

            }
        }
        else if (choix_mode == 2)    // Pousser une colonne
        {
            // Demander quelle colonne pousser
            positionner_curseur(zone_message_y + 2, DECALAGE_X_BASE);
            printf("Quelle colonne pousser (0-3) ? ");
            scanf("%d", &colonne);

            // V�rifier si la colonne est valide et contient la case vide
            if (colonne >= 0 && colonne < 4 && colonne == colonne_vide)
            {
                // Demander la direction
                positionner_curseur(zone_message_y + 3, DECALAGE_X_BASE);
                printf("Depuis quelle direction ? 1) Haut ou 2) Bas ? ");
                scanf("%d", &direction);

                if (direction == 1)    // Pousser depuis le haut
                {
                    // Cas sp�cial : si la case vide est tout en haut, simplement remplacer la case vide
                    if (ligne_vide == 0)
                    {
                        joueur->cartes[ligne_vide][colonne] = carte;
                        joueur->cartes[ligne_vide][colonne].visibilite = 1;
                        joueur->cartes[ligne_vide][colonne].vide = 0;
                    }
                    else
                    {
                        // Marquer la case qui �tait vide comme non-vide et mettre les donn�es de la carte adjacente
                        joueur->cartes[ligne_vide][colonne] = joueur->cartes[ligne_vide-1][colonne];
                        joueur->cartes[ligne_vide][colonne].vide = 0;

                        // D�caler les cartes de la colonne vers le bas
                        for (int r = ligne_vide - 1; r > 0; r--)
                        {
                            joueur->cartes[r][colonne] = joueur->cartes[r-1][colonne];
                        }

                        // Ins�rer la nouvelle carte en haut
                        joueur->cartes[0][colonne] = carte;
                        joueur->cartes[0][colonne].visibilite = 1;
                        joueur->cartes[0][colonne].vide = 0;
                    }

                    choix_valide = 1;
                }
                else if (direction == 2)    // Pousser depuis le bas
                {
                    // Cas sp�cial : si la case vide est tout en bas, simplement remplacer la case vide
                    if (ligne_vide == 3)
                    {
                        joueur->cartes[ligne_vide][colonne] = carte;
                        joueur->cartes[ligne_vide][colonne].visibilite = 1;
                        joueur->cartes[ligne_vide][colonne].vide = 0;
                    }
                    else
                    {
                        // Marquer la case qui �tait vide comme non-vide et mettre les donn�es de la carte adjacente
                        joueur->cartes[ligne_vide][colonne] = joueur->cartes[ligne_vide+1][colonne];
                        joueur->cartes[ligne_vide][colonne].vide = 0;

                        // D�caler les cartes de la colonne vers le haut
                        for (int r = ligne_vide + 1; r < 3; r++)
                        {
                            joueur->cartes[r][colonne] = joueur->cartes[r+1][colonne];
                        }

                        // Ins�rer la nouvelle carte en bas
                        joueur->cartes[3][colonne] = carte;
                        joueur->cartes[3][colonne].visibilite = 1;
                        joueur->cartes[3][colonne].vide = 0;
                    }

                    choix_valide = 1;
                }
                else
                {
                    afficher_message("Direction invalide. Veuillez choisir 1 ou 2.", zone_message_y + 4);

                }
            }
            else if (colonne != colonne_vide)
            {
                afficher_message("Cette colonne ne contient pas la case vide. Veuillez choisir la colonne contenant la case vide.", zone_message_y + 4);

            }
            else
            {
                afficher_message("Colonne invalide. Veuillez entrer une valeur entre 0 et 3.", zone_message_y + 4);

            }
        }
        else
        {
            afficher_message("Mode invalide. Veuillez choisir 1 ou 2.", zone_message_y + 4);

        }

        // Effacer les messages
        for (int i = 1; i <= 4; i++)
        {
            positionner_curseur(zone_message_y + i, DECALAGE_X_BASE);
            printf("%-80s", ""); // Effacer la ligne
        }

    }
    while (!choix_valide);    // Voici le while qui ferme la boucle do

    // Effacer les messages
    afficher_message("", zone_message_y);

    // V�rification finale pour s'assurer qu'aucune carte n'est marqu�e comme vide
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Toutes les cartes doivent maintenant �tre non-vides
            joueur->cartes[i][j].vide = 0;
        }
    }
}

void jouer_tours(S_Carte cartes_posees[], S_Joueur tab_joueurs[], int nb_joueurs, int index_premier_joueur)
{
    char message[100];
    int zone_message_y = ZONE_MESSAGE_Y;

    for (int tour = 0; tour < 16; tour++)
    {
        // Mettre � jour l'affichage complet
        effacer_ecran_et_cadre();
        afficher_tous_joueurs(tab_joueurs, nb_joueurs);

        sprintf(message, "--- Tour %d ---", tour + 1);
        afficher_message(message, zone_message_y);

        // Si personne n'a encore le pion premier joueur
        if (index_premier_joueur == -1)
        {
            for (int i = 0; i < nb_joueurs; i++)
            {
                // Mettre � jour l'affichage � chaque tour de joueur
                effacer_ecran_et_cadre();
                afficher_tous_joueurs(tab_joueurs, nb_joueurs);

                sprintf(message, "Tour %d - %s doit poser une carte", tour + 1, tab_joueurs[i].pseudo);
                afficher_message(message, zone_message_y);

                cartes_posees[i] = poser_carte(&tab_joueurs[i], zone_message_y + 2);

                // Mettre � jour l'affichage apr�s la pose
                effacer_ecran_et_cadre();
                afficher_tous_joueurs(tab_joueurs, nb_joueurs);
                afficher_cartes_posees_graphique(cartes_posees, i + 1, tab_joueurs);

                sprintf(message, "%s a pos� une carte de valeur %d",
                        tab_joueurs[i].pseudo, cartes_posees[i].valeur);
                afficher_message(message, zone_message_y);
            }

            // Trouver la plus petite carte pos�e
            int min_valeur = cartes_posees[0].valeur;
            index_premier_joueur = 0;
            int egalite = 0;

            for (int i = 1; i < nb_joueurs; i++)
            {
                if (cartes_posees[i].valeur < min_valeur)
                {
                    min_valeur = cartes_posees[i].valeur;
                    index_premier_joueur = i;
                    egalite = 0;
                }
                else if (cartes_posees[i].valeur == min_valeur)
                {
                    egalite = 1;
                }
            }

            if (egalite != 0)
            {
                index_premier_joueur = rand() % nb_joueurs;
                sprintf(message, "�galit� pour la plus faible carte, %s est d�sign� premier joueur au hasard.",
                        tab_joueurs[index_premier_joueur].pseudo);
            }
            else
            {
                sprintf(message, "%s a la carte la plus faible et devient premier joueur.",
                        tab_joueurs[index_premier_joueur].pseudo);
            }

            // Attribuer le pion premier joueur
            for (int i = 0; i < nb_joueurs; i++)
            {
                tab_joueurs[i].pion_premier_joueur = (i == index_premier_joueur) ? 1 : 0;
            }

            afficher_message(message, zone_message_y + 1);
        }
        else
        {
            // Tour normal
            for (int i = 0; i < nb_joueurs; i++)
            {
                int idx = (index_premier_joueur + i) % nb_joueurs;

                // Mettre � jour l'affichage � chaque tour de joueur
                effacer_ecran_et_cadre();
                afficher_tous_joueurs(tab_joueurs, nb_joueurs);
                afficher_cartes_posees_graphique(cartes_posees, i, tab_joueurs);

                sprintf(message, "Tour %d - %s doit poser une carte", tour + 1, tab_joueurs[idx].pseudo);
                afficher_message(message, zone_message_y);

                cartes_posees[idx] = poser_carte(&tab_joueurs[idx], zone_message_y + 2);

                // Mettre � jour l'affichage apr�s la pose
                effacer_ecran_et_cadre();
                afficher_tous_joueurs(tab_joueurs, nb_joueurs);
                afficher_cartes_posees_graphique(cartes_posees, nb_joueurs, tab_joueurs);

                sprintf(message, "%s a pos� une carte de valeur %d",
                        tab_joueurs[idx].pseudo, cartes_posees[idx].valeur);
                afficher_message(message, zone_message_y);
            }
        }

        // Chaque joueur choisit une carte � reprendre
        for (int i = 0; i < nb_joueurs; i++)
        {
            int idx = (index_premier_joueur + i) % nb_joueurs;

            // Mettre � jour l'affichage pour le choix de carte
            effacer_ecran_et_cadre();
            afficher_tous_joueurs(tab_joueurs, nb_joueurs);
            afficher_cartes_posees_graphique(cartes_posees, nb_joueurs, tab_joueurs);

            sprintf(message, "%s doit choisir une carte � reprendre", tab_joueurs[idx].pseudo);
            afficher_message(message, zone_message_y);

            int choix = demander_choix_carte(nb_joueurs, tab_joueurs[idx].pseudo, zone_message_y + 2); // Version modifi�e avec v�rification

            sprintf(message, "%s r�cup�re une carte de valeur %d",
                    tab_joueurs[idx].pseudo, cartes_posees[choix].valeur);
            afficher_message(message, zone_message_y + 3);

            // Marquer la carte pos�e comme vide apr�s l'avoir choisie
            cartes_posees[choix].vide = 1;

            remettre_dans_grille(&tab_joueurs[idx], cartes_posees[choix], zone_message_y + 4);

            // Mettre � jour l'affichage apr�s le choix
            effacer_ecran_et_cadre();
            afficher_tous_joueurs(tab_joueurs, nb_joueurs);
            afficher_cartes_posees_graphique(cartes_posees, nb_joueurs, tab_joueurs);
        }

        // Faire tourner le pion premier joueur dans le sens horaire apr�s chaque tour
        if (tour < 15)   // Ne pas changer pour le dernier tour
        {
            // Enlever le pion du joueur actuel
            tab_joueurs[index_premier_joueur].pion_premier_joueur = 0;

            // Passer au joueur suivant (sens horaire)
            index_premier_joueur = (index_premier_joueur + 1) % nb_joueurs;

            // Donner le pion au joueur suivant
            tab_joueurs[index_premier_joueur].pion_premier_joueur = 1;

            // Afficher le message indiquant le nouveau premier joueur
            sprintf(message, "%s sera le premier joueur pour le prochain tour.",
                    tab_joueurs[index_premier_joueur].pseudo);
            afficher_message(message, zone_message_y);

        }
    }
}

int demander_choix_carte(int nb_joueurs, char *pseudo, int pos_y)
{
    int choix;
    positionner_curseur(pos_y, DECALAGE_X_BASE);
    color(15, 0);
    printf("%s, choisissez une carte � reprendre (0 � %d): ", pseudo, nb_joueurs - 1);
    scanf("%d", &choix);

    // Effacer la ligne utilis�e pour la saisie
    positionner_curseur(pos_y, DECALAGE_X_BASE);
    printf("%-80s", ""); // Effacer la question

    return choix;
}

int jouer_partie_rapide(S_Joueur tab_joueurs[], S_Carte tab_cartes[], S_Carte cartes_posees[], int nb_joueurs)
{
    effacer_ecran_et_cadre();

    // Initialiser les scores � z�ro
    for (int i = 0; i < nb_joueurs; i++)
    {
        tab_joueurs[i].score = 0;
    }

    int index_premier_joueur = premier_joueur(nb_joueurs, tab_joueurs);
    jouer_tours(cartes_posees, tab_joueurs, nb_joueurs, index_premier_joueur);

    // Calcul et affichage des scores
    effacer_ecran_et_cadre();
    afficher_tous_joueurs(tab_joueurs, nb_joueurs);

    // Calculer les scores
    int min_score = 999;
    int index_gagnant = 0;

    for (int i = 0; i < nb_joueurs; i++)
    {
        int score_joueur = calculer_score(&tab_joueurs[i]);
        tab_joueurs[i].score = score_joueur;

        if (score_joueur < min_score)
        {
            min_score = score_joueur;
            index_gagnant = i;
        }
    }

    // Afficher les scores
    afficher_scores(tab_joueurs, nb_joueurs);

    // Annoncer le gagnant
    char message[100];
    sprintf(message, "\nLE GAGNANT EST %s AVEC %d POINTS!",
            tab_joueurs[index_gagnant].pseudo, min_score);
    afficher_message(message, ZONE_MESSAGE_Y);

    return index_gagnant;
}


int jouer_partie_longue(S_Joueur tab_joueurs[], S_Carte tab_cartes[], S_Carte cartes_posees[], int nb_joueurs)
{
    int partie_terminee = 0;
    int round = 1;
    char message[100];

    // Initialiser les scores � z�ro
    for (int i = 0; i < nb_joueurs; i++)
    {
        tab_joueurs[i].score = 0;
    }

    while (!partie_terminee)
    {
        effacer_ecran_et_cadre();

        sprintf(message, "=== ROUND %d ===", round);
        afficher_message(message, ZONE_MESSAGE_Y);


        // R�initialiser les cartes pour chaque round
        melanger_cartes(tab_cartes);
        distribuer_cartes(tab_joueurs, nb_joueurs, tab_cartes);

        // R�initialiser le pion premier joueur pour le nouveau round
        for (int i = 0; i < nb_joueurs; i++)
        {
            tab_joueurs[i].pion_premier_joueur = 0;
        }

        // Jouer un round
        int index_premier_joueur = -1; // Forcer la recherche d'un nouveau premier joueur
        jouer_tours(cartes_posees, tab_joueurs, nb_joueurs, index_premier_joueur);

        // Mettre � jour les scores
        effacer_ecran_et_cadre();
        afficher_tous_joueurs(tab_joueurs, nb_joueurs);

        sprintf(message, "=== SCORES DU ROUND %d ===", round);
        afficher_message(message, ZONE_MESSAGE_Y);

        for (int i = 0; i < nb_joueurs; i++)
        {
            int score_round = calculer_score(&tab_joueurs[i]);
            tab_joueurs[i].score += score_round;

            sprintf(message, "%s: %d points (Total: %d)",
                    tab_joueurs[i].pseudo, score_round, tab_joueurs[i].score);
            afficher_message(message, ZONE_MESSAGE_Y + i + 1);

            if (tab_joueurs[i].score >= 100)
            {
                partie_terminee = 1;
            }
        }

        round++;

        if (!partie_terminee)
        {
            positionner_curseur(ZONE_MESSAGE_Y + nb_joueurs + 2, 2);
            printf("Appuyez sur Entr�e pour passer au round suivant...");
            getchar();
        }
    }

    // D�terminer le gagnant (score le plus bas)
    int min_score = tab_joueurs[0].score;
    int index_gagnant = 0;

    for (int i = 1; i < nb_joueurs; i++)
    {
        if (tab_joueurs[i].score < min_score)
        {
            min_score = tab_joueurs[i].score;
            index_gagnant = i;
        }
    }

    // Annoncer le gagnant
    effacer_ecran_et_cadre();
    afficher_tous_joueurs(tab_joueurs, nb_joueurs);
    afficher_scores(tab_joueurs, nb_joueurs);

    sprintf(message, "\nFIN DE LA PARTIE! LE GAGNANT EST %s AVEC %d POINTS!",
            tab_joueurs[index_gagnant].pseudo, min_score);
    afficher_message(message, ZONE_MESSAGE_Y);

    // Afficher le message pour indiquer quel joueur a d�clench� la fin de partie
    for (int i = 0; i < nb_joueurs; i++) {
        if (tab_joueurs[i].score >= 100) {
            sprintf(message, "%s a atteint 100 points et a d�clench� la fin de la partie.",
                    tab_joueurs[i].pseudo);
            afficher_message(message, ZONE_MESSAGE_Y + 1);
            break;
        }
    }

    // Attendre que l'utilisateur appuie sur une touche
    positionner_curseur(ZONE_MESSAGE_Y + 3, 2);
    printf("Appuyez sur Entr�e pour continuer...");
    getchar();
    getchar(); // Deuxi�me getchar pour s'assurer de capturer l'appui sur Entr�e

    return index_gagnant; // Retourner l'index du gagnant au lieu de partie_terminee
}
