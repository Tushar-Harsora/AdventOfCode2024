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

void solve() {
    ll ans = 0, tmp = 0;
    unordered_map<ll, ll> in;
    while(cin >> tmp)
        in[tmp]++;


    auto get_digits = [](ll num) {
        int digits = 0;
        while(num > 0) {
            digits++;
            num /= 10;
        }
        return digits;
    };

    auto split_num = [get_digits](ll num) -> pair<ll, ll> {
        int digits = get_digits(num);
        assert(digits % 2 == 0);
        string r;
        for(int i = 0; i < digits / 2; i++) {
            r.push_back('0' + num % 10);
            num /= 10;
        }
        reverse(r.begin(), r.end());
        return make_pair(num, stoll(r));
    };

    // copy(in.begin(), in.end(), ostream_iterator<ll>(cout, " "));
    // cout << endl;
    const int iterations = 75;
    for(int iteration = 0; iteration < iterations; iteration++) {
        unordered_map<ll, ll> nextt;
        for(auto pr : in) {
            ll num = pr.first;
            ll num_cnt = pr.second;
            if(num == 0) {
                nextt[1] += num_cnt;
            } else if(get_digits(num) % 2 == 0) {
                auto split = split_num(num);
                nextt[split.first] += num_cnt;
                nextt[split.second] += num_cnt;
            } else {
                nextt[num * 2024] += num_cnt;
            }
        }

        in = std::move(nextt);
        // cout << ((iteration + 1) / (double)iterations * 100.) << "% done " << in.size() << " elements" << endl;
    }

    for(auto& elems : in) {
        ans += elems.second;
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
