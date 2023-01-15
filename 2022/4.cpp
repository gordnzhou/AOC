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
	while (getline(infile, line)) {
		istringstream iss(line);
		int l1, l2, r1, r2;
		iss >> l1 >> r1 >> l2 >> r2;

		// PART 1
		// if (min(l1, l2) == l1 && max(r1, r2) == r1) ans++;
		// else if (min(l1, l2) == l2 && max(r1, r2) == r2) ans++;

		// PART 2
		if (l1 < r2 && r1 >= l2) ans++;
		else if (l2 < r1 && r2 >= l1) ans++;
	}
	cout << ans << "\n";
}