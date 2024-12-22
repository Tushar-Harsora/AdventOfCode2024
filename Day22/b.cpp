#include <cassert>
#include <chrono>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <mutex>
#include <set>
#include <thread>
#include <vector>
#include <array>

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
    // ll v[4][2000][2];
    vector<array<array<ll, 2>, 2000>> v;
    // ll v[4][2000][2];
    int n = 0;
    while(cin >> tmp) {
        array<array<ll, 2>, 2000> cc;
        SecretGen g(tmp);
        ll prev = tmp % 10;
        for(int i = 0; i < 2000; i++) {
            ll rand = g.generateNext();
            int val = rand % 10;
            int diff = val - prev;
            cc[i][0] = val;
            cc[i][1] = diff;
            // printf("%d, %lld: %d (%d)\n", n, rand, val, diff);
            prev = val;
        }
        v.push_back(cc);
    }
    n = v.size();

    mutex seen_seq_mut;
    set<array<int, 4>> seen_seq;
    vector<int> rand_rows = {1666, 313, 463, 1588, 416, 293};
    // set<int> seen_rows;
    #pragma omp parallel for
    for(int x = 0; x < 6; x++) {
        int row = rand_rows[x];
        // use all 4 length diffs from row and find best answer;
        for(int start = 0; start + 3 < 2000; start++) {
            array<int, 4> cand;
            for(int i = start; i < start + 4; i++) {
                cand[i - start] = v[row][i][1];
                // printf("%lld,", cand[i - start]);
            }
            if(seen_seq.count(cand) != 0) {
                continue;
            } else {
                lock_guard g(seen_seq_mut);
                seen_seq.insert(cand);
            }

            ll curr_ans = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j + 3 < 2000; j++) {
                    bool good = true;
                    for(int k = 0; good && k < 4; k++) {
                        good &= v[i][j + k][1] == cand[k];
                    }
                    if(good) {
                        curr_ans += v[i][j + 3][0];
                        break;
                    }
                }
            }

            if(ans < curr_ans) {
                cout << "Got new candidate: " << curr_ans << ", row: " << row << ", start: " << start << endl;
                ans = curr_ans;
            }
        }
    }

    cout << "Ans: " << ans << endl;
}

// 1597
int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);
  int t = 1;
#if 0
    scanf("%d", &t);
#endif
  while (t--)
    solve();
}
