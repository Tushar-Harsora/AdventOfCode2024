#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void solve() {
    string s;
    long long ans = 0;
    while(cin >> s) {
        auto i = 0;
        auto consumeMul = [&](int index) -> bool {
            if(index + 2 < s.size() && s.substr(index, 3) == "mul") {
                i += 3;
                return true;
            } else {
                return false;
            }
        };
        auto consume = [&](char ch) {
            if(s[i] == ch){
                i++;
                return true;
            }
            return false;
        };
        auto consumeNumber = [&]() -> int {
            int num = 0;
            do {
                int digit = s[i];
                if(digit >= '0' && digit <= '9') {
                    num *= 10;
                    num += digit - '0';
                    i++;
                } else {
                    return 0;
                }
            } while(s[i] != ',' && s[i] != ')');
            return num;
        };
        while(i < s.size()) {
            if(consumeMul(i)) {
                // cout << "Got mul\n";
                if(!consume('('))
                    goto next_it;
                // cout << "Got (\n";

                int x, y;
                if((x = consumeNumber()) == 0)
                    goto next_it;
                // cout << "Got num1: " << x << endl;

                if(!consume(','))
                    goto next_it;
                // cout << "Got ," << endl;

                if((y = consumeNumber()) == 0)
                        goto next_it;
                // cout << "Got num2: " << y << endl;
                if(!consume(')'))
                        goto next_it;
                // cout << "Got )\n";

                ans += (long long) x * y;
                // cout << "mul(" << x << "," << y << ")" << endl;
                continue;
            }
        next_it:
            i++;
        }
    }

    cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
#if 0
  cin >> t;
#endif
  while (t--)
    solve();
}
