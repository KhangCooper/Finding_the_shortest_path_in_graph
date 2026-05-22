#include "PathNode.h"

PathNode* findSocialPath(double adjMatrix[100][100], int startPerson, int goalPerson) {
    double h_cost[100];
    for(int i = 0; i < 100; ++i) {
        h_cost[i] = 1e9; 
    }
    
    vector<int> q;
    q.push_back(goalPerson);
    h_cost[goalPerson] = 0;
    int head_idx = 0; 
    
    while(head_idx < q.size()) {
        int u = q[head_idx++];
        for(int v = 0; v < 100; ++v) {
            if (adjMatrix[v][u] > 0 && h_cost[v] == 1e9) {
                h_cost[v] = h_cost[u] + 1.0;
                q.push_back(v);
            }
        }
    }

    double g_cost[100];
    int parent[100];
    bool inOpen[100];
    bool inClosed[100];

    for (int i = 0; i < 100; i++) {
        g_cost[i] = 1e9;
        parent[i] = -1;
        inOpen[i] = false;
        inClosed[i] = false;
    }

    g_cost[startPerson] = 0;
    inOpen[startPerson] = true;

    while (true) {
        int current = -1;
        double min_f = 1e9;

        for (int i = 0; i < 100; ++i) {
            if (inOpen[i]) {
                double f = g_cost[i] + h_cost[i]; 
                
                if (f < min_f) {
                    min_f = f;
                    current = i;
                } 
                
                else if (f == min_f && current != -1) {
                    if (g_cost[i] > g_cost[current]) {
                        current = i;
                    }
                }
            }
        }

        if (current == -1) break;         
        if (current == goalPerson) break;

        inOpen[current] = false;
        inClosed[current] = true;

        for (int i = 0; i < 100; ++i) {
            if (adjMatrix[current][i] > 0 && !inClosed[i]) {
                double tentative_g = g_cost[current] + 1.0;
                
                if (tentative_g < g_cost[i]) {
                    parent[i] = current;
                    g_cost[i] = tentative_g;
                    inOpen[i] = true; 
                }
            }
        }
    }

    if (g_cost[goalPerson] == 1e9 && startPerson != goalPerson) {
        return nullptr;
    }

    PathNode* head = nullptr;
    int curr = goalPerson;
    
    while (curr != -1) {
        PathNode* newNode = new PathNode();
        newNode->name = to_string(curr);
        newNode->g = g_cost[curr];
        newNode->h = h_cost[curr]; 
        newNode->f = newNode->g + newNode->h;
        
        newNode->next = head;
        head = newNode;
        curr = parent[curr];
    }
    
    return head;
}

int manhatDist(int current, int goalPoint, int coords[100][2]) {
    return abs(coords[current][0] - coords[goalPoint][0]) + abs(coords[current][1] - coords[goalPoint][1]);
}

double euclidDist(int current, int goalPoint, int coords[100][2]) {
    return sqrt((coords[current][0] - coords[goalPoint][0]) * (coords[current][0] - coords[goalPoint][0])
                + (coords[current][1] - coords[goalPoint][1]) * (coords[current][1] - coords[goalPoint][1]));
}

int chebDist(int current, int goalPoint, int coords[100][2]) {
    return max( abs(coords[current][0] - coords[goalPoint][0]),  abs(coords[current][1] - coords[goalPoint][1]));
}

