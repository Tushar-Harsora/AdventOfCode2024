#include <cassert>
#include <cinttypes>
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;
using ll = long long;

struct CPU {
private:
    ll A, B, C;
    ll ip;
    vector<ll> memory;
public:
    CPU() {
        scanf(" Register A: %lld", &A);
        scanf(" Register B: %lld", &B);
        scanf(" Register C: %lld", &C);
        // cout << "Read registers" << endl;
        string tmp;
        while(getline(cin, tmp)) {
            if(tmp.size() == 0)
                continue;
            tmp = tmp.substr(tmp.find(':') + 2);
            stringstream ss;
            ss << tmp;
            int x; char comma;
            while(ss >> x) {
                memory.push_back(x);
                if(ss.peek() == ',')
                    ss >> comma;
            }
            break;
        }

        ip = 0;
    }
    void set_a(ll value) {
        A = value;
    }
    void set_b(ll value) {
        B = value;
    }
    void set_c(ll value) {
        C = value;
    }

    ll combo(ll operand) {
        if(operand >= 0 && operand <= 3)
            return operand;
        if(operand == 4)
            return A;
        if(operand == 5)
            return B;
        if(operand == 6)
            return C;
        assert(false);
    }

    void adv() {
        ll operand = memory[ip + 1];
        ll numerator = A;
        ll denom = 1 << combo(operand);
        A = numerator / denom;
        ip += 2;
    }

    void bxl() {
        ll operand = memory[ip + 1];
        B = B ^ operand;
        ip += 2;
    }

    void bst() {
        ll operand = memory[ip + 1];
        B = combo(operand) % 8;
        ip += 2;
    }

    void jnz() {
        if(A == 0) {
            ip += 2;
            return;
        }
        ip = memory[ip + 1];
        // ip++;
    }

    void bxc() {
        ll operand = memory[ip + 1];
        (void)operand;
        B = B ^ C;
        ip += 2;
    }

    void out() {
        ll operand = memory[ip + 1];
        ll ans = combo(operand) % 8;
        cout << ans << ",";
        ip += 2;
    }

    void bdv() {
        ll operand = memory[ip + 1];
        ll numerator = A;
        ll denom = 1 << combo(operand);
        B = numerator / denom;
        ip += 2;
    }
    void cdv() {
        ll operand = memory[ip + 1];
        ll numerator = A;
        ll denom = 1 << combo(operand);
        C = numerator / denom;
        ip += 2;
    }

    void run() {
        printf("ip: %lld, memory_size: %d\n", ip, (int)memory.size());
        while(ip < memory.size()) {
            if(memory[ip] == 0) {
                adv();
            } else if(memory[ip] == 1) {
                bxl();
            } else if(memory[ip] == 2) {
                bst();
            } else if(memory[ip] == 3) {
                jnz();
            } else if(memory[ip] == 4) {
                bxc();
            } else if(memory[ip] == 5) {
                out();
            } else if(memory[ip] == 6) {
                bdv();
            } else if(memory[ip] == 7) {
                cdv();
            } else assert(false);
        }
    }
};

void solve() {
    CPU cpu;
    cpu.run();
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
