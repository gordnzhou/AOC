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

	while (getline(infile, line)) {
		istringstream iss(line);
		string s;
		iss >> s;

		// int N = 4;
		int N = 14;

		for (int i = N - 1; i < s.size(); ++i) {
			bool ok = true;
			for (int j = i - N + 1; j <= i; ++j) {
				for (int k = i - N + 1; k <= i; ++k) {
					if (j == k) continue;
					if (s[j] == s[k]) ok = false;
				} 
			}
			if (ok) {
				cout << i + 1 << "\n";
				break;
			}
		}
	}
}