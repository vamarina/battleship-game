//This program is a "Battleship" game
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "battleship.hpp"

//Check if input is digit
bool is_digit(const char &ch)
{
    if (ch < '0' || ch > '9')  {
        return false;
    }
    return true;
}

/*Ask input until get 2 digits separated by "-" symbol (get digits in parameters), '*' for viewing guessing board, 's' to stop game
Return 0 if input is verified for next step, 1 for viewing guessing board, 2 to stop
*/
int get_verified_string (int& row, int& col)
{
    std::string tmp_str("");
    int tmp_num = 0;
    while (true) {
        getline(std::cin, tmp_str);
        if (1 == tmp_str.size()) {
            if ('*' == tmp_str[0]) {
                return 1;
            } else if ('s' == tmp_str[0]) {
                return 2;
            }
        } else if (3 == tmp_str.size()) {
            if (is_digit(tmp_str[0]) && is_digit(tmp_str[2]) && '-' == tmp_str[1]) {
                row = tmp_str[0] - '0';
                col = tmp_str[2] - '0';
                return 0;
            }
        }
        std::cout << "Your input is incorrect. Please try again." << std::endl;
    }
}

//draw board with given state
void draw_board(const char arr[10][10])
{
    if (arr != NULL) {
        std::cout << "  0 1 2 3 4 5 6 7 8 9" << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::cout << i;
            for (int j = 0; j < 10; ++j) {
                std::cout << " " << arr[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

//board initialization
void init_board(char arr[10][10])
{
    if (arr != NULL) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                arr[i][j] = '.';
            }
        }
    }
}

//set ship by given parameters after checking
bool set_ship(char comp_state[10][10], const int& row, const int& col, const int& ship_size, const int& direction)
{
    int size_x = (0 == direction) ? ship_size : 1;    //horizontal
    int size_y = (1 == direction) ? ship_size : 1;    //vertical

    if (row + size_y > 10 || col + size_x > 10) {
        return false;
    }
    for (int i = row - 1; i < row + size_y + 1; ++i) {
        if (i < 0 || i > 9) {
            continue;
        } else {
            for (int j = col - 1; j < col + size_x + 1; ++j) {
                if (j < 0 || j > 9) {
                    continue;
                } else if (comp_state[i][j] != '.') {
                    return false;
                }
            }
        }
    }
    for (int i = row; i < row + size_y; ++i) {
        for (int j = col; j < col + size_x; ++j) {
            comp_state[i][j] = 'X';
        }
    }
    return true;
}

//generate board with ships to start game
void generate_game_state(char comp_state[10][10])
{
    //generate random numbers in the given interval
    std::srand(time(0));
    int row = rand() % 10;
    int col = rand() % 10;
    int dir = rand() % 2;

    for (int ship_size = 4; ship_size > 0; --ship_size) {
        for (int j = 0; j <= 4 - ship_size; ++j) {
            while (!set_ship(comp_state, row, col, ship_size, dir)) {
                row = rand() % 10;
                col = rand() % 10;
                dir = rand() % 2;  //0 for horizontal, 1 for vertical direction
            }
        }
    }
}

//check if input shoots the ship
bool is_fired(const char comp_state[10][10], const int& row, const int& col)
{
    if (comp_state != NULL) {
        if ('.' == comp_state[row][col]) {
            return false;
        } else {
            return true;
        }
    }
}

//check if ship has been killed
bool is_killed(const char comp_state[10][10], char curr_state[10][10], const int& row, const int& col)
{
    int up_row = row - 1;
    int down_row = row + 1;
    int left_col = col - 1;
    int right_col = col + 1;
    int dir = 0;   //0 - horizontal, 1 vertical
    int ship_size = 1;

    while ((-1 != up_row && 'X' == comp_state[up_row][col])
            || (10 != down_row && 'X' == comp_state[down_row][col])) {
        ++ship_size;
        dir = 1;
        if ('X' == curr_state[up_row][col]) {
            --up_row;
        } else if ('X' == curr_state[down_row][col]) {
            ++down_row;
        } else {
            return false;
        }
    }
    if (0 == dir) {
        while ((-1 != left_col && 'X' == comp_state[row][left_col])
                || (10 != right_col && 'X' == comp_state[row][right_col])) {
            ++ship_size;
            if ('X' == curr_state[row][left_col]) {
                --left_col;
            } else if ('X' == curr_state[row][right_col]) {
                ++right_col;
            } else {
                return false;
            }
        }
    }
    if (0 == dir) {
        set_around(curr_state, row, left_col + 1, ship_size, dir);
    } else {
        set_around(curr_state, up_row + 1, col, ship_size, dir);
    }
    return true;
}

//check if input was asked before or is around killed ship
bool is_hitted(const char arr[10][10], const int& row, const int& col)
{
    if (arr != NULL) {
        if ('.' == arr[row][col]) {
            return false;
        } else {
            return true;
        }
    }
}

//set "*" around killed ship with given size, direction and first field (top or left depends on direction). "*" is set in fields which wasn't hit before
void set_around(char arr[10][10], const int& row, const int& col, const int& ship_size, const int& direction)
{
    int size_x = (0 == direction) ? ship_size : 1;  //horizontal ship
    int size_y = (1 == direction) ? ship_size : 1;  //vertical ship

    for (int i = row - 1; i < row + size_y + 1; ++i) {
        if (i < 0 || i > 9) {
            continue;
        } else {
            for (int j = col - 1; j < col + size_x + 1; ++j) {
                if (j < 0 || j > 9) {
                    continue;
                } else if ('.' == arr[i][j]) {
                    arr[i][j] = '*';
                }
            }
        }
    }
}

//generate game board and ask for input till game over or user decides to stop the game
void run_game()
{
    char game_board[10][10];
    char curr_board[10][10];
    int ships_count = 0;
    int row = 0;
    int col = 0;

    init_board(game_board);
    init_board(curr_board);
    generate_game_state(game_board);

    std::cout << "Please enter \n- 2 digits separated by '-' symbol (1st digit for row, 2nd for column, e.g. 1-5) for each attempt,\n- '*' for viewing guessing board and\n- 's' to stop the game\n" << std::endl;

    int get_ver = get_verified_string(row, col);
    while (2 != get_ver) {  //while "s" (key to stop game) was not entered
        if (1 == get_ver) { //if "*" (key for viewing game board) is entered
            draw_board(game_board);
        } else if (!is_hitted(curr_board, row, col)) {
            if (is_fired(game_board, row, col)) {
                curr_board[row][col] = 'X';
                if (is_killed(game_board, curr_board, row, col)) {
                    ++ships_count;
                    if (10 == ships_count) {
                        std::cout << "Game over. You've guessed all ships." << std::endl;
                        draw_board(curr_board);
                        break;
                    }
                    std::cout << "Ship has been killed." << std::endl;
                } else {
                    std::cout << "Ship has been fired." << std::endl;
                }
            } else {
                curr_board[row][col] = 'o';
                std::cout << "You've missed. Try again." << std::endl;
            }
            draw_board(curr_board);
        } else {
            std::cout << "This field has been hit, fired or around killed ship. Try again." << std::endl;
        }
        get_ver = get_verified_string(row, col);
    }
}
