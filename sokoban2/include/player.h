/** @file player.h */ 
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/**
 * @brief La stucture qui contients les informations de ligne et de la colonne où se trouve le joueur dans le game_grid
 * Player[x][y]
 */
typedef struct player
{
    int x;  // Ligne
    int y;  // Colonne
}Player;

/**
 * @enum Direction 
 * @brief Cette enum contient les informations sur les directions de mouvements du joueur
 */
enum Direction{
    Top = 'h',
    Left = 'j',
    Right = 'k',
    Bottom = 'l'
};
typedef enum Direction Direction;   // Pour ne pas ecrire tous le temps "enum direction"

#endif
