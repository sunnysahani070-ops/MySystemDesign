# Elevator System Design Pattern

This directory contains a low-level design (LLD) implementation for a multi-elevator system in a building, written in C++.

## Core Design Elements

- **Request Models**:
  - `Request` (Base class): Holds target floor.
  - `ExternalRequest`: Triggered from outside the elevator (hall call specifying floor and direction).
  - `InternalRequest`: Triggered inside the elevator (cab call specifying destination floor).
- **State Pattern**:
  - Elevator transitions between distinct states implemented as singletons:
    - `IdleState`: Elevator is stationary and idle.
    - `MovingUpState`: Elevator is moving upwards.
    - `MovingDownState`: Elevator is moving downwards.
    - `DoorOpenState`: Elevator doors are open for passengers.
- **Observer Pattern**:
  - Decoupled notification system to push state updates (floor level, direction, moving state) to:
    - `FloorDisplay` (Observer): Subscribes to elevator updates to display positions outside on building floors.
- **Display System**:
  - `ElevatorDisplay`: Integrated inside each elevator car to show status directly to passengers.
- **Button System**:
  - Extensible button components mapping physical interactions:
    - `HallButton` placed on building floors.
    - `ElevatorButton` inside elevator cabins.
- **Controller Dispatch Strategy**:
  - Built-in nearest-elevator assignment based on absolute distance to the requested floor.
- **Building Layout**:
  - `ElevatorController`: Manages and dispatches internal and external requests to the correct elevator.
  - `Building`: Represents the structural envelope housing floors, elevator units, and hall displays.

## Class Diagram Overview

![Elevator Design UML Diagram](ElevatorDesignUML.png)

### Mermaid Class Diagram

```mermaid
classDiagram
    class Request {
        #floor: int
        +getFloor() int
    }
    class ExternalRequest {
        -direction: Direction
        +getDirection() Direction
    }
    class InternalRequest {
    }
    Request <|-- ExternalRequest
    Request <|-- InternalRequest

    class ElevatorState {
        <<interface>>
        +handleRequest(Elevator& elevator, destinationFloor: int)*
        +move(Elevator& elevator)*
        +getStateName()* string
    }
    class IdleState {
        +getInstance() IdleState&
        +handleRequest(Elevator& elevator, destinationFloor: int)
        +move(Elevator& elevator)
    }
    class MovingUpState {
        +getInstance() MovingUpState&
        +handleRequest(Elevator& elevator, destinationFloor: int)
        +move(Elevator& elevator)
    }
    class MovingDownState {
        +getInstance() MovingDownState&
        +handleRequest(Elevator& elevator, destinationFloor: int)
        +move(Elevator& elevator)
    }
    class DoorOpenState {
        +getInstance() DoorOpenState&
        +handleRequest(Elevator& elevator, destinationFloor: int)
        +move(Elevator& elevator)
    }
    ElevatorState <|-- IdleState
    ElevatorState <|-- MovingUpState
    ElevatorState <|-- MovingDownState
    ElevatorState <|-- DoorOpenState

    class Observer {
        <<interface>>
        +update(elevatorId: int, currentFloor: int, status: ElevatorStatus)*
    }
    class FloorDisplay {
        +update(elevatorId: int, currentFloor: int, status: ElevatorStatus)
    }
    Observer <|-- FloorDisplay

    class Subject {
        #observers: vector~Observer*~
        +addObserver(Observer* observer)
        +removeObserver(Observer* observer)
        #notifyObservers(elevatorId: int, floor: int, status: ElevatorStatus)
    }
    Subject o-- Observer

    class Door {
        -state: DoorState
        +open()
        +close()
        +getState() DoorState
    }

    class ElevatorDisplay {
        -currentFloor: int
        -status: ElevatorStatus
        +updateDisplay(floor: int, status: ElevatorStatus)
        +getCurrentFloor() int
    }

    class Button {
        <<interface>>
        +press()*
    }
    class HallButton {
        -floor: int
        -direction: Direction
        +press()
        +getFloor() int
        +getDirection() Direction
    }
    class ElevatorButton {
        -destinationFloor: int
        +press()
        +getDestinationFloor() int
    }
    Button <|-- HallButton
    Button <|-- ElevatorButton

    class Elevator {
        -id: int
        -currentFloor: int
        -status: ElevatorStatus
        -door: Door
        -display: ElevatorDisplay
        -currentState: ElevatorState*
        -upRequests: set~int~
        -downRequests: set~int~
        +getId() int
        +getCurrentFloor() int
        +getStatus() ElevatorStatus
        +getState() ElevatorState*
        +setState(state: ElevatorState*)
        +setStatus(status: ElevatorStatus)
        +moveOneFloorUp()
        +moveOneFloorDown()
        +addRequest(destinationFloor: int)
        +process()
        +submitRequest(floor: int)
        +openDoor()
        +closeDoor()
    }
    Subject <|-- Elevator
    Elevator *-- Door
    Elevator *-- ElevatorDisplay
    Elevator o-- ElevatorState

    class ElevatorController {
        -elevators: vector~shared_ptr~Elevator~~
        +findBestElevator(floor: int, direction: Direction) shared_ptr~Elevator~
        +handleExternalRequest(request: ExternalRequest)
        +handleInternalRequest(elevatorId: int, request: InternalRequest)
        +step()
    }
    ElevatorController o-- Elevator

    class Building {
        -numberOfFloors: int
        -controller: shared_ptr~ElevatorController~
        -floorDisplays: vector~FloorDisplay~
        +requestElevator(floor: int, direction: Direction)
        +selectFloor(elevatorId: int, floor: int)
        +run()
    }
    Building *-- ElevatorController
    Building *-- FloorDisplay
```

## How to Run

To compile and run this implementation:
```bash
# Navigate to the ElevatorDesignPattern folder
cd ElevatorDesignPattern

# Compile the code
g++ -std=c++17 code.cpp -o elevator_design

# Run the executable
./elevator_design
```
