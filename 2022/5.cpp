#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	ifstream infile("input.txt");
	string line;

	int N = 9;
	bool start = false;
	vector<stack<char>> stacks(N);
	vector<vector<char>> pile(N);

	while (getline(infile, line)) {
		istringstream iss(line);
		
		if (!line.length()) {
			start = true;
			for (int i = 0; i < N; ++i) {
				reverse(pile[i].begin(), pile[i].end());
				for (auto x : pile[i]) {
					stacks[i].push(x);
				}
			}
			continue;
		}

		if (!start) {
			for (int i = 0; i < N; ++i) {
				if (line[i] != ' ') pile[i].push_back(line[i]);
			}
		}
		else {
			int cnt, from, to;
			iss >> cnt >> from >> to;
			from--; to--;

			// PART 1
			// while (cnt--) {
			// 	char &c = stacks[from].top();
			// 	stacks[to].push(c);
			// 	stacks[from].pop();
			// }

			// PART 2
			vector<int> together;
			for (int i = 0; i < cnt; ++i) {
				char &c = stacks[from].top();
				together.push_back(c);
				stacks[from].pop();
			}

			for (int i = cnt - 1; i >= 0; --i) {
				stacks[to].push(together[i]);
			}
		}
	}

	string ans = "";
	for (int i = 0; i < N; ++i) {
		char &t = stacks[i].top();
		ans.push_back(t);
	}
	cout << ans << "\n";
}