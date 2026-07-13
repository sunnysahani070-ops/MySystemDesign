#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <memory>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

//=========================================================
// ENUMS
//=========================================================

enum class Direction {
    UP,
    DOWN,
    NONE
};

enum class ElevatorStatus {
    IDLE,
    MOVING_UP,
    MOVING_DOWN
};

enum class DoorState {
    OPEN,
    CLOSED
};

//=========================================================
// REQUEST CLASSES
//=========================================================

class Request {
protected:
    int floor;

public:
    Request(int floor) : floor(floor) {}

    virtual ~Request() {}

    int getFloor() const {
        return floor;
    }
};

class InternalRequest : public Request {
public:
    InternalRequest(int floor)
        : Request(floor) {}
};

class ExternalRequest : public Request {

private:
    Direction direction;

public:
    ExternalRequest(int floor, Direction direction)
        : Request(floor), direction(direction) {}

    Direction getDirection() const {
        return direction;
    }
};

//=========================================================
// OBSERVER PATTERN
//=========================================================

class Observer {
public:
    virtual void update(
        int elevatorId,
        int currentFloor,
        ElevatorStatus status
    ) = 0;

    virtual ~Observer() {}
};

class Subject {

protected:
    vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {

        observers.erase(
            remove(
                observers.begin(),
                observers.end(),
                observer
            ),
            observers.end()
        );
    }

protected:
    void notifyObservers(
        int elevatorId,
        int floor,
        ElevatorStatus status
    ) {

        for (auto observer : observers) {
            observer->update(
                elevatorId,
                floor,
                status
            );
        }
    }
};

//=========================================================
// DOOR
//=========================================================

class Door {

private:
    DoorState state;

public:
    Door() {
        state = DoorState::CLOSED;
    }

    void open() {

        if (state == DoorState::OPEN)
            return;

        state = DoorState::OPEN;

        cout << "Door Opened\n";
    }

    void close() {

        if (state == DoorState::CLOSED)
            return;

        state = DoorState::CLOSED;

        cout << "Door Closed\n";
    }

    DoorState getState() const {
        return state;
    }
};

//=========================================================
// FLOOR DISPLAY
//=========================================================

class FloorDisplay : public Observer {

public:

    void update(
        int elevatorId,
        int currentFloor,
        ElevatorStatus status
    ) override {

        cout << "[Floor Display] Elevator "
             << elevatorId
             << " is at Floor "
             << currentFloor
             << " ";

        if (status == ElevatorStatus::MOVING_UP)
            cout << "(UP)";

        else if (status == ElevatorStatus::MOVING_DOWN)
            cout << "(DOWN)";

        else
            cout << "(IDLE)";

        cout << endl;
    }
};

//=========================================================
// ELEVATOR DISPLAY
//=========================================================

class ElevatorDisplay {

private:
    int currentFloor;
    ElevatorStatus status;

public:

    ElevatorDisplay() {

        currentFloor = 0;
        status = ElevatorStatus::IDLE;
    }

    void updateDisplay(
        int floor,
        ElevatorStatus st
    ) {

        currentFloor = floor;
        status = st;

        cout << "[Elevator Display] Floor : "
             << currentFloor
             << " | ";

        if (status == ElevatorStatus::MOVING_UP)
            cout << "UP";

        else if (status == ElevatorStatus::MOVING_DOWN)
            cout << "DOWN";

        else
            cout << "IDLE";

        cout << endl;
    }

    int getCurrentFloor() const {
        return currentFloor;
    }
};

//=========================================================
// BUTTON CLASSES
//=========================================================

class Button {

public:
    virtual void press() = 0;

    virtual ~Button() {}
};

class HallButton : public Button {

private:
    int floor;
    Direction direction;

public:
    HallButton(
        int floor,
        Direction direction
    )
        : floor(floor),
          direction(direction) {}

    void press() override {

        cout << "Hall Button Pressed at Floor "
             << floor << endl;
    }

    int getFloor() const {
        return floor;
    }

    Direction getDirection() const {
        return direction;
    }
};

class ElevatorButton : public Button {

private:
    int destinationFloor;

public:
    ElevatorButton(int floor)
        : destinationFloor(floor) {}

    void press() override {

        cout << "Destination Selected : "
             << destinationFloor
             << endl;
    }

    int getDestinationFloor() const {
        return destinationFloor;
    }
};

//=========================================================
// STATE PATTERN
//=========================================================

class Elevator;

class ElevatorState {
public:
    virtual ~ElevatorState() = default;

    virtual void handleRequest(
        Elevator& elevator,
        int destinationFloor
    ) = 0;

    virtual void move(Elevator& elevator) = 0;