PathNode* findDronePath(double weightMatrix[100][100], int coords[100][2],
int startPoint, int goalPoint, int mode) {
    double g_cost[100];
    int parent[100];
    bool inOpen[100];
    bool inClosed[100];

    for (int i = 0; i < 100; i++) {
        g_cost[i] = 1e9;
        parent[i] = -1;
        inOpen[i] = false;
        inClosed[i] = false;
    }

    g_cost[startPoint] = 0;
    inOpen[startPoint] = true;

    while (true) {
        int current = -1;
        double min_f = 1e9;

        for (int i = 0; i < 100; i++) {
            if (inOpen[i]) {
                double f;
                if (mode == 1) f = g_cost[i] + manhatDist(i, goalPoint, coords);
                else if (mode == 2) f = g_cost[i] + euclidDist(i, goalPoint, coords);
                else if (mode == 3) f = g_cost[i] + chebDist(i, goalPoint, coords);

                if (f < min_f) {
                    min_f = f;
                    current = i;
                }
            }  
        }

        if (current == -1) break;
        if (current == goalPoint) break;

        inOpen[current] = false;
        inClosed[current] = true;

        for (int i = 0; i < 100; i++) {
            if (weightMatrix[current][i] > 0 && weightMatrix[current][i] < 1e9 && !inClosed[i]) {
                double tentative_g = g_cost[current] + weightMatrix[current][i];
                if (tentative_g < g_cost[i]) {
                    parent[i] = current;
                    g_cost[i] = tentative_g;
                    inOpen[i] = true;
                }
            }
        }
    }

    if (g_cost[goalPoint] == 1e9 && startPoint != goalPoint) {
        return nullptr;
    }

    PathNode* head = nullptr;
    int curr = goalPoint;


    while (curr != -1) {
        PathNode* newNode = new PathNode();
        
        newNode->name = "(" + to_string(coords[curr][0]) + "," + to_string(coords[curr][1]) + ")";
        newNode->g = g_cost[curr];
        
        if (mode == 1) newNode->h = manhatDist(curr, goalPoint, coords);
        else if (mode == 2) newNode->h = euclidDist(curr, goalPoint, coords);
        else if (mode == 3) newNode->h = chebDist(curr, goalPoint, coords);
        newNode->f = newNode->g + newNode->h;

        newNode->next = head;
        head = newNode;
        curr = parent[curr];
    }
    return head;
}

double heuristic(int currX, int currY, int goalX, int goalY, int mode) {
    if (mode == 1) {
        return abs(currX - goalX) + abs(currY - goalY);
    }

    else if (mode == 2) {
        return max(abs(currX - goalX), abs(currY - goalY));
    }
    return 0;
}

PathNode* findWarehousePath(int warehouse[100][100], int m, int n, int startX, int startY, int goalX, int goalY, int mode) {
    double g_cost[100][100];
    int parentX[100][100];
    int parentY[100][100];
    string dir[100][100];
    bool isOpen[100][100];
    bool isClosed[100][100];
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            g_cost[i][j] = 1e9;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
            isOpen[i][j] = false;
            isClosed[i][j] = false;
        }
    }

    g_cost[startX][startY] = 0;
    isOpen[startX][startY] = true;
    dir[startX][startY] = "Start";

    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    double cost[] = {1, 1, 1, 1, 1.5, 1.5, 1.5, 1.5};
    string dName[] = {"Up", "Down", "Left", "Right", "Up-Left", "Up-Right", "Down-Left", "Down-Right"};

    while (true) {
        int currX = -1;
        int currY = -1;
        double min_f = 1e9;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isOpen[i][j]) {
                    double f = g_cost[i][j] + heuristic(i, j, goalX, goalY, mode);

                    if (f < min_f) {
                        min_f = f;
                        currX = i;
                        currY = j;
                    }

                    else if (f == min_f && currX != -1) {
                        if (g_cost[i][j] > g_cost[currX][currY]) {
                            currX = i;
                            currY = j;
                        }
                    }
                }
            }
        }

        if (currX == -1) break;
        if (currX == goalX && currY == goalY) break;

        isOpen[currX][currY] = false;
        isClosed[currX][currY] = true;

        for (int k = 0; k < 8; k++) {
            int nx = currX + dx[k];
            int ny = currY + dy[k];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                if (warehouse[nx][ny] == 0 && !isClosed[nx][ny]) {
                    double tentative_g = g_cost[currX][currY] + cost[k];

                    if (tentative_g < g_cost[nx][ny]) {
                        parentX[nx][ny] = currX;
                        parentY[nx][ny] = currY;
                        dir[nx][ny] = dName[k];
                        g_cost[nx][ny] = tentative_g;
                        isOpen[nx][ny] = true;
                    }
                }
            }
        }
    }

    if (g_cost[goalX][goalY] == 1e9 && (startX != goalX || startY != goalY)) return nullptr;

    PathNode* head = nullptr;
    int cx = goalX, cy = goalY;

    while (cx != -1 && cy != -1) {
        PathNode* newNode = new PathNode();
        newNode->name = dir[cx][cy];
        newNode->g = g_cost[cx][cy];
        newNode->h = heuristic(cx, cy, goalX, goalY, mode);
        newNode->f = newNode->g + newNode->h;

        newNode->next = head;
        head = newNode;

        int px = parentX[cx][cy];
        int py = parentY[cx][cy];
        cx = px;
        cy = py;
    }

    return head;
}

