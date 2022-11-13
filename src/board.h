#pragma once

/** ANSI escape code to clear the screen. */
#define CLEAR_SCR    "\033[2J\033[H"
/** ANSI escape code to write in red. */
#define PRINT_RED    "\033[91m"
/** ANSI escape code to write in green. */
#define PRINT_GREEN  "\033[92m"
/** ANSI escape code to write in yellow. */
#define PRINT_YELLOW "\033[93m"
/** ANSI escape code to clear applied styles. */
#define CLEAR_STYLE  "\033[m"

/**
 * Our Board type. This type holds user the value of each slot, as well as functions related to the board.
 */
typedef struct Board {
  /** 2D Matrix with all possible places to have chips (0s are ignored for convenience). */
  char slots[7][7];

  /** Function to draw the board on the console. */
  void draw_board(void);

  /** 
   * Method that checks if the game has ended in the current board state. it uses the last move for more efficiency.
   * @param last_move Array containing the coordinantes of the last placed piece.
   * @return If the game is over (true) or not.
   */
  bool check_win(int last_move[2]);
} Board;


/**
 * Board initializer. Returns a Board with all slots set to ' '.
 */
Board create_board();
