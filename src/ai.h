#pragma once

#include "board.h"
#include "player.h"

/**
 * Board_state type. It will be used to board evaluation, so the AI can figure which move it should do.
 */
typedef struct Board_state {
  /** Board at this specific state. */
  Board board;

  /** Evaluation of this Board_state. */
  int value;

  /** Board_states derivated from this one. */
  Board_state *child_states[7];

  /** Character that is about to play in the current state. */
  char symbol_to_play;

  /** Last played move. */
  int last_move[2];

  /** Function to free from memory the generated child_states. */
  void free_child_states();
} Board_state;

/**
 * Function that will do the AI play.
 *
 * @param player The AI player that the fuction will play for.
 * @param board Board where the move will be done.
 */
void compute_play(Player &player, Board &board);

/**
 * Function that will set the evaluation for each Board_state, following the minimax algorithm.
 *
 * @param board_state Board_state corresponding to the current board.
 * @param depth How many moves ahead he should analyze.
 * @param isMax Minimax variable to consider if it has to pick the lowest value children, or the highest value one.
 */
void mini_max(Board_state *board_state, int depth, bool isMax);

/**
 * Function that allocates memmory to the order of the depth parameter.
 *
 * @param parent Parent Board_state that will receive the Board_state.child_states.
 * @param depth How many turns ahead the AI will see.
 */
void generate_states(Board_state *parent, int depth);