    virtual string getStateName() const = 0;
};

//=========================================================
// SINGLETON STATE DECLARATIONS
//=========================================================

class IdleState : public ElevatorState {
public:
    static IdleState& getInstance();

    void handleRequest(
        Elevator& elevator,
        int destinationFloor
    ) override;

    void move(Elevator& elevator) override;

    string getStateName() const override {
        return "IDLE";
    }
};

class MovingUpState : public ElevatorState {
public:
    static MovingUpState& getInstance();

    void handleRequest(
        Elevator& elevator,
        int destinationFloor
    ) override;

    void move(Elevator& elevator) override;

    string getStateName() const override {
        return "MOVING_UP";
    }
};

class MovingDownState : public ElevatorState {
public:
    static MovingDownState& getInstance();

    void handleRequest(
        Elevator& elevator,
        int destinationFloor
    ) override;

    void move(Elevator& elevator) override;

    string getStateName() const override {
        return "MOVING_DOWN";
    }
};

class DoorOpenState : public ElevatorState {
public:
    static DoorOpenState& getInstance();

    void handleRequest(
        Elevator& elevator,
        int destinationFloor
    ) override;

    void move(Elevator& elevator) override;

    string getStateName() const override {
        return "DOOR_OPEN";
    }
};

//=========================================================
// STATE SINGLETONS
//=========================================================

inline IdleState& IdleState::getInstance() {
    static IdleState instance;
    return instance;
}

inline MovingUpState& MovingUpState::getInstance() {
    static MovingUpState instance;
    return instance;
}

inline MovingDownState& MovingDownState::getInstance() {
    static MovingDownState instance;
    return instance;
}

inline DoorOpenState& DoorOpenState::getInstance() {
    static DoorOpenState instance;
    return instance;
}

//=========================================================
// HELPER FUNCTIONS
//=========================================================

inline string statusToString(ElevatorStatus status) {

    switch (status) {

    case ElevatorStatus::IDLE:
        return "IDLE";

    case ElevatorStatus::MOVING_UP:
        return "MOVING UP";

    case ElevatorStatus::MOVING_DOWN:
        return "MOVING DOWN";
    }

    return "UNKNOWN";
}

inline string directionToString(Direction direction) {

    switch (direction) {

    case Direction::UP:
        return "UP";

    case Direction::DOWN:
        return "DOWN";

    default:
        return "NONE";
    }
}
//=========================================================
// ELEVATOR
//=========================================================

class Elevator : public Subject {

private:

    int id;
    int currentFloor;

    ElevatorStatus status;

    Door door;

    ElevatorDisplay display;

    ElevatorState* currentState;

    set<int> upRequests;
    set<int, greater<int>> downRequests;

public:

    Elevator(int id)
        : id(id),
          currentFloor(0),
          status(ElevatorStatus::IDLE),
          currentState(&IdleState::getInstance()) {
    }

    //-----------------------------------------------------
    // Getters
    //-----------------------------------------------------

