# EDA project 01 – “Connect four” game

Group 01 elements:
* up202004481 – Miguel Rodrigues Carrilho Borges
* up202005141 - Francisco Rodrigues Camões de Magalhães
* up202008254 – Tomás Pereira Curralo Cruz

In this project, our group developed an application to play connect four, for 2 players. 
Each player can either be controlled with console inputs, by a user, or by moves generated by an AI.

The AI player is implemented using a min-max algorithm, similar to those used in AIs for games 
such as chess and go. This algorithm will search all possible move combinations up to a depth value,
selected by the user, and, assuming the opposing player plays perfectly, choses the move that will result 
in the quickest win or slowest loss. The higher this depth, the harder the AI will be to beat. The maximum 
value for the depth is set as 8, because higher values may cause performance issues (since the number of 
possible states grows exponentially for each increment), but a simple adjustment in the `config.h` file 
can alter this limit. At depth 0, the AI plays randomly.

Each player will make their play by choosing the column in which they will place their “disk”, 
represented in the game by a symbol that is different for both.

At the end of each game, the results will be registered in a .txt file, with the current time for the game 
start, and the user will be prompted to play again.

The user may at any time opt to end the game early, simply by inputting `ctrl + z` (for Windows users) 
or `ctrl + d` (for Unix-based systems users).

The game board will be displayed at the end of each turn, making the input format easier of use.

The application is safeguarded against invalid inputs by the user throughout the whole program, requesting 
another one, in such cases.
