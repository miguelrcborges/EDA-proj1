#include <cctype>
#include <iostream>
#include <cstdlib>
#include "ai.h"
#include "player.h"

#ifdef __APPLE__
#include <cstdio>
#endif

extern const int board_side;

Player create_player(char symbol) {
  Player player;
  char input;
  player.symbol = symbol;
  player.last_move[0] = 0; 
  player.last_move[1] = 0; 

  std::cout << "What should the player name be?\n> ";
  std::getline(std::cin, player.name);

  while (1) {
    input = get_input("Is this player a computer? (Y/N)\n> ");
    input = toupper(input);
    if (input == 'Y' || input == 'N')
      break;
    std::cout << "The input must be either Y or N." << std::endl;
  }

  player.is_computer = input == 'Y';
  if (player.is_computer) {
    player.depth = get_int("What is the computer difficulty? max: 8\n> ");
    if (player.depth > 8) {
      std::cout << "The difficulty will be set to 8." << std::endl;
      player.depth = 8;
    }
  }

  return player;
}


void Player::play(Board &board) {
  char input;
  int column;
  if (is_computer)
    return compute_play(*this, board);

  while (true) {
    input = get_input("Where do you want to play, " + name + "?\n> ");
    input = toupper(input);
    column = input - 'A';

    if (input < 'A' || input > 'G') {
      std::cout << "Your input bust me a letter between A and G!" << std::endl;
      continue;
    }

    if (board.slots[column][BOARD_SIZE-1] != ' ') {
      std::cout << "That column is already stacked!" << std::endl;
      continue;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
      if (board.slots[column][i] == ' ') {
        board.slots[column][i] = symbol;
        last_move[0] = column;
        last_move[1] = i;
        return;
      } 
    }
    std::cout << "Something wrong happened D:" << std::endl;
    std::exit(-1);
  }
}


char get_input(std::string prompt) {
  char input;
ask_input:
  std::cout << prompt;

  if (std::cin >> input) {
    std::cin.ignore(1000, '\n');
    return input;
  }

  do {
    std::cout << "Do you really want to quit? (Y/N)" << std::endl;
    if (std::cin.fail()) {
      std::cin.clear();
#ifdef __APPLE__
      clearerr(stdin);
#endif

      if (std::cin.peek() != '\n')
        std::cin.ignore(100,'\n');
    }

    std::cin >> input;
    input = toupper(input);
    if (input == 'N') goto ask_input;
    std::cout << "Input must be either Y or N!" << std::endl;
  } while (input != 'Y');

  std::exit(0);
}


int get_int(std::string prompt) {
  char exit_confirmation;
  int input;
ask_input:
  std::cout << prompt;

  if (std::cin >> input) {
    std::cin.ignore(1000, '\n');
    return input;
  }

  do {
    std::cout << "Do you really want to quit? (Y/N)" << std::endl;
    if (std::cin.fail()) {
      std::cin.clear();
#ifdef __APPLE__
      clearerr(stdin);
#endif

      if (std::cin.peek() != '\n')
        std::cin.ignore(100,'\n');
    }

    std::cin >> exit_confirmation;
    exit_confirmation = toupper(exit_confirmation);
    if (exit_confirmation == 'N') goto ask_input;
    std::cout << "exit_confirmation must be either Y or N!" << std::endl;
  } while (exit_confirmation != 'Y');

  std::exit(0);
}
