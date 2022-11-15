#include <algorithm>
#include <vector>
#include <cstdlib>
#include "ai.h"

void Board_state::free_child_states() {
  for (int i = 0; i < 7; i++) {
    if (child_states[i] != NULL) {
      child_states[i]->free_child_states();
      delete child_states[i];
      child_states[i] = NULL;
    }
  }
}


void compute_play(Player &player, Board &board) {
  Board_state current_state;

  current_state.symbol_to_play = player.symbol;

  std::copy(&board.slots[0][0], &board.slots[6][6], &current_state.board.slots[0][0]);
  generate_states(&current_state, player.depth);
  
  for (int i = 0; i < 7; i++) {
    if (current_state.child_states[i] != NULL)
      mini_max(current_state.child_states[i], player.depth, true);
  }

  std::vector<int> possible_indexes;
  for (int i = 1; possible_indexes.size() != 0; i--)
    for (int x = 0; x < 7; x++)
      if (current_state.child_states[x]->value == i)
        possible_indexes.push_back(x);

  current_state.free_child_states();
  int column_to_play = possible_indexes[rand() % possible_indexes.size()];
  for (int row = 0; row < 7; row++) {
    if (board.slots[column_to_play][row] == ' ') {
      board.slots[column_to_play][row] = player.symbol;
      break;
    }
  }
}


void generate_states(Board_state *parent, int depth) {
  if (depth <= 0) {
    for (int i = 0; i < 7; i++) {
      parent->child_states[i] = NULL;
    }
    return;
  }

  for (int i = 0; i < 7; i++) {
    if (parent->board.slots[i][6] != ' ') {
      parent->child_states[i] = NULL;
      continue;
    }
    parent->child_states[i] = new Board_state;
    parent->child_states[i]->symbol_to_play = parent->symbol_to_play == 'X' ? 'O' : 'X';
    std::copy(&(parent->board.slots[0][0]), &(parent->board.slots[6][6]), &(parent->child_states[i]->board.slots[0][0]));

    for (int ii = 0; ii < 7; ii++) {
      if (parent->child_states[i]->board.slots[i][ii] == ' ') {
        parent->child_states[i]->board.slots[i][ii] = parent->symbol_to_play;
        parent->child_states[i]->last_move[0] = i;
        parent->child_states[i]->last_move[1] = ii;
        break;
      }
    }

    generate_states(parent->child_states[i], depth - 1);
  }
}


void mini_max(Board_state *board_state, int depth, bool isMax) {
  if (board_state->board.check_win(board_state->last_move)) {
    board_state->value = isMax ? 1 : -1;
    return;
  }

  if (depth <= 0)
    board_state->value = 0;

  for (int i = 0; i <= 6; i++) {
    if (board_state->child_states[i] != NULL)
      mini_max(board_state, depth - 1, !isMax);
  }

  board_state->value = isMax ? -2 : 2;
  for (int i = 0; i <= 6; i++) {
    if (isMax) {
      if (board_state->value < board_state->child_states[i]->value)
        board_state->value = board_state->child_states[i]->value;
    } else {
      if (board_state->value > board_state->child_states[i]->value)
        board_state->value = board_state->child_states[i]->value;
    }
  }

}
