#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <climits>
#include "ai.h"
#include "config.h"

void Board_state::free_child_states() {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (child_states[i] != NULL) {
      child_states[i]->free_child_states();
      delete child_states[i];
      child_states[i] = NULL;
    }
  }
}


void compute_play(Player &player, Board &board) {
  int column_to_play;
  // Plays the piece randomly
  if (player.depth <= 0) {
    std::vector<int> free_columns;
    // Gets free columns
    for (int i = 0; i < BOARD_WIDTH; i++)
      if (board.slots[i][BOARD_HEIGHT-1] == ' ')
        free_columns.push_back(i);
    
    // Randomizes where to play
    column_to_play = free_columns[rand() % free_columns.size()];

    // Places the piece
    for (int row = 0; row < BOARD_HEIGHT; row++) {
      if (board.slots[column_to_play][row] == ' ') {
        board.slots[column_to_play][row] = player.symbol;
        player.last_move[0] = column_to_play;
        player.last_move[1] = row;
        std::cout << "The cpu played on " << (char) ('A' + (char) column_to_play) << ".\n";
        break;
      }
    }
    return;
  }

  Board_state current_state;
  current_state.symbol_to_play = player.symbol;

  // Copies the board to the state and generate child states
  std::copy(&(board.slots[0][0]), &(board.slots[BOARD_WIDTH-1][BOARD_HEIGHT-1]) + 1, &(current_state.board.slots[0][0]));
  generate_states(&current_state, player.depth);
  
  // Scores the child states
  for (int i = 0; i < BOARD_WIDTH; i++)
    if (current_state.child_states[i] != NULL)
      mini_max(current_state.child_states[i], player.depth - 1, true);

  // Get possible places to play
  std::vector<int> possible_indexes;
  for (int x = 0; x < BOARD_WIDTH; x++)
    if (current_state.child_states[x] != NULL) {
      // Adds option when vector off possible options is empty
      if (possible_indexes.size() == 0) 
        possible_indexes.push_back(x);
      // Clears saved options if finds one with better value
      else if (current_state.child_states[x]->value > current_state.child_states[possible_indexes[0]]->value) {
        possible_indexes.clear();
        possible_indexes.push_back(x);
      // Adds to possible options if has the save score to the currently saved ones
      } else if (current_state.child_states[x]->value == current_state.child_states[possible_indexes[0]]->value)
        possible_indexes.push_back(x);
    }

  // DEBUG
  // for (int i = 0; i < BOARD_WIDTH; i++)
  //   if (current_state.child_states[i] != NULL)
  //     std::cout << "Posição " << i << ": " << current_state.child_states[i]->value << std::endl;

  // Free memory and pick and chooses a move randomly from the ones that have the best score
  current_state.free_child_states();
  column_to_play = possible_indexes[rand() % possible_indexes.size()];

  // Plays the piece
  for (int row = 0; row < BOARD_HEIGHT; row++) {
    if (board.slots[column_to_play][row] == ' ') {
      board.slots[column_to_play][row] = player.symbol;
      player.last_move[0] = column_to_play;
      player.last_move[1] = row;
      std::cout << "The CPU " << player.name << " played on " << (char) ('A' + (char) column_to_play) << ".\n";
      break;
    }
  }
}


void generate_states(Board_state *parent, int depth) {
  // Function to be called recursively
  // Depth will be the stop condition
  if (depth <= 0) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
      parent->child_states[i] = NULL;
    }
    return;
  }

  for (int i = 0; i < BOARD_WIDTH; i++) {
    // Don't generate child states when there is already a column filled
    if (parent->board.slots[i][BOARD_HEIGHT-1] != ' ') {
     parent->child_states[i] = NULL;
      continue;
    }
    parent->child_states[i] = new Board_state;
    // Changes turn to the next player
    parent->child_states[i]->symbol_to_play = parent->symbol_to_play == PLAYER_ONE_SYMBOL ? PLAYER_TWO_SYMBOL : PLAYER_ONE_SYMBOL;
    std::copy(&(parent->board.slots[0][0]), &(parent->board.slots[BOARD_WIDTH-1][BOARD_HEIGHT-1]) + 1, &(parent->child_states[i]->board.slots[0][0]));

    // Plays the piece according to the state it corresponds
    for (int ii = 0; ii < BOARD_HEIGHT; ii++) {
      if (parent->child_states[i]->board.slots[i][ii] == ' ') {
        parent->child_states[i]->board.slots[i][ii] = parent->symbol_to_play;
        parent->child_states[i]->last_move[0] = i;
        parent->child_states[i]->last_move[1] = ii;
        break;
      }
    }

    // Recursive call for every child state
    generate_states(parent->child_states[i], depth - 1);
  }
}


void mini_max(Board_state *board_state, int depth, bool was_my_turn) {
  // First stop condition
  // Depth and Winning will be stop condition

  // In case of win
  // Positive if wins
  // Negative if loses
  //
  // Being the modulus of the value assigned to the depth makes it so it picks the moves
  // that win faster, and in case there is only losing moves, picks the one that will take
  // more time to lose (since it will be on a state with higher depth).
  if (board_state->board.check_win(board_state->last_move)) {
    board_state->value = was_my_turn ? depth : - depth;
    return;
  }

  // In case isn't found neither a win or lose in the assigned depth
  if (depth <= 0) {
    board_state->value = 0;
    return;
  }

  // Recursive calls to check the child states to define the value of the parent state
  // (since the parent state wasn't conclusive)
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (board_state->child_states[i] != NULL)
      mini_max(board_state->child_states[i], depth - 1, !was_my_turn);
  }

  // Parent value will correspond either to the maximum value of its child nodes, or the minimum one
  // depending which player is playing.
  //
  // If is the AI playing, it will be the child with higher value, since it is able to pick the best
  // path. Otherwise, it will be the one with the minimum value, since we are expecting our opponent
  // to play perfectly.
  // (note that if was_my_turn is true, it means it is the opponents turn at the moment) 
  board_state->value = was_my_turn ? INT_MAX : INT_MIN;
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (board_state->child_states[i] == NULL) continue;
    if (was_my_turn) {
      if (board_state->value > board_state->child_states[i]->value)
        board_state->value = board_state->child_states[i]->value;
    } else {
      if (board_state->value < board_state->child_states[i]->value)
        board_state->value = board_state->child_states[i]->value;
    }
  }

}
