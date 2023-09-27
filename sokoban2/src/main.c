/** @file main.c */ 
#include <stdio.h>
#include "../include/grid.h"
#include <stdbool.h>
#include <stdlib.h>

int main(void){
	// Les information sur les niveau il faut modifier si on veut ajouter des niveau:
	Path lev1 = "level/level1.txt";
	Path lev2 = "level/level2.txt";
	int niveau_max = 2;
	Path niveau[2] = {lev1,lev2};	// Tableaux qui contient les Path vers les fichiers .txt
	// Initialisation de grid
	Grid * level = init_level(lev1);
	int index_level = 0;	// indice pour passer au niveau suivant

	bool run = true;
	display(level);
	while(run){
		char entry = fgetc(stdin); 
		switch(entry){
			case 'q' :{
				run = false;
				break;
			}
			case 'h': {move_player(level,Top);} break;		// Aller vers l'haut
			case 'j': {move_player(level,Left);} break;		// Aller vers gauche
			case 'k': {move_player(level,Right);} break; 	// Aller vers droite
			case 'l': {move_player(level,Bottom);} break;	// Aller vers le bas
			case 'n': {if(level->goal_number != 0)
						{
							printf("Tricheur!\n Vous ne pouvez pas passer au niveau suivant sans passer le niveau courant!\n");
						}
						else
						{
							index_level ++; 	// Pour passage au niveau suivant	n = next
							if(index_level < niveau_max)
							{
								free_grid(level); free(level);
								level = init_level(niveau[index_level]); 
								display(level);
							}
							else
							{
								printf("Bravo! Vous avez finit le jeu sokoban\n");
								run = false;
							}
						}
					  } break;
			case 'r': {free_grid(level); free(level); level = init_level(niveau[index_level]); display(level);} break;	// Pour rejouer la meme niveau r = rejouer
		}
	}
	free_grid(level);
	free(level);
}

