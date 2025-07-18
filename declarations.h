#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED


typedef struct
{
    int valeur;  //1 � 10
    int visibilite; //r�v�l�e ou non
    int vide; // = 1 si la carte a �t� pos�e

}S_Carte;


typedef struct
{
    char pseudo[20];
    int pion_premier_joueur; //=1 si le joueur poss�de le pion premier joueur
    S_Carte cartes[4][4]; // les cartes sont donc rep�r�es par coordonn�es :  [ligne][colonne]
    int score;

}S_Joueur;


#endif // DECLARATIONS_H_INCLUDED
