#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;
using ll = long long;

void print_arr(const vector<ll>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] != INT_MAX)
            cout << arr[i];
        else
            cout << '.';
    }
    cout << endl;
}

// 6209494449647
// 6209494444401
// 6211348208140
void solve() {
    ll ans = 0, blockid = 0;
    string s;
    cin >> s;
    vector<ll> arr;
    for(int i = 0; i < s.size(); i++) {
        if(i & 1) {
            int times = s[i] - '0';
            while(times--)
                arr.push_back(INT_MAX);
        } else {
            int times = s[i] - '0';
            while(times--)
                arr.push_back(blockid);
            blockid++;
        }
    }

    // print_arr(arr);
    int l = 0, r = arr.size() - 1, n = arr.size();
    while(l < r) {
        while(l + 1 < n && arr[l] != INT_MAX)
            l++;
        while(r - 1 >= 0 && arr[r] == INT_MAX)
            r--;
        assert(arr[l] == INT_MAX && arr[r] != INT_MAX);
        if(l >= r)
            break;
        swap(arr[l], arr[r]);
        l++;
        r--;
        // print_arr(arr);
    }

    cout << endl;
    // print_arr(arr);

    for(int i = 0; i < n; i++) {
        if(arr[i] != INT_MAX)
            ans += i * arr[i];
    }

    cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
#if 0
    scanf("%d", &t);
#endif
  while (t--)
    solve();
}
