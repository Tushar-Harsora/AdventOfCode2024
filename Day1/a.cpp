#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

void solve() {
    vector<int> a, b;
    int x, y;
    while(cin >> x >> y) {
        a.push_back(x);
        b.push_back(y);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    long long ans = 0;
    for(int i = 0; i < a.size(); i++) {
        ans += abs(a[i] - b[i]);
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
