/* -------------------------------------------------------------------------- */
/*  File:       node.cpp                                                     */
/*  Purpose:    Implements the Node class for Fillomino grid cells.          */
/* -------------------------------------------------------------------------- */

#include "node.hpp"

/* -------------------------------------------------------------------------- */
/*  Constructor: Node()                                                      */
/*  Purpose:     Default constructor initializing members to zero/default.   */
/* -------------------------------------------------------------------------- */
Node::Node() : x(0), y(0), init_value(0), value(0), visited(false) {}

/* -------------------------------------------------------------------------- */
/*  Constructor: Node(int x, int y, int init_value)                          */
/*  Purpose:     Initializes node with given coordinates and initial value.  */
/* -------------------------------------------------------------------------- */
Node::Node(int x, int y, int init_value)
    : x(x), y(y), init_value(init_value), value(init_value), visited(false) {}

