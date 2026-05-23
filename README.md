# A* Search Algorithm Implementations - Discrete Structures

This repository contains C++ implementations of the A* (A-star) pathfinding algorithm, developed as part of the Discrete Structure (CO1007) coursework at Ho Chi Minh City University of Technology (HCMUT). 

The project focuses on applying the $A^{*}$ algorithm to solve four distinct practical routing and navigation problems in weighted graphs and grid-based environments.

## 👨‍💻 Author
* **Huỳnh Minh Khang**
* **Student ID:** 2550076
* **Faculty:** Computer Science and Engineering

## 📖 Algorithm Overview
The A* algorithm guarantees the optimal path by combining the strengths of Dijkstra's algorithm and Greedy Best-First Search. It uses the cost function:
$$f(n) = g(n) + h(n)$$ 

Where:
* $g(n)$: The actual cost from the start node to the current node.
* $h(n)$: The heuristic estimate of the cost from the current node to the goal.
* $f(n)$: The total estimated cost of the cheapest solution through node $n$.

## 🚀 Project Features & Tasks

The project is divided into four main programming tasks:

### 1. Degrees of Separation in a Social Network 
* **Problem:** Find the shortest connection path between two people in a social network represented by an adjacency matrix.
* **Implementation:** Calculates the path step-by-step, recording the $f(n)$, $g(n)$, and $h(n)$ values. The heuristic $h(n)$ estimates the remaining connections to the goal.

### 2. Drone Delivery in 2D Space 
* **Problem:** Determine the shortest delivery route between points in a 2D coordinate system using weighted edges.
* **Implementation:** Supports three heuristic distance metrics to evaluate performance:
  * Mode 1: Manhattan distance ($h(n) = |x_1 - x_2| + |y_1 - y_2|$).
  * Mode 2: Euclidean distance ($h(n) = \sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$).
  * Mode 3: Chebyshev distance ($h(n) = \max(|x_1 - x_2|, |y_1 - y_2|)$).

### 3. Warehouse Robot Navigation
* **Problem:** Navigate a robot through an $m \times n$ warehouse grid, avoiding blocked cells (obstacles).
* **Implementation:** Output path includes specific movement directions (Up, Down, Left, Right, and Diagonals). Cardinal moves cost 1 unit, while diagonal moves cost 1.5 units.

### 4. Evacuation Route Planning 
* **Problem:** Rebuild a building floor plan grid into a graph using a weight matrix and find the shortest path to an exit.
* **Implementation:** Converts passable tiles into vertices and outputs the sequence of coordinates leading to safety, utilizing either Manhattan or Chebyshev heuristics.

## 📂 Project Structure

All implementations use only default $C++$ libraries (`<iostream>`, `<fstream>`, `<string>`, `<cmath>`, `<vector>`, `<algorithm>`).

* `PathNode.h` / `PathNode.cpp`: Defines the common linked list data structure used to store and output the final paths[cite: 191, 206]. Each node contains the name, $f(n)$, $g(n)$, $h(n)$, and a pointer to the next step.
* `Algo.h` / `Algo.cpp`: Contains the core implementation logic for all four A* search functions (`findSocialPath`, `findDronePath`, `findWarehousePath`, `findEvacuationPath`).
* `main.cpp`: The driver program containing sample test cases and the `printPath` utility to demonstrate the functionality of each task.

## 🛠️ How to Compile and Run

1. Clone the repository to your local machine:
   ```bash
   git clone <your-repository-url>
   cd <repository-folder>

2. Compile the source code using ```g++```:
   ```bash
   g++ main.cpp Algo.cpp PathNode.cpp -o astar_project
 
3. Run the executable:
   Windows
   ```astar_project.exe```

   Linux/Mac
   ```./astar_project```
