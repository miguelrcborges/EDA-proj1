#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
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
  if (player.depth <= 0) {
    std::vector<int> free_columns;
    for (int i = 0; i < BOARD_WIDTH; i++)
      if (board.slots[i][BOARD_HEIGHT-1] == ' ')
        free_columns.push_back(i);
    column_to_play = free_columns[rand() % free_columns.size()];
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

  std::copy(&board.slots[0][0], &board.slots[BOARD_WIDTH-1][BOARD_HEIGHT-1], &current_state.board.slots[0][0]);
  generate_states(&current_state, player.depth);
  
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (current_state.child_states[i] != NULL)
      mini_max(current_state.child_states[i], player.depth - 1, true);
  }

  std::vector<int> possible_indexes;
  for (int i = 1; possible_indexes.size() == 0; i--)
    for (int x = 0; x < BOARD_WIDTH; x++)
      if (current_state.child_states[x] != NULL)
        if (current_state.child_states[x]->value == i)
          possible_indexes.push_back(x);

  current_state.free_child_states();
  column_to_play = possible_indexes[rand() % possible_indexes.size()];

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
  if (depth <= 0) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
      parent->child_states[i] = NULL;
    }
    return;
  }

  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (parent->board.slots[i][BOARD_HEIGHT-1] != ' ') {
      parent->child_states[i] = NULL;
      continue;
    }
    parent->child_states[i] = new Board_state;
    parent->child_states[i]->symbol_to_play = parent->symbol_to_play == PLAYER_ONE_SYMBOL ? PLAYER_TWO_SYMBOL : PLAYER_ONE_SYMBOL;
    std::copy(&(parent->board.slots[0][0]), &(parent->board.slots[BOARD_WIDTH-1][BOARD_HEIGHT-1]), &(parent->child_states[i]->board.slots[0][0]));

    for (int ii = 0; ii < BOARD_HEIGHT; ii++) {
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


void mini_max(Board_state *board_state, int depth, bool was_my_turn) {
  if (board_state->board.check_win(board_state->last_move)) {
    board_state->value = was_my_turn ? 1 : -1;
    return;
  }

  if (depth <= 0) {
    board_state->value = 0;
    return;
  }

  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (board_state->child_states[i] != NULL)
      mini_max(board_state->child_states[i], depth - 1, !was_my_turn);
  }

  board_state->value = was_my_turn ? 2 : -2;
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
