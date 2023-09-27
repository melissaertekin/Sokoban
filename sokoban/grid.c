/** @file grid.c */ 
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

Grid * init_level(const char* file_path){
	// ouverture du fichier en mode lecture
	FILE* file = fopen(file_path, "r");
	if(!file){
		fprintf(stderr, "Error %s not found", file_path);
		exit(-1);
	}
	char line[100] = {0};
	int number_column = 0; // nombre de colonne
	int number_row = 0; /// nombre de ligne
	int number_goals = 0;	// nombre des goals
	//  ATTENTION !!! -> Il faut voir le fichier txt s'il y a 4 nombre dans le premier ligne (sinon il faut ajouter le nombre des boxes)
	// J'ai ajoute nombre de box pour voir la possibilite de perdre. Il faut ajouter le nombre dans le fichier txt aussi
	int number_box = 0;	// Nombre des boxes
	// on lit la première ligne du fichier
	fgets(line, 100, file);
	sscanf(line, "%d %d %d %d", &number_column, &number_row, &number_goals, &number_box);

	// Creation de level (type : Grid *)
	Grid * level = malloc(sizeof(Grid));	
	// Initialisation du level sans game_grid et goal_positions
	level->row_number = number_row;
	level->column_number = number_column; 
	level->box_number = number_box;
	level->goal_number = number_goals;
	level->total_goal_number = number_goals;

	int current_row = 0;	// compteur de ligne

	// Creation d'une tableau des pointeurs de type Case * (pour les lignes de game_grid)
	level->game_grid = malloc(level->row_number * sizeof(Case *));	// à faire un free

	// On lit le fichier ligne par ligne jusqu'à la fin du fichier
	while(fgets(line, 100, file) != NULL)
	{
		char* buffer = line;
		int current_column = 0; // compteur de colonne
		// on cree une tableau de type Case (pour les colonnes de game_grid)
		level->game_grid[current_row] = malloc(level->column_number * sizeof(Case));	// à faire un free
		while(current_column < number_column)
		{
			char caractere = buffer[current_column];	// On lit le caractere dans le ligne qui se trouve dans le fichier (.txt)
			switch (caractere)
			{
			case '#': level->game_grid[current_row][current_column] = WALL ; break;
			case '$': level->game_grid[current_row][current_column] = BOX ; break;
			case '.': level->game_grid[current_row][current_column] = GOAL ; break;
			case ' ': level->game_grid[current_row][current_column] = NONE ; break;
			case '@': 
					{
						level->game_grid[current_row][current_column] = PLAYER ;
						// Initialisation de la position de joueur
						level->player.x = current_row;
						level->player.y = current_column;
					}	break; 
			}
			current_column ++;	// Incrementation de la compteur des colonnes
		}		
		current_row ++; // Incrementation de la compteur des lignes
	}
	// fermeture du fichier
	fclose(file);

	// Creation de tableau de type Goal qui contient le position des objectives
	level->goal_positions = malloc(number_goals * sizeof(Goal));	// à faire un free
	find_goal_position(level);	// Initialisation des positions des goals

	// On retourne le pointeur de grid qu'on vient de creer
	return level;
}

void display(Grid * grille)
{
	for(int i = 0; i < grille->row_number;i++)
	{
		for(int j = 0; j < grille->column_number; j++)
		{
			printf("%c", (char)grille->game_grid[i][j]);
		}
		printf("\n");
	}
}

void completed(Grid * grille){
	if(grille->goal_number == 0)
	{	
		printf("-------------------\n");  
		printf("Level Completed\n");  
		printf("-------------------\n");  
		printf("Saisir n pour passer au level suivant ou saisir q pour quitter le jeu : \n"); // Demande s'il veut passer au niveau prochaine
	}
	else
	{
		printf("-------------------\n");  
		printf("Goal Completed\n");  
		printf("-------------------\n");  
	}
}

void find_goal_position(Grid * grille)
{
	int index_liste = 0;
	for(int i = 0;i<grille->row_number;i++)
	{
		for(int j=0;j<grille->column_number;j++)
		{
			if(grille->game_grid[i][j] == GOAL)
			{
				grille->goal_positions[index_liste].x = i;
				grille->goal_positions[index_liste].y = j;
				index_liste ++;
			}
		}
	}
}

int place_de_goal(Grid * grille, int pos_x, int pos_y)
{
	for(int i = 0;i < grille->total_goal_number; i++)
	{
		if((grille->goal_positions[i].x == pos_x) && (grille->goal_positions[i].y == pos_y))
			return 1;
	}
	return 0;
}

