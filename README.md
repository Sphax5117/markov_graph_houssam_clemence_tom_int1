# Markov Graph Analysis Project

A C project for analyzing Markov chains and directed graphs, including strongly connected component detection using Tarjan's algorithm and stationary distribution computation.

## Project Overview

This project implements various algorithms and data structures for working with Markov chains represented as directed graphs. It includes functionality for:

- **Graph representation** using adjacency lists
- **Markov chain validation** and analysis
- **Tarjan's algorithm** for finding strongly connected components
- **Stationary distribution** computation
- **Mermaid diagram generation** for graph visualization
- **Matrix operations** for probability calculations

## Team Members

- Houssam
- Clemence  
- Tom

**Course**: TI301 - INT1 (2025-2026)

## Project Structure

```
markov_graph_houssam_clemence_tom_int1/
├── main.c              # Main entry point
├── adjacency.c/.h      # Adjacency list implementation
├── cell.c/.h           # Cell structure for linked lists
├── list.c/.h           # Linked list operations
├── markov.c/.h         # Markov chain validation
├── tarjan.c/.h         # Tarjan's algorithm implementation
├── stack.c/.h          # Stack data structure
├── matrix.c/.h         # Matrix operations
├── mermaid.c/.h        # Mermaid diagram generation
├── bonus.c/.h          # Bonus features
├── utils.c/.h          # Utility functions
├── CMakeLists.txt      # CMake build configuration
└── data/               # Test data files
    └── test_bench/     # Test cases
```

## Data Structures

### Adjacency List (`adjacency.h`)
Represents the graph structure with vertices and their outgoing edges with probabilities.

### Cell and List (`cell.h`, `list.h`)
- **`t_cell`**: Node in a linked list storing destination vertex and transition probability
- **`t_list`**: Linked list of cells representing outgoing edges

### Tarjan Structures (`tarjan.h`)
- **`t_tarjan_vertex`**: Vertex metadata for Tarjan's algorithm
- **`t_class`**: Strongly connected component (equivalence class)
- **`t_partition`**: Collection of all strongly connected components

### Stack (`stack.h`)
Stack implementation used in Tarjan's algorithm.

## Key Features

### 1. Graph Loading
Load graph data from text files with vertex count and edge definitions (source, destination, probability).

### 2. Markov Chain Validation
Verify that the graph represents a valid Markov chain:
- All outgoing probabilities from each vertex sum to 1.0
- All probabilities are between 0 and 1

### 3. Tarjan's Algorithm
Find all strongly connected components in the directed graph using depth-first search.

### 4. Stationary Distribution
Compute the long-term probability distribution of the Markov chain.

### 5. Mermaid Visualization
Generate Mermaid flowchart diagrams for graph visualization with:
- Custom neo theme
- ELK layout engine
- Edge labels showing transition probabilities

Example output saved to [`mermaid.txt`](mermaid.txt).

## Building the Project

### Requirements
- CMake 3.27 or higher
- C11 compatible compiler
- GCC/MinGW (Windows) or Clang (Mac/Linux)

### Build Instructions

```bash
# Create build directory
mkdir cmake-build-debug
cd cmake-build-debug

# Configure and build
cmake ..
make

# Run the executable
./TI_301_PJT
```

## Usage

The main program (`main.c`) demonstrates the following workflow:

1. Load graph from file
2. Validate Markov chain properties
3. Generate Mermaid diagram
4. Compute Tarjan's strongly connected components
5. Analyze stationary distributions
6. Run bonus features

### Input File Format

```
<number_of_vertices>
<source> <destination> <probability>
<source> <destination> <probability>
...
```

Example:
```
10
1 7 0.75
1 5 0.25
2 2 1.00
...
```

## Platform Support

The project supports both Windows and Unix-like systems (macOS, Linux) with platform-specific path handling:
- **Windows**: Uses backslashes for paths (`..\\data\\`)
- **Unix/Mac**: Uses forward slashes for paths (`data/`)

## Output

- **Console**: Algorithm results and analysis
- **mermaid.txt**: Mermaid diagram for visualization (can be rendered on mermaid.live)

## Example Mermaid Output

The generated diagram shows the Markov chain with:
- Circular nodes representing states
- Directed edges with probability labels
- Neo theme styling
- ELK automatic layout

## License

Academic project for TI301 course.

## Notes

- The project uses dynamic memory allocation for flexible graph sizes
- Includes comprehensive test cases in `data/test_bench/`
- Supports floating-point probability calculations with error tolerance