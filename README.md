# My System Design

Welcome to the **My System Design** repository. This is a curated collection of Low-Level Design (LLD) and High-Level Design (HLD) patterns, architectures, and implementations.

The goal of this repository is to showcase clean, modular, and maintainable object-oriented implementations of common system designs.

---

## Design Projects Directory

Below is an overview of the design patterns and projects in this repository. You can click on any completed project's name to view its detailed documentation and source code.

| Project Name | Language | Status | Short Description | Core Design Patterns / Concepts |
| :--- | :--- | :--- | :--- | :--- |
| [**Elevator System Design**](./ElevatorDesignPattern) | `C++` | 🟢 Completed | A low-level design for a multi-elevator system in a building. | State Pattern, Strategy Pattern, OOD |
| **Parking Lot Design** | *TBD* | 🟡 Planned | A multi-story parking lot system with multiple vehicle types and dynamic pricing. | Factory Pattern, Strategy Pattern |
| **Splitwise / Expense Sharing App** | *TBD* | 🟡 Planned | An expense sharing application supporting split options (equal, exact, percentage). | Observer Pattern, Command Pattern |
| **BookMyShow / Movie Booking** | *TBD* | 🟡 Planned | A movie ticket booking platform handling concurrent seat selections and payments. | Singleton, Optimistic/Pessimistic Locking |
| **Snake and Ladder Game** | *TBD* | 🟡 Planned | A multiplayer Snake and Ladder board game with customizable components. | OOD, Game Loop, Strategy Pattern |
| **Distributed Cache** | *TBD* | 🟡 Planned | A thread-safe, in-memory key-value cache with pluggable eviction policies (LRU/LFU). | Doubly Linked List + Hash Map, Concurrency |
| **Message Queue (Kafka-like)** | *TBD* | 🟡 Planned | A pub-sub messaging system supporting topics, partitions, and consumer groups. | Publisher-Subscriber Pattern, Multi-threading |

---

## How to Navigate

- **🟢 Completed** projects contain a link to their respective folder. Inside each folder, you will find:
  - Source code files (e.g., `.cpp`, `.java`, `.py`).
  - A dedicated `README.md` detailing the project's class diagrams, design decisions, and compilation instructions.
- **🟡 Planned** projects indicate designs that will be added to this repository in the future.

---

## How to Run

To run any of the completed C++ designs:
1. Navigate to the desired project folder:
   ```bash
   cd ElevatorDesignPattern
   ```
2. Follow the compiler instructions in that directory's `README.md`.
