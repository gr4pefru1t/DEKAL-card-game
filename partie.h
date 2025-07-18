#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

int premier_joueur(int nb_joueurs,S_Joueur tab_joueurs[]);

void jouer_tours(S_Carte cartes_posees[], S_Joueur tab_joueurs[], int nb_joueurs, int index_premier_joueur);

S_Carte poser_carte(S_Joueur *joueur,int zone_message_y);

void remettre_dans_grille(S_Joueur *joueur, S_Carte carte, int zone_message_y);

int jouer_partie_rapide(S_Joueur tab_joueurs[], S_Carte tab_cartes[], S_Carte cartes_posees[], int nb_joueurs);

int jouer_partie_longue(S_Joueur tab_joueurs[], S_Carte tab_cartes[], S_Carte cartes_posees[], int nb_joueurs);

int calculer_score(S_Joueur *joueur);

int demander_choix_carte(int nb_joueurs, char *pseudo, int pos_y);

#endif // PARTIE_H_INCLUDED