PathNode* findEvacuationPath(int floorPlan[100][100], int m, int n, int startX,
int startY, int exitX, int exitY, double weightMatrix[100][100], int mode) {
    int totalNode = m * n;

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            weightMatrix[i][j] = 1e9;
        }
    }

    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    double cost[] = {1.0, 1.0, 1.0, 1.0, 1.5, 1.5, 1.5, 1.5};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int u = n * i + j;
            
            if (floorPlan[i][j] == 1) continue;
            for (int k = 0; k < 8; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];

                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    if (floorPlan[nx][ny] == 0) {
                        int v = nx * n + ny;
                        weightMatrix[u][v] = cost[k];
                    }
                }
            }
        }
    }

    double g_cost[100];
    int parent[100];
    bool inOpen[100];
    bool inClosed[100];

    int startNode = startX * n + startY;
    int exitNode = exitX * n + exitY;

    for (int i = 0; i < 100; i++) {
        g_cost[i] = 1e9;
        parent[i] = -1;
        inOpen[i] = false;
        inClosed[i] = false;
    }

    g_cost[startNode] = 0;
    inOpen[startNode] = true;

    while (true) {
        int current = -1;
        double min_f = 1e9;

        for (int i = 0; i < totalNode; i++) {
            if (inOpen[i]) {
                int cur_x = i / n;
                int cur_y = i % n;
                double h = heuristic(cur_x, cur_y, exitX, exitY, mode);

                double f = g_cost[i] + h;
                if (f < min_f) {
                    min_f = f;
                    current = i;
                }

                else if (f == min_f && current != -1) {
                    if (g_cost[i] > g_cost[current]) {
                        current = i;
                    } 
                }
            }
        }

        if (current == -1) break;
        if (current == exitNode) break;

        inOpen[current] = false;
        inClosed[current] = true;
        
        for (int i = 0; i < totalNode; i++) {
            if (weightMatrix[current][i] > 0 && weightMatrix[current][i] < 1e9 && !inClosed[i]) {
                double tentative_g = g_cost[current] + weightMatrix[current][i];
                if (tentative_g < g_cost[i]) {
                    parent[i] = current;
                    g_cost[i] = tentative_g;
                    inOpen[i] = true;
                }
            }
        }
    }

    if (g_cost[exitNode] == 1e9 && exitNode != startNode) return nullptr;

    PathNode* head = nullptr;
    int cur = exitNode;

    while (cur != -1) {
        PathNode* newNode = new PathNode();
        int curX = cur / n;
        int curY = cur % n;

        newNode->name = "(" + to_string(curX) + ", " + to_string(curY) + ")";
        newNode->g = g_cost[cur];
        newNode->h = heuristic(curX, curY, exitX, exitY, mode);
        newNode->f = newNode->g + newNode->h;

        newNode->next = head;
        head = newNode;
        cur = parent[cur];
    }
    return head;
}