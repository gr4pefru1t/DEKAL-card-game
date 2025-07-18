#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <windows.h>       //nécessaire pour positionner_curseur
#include "tests.h"
#include"declarations.h"
#include "affichage.h"
#define HAUTEUR 9
#define LARGEUR 16

// Constantes pour le positionnement dans la console
#define DECALAGE_X_BASE 2
#define DECALAGE_Y_BASE 2
#define ESPACEMENT_CARTES_X 18
#define ESPACEMENT_CARTES_Y 10
#define DECALAGE_JOUEUR_Y 45
#define ESPACE_INPUT 20

void plein_ecran()
{
    keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
    keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT
}
//SSP pouvant changer la coueur du texte et du fond
void color (int couleurDuTexte, int couleurDuFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDuFond*16+couleurDuTexte);
// 0.Noir
// 1.Bleu fonc�
// 2.Vert fonc�
// 3.Turquoise
// 4.Rouge fonc�
// 5.Violet
// 6.Vert caca d'oie
// 7.Gris clair
// 8.Gris fonc�
// 9.Bleu fluo
// 10.Vert fluo
// 11.Turquoise
// 12.Rouge fluo
// 13.Violet 2
// 14.Jaune
// 15.Blanc
}

//ssp pouvant changer la position du curseur de l'utilisateur
void positionner_curseur(int ligne, int colonne)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//permet de déclarer la variable "hstdout" qui fait référénce à la console
    COORD pos; // COORD est un type structuré défini dans la bibliothèque windows.h
    pos.X=colonne;// numéro de la colonne
    pos.Y=ligne;// numéro de la ligne
    SetConsoleCursorPosition(hStdout, pos);
}
void afficher_carte(S_Carte carte, int position_x, int position_y)
{
    // Dimensions définies comme constantes


    // Motifs pour chaque chiffre
    // 1 = pixel blanc, 0 = fond coloré
    int motifs[10][HAUTEUR][LARGEUR] =
    {
        // Chiffre 1
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 2
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 3
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 4
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 5
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1},
            {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 6
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1},
            {1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 7
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 8
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 9
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
            {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        // Chiffre 10
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,1},
            {1,0,0,1,0,0,1,0,0,1,1,0,0,0,0,1},
            {1,0,0,1,0,0,1,0,0,1,1,0,0,0,0,1},
            {1,0,0,1,0,0,1,0,0,1,1,0,0,0,0,1},
            {1,0,1,1,0,0,1,1,1,1,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        }
    };

    // Motif pour la lettre D (dos de carte)
    int motif_D[HAUTEUR][LARGEUR] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
        {1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1},
        {1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1},
        {1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // Motif vide (carte jouée)
    int motif_vide[HAUTEUR][LARGEUR] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // Couleur du texte (blanc)
    int COULEUR_TEXTE = 15;

    // Couleurs de fond selon le chiffre
    int couleurs_fond[11] =
    {
        0,   // 0: Noir
        8,   // 1: Gris foncé
        11,  // 2: Bleu clair/turquoise
        1,   // 3: Bleu foncé
        5,   // 4: Violet
        13,  // 5: Rose (violet 2)
        3,   // 6: Turquoise/vert
        2,   // 7: Vert foncé
        14,  // 8: Jaune
        6,   // 9: Orange
        4    // 10: Rouge foncé
    };

    // Sélection du motif et de la couleur selon l'état de la carte
    int (*motif_a_utiliser)[LARGEUR] = NULL;
    int couleur_fond;

    if (carte.vide == 1)
    {
        // Carte jouée - afficher entièrement noire avec bordure
        motif_a_utiliser = motif_vide;
        couleur_fond = 0; // Noir
    }
    else if (carte.visibilite == 0)
    {
        // Carte non révélée - afficher un dos de carte (D)
        motif_a_utiliser = motif_D;
        couleur_fond = 4; // Rouge foncé
    }
    else
    {
        // Carte révélée - afficher le chiffre
        motif_a_utiliser = motifs[carte.valeur - 1 ];
        couleur_fond = couleurs_fond[carte.valeur];
    }

    // Afficher la carte
    for (int y = 0; y < HAUTEUR; y++)
    {
        for (int x = 0; x < LARGEUR; x++)
        {
            positionner_curseur(position_y + y, position_x + x);

            if (motif_a_utiliser[y][x] == 1)
            {
                // Pixel blanc (bordure ou détails)
                color(COULEUR_TEXTE, COULEUR_TEXTE);
            }
            else
            {
                // Fond coloré selon l'état de la carte
                color(COULEUR_TEXTE, couleur_fond);
            }

            printf(" "); // On imprime un espace avec la couleur définie
        }
    }

    // Réinitialiser la couleur
    color(COULEUR_TEXTE, 0);

    // Supprimer les définitions pour éviter les conflits

}



void afficher_grille_joueur(S_Joueur joueur)
{
    printf("Grille du joueur %s :\n", joueur.pseudo);

    // Parcours de la grille et affichage des cartes visibles ou cachées
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (joueur.cartes[i][j].vide == 1)
            {
                if (joueur.cartes[i][j].visibilite == 1)
                {
                    printf("%2d ", joueur.cartes[i][j].valeur); // Affiche la valeur de la carte si elle est visible
                }
                else
                {
                    printf(" X "); // Affiche "X" si la carte est cachée
                }
            }
            else
            {
                printf(" - "); // Affiche "-" si la case est vide
            }
        }
        printf("\n");
    }
}


