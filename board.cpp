#include "board.hpp"

using namespace std;

board *board::Board = nullptr;

board::board() 
    : snakes({{25, 3}, {42, 1}, {56, 48}, {61, 43}, {92, 67}, {95, 12}, {98, 80}}),
      ladders({{7, 30}, {16, 33}, {20, 38}, {36, 83}, {50, 68}, {63, 81}, {71, 89}, {86, 97}}),
      winner(false) {
    cout << "Game starts !!!" << endl;
}

board *board::getBoard() {
    if (Board == nullptr) {
        Board = new board();
    }
    return Board;
}

int board::snake_ladder(int pos, players *player) {
    if (snakes.find(pos) != snakes.end()) {
        cout << player->get_name() << " Bit by a snake!!!" << endl;
        return snakes[pos];
    } else if (ladders.find(pos) != ladders.end()) {
        cout << player->get_name() << " climbed a ladder!!!" << endl;
        return ladders[pos];
    } else {
        return pos;
    }
}

int board::roll() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}