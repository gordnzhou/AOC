#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

vector<string> strings;
void split(string a) {
	stringstream ss;
	ss << a;
	string temp;
	while (!ss.eof()) {
		ss >> temp;
		strings.push_back(temp);
	}
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	ifstream infile("input.txt");
	string line;
	vector<string> lines;
	while (getline(infile, line)) {
		istringstream iss(line);
		lines.push_back(line);	
	}

	int n = (lines.size() + 1)/7;

	vector<queue<ll>> items(n);
	vector<ll> check; // divisible check
	vector<pair<int, int>> res;

	// first 0 = add by second
	// first 1 = multiply by second
	// first 2 = square
	vector<pair<int, ll>> op;

	for (int i = 0; i < n; ++i) {
		int cur = i * 7;

		split(lines[cur + 1]);
		for (auto y : strings) {
			// ADD COMMA TO END OF EVERY NUMBER (ESPECIALLY LAST!!)
			y.pop_back();

			bool ok = true;
			for (auto x : y) if (!isdigit(x)) ok = false;
			if (ok && !y.empty()) {
				items[i].push(stoi(y));
			}
		}

		strings.clear();
		split(lines[cur + 2]);
		if (strings[4] == "+") {
			op.push_back({0, stoi(strings[5])});
		}
		else {
			bool ok = true;
			for (auto x : strings[5]) if (!isdigit(x)) ok = false;
			if (ok) op.push_back({1, stoi(strings[5])});
			else op.push_back({2, 1});
		}

		strings.clear();
		split(lines[cur + 3]);
		check.push_back(stoi(strings[3]));

		int yes, no;
		strings.clear();
		split(lines[cur + 4]);
		yes = stoi(strings[5]);
		strings.clear();
		split(lines[cur + 5]);
		no = stoi(strings[5]);

		res.push_back({yes, no});
	}

	ll MOD = 1;
	for (auto c : check) MOD *= c;

	vector<ll> scores(n);
	int N = 1e4;
	for (int k = 0; k < N; ++k) {
		for (int i = 0; i < n; ++i) {
			while (!items[i].empty()) {
				ll &item = items[i].front();
				scores[i]++;

				if (op[i].first == 2) item = (item * item) % MOD;
				else if (op[i].first == 1) item = (item * op[i].second) % MOD;
				else item += op[i].second;

				item %= MOD;
				// item /= 3;

				if (item % check[i]) items[res[i].second].push(item);
				else items[res[i].first].push(item);

				items[i].pop();
			}
		}
	}
	sort(scores.begin(), scores.end());
	cout << scores[n - 1] * scores[n - 2] << "\n";
}