#include "path.h"

path_directory* createPath(int map[][LARGEUR_MAP], S_ENTITE *joueur, S_ENTITE *ennemis)
{	
	if(ennemis->x == joueur->x && ennemis->y == joueur->y){	/// ennemis au même emplacement que le joueur (return NULL)
		return NULL;
	}
	else{
		char finish = 1;
		int cost[LARGEUR_MAP][HAUTEUR_MAP];	/// map sauvegarde du chemin

		for(i = 0 ; i < LARGEUR_MAP ; i++){	/// on met le poids de chaque case de la map a 0
			for(j = 0 ; j < HAUTEUR_MAP ; j++){
				cost[i][j] = 0;
			}
		}

		path_pos actPos;	/// sauvegarde la position actuel
		path_pos nextPos;	/// sauvegarde la position suivante
		control control_list;

		cost[(ennemis->x-225)/98][(ennemis->y-1)/98] = 1;	/// Poids de la case de l'ennemi est mise à 1

		init_file(&control_list, ennemis);

		while(control_list.first != NULL && finish)
		{
			actPos.x = control_list.first->actPos.x;
			actPos.y = control_list.first->actPos.y;

			if(actPos.x == (joueur->x-225)/98 && actPos.y == (joueur->y-1)/98)
			{
				finish = 0;
			}

			if(actPos.x != 0)
			{
				if(map[actPos.x-1][actPos.y] != MUR && cost[actPos.x-1][actPos.y] == 0)
				{
					nextPos.x = actPos.x-1;
					nextPos.y = actPos.y;
					cost[nextPos.x][nextPos.y] = cost[actPos.x][actPos.y] + 1;

					add_to_file(&control_list, nextPos);					
				}
			}
			if(actPos.x != LARGEUR_MAP -1)
			{
				if(map[actPos.x+1][actPos.y] != MUR && cost[actPos.x+1][actPos.y] == 0)
				{
					nextPos.x = actPos.x+1;
					nextPos.y = actPos.y;
					cost[nextPos.x][nextPos.y] = cost[actPos.x][actPos.y] + 1;

					add_to_file(&control_list, nextPos);
				}
			}
			if(actPos.y != 0)
			{
				if(map[actPos.x][actPos.y-1] != MUR && cost[actPos.x][actPos.y-1] == 0)
				{				
					nextPos.x = actPos.x;
					nextPos.y = actPos.y-1;
					cost[nextPos.x][nextPos.y] = cost[actPos.x][actPos.y] + 1;

					add_to_file(&control_list, nextPos);
				}
			}
			if(actPos.y != HAUTEUR_MAP - 1)
			{
				if(map[actPos.x][actPos.y+1] != MUR && cost[actPos.x][actPos.y+1] == 0)
				{				
					nextPos.x = actPos.x;
					nextPos.y = actPos.y+1;
					cost[nextPos.x][nextPos.y] = cost[actPos.x][actPos.y] + 1;

					add_to_file(&control_list, nextPos);
				}
			}
			remove_to_file(&control_list);
		}

		while(control_list.first != NULL)
		{
			remove_to_file(&control_list);
		}

		if(finish == 0)
		{
			finish = 1;
			actPos.x = (joueur->x-225)/98;
			actPos.y = (joueur->y-1)/98;
			path_directory *control = NULL;
			char directory;

			while((actPos.x != (ennemis->x-225)/98 && finish) || (actPos.y != (ennemis->y-1)/98 && finish))
			{
				if(cost[actPos.x][actPos.y+1] == cost[actPos.x][actPos.y] - 1)
				{
					directory = UP;
					actPos.y++;
				}
				else if(cost[actPos.x][actPos.y-1] == cost[actPos.x][actPos.y] - 1)
				{
					directory = DOWN;
					actPos.y--;
				}
				else if(cost[actPos.x+1][actPos.y] == cost[actPos.x][actPos.y] - 1)
				{
					directory = LEFT;
					actPos.x++;
				}
				else
				{
					directory = RIGHT;
					actPos.x--;
				}
				add_to_pile(&control, directory);
			}
			return(control);
		}
		else
		{
			return NULL;
		}
	}
}

void init_file(control *control_list, S_ENTITE *ennemis)
{
	file_path_pos *add = malloc(sizeof(*add));
	if(add != NULL)
	{
		add->actPos.x = (ennemis->x-225)/98; /// on fait correspondre les coordonnée de l'ennemis avec la grille
		add->actPos.y = (ennemis->y-1)/98;
		add->nextPos = NULL;

		control_list->first = add;	/// on sauvegarde la case avant et aprés dans la liste
		control_list->last = add;
	}
}

void add_to_pile(path_directory **control, char directory)
{
	path_directory *add = malloc(sizeof(*add));
	if(add != NULL)
	{
		add->directory = directory;
		add->nextPos = *control;
		*control = add;
	}
}

void remove_to_file(control *control_list)
{
	file_path_pos *remove = control_list->first;
	if(control_list->first != NULL)
	{
		control_list->first = control_list->first->nextPos;
		free(remove);
	}
}

void add_to_file(control *control_list, path_pos new)
{
	file_path_pos *add = malloc(sizeof(*add));
	if(add != NULL)
	{
		add->actPos.x = new.x;
		add->actPos.y = new.y;

		control_list->last->nextPos = add;
		control_list->last = add;
		add->nextPos = NULL;
	}
}
