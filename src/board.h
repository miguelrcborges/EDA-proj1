#pragma once

#define CLEAR_SCR    "\033[2J\033[H"
#define PRINT_RED    "\033[91m"
#define PRINT_GREEN  "\033[92m"
#define PRINT_YELLOW "\033[93m"
#define CLEAR_STYLE  "\033[m"

typedef struct Board {
  /* 2D Matrix with all possible places to have chips (0s are ignored for convenience) */
  char slots[8][8];

  /* Function to draw the board on the console */
  void drawBoard(void);

  /** Method that checks if the game has ended in the current board state. it uses the last move for more efficiency
   * @param last_move Array containing the coordinantes of the last placed piece
   * @return If the game is over (true) or not.
   */
  bool checkWin(int last_move[2]);
} Board;
