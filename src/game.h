#pragma once

#include <string>
#include <iostream>
#include "player.h"
#include "board.h"
#include <ctime>

/**
* Game type - this type handles game-related information like the current players and turn
* but also the board and time of play.
*/
typedef struct Game {
  /** Game turn. */
  int turn;
  /** Players in game. */
  Player players[2];
  /** Board of game. */
  Board board;
  /** Inital time of game. */
  tm *times;
  /** 
  * Loop of gameplay.
  */
  void game_loop();
  /**
  * Function that outputs the results of the matches and the time to a file.
  * @return 0 if successful, and 1 if not.
  */
  int log_match();
} Game;


/**
 * Function that initializes a Game structure.
 * @return Current game info.
*/
Game create_game();



