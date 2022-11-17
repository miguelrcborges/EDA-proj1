#include <iomanip>
#include <iostream>
#include "board.h"
#include "config.h"

extern const int board_side;

void Board::draw_board() {
  std::cout << PRINT_YELLOW;
  for (char i = 'A'; i < 'A' + BOARD_SIZE; i++)
    std::cout << std::setw(5) << i;
  std::cout << std::endl;


  for (int y = BOARD_SIZE - 1; y >= 0; y--) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      if (slots[x][y] == 'X')
        std::cout << PRINT_RED;
      else if (slots[x][y] == 'O')
        std::cout << PRINT_GREEN;
      std::cout << std::setw(5) << slots[x][y];
      }
    std::cout << std::endl;
  }
  std::cout << CLEAR_STYLE;


  std::cout << PRINT_YELLOW;
  for (char i = 'A'; i < 'A' + BOARD_SIZE; i++)
    std::cout << std::setw(5) << i;
  std::cout << std::endl;
  std::cout << CLEAR_STYLE;
}


bool Board::check_win(int last_move[2]) {

		bool win = false;

		for (int i = -3;i < 1;i++) {
			//horizontal win check
			if (!(win) && (i + last_move[0] > -1 && i + last_move[0] + TO_CONNECT - 1 < BOARD_SIZE)) { /*checks if horizontal limits are not crossed*/
				win = true;
				for (int n = 1;n < TO_CONNECT;n++) {
					if (slots[i + last_move[0]][last_move[1]] != slots[i + last_move[0] + n][last_move[1]]) {
						win = false;
						break;
					}
				}
			}
			//vertical win check
			if (!(win) && (i + last_move[1] > -1 && i + last_move[1] + TO_CONNECT - 1 < BOARD_SIZE)) {/*checks if vertical limits are not crossed*/
				win = true;
				for (int n = 1;n < TO_CONNECT;n++) {
					if (slots[last_move[0]][i + last_move[1]] != slots[last_move[0]][i + last_move[1] + n]) {
						win = false;
						break;
					}

				}

			}
			//negative diagonal win check
			if (!(win) && (i + last_move[1] > -1 && i + last_move[1] + TO_CONNECT - 1 < BOARD_SIZE) && (i + last_move[0] > -1 && i + last_move[0] + TO_CONNECT - 1 < BOARD_SIZE)) { /*checks if  limits are not crossed*/
				win = true;
				for (int n = 1;n < TO_CONNECT;n++) {
					if ((slots[i + last_move[0]][i + last_move[1]] != slots[i + last_move[0] + n][i + last_move[1] + n])) {
						win = false;
						break;

					}


				}
			}
			//positive diagonal win check
			if (!(win) && (-i + last_move[1] < BOARD_SIZE && -i + last_move[1] - TO_CONNECT + 1 >-1) && (i + last_move[0] > -1 && i + last_move[0] + TO_CONNECT - 1 < BOARD_SIZE)) { /*checks if limits are not crossed*/
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
	};
};

Board create_board() {
  Board board;
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int ii = 0; ii < BOARD_SIZE; ii++)
      board.slots[i][ii] = ' ';

  return board;
}
