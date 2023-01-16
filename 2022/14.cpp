#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

int N = 1000;
vector<vector<bool>> vis(N, vector<bool>(N, false));

pair<int, int> fall(int x, int y) {
	if (y == N - 1) return {x, y};

	if (!vis[x][y + 1]) return fall(x, y + 1);
	if (!vis[x - 1][y + 1]) return fall(x - 1, y + 1);
	if (!vis[x + 1][y + 1]) return fall(x + 1, y + 1);
	return {x, y};
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	ifstream infile("input.txt");
	string line;


	int floor = 0;
	while (getline(infile, line)) {
		istringstream iss(line);
		
		int x1, y1, x2, y2;
		iss >> x1 >> y1;
		while (iss >> x2 >> y2) {
			if (x1 == x2) {
				for (int j = min(y1, y2); j <= max(y1, y2); ++j) {
					vis[x1][j] = true;
					floor = max(floor, j);
				}
			}
			else {
				for (int j = min(x1, x2); j <= max(x1, x2); ++j) {
					vis[j][y1] = true;
				}
				floor = max(floor, y1);
			}
			x1 = x2;
			y1 = y2;
		}
	}

	// PART 2
	floor += 2;
	for (int i = 0; i < N; ++i) {
		vis[i][floor] = true;
	}

	int ans = 0;
	while (!vis[500][0]) {
		pair<int, int> cur = fall(500, 0);
		vis[cur.first][cur.second] = true;
		if (cur.second == N - 1) break;
		ans++;
	}
	cout << ans << "\n";
}