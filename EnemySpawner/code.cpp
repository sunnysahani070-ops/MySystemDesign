#include <iostream>
#include <string>
using namespace std;

// Declare the EnemyFactory class and Enemy-related methods
class Enemy {
public:
    virtual int get_health() = 0;
    virtual int get_speed() = 0;
    virtual int get_attack_power() = 0;
    virtual string get_type() = 0;

    virtual ~Enemy() = default;
};
class Zombie : public Enemy {
    public:
    string get_type() override {
    return "Zombie";
}
    int get_health() override {
        return 50;

    }

    int get_speed() override {
        return 2;

    }

    int get_attack_power() override {
        return 10;

    }

};
class Vampire : public Enemy {
    public:
    string get_type() override {
    return "Vampire";
}
    int get_health() override {
        return 30;

    }

    int get_speed() override {
        return 4;

    }

    int get_attack_power() override {
        return 15;

    }

};
class Werewolf : public Enemy {
    public:
    string get_type() override {
    return "Werewolf";
}
    int get_health() override {
        return 80;

    }

    int get_speed() override {
        return 6;

    }

    int get_attack_power() override {
        return 25;

    }

};
class EnemyFactory {
public:
    Enemy* create_enemy(const string& difficulty) {
        if (difficulty == "Easy") {
            return new Zombie();
        }
        else if (difficulty == "Medium") {
            return new Vampire();
        }
        else if (difficulty == "Hard") {
            return new Werewolf();
        };

        return nullptr;
    }
};
// (User will implement these classes and methods)

int main() {
    // Input: Difficulty level
    string difficulty;
    cin >> difficulty;

    // Call the user's factory method to create the enemy
    EnemyFactory factory;
    Enemy* enemy = factory.create_enemy(difficulty);

    // Output in the specified format
    if (enemy != nullptr) {
        cout << "Enemy Type: " << enemy->get_type() << endl;
        cout << "Health: " << enemy->get_health() << endl;
        cout << "Speed: " << enemy->get_speed() << ", Attack Power: " << enemy->get_attack_power() << endl;

        // Clean up memory if necessary
        delete enemy;
    }

    return 0;
}
