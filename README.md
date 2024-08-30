# 🚀 GUIDE ME: Your Travel Companion

GUIDE ME is a C++ application designed to help travelers navigate a country efficiently while staying within budget. This tool enables users to explore various transportation options between cities, ensuring a cost-effective journey. 

## 🌟 Core Features

- **Graph Traversal:**
  - Traverse the country’s transportation graph using:
    - **Breadth-First Search (BFS):** Ideal for finding the shortest path between cities.
    - **Depth-First Search (DFS):** Perfect for exploring all possible routes.
  - Simply input your starting city and choose your preferred algorithm.

- **Dynamic Map Management:**
  - **Update:** Modify existing transportation options between cities.
  - **Add:** Introduce new routes and transportation methods to the graph.
  - **Delete:** Remove outdated or unnecessary transportation options.

- **Completeness Check:**
  - Determine if the transportation map is fully connected, meaning every city is reachable from every other city.

- **Budget-Conscious Route Planning:**
  - Input your starting city, destination, and budget to receive a list of all available transportation options.
  - The results include the route (cities to pass through) and total cost, sorted in ascending order to help you make the best choice.

## 🛠 Technical Highlights

- **Graph Representation:** 
  - The program reads map data from a file, representing cities and transportation options as a graph.
  
- **Data Structures:**
  - Utilized multiple data structures, including graphs, queues, and stacks, to efficiently manage and manipulate transportation data.
  
- **Algorithm Implementation:**
  - Implemented BFS and DFS to allow thorough exploration and pathfinding within the graph.

- **GUI:**
  - For an enhanced user experience, a graphical user interface can be integrated to make the application more user-friendly using QT.

## 🚧 Getting Started

### Prerequisites

- C++ Compiler (e.g., GCC, MSVC)
- Makefile (optional for building the project)
- QT
- Git

### Installation

1. Clone the repository:
   ```bash
   git clone [insert repository link here]
   cd GUIDE_ME
   ```

2. Compile the program:
   ```bash
   g++ -o guide_me main.cpp
   ```

3. Run the program:
   ```bash
   ./guide_me
   ```

### Usage

1. Prepare your map data file according to the required format.
2. Run the program and follow the on-screen prompts to:
   - Traverse the graph.
   - Manage transportation options.
   - Check the completeness of the map.
   - Plan routes within your budget.