    int getId() const {
        return id;
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    ElevatorStatus getStatus() const {
        return status;
    }

    ElevatorState* getState() {
        return currentState;
    }

    Door& getDoor() {
        return door;
    }

    //-----------------------------------------------------
    // State Handling
    //-----------------------------------------------------

    void setState(ElevatorState* state) {
        currentState = state;
    }

    void setStatus(ElevatorStatus st) {
        status = st;
    }

    //-----------------------------------------------------
    // Floor Movement
    //-----------------------------------------------------

    void moveOneFloorUp() {

        currentFloor++;

        display.updateDisplay(
            currentFloor,
            status
        );

        notifyObservers(
            id,
            currentFloor,
            status
        );

        cout << "Elevator "
             << id
             << " reached Floor "
             << currentFloor
             << endl;
    }

    void moveOneFloorDown() {

        currentFloor--;

        display.updateDisplay(
            currentFloor,
            status
        );

        notifyObservers(
            id,
            currentFloor,
            status
        );

        cout << "Elevator "
             << id
             << " reached Floor "
             << currentFloor
             << endl;
    }

    //-----------------------------------------------------
    // Request Handling
    //-----------------------------------------------------

    void addRequest(int destinationFloor) {

        if (destinationFloor > currentFloor) {

            upRequests.insert(destinationFloor);
        }
        else if (destinationFloor < currentFloor) {

            downRequests.insert(destinationFloor);
        }
        else {

            cout << "Already at Floor "
                 << destinationFloor
                 << endl;

            door.open();
            door.close();
        }
    }

    bool hasUpRequests() const {

        return !upRequests.empty();
    }

    bool hasDownRequests() const {

        return !downRequests.empty();
    }

    int nextUpFloor() const {

        return *upRequests.begin();
    }

    int nextDownFloor() const {

        return *downRequests.begin();
    }

    void removeUpRequest() {

        if (!upRequests.empty())
            upRequests.erase(upRequests.begin());
    }

    void removeDownRequest() {

        if (!downRequests.empty())
            downRequests.erase(downRequests.begin());
    }

    //-----------------------------------------------------
    // Processing
    //-----------------------------------------------------

    void process() {

        currentState->move(*this);
    }

    void submitRequest(int floor) {

        currentState->handleRequest(
            *this,
            floor
        );
    }

    //-----------------------------------------------------
    // Door Operations
    //-----------------------------------------------------

    void openDoor() {

        door.open();
    }

    void closeDoor() {

        door.close();
    }
};
//=========================================================
// IDLE STATE
//=========================================================

void IdleState::handleRequest(
    Elevator& elevator,
    int destinationFloor
) {

    elevator.addRequest(destinationFloor);

    if (destinationFloor > elevator.getCurrentFloor()) {

        elevator.setStatus(ElevatorStatus::MOVING_UP);
        elevator.setState(&MovingUpState::getInstance());
    }
    else if (destinationFloor < elevator.getCurrentFloor()) {

        elevator.setStatus(ElevatorStatus::MOVING_DOWN);
        elevator.setState(&MovingDownState::getInstance());
    }
    else {

        elevator.openDoor();
        elevator.closeDoor();
    }
}

void IdleState::move(Elevator&) {

    // Elevator is idle.
}

//=========================================================
// MOVING UP STATE
//=========================================================

void MovingUpState::handleRequest(
    Elevator& elevator,
    int destinationFloor
) {

    elevator.addRequest(destinationFloor);
}

void MovingUpState::move(Elevator& elevator) {

    while (elevator.hasUpRequests()) {

        int target = elevator.nextUpFloor();

        while (elevator.getCurrentFloor() < target) {

            elevator.moveOneFloorUp();
        }

        elevator.openDoor();
        elevator.closeDoor();

        elevator.removeUpRequest();
    }

    if (elevator.hasDownRequests()) {

        elevator.setStatus(ElevatorStatus::MOVING_DOWN);
        elevator.setState(&MovingDownState::getInstance());
    }
    else {

        elevator.setStatus(ElevatorStatus::IDLE);
        elevator.setState(&IdleState::getInstance());
    }
}

//=========================================================
// MOVING DOWN STATE
//=========================================================

void MovingDownState::handleRequest(
    Elevator& elevator,
    int destinationFloor
) {

    elevator.addRequest(destinationFloor);
}

void MovingDownState::move(Elevator& elevator) {

    while (elevator.hasDownRequests()) {

        int target = elevator.nextDownFloor();

        while (elevator.getCurrentFloor() > target) {

            elevator.moveOneFloorDown();
        }

        elevator.openDoor();
        elevator.closeDoor();

        elevator.removeDownRequest();
    }

    if (elevator.hasUpRequests()) {

        elevator.setStatus(ElevatorStatus::MOVING_UP);
        elevator.setState(&MovingUpState::getInstance());
    }
    else {

        elevator.setStatus(ElevatorStatus::IDLE);
        elevator.setState(&IdleState::getInstance());
    }
}

//=========================================================
// DOOR OPEN STATE
//=========================================================

void DoorOpenState::handleRequest(
    Elevator& elevator,
    int destinationFloor
) {

    elevator.addRequest(destinationFloor);
}

void DoorOpenState::move(Elevator& elevator) {

    elevator.closeDoor();

    if (elevator.hasUpRequests()) {

        elevator.setStatus(ElevatorStatus::MOVING_UP);
        elevator.setState(&MovingUpState::getInstance());
    }
    else if (elevator.hasDownRequests()) {

        elevator.setStatus(ElevatorStatus::MOVING_DOWN);
        elevator.setState(&MovingDownState::getInstance());
    }
    else {

        elevator.setStatus(ElevatorStatus::IDLE);
        elevator.setState(&IdleState::getInstance());
    }
}
//=========================================================
// ELEVATOR CONTROLLER
//=========================================================

class ElevatorController {

private:

    vector<shared_ptr<Elevator>> elevators;


public:

    ElevatorController(
        int numberOfElevators
    ) {

        for(int i = 0; i < numberOfElevators; i++) {

            elevators.push_back(
                make_shared<Elevator>(i + 1)
            );
        }
    }


    //-----------------------------------------------------
    // Get Elevator
    //-----------------------------------------------------

    vector<shared_ptr<Elevator>>& getElevators() {

        return elevators;
    }


