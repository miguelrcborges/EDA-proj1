#include <iomanip>
#include <iostream>
#include "board.h"
#include "config.h"

extern const int board_side;

//draws the board according to its current state
void Board::draw_board() { 
  //draws the letter indexes in yellow at the top of the board
  std::cout << PRINT_YELLOW; //sets characters color to yellow
  for (char i = 'A'; i < 'A' + BOARD_WIDTH ; i++)
    std::cout << std::setw(5) << i;
  std::cout << std::endl;

  //draws positions, X in red and O in green, properly formated
  for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
      if (slots[x][y] == PLAYER_ONE_SYMBOL)
        std::cout << PRINT_RED; //sets characters color to red
      else if (slots[x][y] == PLAYER_TWO_SYMBOL)
        std::cout << PRINT_GREEN; //sets characters color to green
      std::cout << std::setw(5) << slots[x][y]; //prints the symbol slots[x][y], formatted by std::setw
      }
    std::cout << std::endl;
  }
  std::cout << CLEAR_STYLE;

  //draws the letter indexes in yellow at the bottom of the board
  std::cout << PRINT_YELLOW;
  for (char i = 'A'; i < 'A' + BOARD_WIDTH; i++)
    std::cout << std::setw(5) << i;
  std::cout << std::endl << std::endl;
  std::cout << CLEAR_STYLE;
}


bool Board::check_win(int last_move[2]) {
		bool win = false;

		for (int i = -3;i < 1;i++) {
			//horizontal win check
			if (!(win) && (i + last_move[0] > -1 && i + last_move[0] + TO_CONNECT - 1 < BOARD_WIDTH)) { /*checks if horizontal limits are not crossed and if another winning condition hasn't been already found*/
				win = true; /*assumes that there is a win for that line, and checks if every element is equal to the first one. if not, there is no win and the other positions of that particular line aren't checked*/
				for (int n = 1;n < TO_CONNECT;n++) {
					if (slots[i + last_move[0]][last_move[1]] != slots[i + last_move[0] + n][last_move[1]]) {
						win = false;
						break;
					}
				}
			}
			//vertical win check
			if (!(win) && (i + last_move[1] > -1 && i + last_move[1] + TO_CONNECT - 1 < BOARD_HEIGHT)) {/*checks if vertical limits are not crossed and if another winning condition hasn't been already found*/
				win = true;
				for (int n = 1;n < TO_CONNECT;n++) {
					if (slots[last_move[0]][i + last_move[1]] != slots[last_move[0]][i + last_move[1] + n]) {
						win = false;
						break;
					}

				}

			}
			//negative diagonal win check
			if (!(win) && (i + last_move[1] > -1 && i + last_move[1] + TO_CONNECT - 1 < BOARD_HEIGHT) && (i + last_move[0] > -1 && i + last_move[0] + TO_CONNECT - 1 < BOARD_WIDTH)) { /*checks if  limits are not crossed and if another winning condition hasn't been already found*/
				win = true;
				for (int n = 1;n < TO_CONNECT;n++) {
					if ((slots[i + last_move[0]][i + last_move[1]] != slots[i + last_move[0] + n][i + last_move[1] + n])) {
						win = false;
						break;

					}


				}
			}
			//positive diagonal win check
			if (!(win) && (-i + last_move[1] < BOARD_HEIGHT && -i + last_move[1] - TO_CONNECT + 1 >-1) && (i + last_move[0] > -1 && i + last_move[0] + TO_CONNECT - 1 < BOARD_WIDTH)) { /*checks if limits are not crossed and if another winning condition hasn't been already found*/
				win = true; 
				for (int n = 1;n < TO_CONNECT;n++) {
					if ((slots[i + last_move[0]][-i + last_move[1]] != slots[i + last_move[0] + n][-i + last_move[1] - n])) {
						win = false;
						break;
					}

				}
			}
		}
		return win;
}

//creates an empty board; used at the start of a new game to reset the board
Board create_board() {
  Board board;
  for (int i = 0; i < BOARD_WIDTH; i++)
    for (int ii = 0; ii < BOARD_HEIGHT; ii++)
      board.slots[i][ii] = ' ';

  return board;
}
