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

	vector<string> ma;
	while (getline(infile, line)) {
		istringstream iss(line);
		ma.push_back(line);	
	}

	// PART 2
	int n = ma.size(), m = ma[0].length();
	ll ans = 0;
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 1; j < m - 1; ++j) {
			int cur = ma[i][j] - '0';

			ll tot[4] = {i, n - i - 1, j, m - j - 1};
			for (int k = i - 1; k >= 0; --k) {
				if (ma[k][j] - '0' >= cur) {
					tot[0] = i - k;
					break;
				}
			}
			for (int k = i + 1; k < n; ++k) {
				if (ma[k][j] - '0' >= cur) {
					tot[1] = k - i;
					break;
				}
			}
			for (int k = j - 1; k >= 0; --k) {
				if (ma[i][k] - '0' >= cur) {
					tot[2] = j - k;
					break;
				}
			}
			for (int k = j + 1; k < m; ++k) {
				if (ma[i][k] - '0' >= cur) {
					tot[3] = k - j;
					break;
				}
			}

			ll score = 1;
			for (int k = 0; k < 4; ++k) {
				score *= tot[k];
			}
			ans = max(ans, score);
		}
	}

	cout << ans << "\n";
}