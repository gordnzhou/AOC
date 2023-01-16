#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 


int compare(string line1, string line2) {

	vector<string> lines = {line1, line2};
	vector<vector<string>> a(2);
	int depth = 0, l = 1;
	for (int i = 0; i < 2; ++i) {
		int depth = 0, l = 1;
		for (int j = 0; j < lines[i].size(); ++j) {
			if (lines[i][j] == '[') depth++;
			if (lines[i][j] == ']') depth--;

			if ((lines[i][j] == ',' && depth == 1) || j == lines[i].size() - 1) {
				string temp = lines[i];
				a[i].push_back(temp.substr(l, j - l));
				l = j + 1;
			}
		}
	}

	int res = -1;
	for (int i = 0; i < min(a[0].size(), a[1].size()) && res == -1; ++i) {
		int x1 = (isdigit(a[0][i][0]) ? (a[0][i][0] - '0') : -1);
		int x2 = (isdigit(a[1][i][0]) ? (a[1][i][0] - '0') : -1);
		if (a[0][i] == "10") x1 = 10;
		if (a[1][i] == "10") x2 = 10;

		if (x1 != -1 && x2 != -1) {
			if (x1 != x2) res = (x1 < x2);
		}
		else if (x1 == -1 && x2 == -1) res = compare(a[0][i], a[1][i]);
		else {
			string s1 = a[0][i];
			string s2 = a[1][i];
			if (x1 != -1) s1 = "[" + to_string(x1) + "]";
			else s2 = "[" + to_string(x2) + "]";
			res = compare(s1, s2);
		}
	}

	if (res == -1) {
		if (a[0].size() != a[1].size()) res = (a[0].size() <= a[1].size());
	}
	return res;
}

bool sort_comp(const string &a, const string &b) {
	return (compare(a, b) != 0);
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	ifstream infile("input.txt");
	string line, line1, line2;

	int i = 0, ans = 0;
	vector<string> lines;
	while (getline(infile, line)) {
		istringstream iss(line);
		if (line.length()) lines.push_back(line);

		// PART 1
		// if (lines.size() == 2) {
		// 	i++;
		// 	bool ok = compare(lines[0], lines[1]);
		// 	if (ok) {
		// 		ans += i;
		// 	}
		// 	lines.clear();
		// }
	}

	// PART 2
	ans = 1;
	sort(lines.begin(), lines.end(), sort_comp);
	for (int i = 0; i < lines.size() - 1; ++i) {
		if (lines[i] == "[[2]]" || lines[i] == "[[6]]") ans *= (i + 1);
	}

	cout << ans << "\n";
}