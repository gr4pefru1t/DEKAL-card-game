#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

void melanger_cartes(S_Carte tab_cartes[]);
void distribuer_cartes(S_Joueur tab_joueurs[], int nb_joueurs, S_Carte tab_cartes[]);
int demarrage_jeu(S_Joueur tab_joueurs[], S_Carte tab_cartes[]);
void choix_partie(int* type_partie);

#endif // INITIALISATION_H_INCLUDED
