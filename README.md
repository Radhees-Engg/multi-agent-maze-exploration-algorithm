# 🐭 Multi-Mouse Maze Explorer

A small C++ / Raylib project where multiple mouse agents explore a maze using **DFS (Depth-First Search) with Backtracking**.

This started as a normal macanze solver, but I changed the idea from **finding a shortest path** to actually **exploring the maze**. This makes it much easier to experiment with multiple agents and eventually make them smarter.

---

## 🧠 What is this?

The basic idea is pretty simple:

> Give multiple agents a maze, let them explore it, and make them figure out where they can and can't go.

Currently, the simulation has **two mouse agents** exploring the same maze.

Each mouse has its own position and its own DFS stack, while both of them share the same representation of the maze.

---

## ⚙️ How It Works

### 1. Maze

The maze is represented using a 2D array.

Each cell has a value representing what is currently there:

```text
0 → Unexplored
1 → Visited
2 → Dead End
3 → Mouse A
4 → Mouse B
8 → Wall
9 → End
```

The actual maze contains the walls and the goal, while a separate **memory grid** is used by the agents to remember what they have discovered.

---

### 2. Each Mouse Has Its Own DFS Stack

Every mouse maintains its own stack:

```cpp
std::stack<std::pair<int, int>> StackMem_A;
std::stack<std::pair<int, int>> StackMem_B;
```

Whenever a mouse moves to a new valid cell, that position gets pushed onto its stack.

So the stack basically represents the path the mouse has taken.

For example:

```text
Start
  ↓
  ↓
  →
  →
  ↓
Current Position
```

The stack contains those positions in the order they were visited.

---

### 3. Checking Neighbours

At every step, the mouse checks its four possible directions:

```text
        UP
         ↑
LEFT ← MOUSE → RIGHT
         ↓
       DOWN
```

If it finds an unexplored and valid cell, it moves there and pushes the new position onto its stack.

---

### 4. Backtracking

If the mouse can't find anywhere else to go, it has reached a dead end.

Instead of getting stuck, it starts **backtracking**.

The current position is removed from the stack, and the mouse moves back to the previous position.

The dead-end cell is then marked as:

```text
DEAD_END
```

This prevents the mouse from repeatedly exploring the same failed path.

So the basic behaviour becomes:

```text
Explore → Explore → Explore → Dead End
                                      ↓
                              Backtrack
                                      ↓
                              Try another path
```

---

## 🐭🐭 Multiple Agents

This is where the project becomes a little more interesting.

Both mice have:

* Their own position
* Their own DFS stack
* Their own exploration history

But they share the same maze and memory.

That means one mouse can affect what the other mouse is able to explore.

For example:

```text
        Mouse A
           ↓
     ┌───────────┐
     │   Maze    │
     │     ↓     │
     │  visited  │
     │     ↓     │
     │ Mouse B   │
     └───────────┘
```

The agents aren't just solving two separate mazes. They're operating inside the **same environment**.

---

## 🧩 Main Components

### `WORLD`

Handles the actual logic of the simulation.

It is responsible for things like:

* Checking whether a position is valid
* Checking neighbouring cells
* Moving the mice
* Maintaining exploration state
* Handling backtracking

---

### `RENDER`

Handles the Raylib side of the project.

It converts the maze/world coordinates into screen coordinates and draws:

* Walls
* Visited cells
* Dead ends
* The goal
* Mouse A
* Mouse B
* Grid lines

The idea is to keep the **simulation logic separate from the rendering logic**.

---

### `main()`

Creates the maze, memory grid, stacks and mouse positions, then runs the simulation loop.

The basic loop is:

```text
Create World
     ↓
Create Agents
     ↓
Check Mouse A
     ↓
Check Mouse B
     ↓
Render Maze
     ↓
Repeat
```

---

## 📚 Things I'm Practicing With This

This project is mainly me messing around with algorithms and C++ while actually building something.

Some of the things I'm working with here:

* C++
* Classes & OOP
* `std::vector`
* `std::stack`
* References
* `std::shared_ptr`
* DFS
* Backtracking
* 2D arrays
* State management
* Multi-agent systems
* Raylib
* Separating logic from rendering

---

## 🚀 Why Maze Exploration Instead of Shortest Path?

I already made a maze solver that focused on **finding a path**.

This time I wanted to approach the problem differently.

Instead of asking:

> "What's the shortest path from A to B?"

I'm asking:

> "How can I make multiple agents explore and understand the maze?"

That gives me a lot more room to experiment with the agents themselves.

Eventually I want to play around with things like:

* More agents
* Different agent behaviours
* Smarter exploration strategies
* Agents with different priorities
* Larger mazes
* Different algorithms
* Agents sharing more information
* Comparing exploration strategies

So this is basically the starting point for a small **multi-agent simulation**.

---

## 🎮 Current Status

Currently:

* ✅ Two agents
* ✅ DFS exploration
* ✅ Backtracking
* ✅ Individual stacks
* ✅ Shared maze memory
* ✅ Dead-end detection
* ✅ Raylib visualization

Still working on improving the architecture and making the agents smarter.

---

## 🛠️ Built With

**Language:** C++

**Graphics:** Raylib

**Algorithms:** DFS + Backtracking

**Data Structures:** `std::vector`, `std::stack`, `std::pair`

---

## 😂 Why Did I Make This?

Honestly...

I wanted to mess around with maze algorithms and somehow ended up making two mice run around a maze.

So yeah.

**Funny way to spend a weekend. 🐭**

🔗For Demo Video Click the Link
(Demo Video)[https://www.linkedin.com/in/radhees-bala/]