void afficher_cartes_posees(S_Carte cartes_posees[], int nb_joueurs)
{
    printf("Cartes posées :\n");
    for (int i = 0; i < nb_joueurs; i++)
    {
        if (cartes_posees[i].vide == 1)
        {
            printf("[   ] ");
        }
        else if (cartes_posees[i].visibilite == 1)
        {
            printf("[ %2d ] ", cartes_posees[i].valeur);
        }
        else
        {
            printf("[ ?? ] ");
        }
    }
    printf("\n");
}

void effacer_ecran_et_cadre()
{
    system("cls");
    color(15, 0); // Texte blanc sur fond noir

    // Afficher un titre centré
    positionner_curseur(0,100);
    printf(" ______   _______  ___   _  _______  ___     \n");
    positionner_curseur(1,100);
    printf("|      | |       ||   | | ||   _   ||   |    \n");
    positionner_curseur(2,100);
    printf("|  _    ||    ___||   |_| ||  |_|  ||   |    \n");
    positionner_curseur(3,100);
    printf("| | |   ||   |___ |      _||       ||   |    \n");
    positionner_curseur(4,100);
    printf("| |_|   ||    ___||     |_ |       ||   |___ \n");
    positionner_curseur(5,100);
    printf("|       ||   |___ |    _  ||   _   ||       |\n");
    positionner_curseur(6,100);
    printf("|______| |_______||___| |_||__| |__||_______|\n");
}


void afficher_grille_joueur_graphique(S_Joueur joueur, int pos_x, int pos_y)
{
    // Afficher le pseudo du joueur
    positionner_curseur(pos_y - 2, pos_x);
    color(15, 0);
    printf("Joueur : %s", joueur.pseudo);

    if (joueur.pion_premier_joueur == 1)
    {
        printf(" (Premier joueur)");
    }

    // Afficher les indices des colonnes
    positionner_curseur(pos_y - 1, pos_x );
    for (int j = 0; j < 4; j++)
    {
        printf("%d                 ", j);//ne pas toucher aux espaces
    }

    // Afficher la grille de cartes
    for (int i = 0; i < 4; i++)
    {
        // Afficher l'indice de ligne
        positionner_curseur(pos_y + i * ESPACEMENT_CARTES_Y, pos_x - 2);
        printf("%d", i);

        for (int j = 0; j < 4; j++)
        {
            // Afficher chaque carte à sa position
            afficher_carte(joueur.cartes[i][j],
                           pos_x + j * ESPACEMENT_CARTES_X,
                           pos_y + i * ESPACEMENT_CARTES_Y);
        }
    }
}


