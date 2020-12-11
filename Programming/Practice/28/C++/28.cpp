#include <iostream>
#include <algorithm>
#include "./../../practice.cpp"

using namespace std;

int main () {
	int n; cout << "Введите число: ", cin >> n; // number to be factorized
	vector <pair<int, int>> ans; // verctor for data storage
	for (int i = 2; i * i <= n; i++) { // for i < sqrt(n)
		if (n % i == 0) { // if i is divider
			ans.push_back(make_pair(i, 0)); // add i to storage
			while (n % i == 0) { // and remove all i multipliers from current n
				n /= i; // removing single i
				ans[ans.size() - 1].second++; // updating counter (on last pair)
			}
		}
	}
	if (n > 1) { // if n has dividers differ from 1
		ans.push_back(make_pair(n, 1)); // add n as divider one time
	}

	sort(ans.begin(), ans.end(), [](auto a, auto b) { return a.first < b.first; }); // sort by divider name
	for (int i = 0; i < ans.size(); i++) { // for each divider
		auto divider = ans[i];
		if (divider.second > 1) {
			string format = (i == 0 ? "%d^%d" : "*%d^%d "); // if first do not print "*"
			printf(format.c_str(), ans[i].first, ans[i].second);
		}
		else {
			string format = (i == 0 ? "%d" : "*%d"); // if first do not print "*"
			printf(format.c_str(), ans[i].first);
		}
	}
	
	printf("\n");
	return 0;
}
