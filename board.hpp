#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <unordered_map>
#include <random>
#include <string>
#include "players.hpp"

using namespace std;

class board {
private:
    board();
    board(const board &) = delete;
    board &operator=(const board &) = delete;

    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;

    static board *Board;

public:
    bool winner;

    static board *getBoard();
    int snake_ladder(int pos, players *player);
    int roll();
};

#endif // BOARD_HPP