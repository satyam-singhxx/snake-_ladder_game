#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <chrono>

using namespace std;

class Board {
private:
    unordered_map<int, int> snakes = {{25, 3}, {42, 1}, {56, 48}, {61, 43}, {92, 67}, {95, 12}, {98, 80}};
    unordered_map<int, int> ladders = {{7, 30}, {16, 33}, {20, 38}, {36, 83}, {50, 68}, {63, 81}, {71, 89}, {86, 97}};
    static const int WINNING_POSITION = 100;

public:
    int adjustPosition(int pos) {
        if (snakes.count(pos)) {
            cout << "Oh no! Bit by a snake! Sliding down from " << pos << " to " << snakes[pos] << endl;
            return snakes[pos];
        }
        if (ladders.count(pos)) {
            cout << "Yay! Climbing a ladder! Moving up from " << pos << " to " << ladders[pos] << endl;
            return ladders[pos];
        }
        return pos;
    }

    bool isWinningPosition(int pos) const {
        return pos == WINNING_POSITION;
    }

    int rollDice() const {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 6);
        return dis(gen);
    }
};

class Player {
private:
    string name;
    int position = 0;

public:
    explicit Player(const string &name) : name(name) {}

    string getName() const { return name; }
    int getPosition() const { return position; }

    void playTurn(Board &board) {
        int dice;
        do {
            cout << name << "'s turn! Press ENTER to roll the dice...";
            cin.ignore();
            dice = board.rollDice();
            cout << name << " rolled a " << dice << "!" << endl;

            if (position + dice <= 100) {
                position += dice;
                position = board.adjustPosition(position);
            } else {
                cout << "Can't move. Need exactly " << 100 - position << " to win." << endl;
            }

            cout << name << " is now at position " << position << "." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        } while (dice == 6 && !board.isWinningPosition(position));
    }

    bool hasWon(Board &board) const {
        return board.isWinningPosition(position);
    }
};

int main() {
    // Initialize players
    int playerCount;
    do {
        cout << "Enter the number of players (minimum 2): ";
        cin >> playerCount;
    } while (playerCount < 2);

    cin.ignore(); // To clear the input buffer for later use.

    vector<Player> players;
    cout << "Enter player names:" << endl;
    for (int i = 0; i < playerCount; ++i) {
        string name;
        cout << "Player " << i + 1 << ": ";
        cin >> name;
        players.emplace_back(name);
    }

    // Initialize board
    Board board;

    // Start the game
    cout << "Press ENTER to start the game...";
    cin.ignore();

    bool winnerFound = false;
    while (!winnerFound) {
        system("clear"); // Adjust for platform compatibility if needed
        cout << "Current Positions:" << endl;
        for (const auto &player : players) {
            cout << player.getName() << ": " << player.getPosition() << endl;
        }
        cout << endl;

        for (auto &player : players) {
            player.playTurn(board);
            if (player.hasWon(board)) {
                cout << endl << player.getName() << " has reached position 100 and won the game! Congratulations!" << endl;
                winnerFound = true;
                break;
            }
        }
    }

    cout << "Game Over. Thanks for playing!" << endl;
    return 0;
}