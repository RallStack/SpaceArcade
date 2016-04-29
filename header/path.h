#ifndef PATH_H
#define PATH_H

#include "constances.h"
#include "perso.h"

typedef struct path_directory path_directory;
struct path_directory
{
	char directory;
	path_directory *nextPos;
};

typedef struct
{
	int x;
	int y;
}path_pos;

typedef struct file_path_pos file_path_pos;
struct file_path_pos
{
	file_path_pos *nextPos;
	path_pos actPos;
};

typedef struct
{
	file_path_pos *first;
	file_path_pos *last;
}control;

enum{NORTH, SOUTH, EAST, WEST};

void init_file(control *control_list, S_ENTITE *ennemis);
void add_to_file(control *control_list, path_pos new);
void remove_to_file(control *control_list);
void add_to_pile(path_directory **control, char directory);
path_directory* createPath(int map[][LARGEUR_MAP], S_ENTITE *joueur, S_ENTITE *ennemis);

#endif