    //-----------------------------------------------------
    // Find Best Elevator
    //-----------------------------------------------------

    shared_ptr<Elevator> findBestElevator(
        int floor,
        Direction direction
    ) {


        shared_ptr<Elevator> best = nullptr;

        int minimumDistance = INT_MAX;


        for(auto elevator : elevators) {


            int distance =
                abs(
                    elevator->getCurrentFloor()
                    -
                    floor
                );


            if(distance < minimumDistance) {

                minimumDistance = distance;

                best = elevator;
            }
        }


        return best;
    }



    //-----------------------------------------------------
    // External Request
    //-----------------------------------------------------

    void handleExternalRequest(
        ExternalRequest request
    ) {


        auto elevator =
            findBestElevator(
                request.getFloor(),
                request.getDirection()
            );


        if(elevator) {


            cout
            << "\nController assigned Elevator "
            << elevator->getId()
            << " for Floor "
            << request.getFloor()
            << endl;


            elevator->submitRequest(
                request.getFloor()
            );
        }

    }



    //-----------------------------------------------------
    // Internal Request
    //-----------------------------------------------------

    void handleInternalRequest(
        int elevatorId,
        InternalRequest request
    ) {


        for(auto elevator : elevators) {


            if(elevator->getId() == elevatorId) {


                elevator->submitRequest(
                    request.getFloor()
                );


                return;
            }
        }
    }



    //-----------------------------------------------------
    // Run Elevators
    //-----------------------------------------------------

    void step() {


        for(auto elevator : elevators) {

            elevator->process();
        }

    }

};
//=========================================================
// BUILDING
//=========================================================

class Building {

private:

    int numberOfFloors;

    shared_ptr<ElevatorController> controller;

    vector<FloorDisplay> floorDisplays;


public:


    Building(
        int floors,
        int elevators
    )
        : numberOfFloors(floors)
    {


        controller =
            make_shared<ElevatorController>(
                elevators
            );


        //-------------------------------------------------
        // Create floor displays
        //-------------------------------------------------

        for(int i = 0; i < floors; i++) {

            floorDisplays.push_back(
                FloorDisplay()
            );
        }


        //-------------------------------------------------
        // Attach observers
        //-------------------------------------------------

        for(auto elevator :
            controller->getElevators()) {


            for(auto& display :
                floorDisplays) {


                elevator->addObserver(
                    &display
                );
            }
        }

    }



    //-----------------------------------------------------
    // Get Controller
    //-----------------------------------------------------

    shared_ptr<ElevatorController>
    getController() {

        return controller;
    }



    //-----------------------------------------------------
    // External Request
    //-----------------------------------------------------

    void requestElevator(
        int floor,
        Direction direction
    ) {


        ExternalRequest request(
            floor,
            direction
        );


        controller
        ->handleExternalRequest(
            request
        );

    }



    //-----------------------------------------------------
    // Select Floor Inside Elevator
    //-----------------------------------------------------

    void selectFloor(
        int elevatorId,
        int floor
    ) {


        InternalRequest request(
            floor
        );


        controller
        ->handleInternalRequest(
            elevatorId,
            request
        );

    }



    //-----------------------------------------------------
    // Run System
    //-----------------------------------------------------

    void run() {


        controller->step();

    }

};
//=========================================================
// MAIN FUNCTION
//=========================================================
int main() {
    cout << "=========================================\n";
    cout << "    Elevator System Initializing...      \n";
    cout << "=========================================\n";

    // 1. System Setup (10 Floors, 3 Elevators)
    Building building(10, 3);
    cout << "Infrastructure deployed successfully.\n\n";

    cout << "=========================================\n";
    cout << "     Executing Test Scenarios            \n";
    cout << "=========================================\n";

    // Scenario A: External Requests (Pressing hall buttons)
    cout << "[Floor Request] Passenger on Floor 3 wants to go UP\n";
    building.requestElevator(3, Direction::UP);
    
    cout << "[Floor Request] Passenger on Floor 8 wants to go DOWN\n";
    building.requestElevator(8, Direction::DOWN);

    // Tick the system once to process scheduling and initial dispatch
    cout << "\n--- System Tick 1: Scheduling ---\n";
    building.run(); 

    // Scenario B: Internal Requests (Pressing panel buttons inside the elevator)
    cout << "\n[Cabin Request] Passenger inside Elevator 1 selects Floor 7\n";
    building.selectFloor(1, 7);

    // Tick the system again to process movements and trigger Observer Displays
    cout << "\n--- System Tick 2: Processing Movement ---\n";
    building.run();

    cout << "\n=========================================\n";
    cout << "      Verification Suite Complete        \n";
    cout << "=========================================\n";

    return 0;
}