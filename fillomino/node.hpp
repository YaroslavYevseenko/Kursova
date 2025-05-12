/* -------------------------------------------------------------------------- */
/*  File:       node.hpp                                                     */
/*  Purpose:    Defines a single cell (node) in the Fillomino puzzle grid.   */
/* -------------------------------------------------------------------------- */

#ifndef NODE_HPP
#define NODE_HPP

/* -------------------------------------------------------------------------- */
/*  Class:      Node                                                          */
/*  Purpose:    Represents a grid cell with coordinates and values.          */
/* -------------------------------------------------------------------------- */
class Node {
public:
    int init_value;  // Original value from input
    int value;       // Current value
    bool visited;    // Visitation flag for traversal
    int x;           // Row index
    int y;           // Column index

    Node();                                  // Default constructor
    Node(int x, int y, int value);           // Parameterized constructor
};

#endif 
