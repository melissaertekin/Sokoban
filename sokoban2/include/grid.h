/** @file grid.h */ 
#ifndef GRID_HEADER
#define GRID_HEADER
#include "player.h"

/**
 * @enum CaseType grid.h
 * @brief Cette structure contient les informations 
 * concernant les cases de la grille du jeu
 */
enum CaseType{
	WALL = '#',
	BOX = '$',
	PLAYER = '@',
	GOAL = '.',
	NONE = ' '
};
/**
 * @typedef Case grid.h
 * @brief Definition du enum CaseType sous le nom Case
 * 	Pour n'est pas ecrire toute le temps "enum CaseType"
*/
typedef enum CaseType Case;	

/**
 * @typedef Path grid.h
 * @brief Definition de type Path : const char * 
 * Pour qu'il soit claire qu'il sagit d'un chemin vers une fichier (.txt)
*/
typedef const char* Path;

/**
 * @struct Goal grid.h
 * @brief Cette structure contient le position d'un objetive
 */
typedef struct Goal
{
	int x;	///< Numero de ligne d'un goal
	int y;	///< Numero de colonne d'un goal
}Goal;

/**
 * @struct Grid grid.h
 * @brief Cette structure contient les informations 
 * concernant la grille du jeu et son contenu
 */
struct grid{
	Case** game_grid; ///< Tableau contenant les entités présents dans le jeu
	int column_number; ///< Nombre de colonne de game_grid
	int row_number; ///< Nomber de ligne de game_grid
	int box_number; ///< Nombre des boxs tatale dans le jeu
	int total_goal_number; ///< Nombre des goal totale
	int goal_number; ///< Nombre des goal reste
	Goal* goal_positions; ///< Une tableau de type Goal qui contiens les position des objectives
	Player player; //< Joueur avec sa position
};	
typedef struct grid Grid; // Pour n'est pas ecrire toute le temps "struct Grid"


/**
*@brief Initialise le grid depuis un fichier.txt
*@param file_path Chemin vers le fichier
*@return Pointeur vers un Grid
*/
Grid * init_level(const char* file_path);

/**
	@brief Affcihe le jeu (grid)
	@param grille : Une pointeur vers une grid (Grid *)
	@return Void
*/
void display(Grid * grille);

/**
	@brief On libere goal_position, game_grid et ses lignes
	@param grille : Une pointeur vers une grid (Grid *)
	@return Void
*/
void free_grid(Grid * grille);

/**
	@brief Affiche "Goal Completed" ou "Level completed selon le nombre d'objective reste"
	@param grille : Une pointeur vers une grid
	@return void
*/
void completed(Grid * grille);

/**
	@brief Controle si le joueur peuvent passer le niveau courant
	@param grille : Une pointeur vers une grid et un direction 
	@return: int (qui est utilise comme une booleen)
*/
int perdue(Grid * grille, Direction move);

/**
 * @brief On tourne le grid et on sauvgarde la position des objectives dans une tableau de type Goal
 * @param grille  Une pointeur vers une grid et un direction 
 * @return void
 */
void find_goal_position(Grid * grille);

/**
 * @brief 
 * 
 * @param grille 
 * @param pos_x Numero de ligne de box 
 * @param pos_y Numero de colonne de box
 * @return int (qui est utilise comme une booleen)
 */
int place_de_goal(Grid * grille, int pos_x, int pos_y);

/**
*@brief Selon la direction il fait appele à la fonction test_and_move avec les bonnes positions à modifier pour deplacer
*@param grille : Une pointeur vers une grid
*@param move : Une direction saisi par le joueur
*@return void
*/
void move_player(Grid * grille, Direction move);

/**
 * @brief Controle les cases s'il est possible de deplacer on deplace et sinon on affiche une message pour expliquer la raison au joueur
 * 
 * @param grille Une pointeur vers une grid et un direction 
 * @param move Une direction saisi par le joueur 
 * @param pos_x1 Selon la direction, il peut avoir la valeur x (numero de ligne actuelle) ou x + 1 (ligne en dessus) ou x - 1 (ligne au dessus)
 * @param pos_x2 Selon la direction, il peut avoir la valeur x (numero de ligne actuelle) ou x + 2 (2 ligne en dessus) ou x - 2 (2ligne au dessus)
 * @param pos_y1 Selon la direction, il peut avoir la valeur y (numero de colonne actuelle) ou y + 1 (colonne à droite) ou y - 1 (colonne à gauche)
 * @param pos_y2 Selon la direction, il peut avoir la valeur y (numero de colonne actuelle) ou y + 2 (2 colonne à droite) ou y - 2 (2 colonne à gauche)
 * @return void
 */
void test_and_move(Grid * grille,Direction move,int pos_x1,int pos_x2, int pos_y1,int pos_y2);

#endif
