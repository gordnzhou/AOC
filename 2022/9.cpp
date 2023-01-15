#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

const int N = 1e5;

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	ifstream infile("input.txt");
	string line;

	vector<vector<bool>> vis(N, vector<bool>(N, false));
	vector<pair<int, int>> pos(10, {N/2, N/2});
	ll ans = 0;

	while (getline(infile, line)) {
		istringstream iss(line);
		char dir;
		int dist;
		iss >> dir >> dist;
		for (int i = 0; i < dist; ++i) {
			if (dir == 'U') pos[0].first++;
			else if (dir == 'D') pos[0].first--;
			else if (dir == 'L') pos[0].second--;
			else pos[0].second++;
			
			for (int j = 1; j < 10; ++j) {
				int y = pos[j].first, x = pos[j].second;
				int prevy = pos[j - 1].first, prevx = pos[j - 1].second;
				if (abs(x - prevx) > 1) {
					pos[j].second += (prevx - x)/2;

					if (abs(prevy - y) > 1) pos[j].first += (prevy - y) / 2;
					else pos[j].first += prevy - y;
				} 
				else if (abs(y - prevy) > 1) {
					pos[j].first += (prevy - y) / 2;
					pos[j].second += prevx - x;
				}
			}
			if (!vis[pos[9].second][pos[9].first]) ans++;
			vis[pos[9].second][pos[9].first] = true;
		}
	}

	cout << ans << "\n";
}