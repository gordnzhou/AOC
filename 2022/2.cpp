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
    string line, s;

    ll ans1 = 0, ans2 = 0;
    while (getline(infile, line)) {
        istringstream iss(line);
        char c1, c2;
        iss >> c1 >> c2;

        // PART 1
        if (c2 == 'X') {
            if (c1 == 'C') ans1 += 6;
            else if (c1 == 'A') ans1 += 3;
            ans1++;
        }
        else if (c2 == 'Y') {
            if (c1 == 'A') ans1 += 6;
            else if (c1 == 'B') ans1 += 3;
            ans1 += 2;
        }
        else {
            if (c1 == 'B') ans1 += 6;
            else if (c1 == 'C') ans1 += 3;
            ans1 += 3;
        }

        // PART 2
        if (c2 == 'X') { //lose
            if (c1 == 'A') ans2 += 3;
            else if (c1 == 'B') ans2 += 1;
            else ans2 += 2;
        }
        else if (c2 == 'Y') { // draw
            ans2 += 3;
            if (c1 == 'A') ans2++;
            else if (c1 == 'B') ans2 += 2;
            else ans2 += 3;
        }
        else {  // win
            ans2 += 6;
            if (c1 == 'A') ans2 += 2;
            else if (c1 == 'B') ans2 += 3;
            else ans2++;
        }
    }
    cout << ans1 << " " << ans2 << "\n";
}