#ifndef _PATHNODE_H_
#define _PATHNODE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;


struct PathNode {
    string name;
    double f;
    double g;
    double h;
    PathNode* next;

    PathNode();
    PathNode(string name, int f, int g, int h, PathNode* next);
};

#endif