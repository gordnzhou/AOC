#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

map<string, int> storage;
map<string, vector<string>> chil;

ll dfs(string a) {
	ll tot = storage[a];
	for (string &x : chil[a]) {
		tot += dfs(x);
	}
	return tot;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	ifstream infile("input.txt");
	string line;

	vector<string> path;
	while (getline(infile, line)) {
		istringstream iss(line);

		string a, b;
		iss >> a >> b;
		if (a == "$") {
			if (b == "cd") {
				string c;
				iss >> c;
				if (c == "..") path.pop_back();
				else path.push_back(c);
			}
		}
		else {
			string name = "";
			for (int i = 1; i < path.size(); ++i) name.append("/"+path[i]);
			if (a == "dir") chil[name].push_back(name+"/"+b);
			else storage[name] += (ll)stoi(a);
		}
	}

	// PART 1
	// ll ans = 0;
	// for (auto x : chil) {
	// 	ll tot = dfs(x.first);
	// 	if (tot <= 100000) ans += tot;
	// }

	// PART 2
	ll ans = 1e9, full = dfs("");
	for (auto x : chil) {
		ll tot = dfs(x.first);
		if (70000000LL - full + tot >= 30000000LL) ans = min(ans, tot);
	}
	cout << ans << "\n";
}