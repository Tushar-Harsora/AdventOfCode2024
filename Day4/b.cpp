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

    for(int i = 0; i < n - 2; i++) {
        for(int j = 0; j < m - 2; j++) {
            bool good = true;
            good &= mat[i + 1][j + 1] == 'A';
            good &= (mat[i][j] == 'M' && mat[i + 2][j + 2] == 'S') || (mat[i][j] == 'S' && mat[i + 2][j + 2] == 'M');
            good &= (mat[i][j + 2] == 'M' && mat[i + 2][j] == 'S') || (mat[i][j + 2] == 'S' && mat[i + 2][j] == 'M');
            ans += good;
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
