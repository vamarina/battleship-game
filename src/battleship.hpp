//This program is a "Battleship" game
bool is_digit(const char &ch);
int get_verified_string (int& row, int& col);
void draw_board(const char arr[10][10]);
void init_board(char arr[10][10]);
bool set_ship(char comp_state[10][10], const int& row, const int& col, const int& ship_size, const int& direction);
void generate_game_state(char comp_state[10][10]);
bool is_fired(const char comp_state[10][10], const int& row, const int& col);
bool is_killed(const char comp_state[10][10], const char curr_state[10][10], const int& row, const int& col);
bool is_hitted(const char arr[10][10], const int& row, const int& col);
void set_around(char arr[10][10], const int& row, const int& col, const int& ship_size, const int& direction);
void run_game();
