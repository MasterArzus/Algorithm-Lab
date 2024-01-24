#include <iomanip>
#include <iostream>
#include <queue>
#include <algorithm>
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

public:
    Graph(char vexs[], int vlen, int matrix[][9]);
    ~Graph();
    void print();
    int DP(int start);
    int Dp(int start);

private:
    int getPosition(char ch);
    int firstVertex(int v);
    int nextVertex(int v, int w);
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

int Graph::DP(int start)
{
    int i = firstVertex(start);
    if (i < 0) { return 0; }
    int min_res = 0;
    int min_temp = mMatrix[start][i];
    if (nextVertex(start, i) > 0){
        min_res = min(mMatrix[start][i] + DP(i), mMatrix[start][nextVertex(start, i)] + DP(nextVertex(start, i)));
    }
    else { min_res = mMatrix[start][i] + DP(i); }

    while (nextVertex(start, i) > 0 )
    {
        min_res = min(mMatrix[start][i] + DP(i), min_res);
        cout << "(" << start << ", " << i << ")   "<< min_res << ":" << mMatrix[start][i] + DP(i) << "" << endl;
        cout << min_res << endl;
        i = nextVertex(start, i);
    }

    return min_res;
}

int Graph::Dp(int start)
{
    int minDis[totalnum] = { 0 };

    for (int i = 0; i < verticeNum; i++){
        if (mMatrix[start][i] > 0 && mMatrix[start][i] < INF) minDis[i] = mMatrix[start][i];
    }

    for (int cur = 1; cur < verticeNum; cur++)
    {
        for (int i = 0; i < verticeNum; i++) {
            if (mMatrix[cur][i] > 0 && mMatrix[cur][i] < INF){
                if ( minDis[i] <= 0) minDis[i] = mMatrix[cur][i] + minDis[cur];
                else if (mMatrix[cur][i] + minDis[cur] < minDis[i]) minDis[i] = mMatrix[start][i] + minDis[cur];
            }
        }
    }
    return minDis[verticeNum - 1];
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
    char Vertices[] = { 'S', 'V1', 'V2', 'V3', 'V4', 'V5', 'T'};
    int matrix[][9] = {
         {   0,   2,   3,   4, INF, INF, INF},
         { INF,   0,   3, INF,   2, INF, INF},
         { INF, INF,   0, INF,   2,   2, INF},
         { INF, INF, INF,   0, INF,   2, INF},
         { INF, INF, INF, INF,   0,   1,   3},
         { INF, INF, INF, INF, INF,   0,   5},
         { INF, INF, INF, INF, INF, INF,   0} };

    int VerticesLen = sizeof(Vertices) / sizeof(Vertices[0]);
    Graph* myGraph;

    auto tt1 = Clock::now();
    myGraph = new Graph(Vertices, VerticesLen, matrix);
    cout << "The min cost is: " << myGraph->Dp(0) << endl;
    myGraph->print();
    auto tt2 = Clock::now();
    cout << "Time cost: " << chrono::duration_cast<chrono::nanoseconds>(tt2 - tt1).count() << endl;

    return 0;
}