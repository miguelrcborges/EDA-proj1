#include <cctype>
#include <iostream>
#include <cstdlib>
#include "ai.h"
#include "player.h"

// Needed to be able to clear stdin error flags
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

  player.name = get_string("What should the player name be?\n> ");

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
      std::cout << "That difficulty is too high, would result in long times to generate the move." << std::endl
                << "The difficulty will be set to 8." << std::endl;
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

    // Limits input to the number of columns of the board
    if (input < 'A' || input > 'A' + BOARD_WIDTH - 1) {
      std::cout << "Your input must me a letter between A and " << (char) ('A' + BOARD_WIDTH - 1) << '!' << std::endl;
      continue;
    }

    // Filled column
    if (board.slots[column][BOARD_HEIGHT-1] != ' ') {
      std::cout << "That column is already stacked!" << std::endl;
      continue;
    }

    // Places the piece
    for (int i = 0; i < BOARD_HEIGHT; i++) {
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


// Comments here are redudant for the next functions too
char get_input(std::string prompt) {
  char input;
ask_input:
  std::cout << prompt;

  if (std::cin >> input) {
    // Get instead of peek makes it able to use getline afterwards.
    bool was_it_alone = std::cin.get() == '\n'; 
    if (!was_it_alone) {
      std::cout << "Please, send only one character." << std::endl;
      std::cin.ignore(100, '\n');
      goto ask_input;
    }
    return input;
  }

  do {
    std::cout << "Do you really want to quit? (Y/N)" << std::endl;
    // Checks if the reason why is running this was due to an EOF input
    bool eof = std::cin.eof();
    if (std::cin.fail()) {
      std::cin.clear();
    // Apple std::cin isn't fully cleared with just this.
#ifdef __APPLE__
      clearerr(stdin);
#endif
    }
    if (!eof && std::cin.peek() != '\n')
        std::cin.ignore(100, '\n');
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
    bool was_it_alone = std::cin.get() == '\n'; 
    if (!was_it_alone) {
      std::cout << "Please, send only one integer number." << std::endl;
      std::cin.ignore(100, '\n');
      goto ask_input;
    }
    return input;
  }

  do {
    std::cout << "Do you really want to quit? (Y/N)" << std::endl;
    bool eof = std::cin.eof();
    if (std::cin.fail()) {
      std::cin.clear();
#ifdef __APPLE__
      clearerr(stdin);
#endif
    }

    if (!eof && std::cin.peek() != '\n')
      std::cin.ignore(100,'\n');

    std::cin >> exit_confirmation;
    exit_confirmation = toupper(exit_confirmation);
    if (exit_confirmation == 'N') goto ask_input;
    std::cout << "exit_confirmation must be either Y or N!" << std::endl;
  } while (exit_confirmation != 'Y');

  std::exit(0);
}

std::string get_string(std::string prompt) {
  char exit_confirmation;
  std::string input;
ask_input:
  std::cout << prompt;

  getline(std::cin, input);
  if (!std::cin.eof()) {
    return input;
  }

  do {
    std::cout << "Do you really want to quit? (Y/N)" << std::endl;
    bool eof = std::cin.eof();
    if (std::cin.fail()) {
      std::cin.clear();
#ifdef __APPLE__
      clearerr(stdin);
#endif
    }

    if (!eof && std::cin.peek() != '\n')
      std::cin.ignore(100,'\n');

    std::cin >> exit_confirmation;
    exit_confirmation = toupper(exit_confirmation);
    if (exit_confirmation == 'N') goto ask_input;
    std::cout << "exit_confirmation must be either Y or N!" << std::endl;
  } while (exit_confirmation != 'Y');

  std::exit(0);
}
