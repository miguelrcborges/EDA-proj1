#include "game.h"
#include "board.h"
#include "player.h"
#include <iostream>
#include <string>
#include <ctime>

bool Game::game_loop()
{
	while (turn <= 49) {
		players[(turn - 1) % 2].play(board);
		if (!board.check_win(players[++turn % 2].last_move))
			break;
	}
	log_match();
	
}


Game create_game()
{
	Game game;
	game.turn = 1;
	game.players[0] = create_player('O');
	game.players[1] = create_player('X');
	game.board = create_board();
	game.times = localtime(time(NULL));
	return game;
}

int Game::log_match()
{
  std::ofstream out;
	out.open("match logs.txt");
	if (board.check_win())
	{
		out << times //2022 - 10 - 15 / 09:05 – 1)computador vs 2)Pedro Costa – vencedor : 2 .
	}
}

