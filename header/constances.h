#ifndef CONSTANCES_H_INCLUDED
#define CONSTANCES_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_BLOC 98
#define TAILLE_JOUEUR 84

#define HAUTEUR_MAP 11
#define LARGEUR_MAP 11

#define JEU 1078

#define SCALE TAILLE_BLOC/1078*JEU

#define FENETRE_X 1920
#define FENETRE_Y 1080

enum{VIDE, MUR, CRISTAUXB, CRISTAUXR};
enum{UP, RIGHT , DOWN, LEFT, KEY_MAX, F1, F2, ESCAPE};

ALLEGRO_BITMAP *mur, *vide, *bleu, *rouge, *buffer, *image, *GUI, *on;
int i, j, l;

ALLEGRO_EVENT events;
ALLEGRO_DISPLAY *display;

#endif // CONSTANCES_H_INCLUDED
