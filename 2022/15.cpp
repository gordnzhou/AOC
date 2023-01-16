#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

int N = 4e6;

vector<vector<int>> dists;
vector<pair<int, int>> beacons;

bool check(pair<int, int> coord) {
	int x = coord.first, y = coord.second;
	if (x < 0 || x > N || y < 0 || y > N) return false;

	for (auto b : beacons) {
		if (b == coord) return false;
	}

	for (auto d : dists) {
		int dist = abs(x - d[0]) + abs(y - d[1]);
		if (dist <= d[2]) return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	ifstream infile("input.txt");
	string line;


	while (getline(infile, line)) {
		istringstream iss(line);
		vector<string> lines;
		string s;
		while (iss >> s) {
			lines.push_back(s);
		}

		int x1 = stoi(lines[2].substr(2, lines[2].size() - 3));
		int y1 = stoi(lines[3].substr(2, lines[3].size() - 3));
		int x2 = stoi(lines[8].substr(2, lines[8].size() - 3));
		int y2 = stoi(lines[9].substr(2, lines[9].size() - 2));
		
		int dist = abs(x1 - x2) + abs(y1 - y2);
		dists.push_back({x1, y1, dist});
		beacons.push_back({x2, y2});
	}


	// PART 2
	ll x = 0, y = 0;
	for (auto d : dists) {
		int r = d[2] + 1, x1 = d[0], y1 = d[1];

		for (int i = 0; i < r; ++i) {
			if (check({x1 + r - i, y1 + i})) {
				x = x1 + r - i;
				y = y1 + i;
			}
			if (check({x1 + r - i, y1 - i})) {
				x = x1 + r - i;
				y = y1 - i;
			}
			if (check({x1 - r + i, y1 + i})) {
				x = x1 - r + i;
				y = y1 + i;
			}
			if (check({x1 - r + i, y1 - i})) {
				x = x1 - r + i;
				y = y1 - i;
			}
		}

		if (x != 0 || y != 0) {
			cout << x * 4000000LL + y << "\n";
			break;
		}
	}
}