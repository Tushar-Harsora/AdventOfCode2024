#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;
using ll = long long;

void get_sums(vector<ll> ops, vector<ll>& sums) {
    if(!ops.size())
        return;

    ll mx = 1 << (ops.size() - 1);
    // cout << ops.size() << " : ";
    for(int x = 0; x < mx; x++) {
        ll sum = ops[0];
        for(int i = 1; i < ops.size(); i++) {
            switch((x >> (i - 1)) & 1) {
                case 0: {
                    sum = sum + ops[i];
                    break;
                }
                case 1: {
                    sum = sum * ops[i];
                    break;
                }
            }
        }
        sums.push_back(sum);
    }
}

// 18903717626
void solve() {
    ll ans = 0;
    string tmp;
    while(getline(cin, tmp)) {
        string s_nums = tmp.substr(tmp.find(' '));
        ll target, num; sscanf(tmp.c_str(), "%lld", &target);
        vector<ll> ops;
        stringstream ss;
        ss << s_nums;
        while(ss >> num)
            ops.push_back(num);

        for(int i = 1; i <= ops.size(); i++) {
            vector<ll> left, right;
            // take first i elements;
            vector<ll> lops(ops.begin(), ops.begin() + i);
            get_sums(lops, left);

            vector<ll> rops(ops.begin() + i, ops.end());
            get_sums(rops, right);

            // cout << "i: " << i << endl;
            // copy(left.begin(), left.end(), ostream_iterator<ll>(cout, " ")); cout << endl;
            // copy(right.begin(), right.end(), ostream_iterator<ll>(cout, " ")); cout << endl;
            // cout << endl;
            for(int x = 0; x < left.size(); x++) {
                if(left[x] == target) {
                    ans += target;
                    goto endloop;
                }
                for(int y = 0; y < right.size(); y++) {
                    ll sum = stoll(to_string(left[x]) + to_string(right[y]));
                    if(sum == target) {
                        cout << tmp << endl;
                        ans += target;
                        goto endloop;
                    }
                }
            }
        }
        endloop:
        (void)0;
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
