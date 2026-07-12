# Elevator System Design Pattern

This directory contains a low-level design (LLD) implementation for a multi-elevator system in a building, written in C++.

## Core Design Elements

- **Request Models**:
  - `Request` (Base class)
  - `ExternalRequest`: Triggered from outside the elevator (hall call specifying floor and direction).
  - `InternalRequest`: Triggered inside the elevator (cab call specifying destination floor).
- **State Pattern**:
  - Elevator transitions smoothly between states:
    - `IdleState`: Elevator is stationary.
    - `MovingUpState`: Elevator is traversing upwards.
    - `MovingDownState`: Elevator is traversing downwards.
- **Observer Pattern**:
  - Decoupled notification system to push state updates (floor level, direction, moving state) to:
    - `CabinDisplay`: Inside the elevator cabin.
    - `FloorDisplay`: Outside on individual floors.
- **Button System**:
  - Extensible button components mapping physical interactions:
    - `ExternalButton` (implemented as `UpButton` and `DownButton`) placed on building floors.
    - `InternalButton` inside elevator cars.
- **Strategy Pattern (Dispatching Strategy)**:
  - Supports pluggable scheduling strategies:
    - `NearestStrategy`: Selects the closest elevator to service the request.
    - `LeastLoadedStrategy`: Selects the elevator with the minimum pending load/requests.
- **Controller & Building Layout**:
  - `Floor`: Represents physical floors with up/down buttons.
  - `ElevatorController`: Manages state and dispatches requests.
  - `Building`: Represents the structural envelope housing floors and elevator units.

## Class Diagram Overview

![Elevator Design UML Diagram](ElevatorDesignUML.png)

### Mermaid Class Diagram

```mermaid
classDiagram
    class Request {
        <<interface>>
    }
    class ExternalRequest {
        -floor: int
        -direction: Direction
        +getFloor() int
        +getDirection() Direction
    }
    class InternalRequest {
        -destinationFloor: int
        +getDestinationFloor() int
    }
    Request <|-- ExternalRequest
    Request <|-- InternalRequest

    class State {
        <<interface>>
        +handle(Elevator* elevator)*
    }
    class IdleState {
        +handle(Elevator* elevator)
    }
    class MovingUpState {
        +handle(Elevator* elevator)
    }
    class MovingDownState {
        +handle(Elevator* elevator)
    }
    State <|-- IdleState
    State <|-- MovingUpState
    State <|-- MovingDownState

    class Observer {
        <<interface>>
        +update(Elevator* elevator)*
    }
    class CabinDisplay {
        +update(Elevator* elevator)
    }
    class FloorDisplay {
        +update(Elevator* elevator)
    }
    Observer <|-- CabinDisplay
    Observer <|-- FloorDisplay

    class Button {
        <<interface>>
        +press()*
    }
    class ExternalButton {
        #floorNumber: int
        #controller: ElevatorController*
    }
    class UpButton {
        +press()
    }
    class DownButton {
        +press()
    }
    class InternalButton {
        -destinationFloor: int
        -elevator: Elevator*
        +press()
    }
    Button <|-- ExternalButton
    Button <|-- InternalButton
    ExternalButton <|-- UpButton
    ExternalButton <|-- DownButton

    class Floor {
        -floorNumber: int
        -upButton: UpButton*
        -downButton: DownButton*
        +getFloorNumber() int
        +pressUpButton()
        +pressDownButton()
    }
    Floor *-- UpButton
    Floor *-- DownButton

    class Elevator {
        -id: int
        -currentFloor: int
        -currentState: State*
        -upRequests: set<int>
        -downRequests: set<int>
        -observers: set<Observer*>
        +addRequest(Request* request)
        +move()
        +attachObserver(Observer* observer)
        +detachObserver(Observer* observer)
        +notifyObservers()
        +getCurrentFloor() int
        +getCurrentState() State*
        +setState(State* state)
    }
    Elevator *-- State
    Elevator o-- Observer

    class DispatchStrategy {
        <<interface>>
        +selectElevator(elevators, request)* Elevator*
    }
    class NearestStrategy {
        +selectElevator(elevators, request) Elevator*
    }
    class LeastLoadedStrategy {
        +selectElevator(elevators, request) Elevator*
    }
    DispatchStrategy <|-- NearestStrategy
    DispatchStrategy <|-- LeastLoadedStrategy

    class ElevatorController {
        -elevators: vector<Elevator*>
        -strategy: DispatchStrategy*
        +handleExternalRequest(ExternalRequest* request)
        +setDispatchStrategy(DispatchStrategy* newStrategy)
    }
    ElevatorController *-- DispatchStrategy
    ElevatorController o-- Elevator

    class Building {
        -totalFloors: int
        -elevators: vector<Elevator*>
        -controller: ElevatorController*
    }
    Building *-- ElevatorController
    Building o-- Elevator
```

## How to Run

To compile and run this implementation:
```bash
# Navigate to the ElevatorDesignPattern folder
cd ElevatorDesignPattern

# Compile the code
g++ -std=c++11 code.cpp -o elevator_design

# Run the executable
./elevator_design
```
