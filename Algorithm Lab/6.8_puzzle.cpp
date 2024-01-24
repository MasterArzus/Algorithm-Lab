//#include<iostream>
//#include<stack>
//#include<queue>
//using namespace std;
//
//class PuzzleState
//{
//public:
//	PuzzleState(int n[3][3]);
//	~PuzzleState();
//
//	bool isgoal();
//private:
//	int numbers[3][3] = { 0 };
//};
//
//
//class Pizzle
//{
//public:
//	Pizzle() {};
//	~Pizzle() {};
//
//	void move();
//	bool BreadthFS(PuzzleState root);
//	void DepthFS(PuzzleState root);
//	void BestFS(PuzzleState root);
//	void DBD(PuzzleState root);
//private:
//
//};
//
//PuzzleState::PuzzleState(int n[3][3])
//{
//	for (int i = 0; i < 3; i++){
//		for (int j = 0; j < 3; j++){
//			numbers[i][j] = n[i][j];
//		}
//	}
//}
//
//PuzzleState::~PuzzleState(){}
//
//bool PuzzleState::isgoal() {
//	for (int i = 0; i < 3; i++) {
//		if (numbers[0][i] != 1 + i) return false;
//		if (numbers[2][2-i] != 5 + i) return false;
//	}
//	if (numbers[1][0] != 8) return false;
//	if (numbers[1][2] != 4) return false;
//	return true;
//}
//
//void Pizzle::move()
//{
//
//}
//
//bool Pizzle::BreadthFS(PuzzleState root)
//{
//	queue<PuzzleState> q;
//	q.push(root);
//	while (!q.empty())
//	{
//		if (q.front().isgoal()) return true;
//
//
//
//	}
//}
//
//void Pizzle::DepthFS(PuzzleState root)
//{
//
//}
//
//void Pizzle::BestFS(PuzzleState root)
//{
//
//}
//
//void Pizzle::DBD(PuzzleState root)
//{
//
//}