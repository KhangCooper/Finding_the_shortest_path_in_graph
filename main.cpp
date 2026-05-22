#include "PathNode.h"
#include "Algo.h"
void printPath(PathNode* head) {
    cout << "Solution Path:\n";
    while (head != nullptr) {
    cout << "Node: " << head->name
    << " | f: " << head->f
    << " | g: " << head->g
    << " | h: " << head->h << "\n";
    head = head->next;
    }
}

int main() {
    cout << "========== TASK 1: SOCIAL NETWORK ==========\n";
    double adjMatrix[100][100] = {0};

    /*
    [0, 1, 0, 1, 0]
    [1, 0, 1, 0, 0]
    [0, 1, 0, 0, 1]
    [1, 0, 0, 0, 1]
    [0, 0, 1, 1, 0]
    */
    
    adjMatrix[0][1] = 1; adjMatrix[1][0] = 1;
    adjMatrix[1][2] = 1; adjMatrix[2][1] = 1;
    adjMatrix[2][4] = 1; adjMatrix[4][2] = 1;    
    adjMatrix[0][3] = 1; adjMatrix[3][0] = 1;
    adjMatrix[3][4] = 1; adjMatrix[4][3] = 1;

    PathNode* task1 = findSocialPath(adjMatrix, 0, 4);
    printPath(task1); 


    cout << "========== TASK 2: DRONE DELIVERY ==========\n";
    double weightMatrix[100][100];
    int coords[100][2] = {
        {0, 0},   
        {0, 10},  
        {10, 0},  
        {10, 10}  
    };
    
    for(int i = 0; i < 100; i++) for(int j = 0; j < 100; j++) weightMatrix[i][j] = 1e9;
    
    weightMatrix[0][1] = 2.0;  
    weightMatrix[1][3] = 10.0; 
    
    weightMatrix[0][2] = 10.0; 
    weightMatrix[2][3] = 10.0; 
    
    cout << "[Mode 1 - Manhattan]\n";
    PathNode* task2 = findDronePath(weightMatrix, coords, 0, 3, 1);
    printPath(task2); 


    cout << "========== TASK 3: WAREHOUSE ROBOT ==========\n";
    int warehouse[100][100] = {0}; 
    int m = 5, n = 5;
    
    warehouse[0][2] = 1;
    warehouse[1][2] = 1;
    warehouse[2][2] = 1;
    
    cout << "[Mode 2 - Chebyshev\n";
    PathNode* task3 = findWarehousePath(warehouse, m, n, 0, 0, 0, 4, 2);
    printPath(task3); 


    cout << "========== TASK 4: EVACUATION ROUTE ==========\n";
    int floorPlan[100][100] = {0};
    double wMatrix4[100][100] = {0};
    int m4 = 3, n4 = 3;
    
    floorPlan[1][1] = 1; 
    
    cout << "[Mode 1 - Manhattan]\n";
    PathNode* task4 = findEvacuationPath(floorPlan, m4, n4, 0, 0, 2, 2, wMatrix4, 1);
    printPath(task4);
    return 0;
}