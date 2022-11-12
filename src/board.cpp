#include <iomanip>
#include <iostream>
#include "board.h"

void Board::draw_board() {
  std::cout << PRINT_YELLOW;

  for (char i = '1'; i <= '7'; i++)
    std::cout << std::setw(5) << i;
  std::cout << std::endl;

  for (int y = 0; y <= 7; y++) {
    for (int x = 0; x <= 7; x++) {
      if (slots[x][y] == 'X')
        std::cout << PRINT_RED;
      else if (slots[x][y] == 'O')
        std::cout << PRINT_GREEN;
      std::cout << std::setw(5) << slots[x][y];
      }
    std::cout << std::endl;
  }
  std::cout << CLEAR_STYLE;
}


bool Board::check_win(int last_move[2]) {

  /* There are 4 possible places a given piece can take in a winning move */
 for (int i = -3; i < 1; i++) { 

   /* Checks if horizontal limits are not crossed */
   if (i + last_move[0] > 0 && i + last_move[0] + 3 < 8) { 
     // horizontal win check
     if ((slots[i + last_move[0]][last_move[1]] == slots[i + last_move[0] + 1][last_move[1]]) && (slots[i + last_move[0] + 1][last_move[1]] == slots[i + last_move[0] + 2][last_move[1]]) && (slots[i + last_move[0] + 2][last_move[1]] == slots[i + last_move[0] + 3][last_move[1]]))
       return true;
   }

   /* Checks if vertical limits are not crossed */
   if (i + last_move[1] > 0 && i + last_move[1] + 3 < 8) { 
     // vertical win check
     if ((slots[last_move[0]][i + last_move[1]] == slots[last_move[0]][i + last_move[1] + 1]) && (slots[last_move[0]][i + last_move[1] + 1] == slots[last_move[0]][i + last_move[1] + 2]) && (slots[last_move[0]][i + last_move[1] + 2] == slots[last_move[0]][i + last_move[1] + 3]))
       return true;
   }

   /* Checks if negative diagonal limits are not crossed */
   if ((i + last_move[1] > 0 && i + last_move[1] + 3 < 8) && (i + last_move[0] > -1 && i + last_move[0] + 3 < 8)) { 
     // Negative diagonal win check
     if ((slots[i + last_move[0]][i + last_move[1]] == slots[i + last_move[0] + 1][i + last_move[1] + 1]) && (slots[i + last_move[0] + 1][i + last_move[1] + 1] == slots[i + last_move[0] + 2][i + last_move[1] + 2]) && (slots[i + last_move[0] + 2][i + last_move[1] + 2] == slots[i + last_move[0] + 3][i + last_move[1] + 3]))
       return true;
   }

   /* Checks if limits are not crossed */
   if ((-i + last_move[1] < 8 && -i + last_move[1] - 3 > 0) && (i + last_move[0] > -1 && i + last_move[0] + 3 < 8)) { 
     // Positive diagonal win check
     if ((slots[i + last_move[0]][-i + last_move[1]] == slots[i + last_move[0] + 1][-i + last_move[1] - 1]) && (slots[i + last_move[0] + 1][-i + last_move[1] - 1] == slots[i + last_move[0] + 2][-i + last_move[1] - 2]) && (slots[i + last_move[0] + 2][-i + last_move[1] - 2] == slots[i + last_move[0] + 3][-i + last_move[1] - 3]))
       return true;
   }
 }

 return false;
}
