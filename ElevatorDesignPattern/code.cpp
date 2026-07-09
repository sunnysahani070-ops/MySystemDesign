#include <iostream>
#include <vector>
#include <set>

using namespace std;

//====================== REQUEST ======================

class Request {
public:
    virtual ~Request() {}
};

enum class Direction {
    UP,
    DOWN
};

class ExternalRequest : public Request {
private:
    int floor;
    Direction direction;

public:
    ExternalRequest(int floor, Direction direction)
        : floor(floor), direction(direction) {}
};

class InternalRequest : public Request {
private:
    int destinationFloor;

public:
    InternalRequest(int destinationFloor)
        : destinationFloor(destinationFloor) {}
};

//====================== STATE PATTERN ======================

class Elevator;

class State {
public:
    virtual void handle(Elevator* elevator) = 0;
    virtual ~State() {}
};

class IdleState : public State {
public:
    void handle(Elevator* elevator) override;
};

class MovingUpState : public State {
public:
    void handle(Elevator* elevator) override;
};

class MovingDownState : public State {
public:
    void handle(Elevator* elevator) override;
};

//====================== ELEVATOR ======================

class Elevator {
private:
    int id;
    int currentFloor;

    State* currentState;

    set<int> upRequests;
    set<int> downRequests;

public:
    Elevator(int id)
        : id(id), currentFloor(0), currentState(nullptr) {}

    void addRequest(Request* request) {
        // Will implement later
    }

    void move() {
        // Will implement later
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    State* getState() const {
        return currentState;
    }

    void setState(State* state) {
        currentState = state;
    }
};

//====================== STATE IMPLEMENTATION ======================

void IdleState::handle(Elevator* elevator) {
    cout << "Elevator is idle\n";
}

void MovingUpState::handle(Elevator* elevator) {
    cout << "Elevator moving up\n";
}

void MovingDownState::handle(Elevator* elevator) {
    cout << "Elevator moving down\n";
}

//====================== STRATEGY PATTERN ======================

class DispatchStrategy {
public:
    virtual Elevator* selectElevator(
        vector<Elevator*>& elevators,
        ExternalRequest* request) = 0;

    virtual ~DispatchStrategy() {}
};

class NearestStrategy : public DispatchStrategy {
public:
    Elevator* selectElevator(
        vector<Elevator*>& elevators,
        ExternalRequest* request) override {

        cout << "Nearest Strategy\n";

        return nullptr;
    }
};

class LeastLoadedStrategy : public DispatchStrategy {
public:
    Elevator* selectElevator(
        vector<Elevator*>& elevators,
        ExternalRequest* request) override {

        cout << "Least Loaded Strategy\n";

        return nullptr;
    }
};

//====================== CONTROLLER ======================

class ElevatorController {
private:
    vector<Elevator*> elevators;
    DispatchStrategy* strategy;

public:
    ElevatorController(vector<Elevator*> elevators,
                       DispatchStrategy* strategy)
        : elevators(elevators), strategy(strategy) {}

    void handleExternalRequest(ExternalRequest* request) {

        Elevator* elevator =
            strategy->selectElevator(elevators, request);

        if (elevator != nullptr) {
            elevator->addRequest(request);
        }
    }

    void setDispatchStrategy(DispatchStrategy* newStrategy) {
        strategy = newStrategy;
    }
};

//====================== BUILDING ======================

class Building {
private:
    int totalFloors;

    vector<Elevator*> elevators;

    ElevatorController* controller;

public:
    Building(int floors,
             vector<Elevator*> elevators,
             ElevatorController* controller)
        : totalFloors(floors),
          elevators(elevators),
          controller(controller) {}
};

//====================== MAIN ======================

int main() {

    Elevator* e1 = new Elevator(1);
    Elevator* e2 = new Elevator(2);
    Elevator* e3 = new Elevator(3);

    vector<Elevator*> elevators = {e1, e2, e3};

    DispatchStrategy* strategy = new NearestStrategy();

    ElevatorController* controller =
        new ElevatorController(elevators, strategy);

    Building building(10, elevators, controller);

    return 0;
}
