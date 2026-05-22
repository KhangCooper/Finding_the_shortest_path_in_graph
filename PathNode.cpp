#include "PathNode.h"

PathNode::PathNode() {
    name = "";
    f = 0;
    g = 0;
    h = 0;
    next = nullptr;
}

PathNode::PathNode(string name, int f, int g, int h, PathNode* next) {
    this->name = name;
    this->f = f;
    this->g = g;
    this->h = h;
    this->next = next;
}