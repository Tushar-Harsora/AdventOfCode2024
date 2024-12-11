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
    vector<ll> in;
    while(cin >> tmp)
        in.push_back(tmp);


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
    const int iterations = 10;
    for(int iteration = 0; iteration < iterations; iteration++) {
        vector<ll> nextt;
        for(int i = 0; i < in.size(); i++) {
            if(in[i] == 0) {
                nextt.push_back(1);
            } else if(get_digits(in[i]) % 2 == 0) {
                auto pr = split_num(in[i]);
                nextt.push_back(pr.first);
                nextt.push_back(pr.second);
            } else {
                nextt.push_back(in[i] * 2024);
            }
        }

        in = nextt;
        cout << ((iteration + 1) / (double)iterations * 100.) << "% done " << in.size() << " elements" << endl;
        // copy(in.begin(), in.end(), ostream_iterator<ll>(cout, " "));
        // cout << endl;
    }
    cout << in.size() << endl;
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
