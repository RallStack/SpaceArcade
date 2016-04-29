#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED

#include "constances.h"

typedef struct
{
    int x;
    int y;
    int rouge, bleu, nbBleu;
    int directory;
    ALLEGRO_BITMAP *vaisseau[8];

}S_ENTITE;

void init(S_ENTITE *p_joueur, int pos[], char type[]);
void resolution(S_ENTITE *p_vaisseau);
void afficher(S_ENTITE *p_vaisseau);

int collision(S_ENTITE *p_vaisseau,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu);

int right(S_ENTITE *p_vaisseau,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu);
int left(S_ENTITE *p_vaisseau,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu);
int up(S_ENTITE *p_vaisseau,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu);
int down(S_ENTITE *p_vaisseau,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu);

void pathFinding(S_ENTITE *p_ennemis, S_ENTITE *p_joueur, int carte[][HAUTEUR_MAP]);

#endif // PERSO_H_INCLUDED
