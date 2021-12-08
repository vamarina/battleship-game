# battleship-game
Battleship game for one player implemented in C++

Game is implemented for only one user, who must guess ships’ location of computer.
Size of board is 10x10.
Number of ships is 10: one 4-square ship, two 3-square ships, three 2-square and four 1-square ships.
Ships cannot touch neither diagonally, nor horizontally, nor vertically.
Special symbols for free or shot fields: ‘X’ – for fired squares, ‘o’ – for shot, but not fired, ‘.’ - for not shot, ‘*’ - for not shot fields around killed ships
User must enter two digits, separated by ‘-’ symbol, one for row’s number and another for column’s, e. g. 0-9, ‘*’ - for viewing generated board, and ‘s’ - to stop game.
