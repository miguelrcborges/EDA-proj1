#pragma once

#include <string>
#include "board.h"

/**
 * Our Player type. This type handles user input or computer move computation. It also stores the player name and the last move done,
 * in order to save computation when checking the state of the game.
 *
 * The Player.depth parameter will only be used if Player.is_computer is true. It will specify the depth of the AI (minimax) algorithm.
 */
typedef struct Player {
  /** Player Name. */
  std::string name;                          

  /** Last executed move (x, y). */
  int last_move[2];                          

  /** Boolean that represents if the player is an AI. */
  bool is_computer;                          

  /** AI depth. */
  int depth;                                 

  /** Player symbol in the board. */
  char symbol;                               


  /** 
   * Plays the player move. Updates last_move and Board values. 
   * 
   * @param board Current game board.
   */
  void play(Board &board); 

} Player;

char getInput(const std::string& prompt);

/**
 * Function that returns a player that accepts parameters to feed the initial data. Serves as a constructor.
 *
 * @param name Player name.
 * @param symbol Symbol that will show up in the board.
 * @param is_computer Boolean that should be true if the player isn't human.
 * @param depth Depth of minimax algorith for the AI (only used if is_computer is true).
 * @return Player with the given data.
 */
Player create_player(char symbol);

/**
 * Function that receives player inputs.
 *
 * @param prompt Text that will be displayed before asking input.
 * @return The char the user inputted.
 */
char get_input(std::string prompt);


/**
 * Same as getInput, but for integers.
 * @see getInput.
 *
 * @param prompt Text that will be displayed before asking input.
 * @return The int the user inputted.
 */
int get_int(std::string prompt);