int perdue(Grid * grille, Direction move)
{
	int result = 1;
	int pos_x = grille->player.x;
	int pos_y = grille->player.y;
	switch (move)
	{
		case Top: {for(int i = 0; i < grille->column_number; i++)
					{
						if(grille->game_grid[pos_x-1][i] == GOAL)
						{
							result = 0;
						}
					}
					};	break;
		case Bottom:{for(int i = 0; i < grille->column_number; i++)
					{
						if(grille->game_grid[pos_x+1][i] == GOAL)
						{
							result = 0;
						}
						break;
					}
					};	break;
		case Left:	{for(int i = 0; i < grille->column_number; i++)
					{
						if(grille->game_grid[i][pos_y-1] == GOAL)
						{
							result = 0;
						}
						break;
					}
					};	break;
		case Right: {for(int i = 0; i < grille->column_number; i++)
					{
						if(grille->game_grid[i][pos_y+1] == GOAL)
						{
							result = 0;
						}
						break;
					}
					};	break;
	}
	return result;
}

void move_player(Grid * grille, Direction move){
	int pos_x = grille->player.x;
	int pos_y = grille->player.y;
	switch (move)
	{
		case Top:	test_and_move(grille,Top,pos_x-1,pos_x-2,pos_y,pos_y);	break;
		case Bottom:	test_and_move(grille,Bottom,pos_x+1,pos_x+2,pos_y,pos_y);	break;
		case Left:	test_and_move(grille,Left,pos_x,pos_x,pos_y-1,pos_y-2);  break;
		case Right:	test_and_move(grille,Right,pos_x,pos_x,pos_y+1,pos_y+2); break;
	}
}

void test_and_move(Grid * grille,Direction move,int pos_x1,int pos_x2, int pos_y1,int pos_y2)
{
	// Initialisation des positions
	int pos_x = grille->player.x;
	int pos_y = grille->player.y; 
	int x1 = pos_x1;	
	int x2 = pos_x2;
	int y1 = pos_y1;
	int y2 = pos_y2;
	// Pour test de perdre
	int x3 = x1;
	int y3 = y1;
	switch (grille->game_grid[x1][y1])	// Controle de la prochaine case à deplacer
	{
		case WALL:printf("Ops! C'est le mur!\n");	break;
		case BOX :
		{ 	if(place_de_goal(grille,x1,y1))	// Pour ne pas perdre la position d'un objective
			{
				printf("Le box est dans la bonne position.\n Vous ne pouvez pas bouger le box. \n");
			}
			else
			{
				grille->game_grid[pos_x][pos_y] = NONE;
				grille->game_grid[x1][y1] = PLAYER; // On change la position de joueur
				switch (move)
				{
					case Top: grille->player.x --; break;
					case Bottom: grille->player.x ++;	break;
					case Left:	grille->player.y --; break;
					case Right:	grille->player.y ++; break;
				}
				if(grille->game_grid[x2][y2] == GOAL)
				{
					grille->game_grid[x2][y2] = BOX; 
					grille->box_number--;	// On diminue le nombre des box
					grille->goal_number --;	// On diminue le nombre des objectives
					completed(grille);
				}
				else
				{
					if(grille->game_grid[x2][y2] == WALL)
					{
						printf("C'est la fin du grid changer votre direction\n");
						grille->game_grid[pos_x][pos_y] = PLAYER;
						switch (move)	// On remodifie la position du player
						{
							case Top: grille->player.x ++; break;
							case Bottom: grille->player.x --;	break;
							case Left:	grille->player.y ++; break;
							case Right:	grille->player.y --; break;
						}
						grille->game_grid[x1][y1] = BOX; 
					}
					else
					{
						switch (move)	// Pour les conditions de perdre
						{
							case Top: x3 -= 2; break;
							case Bottom: x3 += 2; break;
							case Left:	y3 -= 2; break;
							case Right:	y3 += 2; break;
						}
						if(grille->game_grid[x3][y3] == WALL)
						{
							if(perdue(grille,move) && (grille->box_number <= grille->goal_number))	// Les conditions de perdre
							{
								printf("Vous avez perdue.\n Saisir r pour rejouer\n");
								grille->game_grid[x2][y2] = BOX;
							}
							else
							{
								grille->box_number --;
								printf("Attention! Vous pouvez perdre le jeu\n");
								grille->game_grid[x2][y2] = BOX;	
							}
						}
						else
							grille->game_grid[x2][y2] = BOX; 
					}
						
				}	
			}
		} break;
		case NONE:	grille->game_grid[pos_x][pos_y] = NONE;
					grille->game_grid[x1][y1] = PLAYER;
					switch (move) // On change la position de joueur
					{
						case Top: grille->player.x --; break;
						case Bottom: grille->player.x ++;	break;
						case Left:	grille->player.y --; break;
						case Right:	grille->player.y ++; break;
					} break;
		case GOAL:  printf("Ops! C'est le l'objective!\n");	break;
		default: printf("Il y a un erreur!\n");	break;
	}
}

void free_grid(Grid * grille)
{
	for(int i = 0; i < grille->row_number; i++)
	{
		free(grille->game_grid[i]);
	}
	free(grille->game_grid);
	free(grille->goal_positions);
}

