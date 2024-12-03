#include "board.hpp"
#include "players.hpp"
#include <vector>

using namespace std;

int main() {
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

    for (auto player : player_array) {
        delete player;
    }

    return 0;
}