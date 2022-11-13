#include <algorithm>
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
  generate_states(current_state, player.depth);

  current_state.free_child_states();
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
        break;
      }
    }

    generate_states(parent->child_states[i], depth - 1);
  }
}
