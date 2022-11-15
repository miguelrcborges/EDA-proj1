#include "game.h"
#include "player.h"
#include <iostream>
#include <cctype>
#include <cstdlib>

int main() {
  srand(time(NULL));
  for (; ;) {
    Game game = create_game();
    game.game_loop();
    for (; ;) {
      char input = get_input("Do you want to play again? (Y/N)\n> ");
      input = toupper(input);
      if (input == 'Y') break;
      else if (input == 'N') return 0;
      std::cout << "The input must be either Y or N!" << std::endl;
    }
  }
}
