#include "game.h"
#include "board.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

void Game::game_loop()
{
	while (turn < BOARD_HEIGHT * BOARD_WIDTH) { 
		board.draw_board();
		players[(turn - 1) % 2].play(board);
		if (board.check_win(players[++turn % 2].last_move))
			break;
	}
  board.draw_board();
  if (board.check_win(players[turn % 2].last_move))
  {
	  std::cout << "Winner is " << players[turn % 2].name << "! Congratulations!" << std::endl;
  }
  else
  {
	  std::cout << "Draw!" << std::endl;
  }
  log_match();
}


Game create_game()
{
	Game game;
	game.turn = 1;
	game.players[0] = create_player(PLAYER_ONE_SYMBOL, "first");
	game.players[1] = create_player(PLAYER_TWO_SYMBOL, "second");
	game.board = create_board();
  time_t current_time = time(NULL);
	game.times = localtime(&current_time);
	return game;
}

int Game::log_match()
{
  std::ofstream out;
	out.open("match logs.txt", std::ios_base::app);
	out << times->tm_year+1900 << " - " << times->tm_mon+1 << " - " << times->tm_mday << " / " << times->tm_hour << ":" << times->tm_min << " - " << " 1) " << players[0].name;

	if (players[0].is_computer)
	{
		out << " (CPU - " << players[0].depth << ')'  ;
	}
	out << " vs 2) " << players[1].name;
	if (players[1].is_computer)
	{
		out << " (CPU - " << players[1].depth << ')' ;
	}
	if (board.check_win(players[turn % 2].last_move))
	{
		out << " - vencedor : ";
		if (turn % 2 == 0)
		{
			out << "1) " << players[0].name;
		}
		else
		{
			out << "2) " << players[1].name;
		}
		if (players[turn % 2].is_computer)
		{
			out << " (CPU - " << players[turn %2].depth << ')';
		}
	}
	else
	{
		out << " - Empate";
	}
  out << ".\n";
	out.close();
	return 1;

}

