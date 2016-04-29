#include "charger.h"

void charger(int niveau[][HAUTEUR_MAP], int lvl)
{
FILE *ficher = NULL;
char ligneFichier[LARGEUR_MAP * HAUTEUR_MAP + 1] = {0};

    ficher = fopen("./Map/map.txt", "r");
    fseek(ficher, lvl*(LARGEUR_MAP * HAUTEUR_MAP + 1), SEEK_SET);
    fgets(ligneFichier, LARGEUR_MAP * HAUTEUR_MAP + 1, ficher);
	
    for(i = 0; i < LARGEUR_MAP; i++){
        for(j = 0; j < HAUTEUR_MAP; j++){
            switch(ligneFichier[(j*HAUTEUR_MAP)+i]){
                case '0':
                    niveau[i][j] = 0;
                    break;
                case '1':
                    niveau[i][j] = 1;
                    break;
                case '2':
                    niveau[i][j] = 2;
                    break;
                case '3':
                    niveau[i][j] = 3;
                    break;
            }
        }
    }

    fclose(ficher);
}

void positonPerso(int pos[], int lvl)
{
FILE *ficher = NULL;
char ligneFichier[4] = {0};

    ficher = fopen("./Map/pos.txt", "r");
    fseek(ficher, lvl*4, SEEK_SET);
    fgets(ligneFichier, 4, ficher);

    for(i = 0, j = 0; i < 4; i++){
    	switch(ligneFichier[i]){
            case '0':
                pos[j] = 0;
                j++;
                break;
            case '1':
                pos[j] = 1;
                j++;
                break;
            case '2':
                pos[j] = 2;
                j++;
                break;
            case '3':
                pos[j] = 3;
                j++;
                break;
            case '4':
                pos[j] = 4;
                j++;
                break;
            case '5':
                pos[j] = 5;
                j++;
                break;
            case '6':
                pos[j] = 6;
                j++;
                break;
            case '7':
                pos[j] = 7;
                j++;
                break;
            case '8':
                pos[j] = 8;
                j++;
                break;
            case '9':
                pos[j] = 9;
                j++;
                break;
            case 'a':
                pos[j] = 10;
                j++;
                break;
            case 'b':
                pos[j] = 11;
                j++;
                break;
            case 'c':
                pos[j] = 12;
                j++;
                break;
            case 'd':
                pos[j] = 13;
                j++;
                break;
            case 'e':
                pos[j] = 14;
                j++;
                break;
            case 'f':
                pos[j] = 15;
                j++;
                break;
            default:
            	break;
        }
    }

    fclose(ficher);
}
