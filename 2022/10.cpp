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

	int cycles = 0, x = 1, ans = 0;
	vector<int> xs;
	while (getline(infile, line)) {
		istringstream iss(line);

		int inc = 2;
		if (line == "noop") inc = 1;
		for (int i = 0; i < inc; ++i) {
			// PART 1
			// if ((cycles - 20) % 40 == 0) ans += x * cycles;
			
			xs.push_back(x);
			cycles++;
		}

		if (line != "noop") {
			string a;
			int val;
			iss >> a >> val;
			x += val;
		}
	}
	
	// PART 2;
	for (int i = 0; i < xs.size(); ++i) {
		if (i % 40 >= xs[i] - 1 && i % 40 <= xs[i] + 1) cout << "#";
		else cout << ".";
		if ((i + 1) % 40 == 0) cout << "\n";
	}
}