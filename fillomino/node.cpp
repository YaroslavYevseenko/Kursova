#include "node.hpp"

Node::Node() : x(0), y(0), init_value(0), value(0), visited(false) {}

Node::Node(int x, int y, int init_value)
    : init_value(init_value), value(init_value), visited(false), x(x), y(y) {}

