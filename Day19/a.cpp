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

bool possible(const string& target, map<char, vector<string>>& mp, int index = 0) {
    if(index >= target.size())
        return true;

    if(mp.find(target[index]) == mp.end())
        return false;
    // cout << "For: " << target.substr(index) << endl;
    vector<string>& cand = mp[target[index]];
    for(const string& s : cand) {
        if(index + s.size() <= target.size()) {
            // printf("    Checking %s\n", s.c_str());
            bool good = true;
            for(int i = 0; i < s.size(); i++) {
                good &= target[index + i] ==  s[i];
            }
            if(good && possible(target, mp, index + s.size())) {
                return true;
            }
        }
    }

    return false;
}

void solve() {
    int ans = 0;

    string tmp;
    map<char, vector<string>> towels;
    getline(cin, tmp);

    stringstream ss(tmp);
    string word;

    // Split and display each word
    while (getline(ss, word, ',')) {
        // Remove any leading or trailing spaces
        word.erase(0, word.find_first_not_of(' '));
        word.erase(word.find_last_not_of(' ') + 1);

        // cout << "towel: " << word << endl;
        towels[word[0]].push_back(word);
    }

    while(getline(cin, tmp)) {
        if(tmp.size() == 0)
            continue;
        string target = tmp;
        if(possible(target, towels))
            ans++;
    }

    cout << "Ans: " << ans << endl;
}

int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);
  int t = 1;
#if 0
    scanf("%d", &t);
#endif
  while (t--)
    solve();
}
