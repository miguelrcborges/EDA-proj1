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
	ofstream out;
	out.open("match logs.txt");
	if (game.board.check_win)
	{
		output_string = times_year << " - " << times_mon << " - " << times_day << " / " << times_hour << ":" << times_min 
			<< " - " << " 1)" << players[0].name << " vs 2)" << players[1].name << " - vencedor : ";
		if (players->is_computer)
		{
			output_string = +"(CPU) ";
		}
		if (players[turn % 2] == 0)
		{
			out << output_string << "1) " << players[0].name;
		}
		else
		{
			out << output_string << "2) " << players[1].name;
		}
	}
	out.close();
	return 1;

}

