# Fillomino Solver

This repository contains a C++ solver for Fillomino – a logic puzzle about dividing a grid into regions based on numeric clues.

## Description

The solver reads an input grid from a file or user input, then applies heuristic-based algorithms to fill the entire grid while satisfying the puzzle's constraints


The program utilizes two advanced search heuristics **MRV Minimum Remaining Values** and **Degree heuristic**

These techniques help efficiently guide the search through possible grid configurations.

## Technologies Used

- **Language**: C++ (ANSI standard)
- **Compiler**: g++
- **Development Tools**: Visual Studio Code
- **Input Format**: Grid data provided via `exapmle.in` files or manual user input
- **Output**: Result displayed in the console

## How to Use

 **Compile** the project:

 g++ main.cpp logic.cpp node.cpp -o fillomino

   
## Author

**Yevsieienko Yaroslav**

