#include <algorithm>
#include <climits>
#include <cmath>
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
    string line;
    ll final_ans = 0;
    for(int it = 1; true; it++) {
        string a, b, p, tmp;
        getline(cin, a);
        getline(cin, b);
        getline(cin, p);
        getline(cin, line);

        if(cin.eof())
            break;
        // cout << "'" << a << "'" << endl;
        ll ax = atoi(a.c_str() + a.find('+') + 1);
        ll ay = atoi(a.c_str() + a.find_last_of('+') + 1);
        ll bx = atoi(b.c_str() + b.find('+') + 1);
        ll by = atoi(b.c_str() + b.find_last_of('+') + 1);
        long long x = atoi(p.c_str() + p.find('=') + 1);
        long long y = atoi(p.c_str() + p.find_last_of('=') + 1);
        x += 10000000000000;
        y += 10000000000000;

        cout << ax << " " << ay << endl;
        cout << bx << " " << by << endl;
        cout << x << " " << y << endl;
        ll ans = LLONG_MAX;
        {
            if((x * ay - y * ax) % (bx * ay - by * ax) == 0) {
                ll yreq = (x * ay - y * ax) / (bx * ay - by * ax);
                // cout << "yreq: " << yreq << endl;
                // cout << x - (bx * yreq) << " % " << ax << endl;
                if((x - (bx * yreq)) % ax == 0) {
                    ll xreq = (x - (bx * yreq)) / ax;
                    ans = xreq * 3 + yreq;
                    // cout << "xreq: " << xreq << endl;
                }
            }
        }

        if(ans != LLONG_MAX) {
            // cout << "it: " << it << " = " << ans << endl;
            final_ans += ans;
        }
    }

    cout << "Ans: " << final_ans << endl;
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
