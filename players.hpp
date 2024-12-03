#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class board;  // Forward declaration

class players {
private:
    string name;
    int position;
    bool complete;

public:
    players();
    void set_name(string name);
    string get_name();
    void set_position(int position);
    int get_position();
    void set_complete(bool complete);
    bool get_complete();
    void move();
};

#endif // PLAYERS_HPP