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

void solve() {
    ll ans = 0, blockid = 0;
    string s;
    cin >> s;
    vector<ll> arr;
    vector<array<int, 3>> fill_block, free_block;
    for(int i = 0; i < s.size(); i++) {
        if(i & 1) {
            int times = s[i] - '0';
            free_block.emplace_back(array<int, 3>{(int)arr.size(), times, INT_MAX});
            while(times--)
                arr.push_back(INT_MAX);
        } else {
            int times = s[i] - '0';
            fill_block.emplace_back(array<int, 3>{(int)arr.size(), times, (int)blockid});
            while(times--)
                arr.push_back(blockid);
            blockid++;
        }
    }

    // print_arr(arr);
    int l = 0, r = arr.size() - 1, n = arr.size();
    for(int i = fill_block.size() - 1; i >= 0; i--) {
        int block_size = fill_block[i][1];
        int blk_pos = fill_block[i][0];
        int curr_block_id = fill_block[i][2];
        for(int j = 0; j < free_block.size() && free_block[j][0] < blk_pos;  j++) {
            if(free_block[j][1] >= block_size) {
                int free_blk_pos = free_block[j][0];
                // we can copy fill_block[i] to free_block[j]
                for(int x = 0; x < block_size; x++) {
                    arr[blk_pos + x] = INT_MAX;
                    arr[free_blk_pos + x] = curr_block_id;
                }
                free_block[j][0] += block_size;
                free_block[j][1] -= block_size;
                break;
            }
        }

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
