#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "declarations.h"

void choix_partie(int* type_partie)
{
    do
    {
        printf("\n====CHOISIR UN TYPE DE PARTIE====\n");
        printf("\n1. Partie rapide :  Jouez un seul round\n");
        printf("\n2. Partie longue : Enchainez les rounds tant que personne n'a atteint 100 points, le premier joueur atteignant 100 points perd la partie et celui avec le moins de points gagne la partie.\n");
        scanf("%d",type_partie);
        //printf("\ntype partie = %d\n",*type_partie);

        // Vider le buffer d'entrée : garantit d'éviter un scanf infini
        int c;
        while ((c = getchar()) != '\n' && c != EOF);


    }while((*type_partie != 1)&&(*type_partie != 2));



}

void distribuer_cartes(S_Joueur tab_joueurs[], int nb_joueurs, S_Carte tab_cartes[])
{
    int index_carte = 0; // Index de la carte actuelle dans tab_cartes

    // Distribution des cartes à tous les joueurs
    for (int joueur = 0; joueur < nb_joueurs; joueur++)
    {
        // Pour chaque joueur, parcourir la grille ligne par ligne
        for (int ligne = 0; ligne < 4; ligne++)
        {
            for (int colonne = 0; colonne < 4; colonne++)
            {
                // Copier la carte du paquet dans la grille du joueur
                tab_joueurs[joueur].cartes[ligne][colonne].valeur = tab_cartes[index_carte].valeur;
                tab_joueurs[joueur].cartes[ligne][colonne].visibilite = tab_cartes[index_carte].visibilite;
                tab_joueurs[joueur].cartes[ligne][colonne].vide = 0; // La case n'est plus vide

                // Passer à la carte suivante
                index_carte++;
            }
        }
    }

    printf("Distribution terminee. %d cartes distribuees.\n", index_carte);
}

void melanger_cartes(S_Carte tab_cartes[])
{
    int taille = 100;

    srand(time(NULL));

    for (int i = taille - 1; i > 0; i--)// taille - 1 car on veut la derniere case du tableau et il est indexé à 0
    {
        // Générer un index aléatoire entre 0 et i
        int j = rand() % (i + 1);

        // Échanger les cartes aux positions i et j
        S_Carte temp = tab_cartes[i];
        tab_cartes[i] = tab_cartes[j];
        tab_cartes[j] = temp;
    }
    printf("Les cartes ont ete melangees ! \n");
}

int demarrage_jeu(S_Joueur tab_joueurs[], S_Carte tab_cartes[])
{
    // Initialisation des 100 cartes du paquet (10 cartes de chaque valeur, de 1 à 10)

    int index = 0,c; // c set a vider le buffer d'entrée
    for (int valeur = 1; valeur <= 10; valeur++)
    {
        for (int i = 0; i < 10; i++)
        {
            tab_cartes[index].valeur = valeur;
            tab_cartes[index].visibilite = 0;  // Non révélée initialement
            tab_cartes[index].vide = 0;        // Non posée initialement
            index++;
        }
    }

    melanger_cartes(tab_cartes);

    // Demander le nombre de joueurs (entre 2 et 6)
    int nb_joueurs, lecture_valide;
    do
    {
        printf("Entrez le nombre de joueurs (2-6) : ");
        lecture_valide = scanf("%d", &nb_joueurs);//scanf retourne 1 s'il réussit

        // Vider le buffer d'entrée : garantit d'éviter un scanf infini
        while ((c = getchar()) != '\n' && c != EOF);

        if (lecture_valide != 1 || nb_joueurs < 2 || nb_joueurs > 6)
        {
            printf("Nombre de joueurs invalide. Veuillez entrer un nombre entre 2 et 6.\n");
        }
    }
    while (nb_joueurs < 2 || nb_joueurs > 6);

    // Saisie des pseudos pour chaque joueur
    for (int i = 0; i < nb_joueurs; i++)
    {
        printf("Entrez le pseudo du joueur %d : ", i+1);
        scanf(" %s", tab_joueurs[i].pseudo);
        tab_joueurs[i].pion_premier_joueur = 0 ; //initialisation des pions premier joueurs à 0

        // Vider le buffer d'entrée : garantit d'éviter un scanf infini

        while ((c = getchar()) != '\n' && c != EOF);
    }

    distribuer_cartes(tab_joueurs,nb_joueurs,tab_cartes);
    return nb_joueurs;

}


