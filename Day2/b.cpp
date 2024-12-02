#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool isGood(const vector<int>& arr) {
    bool good = true;
    for(int i = 1; i < arr.size(); i++) {
        good &= (arr[i] > arr[i - 1] && arr[i] <= arr[i - 1] + 3);
    }
    if(good) {
        return true;
    }
    good = true;
    for(int i = 1; i < arr.size(); i++) {
        good &= (arr[i] < arr[i - 1] && arr[i] >= arr[i - 1] - 3);
    }
    return good;
}
// 386
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

        auto arr_bak = arr;
        // bool done = false;
        for(int i = 0; i < arr.size(); i++) {
            arr.erase(arr.begin() + i);
            if(isGood(arr)) {
                // done = true;
                // copy(arr_bak.begin(), arr_bak.end(), ostream_iterator<int>(cout, " "));
                // cout << endl;
                ans++;
                break;
            }
            arr = arr_bak;
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
