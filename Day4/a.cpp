#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void solve() {
    vector<string> mat;
    string tmp;
    while(cin >> tmp) {
        mat.push_back(tmp);
    }

    long long ans = 0;
    int n = mat.size(), m = mat[0].size();
    for(int i = 0; i < n; i++) {
        string& curr = mat[i];
        for(int j = 0; j < m - 3; j++) {
            const string& cut = curr.substr(j, 4);
            if(cut == "XMAS" || cut == "SAMX") {
                // cout <<  "1: " << i << " " << j << endl;
                ans++;
            }
        }
    }

    for(int i = 0; i < n - 3; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == 'X' && mat[i + 1][j] == 'M' && mat[i + 2][j] == 'A' && mat[i + 3][j] == 'S') {
                // cout <<  "2: " << i << " " << j << endl;
                ans++;
            }
            if(mat[i][j] == 'S' && mat[i + 1][j] == 'A' && mat[i + 2][j] == 'M' && mat[i + 3][j] == 'X') {
                // cout <<  "2: " << i << " " << j << endl;
                ans++;
            }
        }
    }

    for(int x = 0; x < m; x++) {
        int i = 0, j = x;
        for(; i < n - 3 && j < m - 3; i++, j++) {
            if(mat[i][j] == 'X' && mat[i + 1][j + 1] == 'M' && mat[i + 2][j + 2] == 'A' && mat[i + 3][j + 3] == 'S') {
                // cout <<  "3: " << i << " " << j << endl;
                ans++;
            }
            if(mat[i][j] == 'S' && mat[i + 1][j + 1] == 'A' && mat[i + 2][j + 2] == 'M' && mat[i + 3][j + 3] == 'X') {
                // cout <<  "3: " << i << " " << j << endl;
                ans++;
            }
        }
    }
    for(int x = 1; x < n; x++) {
        int i = x, j = 0;
        for(; i < n - 3 && j < m - 3; i++, j++) {
            if(mat[i][j] == 'X' && mat[i + 1][j + 1] == 'M' && mat[i + 2][j + 2] == 'A' && mat[i + 3][j + 3] == 'S') {
                // cout <<  "3: " << i << " " << j << endl;
                ans++;
            }
            if(mat[i][j] == 'S' && mat[i + 1][j + 1] == 'A' && mat[i + 2][j + 2] == 'M' && mat[i + 3][j + 3] == 'X') {
                // cout <<  "3: " << i << " " << j << endl;
                ans++;
            }
        }
    }



    for(int x = 0; x < m; x++) {
        int i = 0, j = x;
        for(; i < n - 3 && j - 3 >= 0; i++, j--) {
            if(mat[i][j] == 'X' && mat[i + 1][j - 1] == 'M' && mat[i + 2][j - 2] == 'A' && mat[i + 3][j - 3] == 'S') {
                // cout <<  "4: " << i << " " << j << endl;
                ans++;
            }
            if(mat[i][j] == 'S' && mat[i + 1][j - 1] == 'A' && mat[i + 2][j - 2] == 'M' && mat[i + 3][j - 3] == 'X') {
                // cout <<  "4: " << i << " " << j << endl;
                ans++;
            }
        }
    }
    for(int x = 1; x < n; x++) {
        int i = x, j = m - 1;
        for(; i < n - 3 && j - 3 >= 0; i++, j--) {
            if(mat[i][j] == 'X' && mat[i + 1][j - 1] == 'M' && mat[i + 2][j - 2] == 'A' && mat[i + 3][j - 3] == 'S') {
                // cout <<  "4: " << i << " " << j << endl;
                ans++;
            }
            if(mat[i][j] == 'S' && mat[i + 1][j - 1] == 'A' && mat[i + 2][j - 2] == 'M' && mat[i + 3][j - 3] == 'X') {
                // cout <<  "4: " << i << " " << j << endl;
                ans++;
            }
        }
    }

    cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
#if 0
  cin >> t;
#endif
  while (t--)
    solve();
}
