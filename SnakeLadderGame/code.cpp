#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

//=========================================================
// JUMPER CLASS (BASE CLASS FOR SNAKES & LADDERS)
//=========================================================
class Jumper {
protected:
    int start;
    int end;

public:
    Jumper(int start, int end) : start(start), end(end) {}
    virtual ~Jumper() = default;

    int getStart() const { return start; }
    int getEnd() const { return end; }
    
    virtual string getType() const = 0;
};

//=========================================================
// CONCRETE JUMPERS
//=========================================================
class Snake : public Jumper {
public:
    Snake(int start, int end) : Jumper(start, end) {
        if (start <= end) {
            throw invalid_argument("Snake start must be greater than end position!");
        }
    }

    string getType() const override {
        return "Snake";
    }
};

class Ladder : public Jumper {
public:
    Ladder(int start, int end) : Jumper(start, end) {
        if (start >= end) {
            throw invalid_argument("Ladder start must be less than end position!");
        }
    }

    string getType() const override {
        return "Ladder";
    }
};

//=========================================================
// DICE CLASS
//=========================================================
class Dice {
private:
    int numberOfDice;

public:
    Dice(int count = 1) : numberOfDice(count) {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    int roll() const {
        int totalRoll = 0;
        for (int i = 0; i < numberOfDice; ++i) {
            totalRoll += (rand() % 6) + 1;
        }
        return totalRoll;
    }
};

//=========================================================
// PLAYER CLASS
//=========================================================
class Player {
private:
    int id;
    string name;
    int position;

public:
    Player(int id, const string& name) : id(id), name(name), position(0) {}

    int getId() const { return id; }
    string getName() const { return name; }
    
    int getPosition() const { return position; }
    void setPosition(int pos) { position = pos; }
};

//=========================================================
// BOARD CLASS
//=========================================================
class Board {
private:
    int size;
    unordered_map<int, shared_ptr<Jumper>> jumpers;

public:
    Board(int size = 100) : size(size) {}

    int getSize() const { return size; }

    void addJumper(shared_ptr<Jumper> jumper) {
        jumpers[jumper->getStart()] = jumper;
    }

    shared_ptr<Jumper> getJumperAt(int position) const {
        auto it = jumpers.find(position);
        if (it != jumpers.end()) {
            return it->second;
        }
        return nullptr;
    }
};

//=========================================================
// GAME CLASS (MANAGES GAME STATE & LOOP)
//=========================================================
class Game {
private:
    shared_ptr<Board> board;
    shared_ptr<Dice> dice;
    queue<shared_ptr<Player>> players;
    vector<shared_ptr<Player>> leaderboard;

public:
    Game(shared_ptr<Board> b, shared_ptr<Dice> d, const vector<shared_ptr<Player>>& playerList) 
        : board(b), dice(d) {
        for (const auto& player : playerList) {
            players.push(player);
        }
    }

    void start() {
        cout << "=========================================\n";
        cout << "   Snake and Ladder Game Initializing... \n";
        cout << "=========================================\n";
        cout << "Board Size: " << board->getSize() << "\n";
        cout << "Players in Game: " << players.size() << "\n\n";

        while (players.size() > 1) {
            shared_ptr<Player> currentPlayer = players.front();
            players.pop();

            int rollValue = dice->roll();
            int currentPos = currentPlayer->getPosition();
            int nextPos = currentPos + rollValue;

            cout << "[Turn] " << currentPlayer->getName() << " rolled a " << rollValue 
                 << ". Move: " << currentPos << " -> ";

            if (nextPos > board->getSize()) {
                cout << currentPos << " (exceeds board size " << board->getSize() << ", turn skipped)\n";
                players.push(currentPlayer);
                continue;
            }

            // Check for Snakes or Ladders
            shared_ptr<Jumper> jumper = board->getJumperAt(nextPos);
            if (jumper) {
                cout << nextPos << " (" << jumper->getType() << " hit!) -> ";
                nextPos = jumper->getEnd();
            }

            currentPlayer->setPosition(nextPos);
            cout << nextPos << "\n";

            if (nextPos == board->getSize()) {
                cout << "🏆 " << currentPlayer->getName() << " has reached the destination and won!\n";
                leaderboard.push_back(currentPlayer);
            } else {
                players.push(currentPlayer);
            }
        }

        // Add the last remaining player to the leaderboard
        if (!players.empty()) {
            leaderboard.push_back(players.front());
            players.pop();
        }

        printLeaderboard();
    }

private:
    void printLeaderboard() {
        cout << "\n=========================================\n";
        cout << "               Leaderboard               \n";
        cout << "=========================================\n";
        for (size_t i = 0; i < leaderboard.size(); ++i) {
            cout << i + 1 << ". " << leaderboard[i]->getName();
            if (i == 0) cout << " 🥇";
            cout << "\n";
        }
        cout << "=========================================\n";
    }
};

//=========================================================
// MAIN FUNCTION (TEST RUN)
//=========================================================
int main() {
    // 1. Create a 100-cell board
    auto board = make_shared<Board>(100);

    // 2. Add Snakes
    board->addJumper(make_shared<Snake>(99, 54));
    board->addJumper(make_shared<Snake>(70, 55));
    board->addJumper(make_shared<Snake>(52, 29));
    board->addJumper(make_shared<Snake>(25, 2));
    board->addJumper(make_shared<Snake>(95, 72));

    // 3. Add Ladders
    board->addJumper(make_shared<Ladder>(6, 25));
    board->addJumper(make_shared<Ladder>(11, 40));
    board->addJumper(make_shared<Ladder>(60, 85));
    board->addJumper(make_shared<Ladder>(46, 90));
    board->addJumper(make_shared<Ladder>(17, 69));

    // 4. Create single 6-sided dice
    auto dice = make_shared<Dice>(1);

    // 5. Create players
    vector<shared_ptr<Player>> players = {
        make_shared<Player>(1, "Alice"),
        make_shared<Player>(2, "Bob"),
        make_shared<Player>(3, "Charlie")
    };

    // 6. Initialize and start game
    Game game(board, dice, players);
    game.start();

    return 0;
}
