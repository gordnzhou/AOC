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

	vector<string> lines;
	while (getline(infile, line)) {
		istringstream iss(line);
		lines.push_back(line);

	}

	int n = lines.size(), m = lines[0].length();

	pair<int, int> start, end;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (lines[i][j] == 'S') {
				start = {i, j};
				lines[i][j] = 'a';
			}
			else if (lines[i][j] == 'E') {
				end = {i, j};
				lines[i][j] = 'z';
			}
		}
	}
	
	vector<vector<vector<pair<int, int>>>> adj(n, vector<vector<pair<int, int>>>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int cur = lines[i][j] - 'a';
			if (i && lines[i - 1][j] - 'a' >= cur - 1) {
				adj[i][j].push_back({i - 1, j});
			}
			if (i != n - 1 && lines[i + 1][j] - 'a' >= cur - 1) {
				adj[i][j].push_back({i + 1, j});
			}
			if (j && lines[i][j - 1] - 'a' >= cur - 1) {
				adj[i][j].push_back({i, j - 1});
			}
			if (j != m - 1 && lines[i][j + 1] - 'a' >= cur - 1) {
				adj[i][j].push_back({i, j + 1});
			}
		}
	}

	vector<vector<int>> dist (n, vector<int>(m, 1e9));

	// PART 1
	// BFS
	// dist[start.first][start.second] = 0;
	// bool vis[n][m];
	// memset(vis, 0, sizeof(vis[0][0]) * n * m);
	// queue<pair<int, int>> q;
	// q.push(start); vis[start.first][start.second] = true;
	// while (!q.empty()) {
	// 	pair<int, int> &t = q.front();
	// 	q.pop();
	// 	for (auto &c : adj[t.first][t.second]) {
	// 		if (vis[c.first][c.second] == false) {
	// 			q.push(c);
	// 			dist[c.first][c.second] = dist[t.first][t.second] + 1;
	// 			vis[c.first][c.second] = true;
	// 		}
	// 	}
	// }
	// cout << dist[end.first][end.second] << "\n";

	// PART 2
	// BFS (from end -> any 'a' spot)
	dist[end.first][end.second] = 0;
	bool vis[n][m];
	memset(vis, 0, sizeof(vis[0][0]) * n * m);
	queue<pair<int, int>> q;
	q.push(end); vis[end.first][end.second] = true;
	while (!q.empty()) {
		pair<int, int> &t = q.front();
		q.pop();
		for (auto &c : adj[t.first][t.second]) {
			if (vis[c.first][c.second] == false) {
				q.push(c);
				dist[c.first][c.second] = dist[t.first][t.second] + 1;
				vis[c.first][c.second] = true;
			}
		}
	}

	int ans = 1e9;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (lines[i][j] == 'a') {
				ans = min(ans, dist[i][j]);
			}
		}
		cout << "\n";
	}
	cout << ans << "\n";
}