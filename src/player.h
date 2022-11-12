#pragma once
#include <string>

/**
 * Our Player type. This type handles user input or computer move computation. It also stores the player name and the last move done,
 * in order to save computation when checking if the state of the game.
 *
 * The depth parameter will only be used in case is_computer is true. It will specify the depth of the AI (minimax) algorithm.
 */
typedef struct Player {
  std::string name;          /* Player Name */
  int last_move[2];          /* Last executed move (x, y) */
  void play(int *last_move); /* Receveis input and updates @last_move and @Board values */
  bool is_computer;          /* Boolean that represents if the player is an AI */
  int depth;                 /* AI depth */
} Player;


Player create_player(std::string name, bool is_computer = false, int depth = 0);
