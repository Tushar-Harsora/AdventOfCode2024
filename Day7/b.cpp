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

bool helper(vector<ll> ops, vector<int>& operators, const ll target_sum, ll ind = 0) {
    if(ind == operators.size()) {
        ll ans = ops[0];
        for(int i = 1, j = 0; i < ops.size(); i++, j++) {
            switch(operators[j]) {
                case 0: {
                    ans = (ans + ops[i]);
                    break;
                }
                case 1: {
                    ans = ans * ops[i];
                    break;
                }
                case 2: {
                    ans = stoll(to_string(ans)+to_string(ops[i]));
                    break;
                }
            }
        }
        return ans == target_sum;
    }
    assert(operators[ind] == 0);
    if(helper(ops, operators, target_sum, ind + 1))
        return true;
    operators[ind] = 1;
    if(helper(ops, operators, target_sum, ind + 1))
        return true;
    operators[ind] = 2;
    if(helper(ops, operators, target_sum, ind + 1))
        return true;
    operators[ind] = 0;
    return false;
}

// 18903717626
void solve() {
    ll ans = 0;
    string tmp;
    vector<string> input;
    while(getline(cin, tmp)) {
        input.push_back(tmp);
    }

    #pragma omp parallel for reduction(+:ans)
    // #pragma omp parallel for
    for(int i = 0; i < input.size(); i++) {
        const string& tmp = input[i];
        string s_nums = tmp.substr(tmp.find(' '));
        ll target, num; sscanf(tmp.c_str(), "%lld", &target);
        vector<ll> ops;
        stringstream ss;
        ss << s_nums;
        while(ss >> num)
            ops.push_back(num);

        vector<int> operators(ops.size() - 1);      // 0 is +, 1 is *
        if(helper(ops, operators, target)) {
            ans += target;
        }
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
