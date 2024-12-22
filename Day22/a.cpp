#include <cassert>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;
using ll = long long;

struct SecretGen {
    ll secret;
    SecretGen(ll init): secret(init) { }

    ll generateNext() {
        ll res = secret * 64;
        secret = secret ^ res;
        secret = secret % 16777216;

        res = secret / 32;
        secret = secret ^ res;
        secret = secret % 16777216;

        res = secret * 2048;
        secret = secret ^ res;
        secret = secret % 16777216;

        return secret;
    }
};

void solve() {
    ll ans = 0;

    ll tmp;
    while(cin >> tmp) {
        SecretGen g(tmp);
        for(int i = 0; i < 1999; i++)
            g.generateNext();
        ans += g.generateNext();
    }

    cout << "Ans: " << ans << endl;
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
