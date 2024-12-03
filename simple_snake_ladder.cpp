#include <iostream>
#include <bits/stdc++.h>
#include <random>

using namespace std;

class players;  // Forward declaration

class board {
    // private constructor
    board() {
        cout << "Game starts  !!!" << endl;
    }

    // deleting copy and assignment constructor
    board(const board &) = delete;
    board &operator=(const board &) = delete;

    // Snake and ladder declaration
    unordered_map<int, int> snakes = {{25, 3}, {42, 1}, {56, 48}, {61, 43}, {92, 67}, {95, 12}, {98, 80}};
    unordered_map<int, int> ladders = {{7, 30}, {16, 33}, {20, 38}, {36, 83}, {50, 68}, {63, 81}, {71, 89}, {86, 97}};

    // static private object
    static board *Board;

public:
    // winner status
    bool winner = false;

    // board instantiation
    static board *getBoard() {
        if (Board == NULL) {
            Board = new board();
            return Board;
        }
        return Board;
    }

    // board element movement
    int snake_ladder(int pos, players *player);

    // dice rolling
    int roll() {
        // random number generator
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 6);
        return dis(gen);
    }
};

class players {
    string name;
    int position = 0;
    bool complete = false;

public:
    // getter and setter
    void set_name(string name) {
        this->name = name;
    }

    string get_name() {
        return name;
    }

    void set_position(int position) {
        this->position = position;
    }

    int get_position() {
        return position;
    }

    void set_complete(bool complete) {
        this->complete = complete;
    }

    bool get_complete() {
        return complete;
    }

    // move
    void move() {
        board *Board = board::getBoard();
        int step;
        do {
            cout <<endl<< this->name << "'s Turn" << endl;
            cout << "Press ENTER to throw dice...";
            cin.ignore();
            cin.get();    // Capture the ENTER key press
            step = Board->roll();
            cout << "You Got a " << step << endl;
            if (step+position<=100) {
                position = Board->snake_ladder(position + step, this);
            }
            this_thread::sleep_for(std::chrono::seconds(1));
        } while (step == 6 && position!=100);
        
    }
};

// Static member initialization
board *board::Board = nullptr;

int board::snake_ladder(int pos, players *player) {
    if (snakes.find(pos) != snakes.end()) {
        cout << player->get_name() << " Bit by a snake!!!" << endl;
        return snakes[pos];
    }
    else if (ladders.find(pos) != ladders.end()) {
        cout << player->get_name() << " climbed a ladder!!!" << endl;
        return ladders[pos];
    }
    else {
        return pos;
    }
}

int main() {
    // player configuration
    int player_cnt = 0;
    while (player_cnt < 2) {
        cout << "Enter the number of players (at least 2): ";
        cin >> player_cnt;
    }
    vector<players *> player_array;
    for (int i = 0; i < player_cnt; i++) {
        player_array.push_back(new players());
    }

    cout << "Enter the names of players one by one: " << endl;
    for (auto player : player_array) {
        string name;
        cin >> name;
        player->set_name(name);
    }

    // board initialization
    board *Board = board::getBoard();
    cout << "Press ENTER to start the game...";
    cin.get();

    players *winner_plr = nullptr;
    while (!Board->winner) {
        system("clear"); 
        for (auto player : player_array) {
            cout << player->get_name() << " position -> " << player->get_position() << endl;
        }
        for (auto player : player_array) {
            player->move();
            if (player->get_position() == 100) {
                player->set_complete(true);
                winner_plr = player;
                Board->winner = true;
            }
        }
    }

    cout << endl << winner_plr->get_name() << " is the WINNER!!!" << endl;
    return 0;
}