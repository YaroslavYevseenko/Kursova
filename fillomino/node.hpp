#ifndef NODE_HPP
#define NODE_HPP

class Node {
public:
    int init_value;
    int value;
    bool visited;
    int x;
    int y;

    Node();
    Node(int x, int y, int value);
};

#endif
