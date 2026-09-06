# 🐭 Multi-Mouse Maze Explorer

A C++ / Raylib project where multiple mouse agents explore the same maze using **DFS (Depth-First Search) with Backtracking**.

This started as a normal maze solver, but instead of focusing on finding the shortest path, I wanted to experiment with **multiple agents exploring the same environment**.

## 🧠 How It Works

* Two mice explore the maze independently.
* Each mouse has its own **position and DFS stack**.
* Both mice share the same **maze memory**.
* The memory keeps track of walls, visited cells, dead ends, the goal, and the mice.
* When a mouse reaches a dead end, it **backtracks** and tries another unexplored path.
* Since both mice share the same environment, their exploration can affect each other.

### Basic Flow

```text
Check Neighbours
      ↓
 Unexplored Cell?
   ↙         ↘
 Yes          No
  ↓            ↓
Move        Backtrack
  ↓            ↓
Push Stack   Try Again
```

## 🧩 Main Components

**`WORLD`**
Handles the maze logic, movement, neighbour checking, exploration and backtracking.

**`RENDER`**
Handles the Raylib visualization of the maze and agents.

**`main()`**
Creates the maze, agents, stacks and runs the simulation.

## 📚 What I'm Practicing

* C++
* OOP & Classes
* `std::vector`
* `std::stack`
* References & Smart Pointers
* DFS & Backtracking
* Multi-Agent Systems
* Raylib

## 🚀 What's Next?

The main reason I built this as an **exploration system** instead of a simple pathfinder is that it gives me more room to experiment with:

* More agents
* Smarter agents
* Different behaviours
* Different exploration algorithms
* Agents sharing more information

Basically, this is the starting point for me to mess around with **multi-agent simulations**.

Yeah... funny way to spend a weekend. 🐭
