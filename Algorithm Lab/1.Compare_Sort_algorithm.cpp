#include<iostream>
#include<chrono>
#include<iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

template<typename T>
class cAlg
{
private:
	int N = 0;
	T fD[2005] = {};
	
public:
	cAlg() {}
	~cAlg() {};

	void initialization(int n, T *fd){
		N = n;
		*fD = *fd;
	}

	T* get_fD(){}

	void set_fD(int n, T fd[]) {
		N = n;
		for (int i = 0; i < n; i++)
		{
			fD[i] = fd[i];
		}
	}

	bool lt(T x, T y) {
		if (x < y) {return true;}
		else {return false;}
	}

	bool gt(T x, T y) {
		if (x >= y) {return true;}
		else {return false;}
	}

	void swap(T A[], int x, int y) {
		T temp = A[x];
		A[x] = A[y];
		A[y] = temp;
	}

	void bubsort(T A[], int n) {
		for (int i = 0; i < n - 1; i++)
			for (int j = n - 1; j > i; j--)
				if (cAlg::lt(A[j], A[j - 1]))
					swap(A, j, j - 1);
	}

	void selsort(T A[], int n) {
		for (int i = 0; i < n - 1; i++) {
			int lowindex = i; // Remember its index
			for (int j = n - 1; j > i; j--) // Find least
				if (cAlg::lt(A[j], A[lowindex]))
					lowindex = j; // Put it in place
			if (lowindex != i)
				swap(A, i, lowindex);
		}
	}

	void inssort(T A[], int n) {
		for (int i = 1; i < n; i++){
			for (int j = i; (j > 0) && (cAlg::lt(A[j], A[j - 1])); j--) {
				swap(A, j, j - 1);
			}
		}
	}

	void mergesort(T A[], T temp[], int left, int right) {
		int mid = (left + right) / 2;
		if (left == right) return;
		mergesort(A, temp, left, mid);
		mergesort(A, temp, mid + 1, right);
		for (int i = left; i <= right; i++) // Copy
			temp[i] = A[i];
		int i1 = left; int i2 = mid + 1;
		for (int curr = left; curr <= right; curr++) {
			if (i1 == mid + 1) // Left exhausted
				A[curr] = temp[i2++];
			else if (i2 > right) // Right exhausted
				A[curr] = temp[i1++];
			else if (cAlg::lt(temp[i1], temp[i2]))
				A[curr] = temp[i1++];
			else A[curr] = temp[i2++];
		}
	}

	int findpivot(T A[], int i, int j) {
		return (i + j) / 2;
	}

	int partition(T A[], int l, int r, T& pivot) {
		do { // Move the bounds in until they meet
			while (cAlg::lt(A[++l], pivot));
			while ((r != 0) && cAlg::gt(A[--r], pivot));
			swap(A, l, r); // Swap out-of-place values
		} while (l < r); // Stop when they cross
		swap(A, l, r); // Reverse last swap
		return l; // Return first pos on right
	}

	void qsort(T A[], int i, int j) {
		if (j <= i) return; // Don't sort 0 or 1 Elem 
		T pivotindex = findpivot(A, i, j);
		swap(A, pivotindex, j); // Put pivot at end 

		T k = partition(A, i - 1, j, A[j]);
		swap(A, k, j); // Put pivot in place
		qsort(A, i, k - 1);
		qsort(A, k + 1, j);
	}

	void Alg_Sort1() {this -> bubsort(fD, N);}
	void Alg_Sort2() {this->inssort(fD, N);}
	void Alg_Sort3() {this->selsort(fD, N);}
	void Alg_Sort4() {
		float temp[2005] = {};
		this ->mergesort(fD, temp, 0, N);
	}
	void Alg_Sort5() {this->qsort(fD, 0, N);}
};

bool csvWrite(vector<vector<double>> data, string output_filename)
{
	ofstream outFile(output_filename, ios::out);
	if (!outFile){
		cout << "打开文件失败！" << endl;
		return false;
	}
	outFile << "Numbers,Bubble,Insertion,Selection,Merge,Quick " << endl;
	for (auto i : data) {
		for (auto j : i) {
			outFile << j << ",";
		}
		outFile << endl;
	}
	outFile.close();
	return true;
}

int main()
{
	cout << "=========算法排序实验========== \n";

	int iNum = 2005, iS;
	float fRandom[2005];

	typedef chrono::high_resolution_clock Clock;
	double t1, t2, t3, t4, t5;
	vector<vector<double>> time(10);
	cAlg<typename float> algo;
	
	cout << left << "Numbers \t" << "Bubble \t" << "Insertion \t" << "Selection \t" << "Merge \t" << "Quick \t" << endl;
	for (int i = 1; i < 11; i++)
	{
		iS = i * 200;
		time[i-1].push_back(iS);

		for (int i = 0; i < iS; i++)
		{
			fRandom[i] = rand() % iS;
		}

		algo.initialization(iS, fRandom);
		

		cout << iS << " \t";
		algo.set_fD(iS, fRandom);
		auto tt1 = Clock::now();
		algo.Alg_Sort1();
		auto tt2 = Clock::now();
		t1 = chrono::duration_cast<chrono::nanoseconds>(tt2 - tt1).count();
		cout << t1 << " \t";
		time[i-1].push_back(t1);

		algo.set_fD(iS, fRandom);
		tt1 = Clock::now();
		algo.Alg_Sort2();
		tt2 = Clock::now();
		t2 = chrono::duration_cast<chrono::nanoseconds>(tt2 - tt1).count();
		cout << t2 << " \t";
		time[i - 1].push_back(t2);

		algo.set_fD(iS, fRandom);
		tt1 = Clock::now();
		algo.Alg_Sort3();
		tt2 = Clock::now();
		t3 = chrono::duration_cast<chrono::nanoseconds>(tt2 - tt1).count();
		cout << t3 << " \t";
		time[i - 1].push_back(t3);

		algo.set_fD(iS, fRandom);
		tt1 = Clock::now();
		algo.Alg_Sort4();
		tt2 = Clock::now();
		t4 = chrono::duration_cast<chrono::nanoseconds>(tt2 - tt1).count();
		cout << t4 << " \t";
		time[i - 1].push_back(t4);

		algo.set_fD(iS, fRandom);
		tt1 = Clock::now();
		algo.Alg_Sort5();
		tt2 = Clock::now();
		t5 = chrono::duration_cast<chrono::nanoseconds>(tt2 - tt1).count();
		cout << t5 << endl;
		time[i - 1].push_back(t5);
	}

	csvWrite(time, "Lab1.csv");
}
