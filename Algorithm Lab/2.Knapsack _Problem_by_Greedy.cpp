#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Item
{
	float profit;
	float weight;
};

bool Compare(Item x, Item y) {
	if (x.profit/x.weight > y.profit/y.weight){return true;}
	else { return false; }
}

float Knapsack_Greedy_Algo(vector<Item> vec, float capacity)
{
	sort(vec.begin(), vec.end(), Compare);
	float maxValue = 0;

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].weight < capacity){
			maxValue += vec[i].profit;
			capacity -= vec[i].weight;
		}
		else{
			maxValue += capacity * (vec[i].profit / vec[i].weight);
			break;
		}
	}

	return maxValue;
}

int main()
{
	float capacity = 50;
	int n = 5;

	vector<Item> allItems;
	Item input;

	for (int i = 0; i < n; i++)
	{
		input.profit = rand() % 80 + 1;
		input.weight = rand() % 40 + 1;
		cout << input.profit << " " << input.weight << endl;
		allItems.push_back(input);
	}
	cout << "Maximum value we can obtain = " << Knapsack_Greedy_Algo(allItems, capacity) << endl;
}