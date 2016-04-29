#include "perso.h"

/// Initialisation S_ENTITE (1)

void init(S_ENTITE *p_joueur, int pos[], char type[])
{
	al_set_target_bitmap(buffer);
	p_joueur->x=(float)pos[0]*SCALE+225;
    p_joueur->y=(float)pos[1]*SCALE+1;
	p_joueur->bleu = 0;
	p_joueur->directory = RIGHT;

 	char nom[256];
	for( i=0; i<4; i++){
    	sprintf(nom,"image/%s/%s%d.png",type, type, i);
    	p_joueur->vaisseau[i]=al_load_bitmap(nom);
	}
}

void afficher(S_ENTITE *p_joueur)
{
	al_draw_bitmap(p_joueur->vaisseau[p_joueur->directory], p_joueur->x, p_joueur->y, 0);
}

/// *********************** (1)

/// Deplacement personnage (2)

int right(S_ENTITE *p_joueur,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu)
{
    p_joueur->x += 7;

    if(collision(p_joueur, buffer, carte, nbBleu) == 1 || p_joueur->x+TAILLE_BLOC > JEU + 225){
    	p_joueur->x -= 7;
        return 0;
    }
    else if(collision(p_joueur, buffer, carte, nbBleu) == 2 || collision(p_joueur, buffer, carte, nbBleu) == 0){
        return 0;
    }
    else if(collision(p_joueur, buffer, carte, nbBleu) == 3){
    	return 1;
    }
    return 0;
}

int left(S_ENTITE *p_joueur,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu)
{
    p_joueur->x -= 7;

    if(collision(p_joueur, buffer, carte, nbBleu) == 1 || p_joueur->x < 0 + 225){
        p_joueur->x += 7;
        return 0;
    }
    else if(collision(p_joueur, buffer, carte, nbBleu) == 2 || collision(p_joueur, buffer, carte, nbBleu) == 0){
        return 0;
    }
    else if(collision(p_joueur, buffer, carte, nbBleu) == 3){
    	return 1;
    }
    return 0;
}

int up(S_ENTITE *p_joueur,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu)
{
    p_joueur->y -= 7;

    if(collision(p_joueur, buffer, carte, nbBleu) == 1 || p_joueur->y < 0 + 1){
        p_joueur->y += 7;
        return 0;
    }
    else if(collision(p_joueur, buffer, carte, nbBleu) == 2 || collision(p_joueur, buffer, carte, nbBleu) == 0){
        return 0;
    }
    else if(collision(p_joueur, buffer, carte, nbBleu) == 3){
    	return 1;
    }
    return 0;
}

int down(S_ENTITE *p_joueur,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu)
{
    p_joueur->y += 7;

    if(collision(p_joueur, buffer, carte, nbBleu) == 1 || p_joueur->y+TAILLE_BLOC > JEU + 1){
        p_joueur->y -= 7;
        return 0;
    }
    else if(collision(p_joueur, buffer, carte, nbBleu) == 2 || collision(p_joueur, buffer, carte, nbBleu) == 0){
        return 0;
    }
    else if(collision(p_joueur, buffer, carte, nbBleu) == 3){
    	return 1;
    }
    return 0;
}

/// ********************** (2)

/// Gestion de la colision (3)

int collision(S_ENTITE *p_joueur,ALLEGRO_BITMAP *buffer, int carte[][HAUTEUR_MAP], int nbBleu)
{
    for(i = (int)(p_joueur->x - 225)/TAILLE_BLOC; i <= (int)(p_joueur->x + TAILLE_JOUEUR - 226)/TAILLE_BLOC; i++){
        for(j = (int)(p_joueur->y - 1)/TAILLE_BLOC; j <= (int)(p_joueur->y + TAILLE_JOUEUR - 2)/TAILLE_BLOC; j++){
            if(carte[i][j] == MUR){
                return 1;
			}
            else if(carte[i][j] == CRISTAUXB){
                carte[i][j] = VIDE;
                al_set_target_bitmap(buffer);
                al_draw_bitmap(vide, TAILLE_BLOC*i, TAILLE_BLOC*j, 0);
                al_set_target_bitmap(al_get_backbuffer(display));
                
                p_joueur->bleu++;
                if((p_joueur->bleu)%5 == 0 && p_joueur->bleu != 0){
                	p_joueur->rouge++;
                }
                return 2;
            }
            else if(carte[i][j] == CRISTAUXR && p_joueur->bleu == nbBleu){
                return 3;
            }
        }
    }
    return 0;
}

/// ********************** (3)