void afficher_tous_joueurs(S_Joueur tab_joueurs[], int nb_joueurs)
{
    int joueurs_par_ligne = 3; // Maximum 3 joueurs par ligne

    for (int i = 0; i < nb_joueurs; i++)
    {
        int ligne = i / joueurs_par_ligne;
        int colonne = i % joueurs_par_ligne;

        afficher_grille_joueur_graphique(
            tab_joueurs[i],
            DECALAGE_X_BASE + colonne * (4 * ESPACEMENT_CARTES_X + 10),
            DECALAGE_Y_BASE + ESPACE_INPUT + ligne * DECALAGE_JOUEUR_Y
        );
    }
    //afficher_joueurs(tab_joueurs,nb_joueurs);//test

}


void afficher_cartes_posees_graphique(S_Carte cartes_posees[], int nb_joueurs, S_Joueur tab_joueurs[])
{
    int pos_y = DECALAGE_Y_BASE + ESPACE_INPUT + ((nb_joueurs + 2) / 3) * DECALAGE_JOUEUR_Y;

    // Titre
    positionner_curseur(pos_y - 2, DECALAGE_X_BASE);
    color(15, 0);
    printf("Cartes posées :");

    // Afficher chaque carte posée
    for (int i = 0; i < nb_joueurs; i++)
    {
        // Afficher le pseudo du joueur au-dessus de sa carte
        positionner_curseur(pos_y - 1, DECALAGE_X_BASE + i * ESPACEMENT_CARTES_X);
        printf("%s", tab_joueurs[i].pseudo);

        // Afficher la carte
        afficher_carte(cartes_posees[i],
                       DECALAGE_X_BASE + i * ESPACEMENT_CARTES_X,
                       pos_y);
    }
}


void afficher_scores(S_Joueur tab_joueurs[], int nb_joueurs)
{
    int pos_y = DECALAGE_Y_BASE + ((nb_joueurs + 2) / 3) * DECALAGE_JOUEUR_Y + 15;

    positionner_curseur(pos_y, DECALAGE_X_BASE);
    color(15, 0);
    printf("=== SCORES ===");

    for (int i = 0; i < nb_joueurs; i++)
    {
        positionner_curseur(pos_y + i + 1, DECALAGE_X_BASE);
        printf("%s: %d points", tab_joueurs[i].pseudo, tab_joueurs[i].score);
    }
}


void afficher_grille_texte(S_Joueur joueur, int pos_x, int pos_y)
{
    positionner_curseur(pos_y, pos_x);
    printf("Grille de %s :", joueur.pseudo);

    for (int i = 0; i < 4; i++)
    {
        positionner_curseur(pos_y + i + 1, pos_x);
        for (int j = 0; j < 4; j++)
        {
            if (joueur.cartes[i][j].vide == 0)
            {
                if (joueur.cartes[i][j].visibilite == 1)
                {
                    printf("%2d ", joueur.cartes[i][j].valeur);
                }
                else
                {
                    printf(" X ");
                }
            }
            else
            {
                printf(" - ");
            }
        }
    }
}


void demander_coordonnees(int *ligne, int *colonne, char *message, int pos_y)
{
    positionner_curseur(pos_y, DECALAGE_X_BASE);
    color(15, 0);
    printf("%-50s", message); // Afficher le message avec un espace fixe pour effacer les anciens messages

    positionner_curseur(pos_y + 1, DECALAGE_X_BASE);
    printf("Ligne (0-3): ");
    scanf("%d", ligne);

    positionner_curseur(pos_y + 2, DECALAGE_X_BASE);
    printf("Colonne (0-3): ");
    scanf("%d", colonne);

    // Effacer les lignes utilisées pour la saisie
    positionner_curseur(pos_y, DECALAGE_X_BASE);
    printf("%-50s", ""); // Effacer le message
    positionner_curseur(pos_y + 1, DECALAGE_X_BASE);
    printf("%-50s", ""); // Effacer la ligne
    positionner_curseur(pos_y + 2, DECALAGE_X_BASE);
    printf("%-50s", ""); // Effacer la colonne
}


void afficher_message(char *message, int pos_y)
{
    positionner_curseur(pos_y, DECALAGE_X_BASE);
    color(15, 0);
    printf("%-80s", message); // Afficher le message avec un espace fixe pour effacer les anciens messages
}
