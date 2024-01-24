#include <iomanip>
#include <iostream>
#include <vector>
#include<chrono>
using namespace std;

class Graph {
#define totalnum    10
#define INF    (~(0x1<<31))
private:
    char vertice[totalnum];
    int verticeNum;
    int edgeNum;
    int mMatrix[totalnum][totalnum];

    int getPosition(char ch);
    int firstVertex(int v);
    int nextVertex(int v, int w);

public:
    Graph(char vexs[], int vlen, int matrix[][9]);
    ~Graph();
    void prim(int start);
    void print();

};

Graph::Graph(char vexs[], int vlen, int matrix[][9])
{
    int i, j;
    verticeNum = vlen;
    for (i = 0; i < verticeNum; i++){ vertice[i] = vexs[i]; }

    for (i = 0; i < verticeNum; i++) {
        for (j = 0; j < verticeNum; j++) {
            mMatrix[i][j] = matrix[i][j];
        }
    }
    for (i = 0; i < verticeNum; i++) {
        for (j = 0; j < verticeNum; j++) {
            if (i != j && mMatrix[i][j] != INF)
                edgeNum++;
        }
    }
    edgeNum /= 2;
}

Graph::~Graph(){}

int Graph::getPosition(char ch)
{
    int i;
    for (i = 0; i < verticeNum; i++)
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

void Graph::print()
{
    for (int i = 0; i < verticeNum; i++)
    {
        cout << vertice[i] << "  ";
        for (int j = 0; j < verticeNum; j++) { cout << setw(10) << mMatrix[i][j] << " "; }
        cout << endl;
    }
}

void Graph::prim(int first)
{
    int currentMin; // current min edge
    int currentIndex = 0; // current min index of point
    char primsVertices[totalnum]; // markdown the vertices
    int weights[totalnum]; // markdown the weight of edges

    primsVertices[currentIndex++] = vertice[first];
    for (int i = 0; i < verticeNum; i++) { 
        weights[i] = mMatrix[first][i];
    }

    weights[first] = 0;
    for (int i = 0; i < verticeNum; i++){

        if (i == first) { continue; }

        int minIndex = 0;
        currentMin = INF;

        for (int j = 0; j < verticeNum; j++) {
            if (weights[j] != 0 && weights[j] < currentMin){
                currentMin = weights[j];
                minIndex = j;
            }
        }
        primsVertices[currentIndex++] = vertice[minIndex];
        weights[minIndex] = 0;

        for (int j = 0; j < verticeNum; j++){
            if (weights[j] != 0 && mMatrix[minIndex][j] < weights[j])
                weights[j] = mMatrix[minIndex][j];
        }
    }

    //calculate sum
    int sum = 0;
    for (int i = 1; i < currentIndex; i++)
    {
        currentMin = INF;
        int x;
        int y = getPosition(primsVertices[i]);
        for (int j = 0; j < i; j++){
            x = getPosition(primsVertices[j]);
            if (mMatrix[x][y] < currentMin){currentMin = mMatrix[x][y];}
        }
        cout << "(" << this->vertice[x] << ", " << this->vertice[y] << ")   " << currentMin << endl;
        sum += currentMin;
    }
    cout << "Total edge cost is: " << sum << "\n ";

}

int main()
{
    typedef chrono::high_resolution_clock Clock;
    char vertices[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    int matrix[][9] = {
         {   0,  12, INF, INF, INF,  16},
         {  12,   0,  10, INF, INF,   7},
         { INF,  10,   0,   3,   5,   6},
         { INF, INF,   3,   0,   4, INF},
         { INF, INF,   5,   4,   0,   2},
         {  16,   7,   6, INF,   2,   0} };


    int Verticeslen = sizeof(vertices) / sizeof(vertices[0]);
    Graph* myGraph;

    myGraph = new Graph(vertices, Verticeslen, matrix);

    myGraph->print();

    cout << "prim\n";
    auto tt1 = Clock::now();
    myGraph->prim(5); 
    auto tt2 = Clock::now();
    cout << "Time cost: "<< chrono::duration_cast<chrono::nanoseconds>(tt2 - tt1).count() << endl;

    return 0;
}