#include "player.h"

Player create_player(std::string name, bool is_computer, int depth) {
  Player player;
  player.name = name;
  player.is_computer = is_computer;
  player.depth = depth;
  player.last_move[0] = 0; 
  player.last_move[1] = 0; 
  return player;
}

void Player::play(int *last_move) {
  if (is_computer)
    return;
  return;
}
