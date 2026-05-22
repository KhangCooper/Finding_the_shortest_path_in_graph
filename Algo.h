#ifndef _ALGO_H_
#define _ALGO_H_

#include "PathNode.h"
 
PathNode* findSocialPath(double adjMatrix[100][100], int startPerson, int goalPerson);
PathNode* findDronePath(double weightMatrix[100][100], int coords[100][2],
int startPoint, int goalPoint, int mode);
PathNode* findWarehousePath(int warehouse[100][100], int m, int n, int startX,
int startY, int goalX, int goalY, int mode);
PathNode* findEvacuationPath(int floorPlan[100][100], int m, int n, int startX,
int startY, int exitX, int exitY, double weightMatrix[100][100], int mode);

#endif