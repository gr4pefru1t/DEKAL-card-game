#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED


typedef struct
{
    int valeur;  //1 à 10
    int visibilite; //révélée ou non
    int vide; // = 1 si la carte a été posée

}S_Carte;


typedef struct
{
    char pseudo[20];
    int pion_premier_joueur; //=1 si le joueur possède le pion premier joueur
    S_Carte cartes[4][4]; // les cartes sont donc repérées par coordonnées :  [ligne][colonne]
    int score;

}S_Joueur;


#endif // DECLARATIONS_H_INCLUDED
