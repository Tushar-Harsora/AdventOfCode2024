#include <cassert>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;
using ll = long long;

void solve() {
    ll ans = 0;

    string tmp;
    // for every key store all towels ending with this key
    map<char, vector<string>> towels;
    getline(cin, tmp);

    stringstream ss(tmp);
    string word;

    // Split and display each word
    while (getline(ss, word, ',')) {
        // Remove any leading or trailing spaces
        word.erase(0, word.find_first_not_of(' '));
        word.erase(word.find_last_not_of(' ') + 1);

        // cout << word << " ";
        towels[word.back()].push_back(word);
        // printf("putting %s for key: %c\n", word.c_str(), word.back());
    }
    // cout << endl;

    vector<string> input;
    while(getline(cin, tmp)) {
        if(tmp.size() == 0)
            continue;
        input.push_back(tmp);
    }


    #pragma omp parallel for
    for(int x = 0; x < input.size(); x++) {
        string curr = input[x];
        int n = curr.size();
        vector<ll> dp(n + 1, 0);
        dp[0] = 1;

        for(int i = 0; i < n; i++) {
            // ways to make this word
            if(towels.find(curr[i]) == towels.end())
                continue;
            for(const string& towel : towels[curr[i]]) {
                if(i + 1 - (int)towel.size() >= 0) {
                    bool good = true;
                    for(int j = 0; j < towel.size(); j++) {
                        good &= curr[i - j] == towel[(int)towel.size() - 1 - j];
                    }
                    if(good) {
                        dp[i + 1] += dp[i + 1 - (int)towel.size()];
                    }
                }
            }
        }

        ans += dp.back();
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
