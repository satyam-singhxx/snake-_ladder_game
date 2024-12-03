#include "players.hpp"
#include "board.hpp"

using namespace std;

players::players() : position(0), complete(false) {}

void players::set_name(string name) {
    this->name = name;
}

string players::get_name() {
    return name;
}

void players::set_position(int position) {
    this->position = position;
}

int players::get_position() {
    return position;
}

void players::set_complete(bool complete) {
    this->complete = complete;
}

bool players::get_complete() {
    return complete;
}

void players::move() {
    board *Board = board::getBoard();
    int step;
    do {
        cout << endl << name << "'s Turn" << endl;
        cout << "Press ENTER to throw dice...";
        cin.ignore();
        cin.get();
        step = Board->roll();
        cout << "You Got a " << step << endl;
        if (step + position <= 100) {
            position = Board->snake_ladder(position + step, this);
        }
        this_thread::sleep_for(chrono::seconds(1));
    } while (step == 6 && position != 100);
}