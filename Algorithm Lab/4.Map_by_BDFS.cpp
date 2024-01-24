#include <iomanip>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class Graph {
#define MAX    10
#define INF    (~(0x1<<31))
private:
    char vertice[MAX];
    int verticeNum;
    int edgeNum;
    int mMatrix[MAX][MAX];

    int getPosition(char ch);
    int firstVertex(int v);
    int nextVertex(int v, int w);
    void checkVisit(int i, int* visited);

public:
    Graph(char vexs[], int vlen, int matrix[][9]);
    ~Graph();
    void DFS();
    void BFS();
    void print();
};



Graph::Graph(char vexs[], int vlen, int matrix[][9])
{
    int i, j;

    verticeNum = vlen;
    for (i = 0; i < verticeNum; i++)
        vertice[i] = vexs[i];

    for (i = 0; i < verticeNum; i++)
        for (j = 0; j < verticeNum; j++)
            mMatrix[i][j] = matrix[i][j];

    for (i = 0; i < verticeNum; i++)
        for (j = 0; j < verticeNum; j++)
            if (i != j && mMatrix[i][j] != INF)
                edgeNum++;
    edgeNum /= 2;
}

Graph::~Graph(){}

int Graph::getPosition(char ch)
{
    for (int i = 0; i < verticeNum; i++)
        if (vertice[i] == ch)
            return i;
    return -1;
}


int Graph::firstVertex(int v)
{
    if (v<0 || v>(verticeNum - 1)) { return -1; }

    for (int i = 0; i < verticeNum; i++) {
        if (mMatrix[v][i] != 0 && mMatrix[v][i] != INF) {
            return i;
        }
    }
    return -1;
}

int Graph::nextVertex(int v, int w)
{
    if (v<0 || v>(verticeNum - 1) || w<0 || w>(verticeNum - 1)) { return -1; }

    for (int i = w + 1; i < verticeNum; i++) {
        if (mMatrix[v][i] != 0 && mMatrix[v][i] != INF) {
            return i;
        }
    }
    return -1;
}

void Graph::checkVisit(int i, int* visited)
{
    int w;

    visited[i] = 1;
    cout << vertice[i] << " ";

    for (w = firstVertex(i); w >= 0; w = nextVertex(i, w))
    {
        if (!visited[w])
            checkVisit(w, visited);
    }

}

void Graph::DFS()
{
    int i;
    int visited[MAX];

    for (i = 0; i < verticeNum; i++)
        visited[i] = 0;

    cout << "DFS: ";
    for (i = 0; i < verticeNum; i++)
    {
        if (!visited[i])
            checkVisit(i, visited);
    }
    cout << endl;
}

void Graph::BFS()
{
    int head = 0;
    int rear = 0;
    int queue[MAX];
    int visited[MAX];
    int i, j, k;

    for (i = 0; i < verticeNum; i++) {
        visited[i] = 0;
    }
    cout << "BFS: ";
    for (i = 0; i < verticeNum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            cout << vertice[i] << " ";
            queue[rear++] = i;
        }
        while (head != rear)
        {
            j = queue[head++];
            for (k = firstVertex(j); k >= 0; k = nextVertex(j, k))
            {
                if (!visited[k])
                {
                    visited[k] = 1;
                    cout << vertice[k] << " ";
                    queue[rear++] = k;
                }
            }
        }
    }
    cout << endl;
}

void Graph::print()
{
    int i, j;

    cout << "Martix Graph:" << endl;
    for (i = 0; i < verticeNum; i++)
    {
        for (j = 0; j < verticeNum; j++)
            cout << setw(10) << mMatrix[i][j] << " ";
        cout << endl;
    }
}


int main()
{
    typedef chrono::high_resolution_clock Clock;
    char vexs[] = { 'S', 'V1', 'V2', 'V3', 'V4', 'V5', 'T' };
    int matrix[][9] = {
         {   0,   2,   3,   4, INF, INF, INF},
         { INF,   0,   3, INF,   2, INF, INF},
         { INF, INF,   0, INF,   2,   2, INF},
         { INF, INF, INF,   0, INF,   2, INF},
         { INF, INF, INF, INF,   0,   1,   3},
         { INF, INF, INF, INF, INF,   0,   5},
         { INF, INF, INF, INF, INF, INF,   0} };

    int vlen = sizeof(vexs) / sizeof(vexs[0]);
    Graph* pG;
    //pG = new MatrixUDG();

    pG = new Graph(vexs, vlen, matrix);

    auto tt1 = Clock::now();
    pG->print();
    pG->BFS(); 
    pG->DFS();
    auto tt2 = Clock::now();
    cout << "Time cost: " << chrono::duration_cast<chrono::nanoseconds>(tt2 - tt1).count() << endl;
    return 0;
}