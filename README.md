# Monte Carlo Tree Search (MCTS) — AI Board Game Project

> **The application of Artificial Intelligence in board games.**  
> Author: Samuel Hardy (p13193068)

---

## Overview

This project implements **Monte Carlo Tree Search (MCTS)** — an algorithm that simulates gameplay, builds statistical models of success and failure, and uses those statistics to determine the optimal move. Unlike traditional heuristic-driven AI, MCTS can achieve strong performance with little to no domain knowledge of the game itself.

The project demonstrates MCTS in the context of **Checkers**, chosen for its smaller branching factor compared to Go, and because it is heuristically sound — making it an ideal testbed to measure MCTS performance against other AI techniques.

---

## Requirements

### SFML

This project uses **SFML 2.3.2** (Simple and Fast Multimedia Library) for rendering and window management.

> ⚠️ **You must use SFML version 2.3.2 exactly.** Other versions may not be compatible.

#### Download SFML 2.3.2

- **Windows:** https://www.sfml-dev.org/download/sfml/2.3.2/
- **Linux:** `sudo apt-get install libsfml-dev` (check version) or build from source
- **macOS:** `brew install sfml` (check version) or build from source

#### Linking SFML (example — g++)

```bash
g++ main.cpp -o mcts_game \
    -lsfml-graphics -lsfml-window -lsfml-system
```

#### CMake (if using)

```cmake
cmake_minimum_required(VERSION 3.10)
project(MCTS_Game)

find_package(SFML 2.3.2 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
```

---

## Build & Run

```bash
# Clone / navigate to the project directory
cd MCTS_Project

# Compile (adjust flags for your environment)
g++ -std=c++11 src/*.cpp -o mcts -lsfml-graphics -lsfml-window -lsfml-system

# Run
./mcts
```

---

## How MCTS Works

MCTS operates through four repeated phases per iteration:

### 1. Selection
Starting from the root node, the algorithm traverses the tree selecting the most promising non-terminal node that has not yet been fully expanded. Node selection is guided by the **UCT policy** (see below).

### 2. Expansion
A child node is added to the selected node based on the available legal moves.

### 3. Simulation (Rollout)
From the newly added child node, the game is played out to a terminal state using a default policy (typically random moves for both the AI and player).

### 4. Backpropagation
The result of the simulation (win/loss/reward) is propagated back up the tree, updating each ancestor node's visit count and win value.

This cycle repeats until a computational budget (time limit or iteration count) is exhausted, at which point the **best child of the root node** is returned as the chosen move.

---

## Node Selection — UCT

The most widely used selection strategy is **UCT (Upper Confidence Bounds for Trees)**, which balances exploration and exploitation:

```
UCT(node) = (wins / visits) + Cp * sqrt(ln(parent_visits) / visits)
```

- `wins / visits` — exploitation: favour nodes that have historically performed well
- `Cp` — exploration constant: tunable to increase or decrease exploration
- `sqrt(ln(parent_visits) / visits)` — exploration: ensure under-visited nodes are tried

UCT guarantees that all children can eventually be simulated, preventing promising branches from being permanently ignored.

---

## Comparison with Other AI Methods

| Algorithm | Strengths | Weaknesses |
|-----------|-----------|------------|
| **MCTS / UCT** | No domain knowledge needed; dynamic; works on high-branching games | Can be slow; search dynamics not fully understood |
| **Minimax** | Guaranteed optimal solution; unbeatable on small trees | Must traverse the entire game tree; infeasible for large branching factors |
| **Alpha-Beta Pruning** | Reduces minimax overhead by cutting irrelevant branches | Still requires heuristic knowledge; poor on low-heuristic games like Go |
| **A\*** | Fast optimal pathfinding when weights are known | Cannot handle hidden data or unknown future node weights |

---

## Project Structure

```
MCTS_Project/
├── src/
│   ├── main.cpp          # Entry point
│   ├── MCTS.cpp          # Core MCTS algorithm
│   ├── Node.cpp          # Tree node structure
│   ├── Game.cpp          # Game logic (Checkers)
│   └── Renderer.cpp      # SFML rendering
├── include/
│   ├── MCTS.h
│   ├── Node.h
│   ├── Game.h
│   └── Renderer.h
├── assets/               # Textures, fonts
├── README.md
└── CMakeLists.txt
```

---

## Key Concepts & Glossary

| Term | Definition |
|------|------------|
| **Node** | Represents a game state or action in the search tree |
| **Terminal state** | A game state with no children and no possible moves (end of game) |
| **Non-terminal node** | A node that still has possible child moves |
| **Weight** | A static value representing the estimated worth of a node/action |
| **Path** | A route through the tree graph |
| **Branching factor** | The number of possible moves available at each state |
| **UCB1** | Upper Confidence Bound formula used to estimate node reward |
| **UCT** | UCB1 adapted for trees — the standard MCTS selection policy |
| **GGP** | General Game Player — AI using MCTS to play multiple games with no domain knowledge |

---

## References

1. Browne, C.B., Powley, E., Whitehouse, D., Lucas, S.M., Cowling, P.I., Rohlfshagen, P., Tavener, S., Perez, D., Samothrakis, S., and Colton, S. — *"A Survey of Monte Carlo Tree Search Methods"*, pp. 1–47
2. Lai, T.L. and Robbins, H. — *"Asymptotically efficient adaptive allocation rules"*, Adv. Appl. Math., vol. 6, pp. 4–22, 1985
3. Auer, P., Cesa-Bianchi, N., and Fischer, P. — *"Finite-time analysis of the multiarmed bandit problem"*, Mach. Learn., vol. 47, no. 2, pp. 235–256, 2002
4. Finnsson, H. — *"CADIA-Player: A general game playing agent"*, M.S. thesis, Reykjavik University, 2007
5. Jakl, T. — *"Arimaa challenge – comparison study of MCTS versus alpha-beta methods"*, BSc thesis, Charles University, Prague
