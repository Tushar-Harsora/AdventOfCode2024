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
    int ans = 0;
    string s;
    int a;
    while(true) {
        vector<int> arr;
        if(cin.eof())
            break;
        getline(cin, s);
        if(s.empty())
            break;
        stringstream ss(s);
        while(ss >> a)
            arr.push_back(a);

        // copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
        // cout << endl;

        bool good = true;
        for(int i = 1; i < arr.size(); i++) {
            good &= (arr[i] > arr[i - 1] && arr[i] <= arr[i - 1] + 3);
        }
        if(good) {
            ans++;
            continue;
        }
        good = true;
        for(int i = 1; i < arr.size(); i++) {
            good &= (arr[i] < arr[i - 1] && arr[i] >= arr[i - 1] - 3);
        }
        ans += good;
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
