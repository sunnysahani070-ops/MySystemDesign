# My System Design

Welcome to the **My System Design** repository. This repository serves as a collection of various low-level and high-level system design patterns, architectures, and implementations.

As the collection grows, more design implementations, design patterns, and case studies will be documented and added here.

---

## Table of Contents

- [Implemented Designs](#implemented-designs)
  - [1. Elevator System Design Pattern](#1-elevator-system-design-pattern)
- [Future Designs](#future-designs)
- [How to Run](#how-to-run)

---

## Implemented Designs

### 1. Elevator System Design Pattern
Located in the [`ElevatorDesignPattern`](./ElevatorDesignPattern) directory.

This project implements a low-level design (LLD) for a multi-elevator system in a building. The implementation uses core Object-Oriented Design (OOD) principles and structural/behavioral design patterns in C++.

#### Core Design Elements:
- **Request Models**:
  - `Request` (Base class)
  - `ExternalRequest`: Triggered from outside the elevator (hall call specifying floor and direction).
  - `InternalRequest`: Triggered inside the elevator (cab call specifying destination floor).
- **State Pattern**:
  - Elevator transitions smoothly between states:
    - `IdleState`: Elevator is stationary.
    - `MovingUpState`: Elevator is traversing upwards.
    - `MovingDownState`: Elevator is traversing downwards.
- **Strategy Pattern (Dispatching Strategy)**:
  - Supports pluggable scheduling strategies:
    - `NearestStrategy`: Selects the closest elevator to service the request.
    - `LeastLoadedStrategy`: Selects the elevator with the minimum pending load/requests.
- **Controller & Building Layout**:
  - `ElevatorController`: Manages state and dispatches requests.
  - `Building`: Represents the structural envelope housing floors and elevator units.

#### Design Diagram Overview:

```mermaid
classDiagram
    class Request {
        <<interface>>
    }
    class ExternalRequest {
        -floor: int
        -direction: Direction
    }
    class InternalRequest {
        -destinationFloor: int
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

    class Elevator {
        -id: int
        -currentFloor: int
        -currentState: State*
        -upRequests: set<int>
        -downRequests: set<int>
        +addRequest(Request* request)
        +move()
        +getCurrentFloor() int
        +getState() State*
        +setState(State* state)
    }
    Elevator *-- State

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

---

## Future Designs

The following system design topics are planned to be added to this repository:
- **Parking Lot Design**
- **Splitwise / Expense Sharing App**
- **BookMyShow / Movie Ticket Booking System**
- **Snake and Ladder Game**
- **Distributed Cache / Key-Value Store**
- **Message Queue (e.g., Kafka-like system)**

---

## How to Run

To compile and run the current C++ design implementations, use any standard C++ compiler (supporting C++11 or higher).

For example, to run the **Elevator System Design**:
```bash
# Navigate to the ElevatorDesignPattern folder
cd ElevatorDesignPattern

# Compile the code
g++ -std=c++11 code.cpp -o elevator_design

# Run the executable
./elevator_design
```
