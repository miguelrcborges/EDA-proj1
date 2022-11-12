#include <cctype>
#include <iostream>
#include <cstdlib>
#include "player.h"

#ifdef __APPLE__
#include <cstdio>
#endif

Player create_player(std::string name, char symbol, bool is_computer, int depth) {
  Player player;
  player.name = name;
  player.is_computer = is_computer;
  player.depth = depth;
  player.last_move[0] = 0; 
  player.last_move[1] = 0; 
  return player;
}

void Player::play(int last_move[2]) {
  int input;
  char exit_confirmation;
  if (is_computer)
    return;

ask_input:
  std::cout << "Where do you want to play?\n> " << std::endl;
  if (std::cin >> input) {
    /* Codigo para por a input */
    return;
  }

  if (!std::cin.eof()) {
    std::cout << "Invalid input, must be a integer number" << std::endl;
    std::cin.clear();
#ifdef __APPLE__
    clearerr(stdin);
#endif
    goto ask_input;
  }

  do {
    std::cout << "Do you really want to quit? (Y/N)" << std::endl;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
#ifdef __APPLE__
      clearerr(stdin);
#endif
    }

    std::cin >> exit_confirmation;
    exit_confirmation = toupper(exit_confirmation);
    std::cout << "Input must be either Y or N!" << std::endl;
    if (exit_confirmation == 'N') goto ask_input;

  } while (exit_confirmation != 'Y');
  std::exit(0);
}
