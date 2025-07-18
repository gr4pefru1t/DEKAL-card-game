#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

void plein_ecran();
void color (int couleurDuTexte, int couleurDuFond);
void positionner_curseur(int ligne, int colonne);
void dessiner_carte (int ligne,int colonne,S_Carte carte);
void afficher_grille_joueur(S_Joueur joueur);
void afficher_cartes_posees(S_Carte cartes_posees[], int nb_joueurs);





// Fonctions d'affichage graphique
void effacer_ecran_et_cadre();
void afficher_grille_joueur_graphique(S_Joueur joueur, int pos_x, int pos_y);
void afficher_tous_joueurs(S_Joueur tab_joueurs[], int nb_joueurs);
void afficher_cartes_posees_graphique(S_Carte cartes_posees[], int nb_joueurs, S_Joueur tab_joueurs[]);
void afficher_scores(S_Joueur tab_joueurs[], int nb_joueurs);
void afficher_grille_texte(S_Joueur joueur, int pos_x, int pos_y);
void demander_coordonnees(int *ligne, int *colonne, char *message, int pos_y);
void afficher_message(char *message, int pos_y);


#endif // AFFICHAGE_H_INCLUDED
