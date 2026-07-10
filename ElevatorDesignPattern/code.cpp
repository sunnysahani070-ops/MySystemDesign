#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

//=====================================================
// ENUMS
//=====================================================

enum class Direction {
    UP,
    DOWN
};

// Forward Declarations
class Elevator;
class ElevatorController;

//=====================================================
// REQUEST
//=====================================================

class Request {
public:
    virtual ~Request() = default;
};

class ExternalRequest : public Request {
private:
    int floor;
    Direction direction;

public:
    ExternalRequest(int floor, Direction direction)
        : floor(floor), direction(direction) {}

    int getFloor() const {
        return floor;
    }

    Direction getDirection() const {
        return direction;
    }
};

class InternalRequest : public Request {
private:
    int destinationFloor;

public:
    InternalRequest(int destinationFloor)
        : destinationFloor(destinationFloor) {}

    int getDestinationFloor() const {
        return destinationFloor;
    }
};

//=====================================================
// OBSERVER PATTERN
//=====================================================

class Observer {
public:
    virtual void update(Elevator* elevator) = 0;
    virtual ~Observer() = default;
};

//=====================================================
// STATE PATTERN
//=====================================================

class State {
public:
    virtual void handle(Elevator* elevator) = 0;
    virtual ~State() = default;
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

//=====================================================
// BUTTONS
//=====================================================

class Button {
public:
    virtual void press() = 0;
    virtual ~Button() = default;
};

class ExternalButton : public Button {
protected:
    int floorNumber;
    ElevatorController* controller;

public:
    ExternalButton(int floorNumber, ElevatorController* controller)
        : floorNumber(floorNumber),
          controller(controller) {}
};

class UpButton : public ExternalButton {
public:
    UpButton(int floorNumber, ElevatorController* controller)
        : ExternalButton(floorNumber, controller) {}

    void press() override {
        // TODO
    }
};

class DownButton : public ExternalButton {
public:
    DownButton(int floorNumber, ElevatorController* controller)
        : ExternalButton(floorNumber, controller) {}

    void press() override {
        // TODO
    }
};

class InternalButton : public Button {
private:
    int destinationFloor;
    Elevator* elevator;

public:
    InternalButton(int destinationFloor, Elevator* elevator)
        : destinationFloor(destinationFloor),
          elevator(elevator) {}

    void press() override {
        // TODO
    }
};

//=====================================================
// ELEVATOR
//=====================================================

class Elevator {
private:
    int id;
    int currentFloor;

    State* currentState;

    set<int> upRequests;
    set<int> downRequests;

    set<Observer*> observers;

public:
    Elevator(int id)
        : id(id),
          currentFloor(0),
          currentState(nullptr) {}

    void addRequest(Request* request) {
        // TODO
    }

    void move() {
        // TODO
    }

    void attachObserver(Observer* observer) {
        observers.insert(observer);
    }

    void detachObserver(Observer* observer) {
        observers.erase(observer);
    }

    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update(this);
        }
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    State* getCurrentState() const {
        return currentState;
    }

    void setState(State* state) {
        currentState = state;
    }
};

//=====================================================
// OBSERVERS
//=====================================================

class CabinDisplay : public Observer {
public:
    void update(Elevator* elevator) override {
        cout << "Cabin Display Updated\n";
    }
};

class FloorDisplay : public Observer {
public:
    void update(Elevator* elevator) override {
        cout << "Floor Display Updated\n";
    }
};

//=====================================================
// STATE IMPLEMENTATION
//=====================================================

void IdleState::handle(Elevator* elevator) {
    cout << "Idle State\n";
}

void MovingUpState::handle(Elevator* elevator) {
    cout << "Moving Up\n";
}

void MovingDownState::handle(Elevator* elevator) {
    cout << "Moving Down\n";
}

//=====================================================
// STRATEGY PATTERN
//=====================================================

class DispatchStrategy {
public:
    virtual Elevator* selectElevator(
        vector<Elevator*>& elevators,
        ExternalRequest* request) = 0;

    virtual ~DispatchStrategy() = default;
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

//=====================================================
// CONTROLLER
//=====================================================

class ElevatorController {
private:
    vector<Elevator*> elevators;
    DispatchStrategy* strategy;

public:
    ElevatorController(
        vector<Elevator*> elevators,
        DispatchStrategy* strategy)
        : elevators(elevators),
          strategy(strategy) {}

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

//=====================================================
// FLOOR
//=====================================================

class Floor {
private:
    int floorNumber;

    UpButton* upButton;
    DownButton* downButton;

public:
    Floor(int floorNumber,
          ElevatorController* controller)
        : floorNumber(floorNumber) {

        upButton = new UpButton(floorNumber, controller);
        downButton = new DownButton(floorNumber, controller);
    }

    int getFloorNumber() const {
        return floorNumber;
    }

    void pressUpButton() {
        upButton->press();
    }

    void pressDownButton() {
        downButton->press();
    }
};

//=====================================================
// BUILDING
//=====================================================

class Building {
private:
    int totalFloors;

    vector<Elevator*> elevators;

    ElevatorController* controller;

public:
    Building(int totalFloors,
             vector<Elevator*> elevators,
             ElevatorController* controller)
        : totalFloors(totalFloors),
          elevators(elevators),
          controller(controller) {}
};

//=====================================================
// MAIN
//=====================================================

int main() {

    return 0;
}