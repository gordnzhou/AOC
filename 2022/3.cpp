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

	ll ans = 0;
	int cnt[53] = {0};
	int j = 0;
	while (getline(infile, line)) {
		istringstream iss(line);
		string s;
		iss >> s;
		
		// PART 1
		// bool vis[53] = {false};
		// for (int i = 0; i < s.length()/2; ++i) {
		// 	int idx = s[i] - 'a' + 1;
		// 	if (idx < 0) idx = s[i] - 'A' + 27;
		// 	vis[idx] = true;
		// }

		// for (int i = s.length()/2; i < s.length(); ++i) {
		// 	int idx = s[i] - 'a' + 1;
		// 	if (idx < 0) idx = s[i] - 'A' + 27;
		// 	if (vis[idx]) {
		// 		ans += idx;
		// 		vis[idx] = false;
		// 	}
		// }

		// PART 2;
		bool vis[53] = {false};
		for (int i = 0; i < s.length(); ++i) {
			int idx = s[i] - 'a' + 1;
			if (idx < 0) idx = s[i] - 'A' + 27;
			if (!vis[idx]) {
				cnt[idx]++;
				vis[idx] = true;
			}
		}

		j++;
		if (j % 3 == 0) {

			for (int i = 0; i < 53; ++i) {
				if (cnt[i] >= 3) ans += i;
				cnt[i] = 0;
			}
		}
	}
	cout << ans << "\n";
}