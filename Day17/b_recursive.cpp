#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;
using ll = long long;

std::size_t hash_vector_std(const vector<int>& s) noexcept
{
    size_t hash = 0;
    for (int val : s) {
        hash ^= std::hash<int>{}(val) + 0x9e3779b9 + (hash << 6) + (hash >> 2); // Combining with a variant of the Fowler-Noll-Vo hash
    }
    return hash;
}

struct CPU {
public:
    ll A, B, C;
    ll ip;
    vector<ll> memory;
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

    CPU(const CPU& other) {
        A = other.A;
        B = other.B;
        C = other.C;
        memory = other.memory;
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

    int out() {
        ll operand = memory[ip + 1];
        ll ans = combo(operand) % 8;
        ip += 2;
        return ans;
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

    void print_state() {
        printf("A: %lld, B: %lld, C: %lld\n", A, B, C);
        for(auto val : memory) {
            printf("%lld,",val);
        }
        printf("\n");
    }

    vector<int> run() {
        vector<int> ret;
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
                ret.push_back(out());
            } else if(memory[ip] == 6) {
                bdv();
            } else if(memory[ip] == 7) {
                cdv();
            } else assert(false);
        }
        return ret;
    }
};

void guess_pos(const CPU& cpu, const vector<int>& input_vec, int pos, int base_val = 0) {
    ll low = (base_val << 3);
    ll high = low + 8;
    ll n = input_vec.size();

    printf("Guessing pos: %d, low=%lld, high=%lld\n", pos, low, high);
    fflush(stdout);
    for(ll i = low; i <= high; i++) {
        CPU copyy = cpu;
        copyy.set_a(i);
        // copyy.print_state();
        vector<int> res = copyy.run();
        // Debug
        // if(res.size() < input_vec.size()) {
        //     // copyy.print_state();
        //     printf("i: %lld, res: %zu, input_vec: %zu\n", i, res.size(), input_vec.size());
        //     for(auto val : res)
        //         cout << val << ", ";
        //     cout << endl;
        //     for(auto val : input_vec)
        //         cout << val << ", ";
        //     cout << endl;
        // }
        // assert(res.size() == input_vec.size());
        if(equal(res.end() - 1 - pos, res.end(), input_vec.end() - 1 - pos, input_vec.end())) {
            // cout << "DBG" << endl;
            if(pos == n - 1) {
                cout << "Found!!!\ni: " << i << endl;
                return;
            }
            guess_pos(cpu, input_vec, pos + 1, i);
            return;
        }
    }

}

// 8    -> 2    -> 000001000
// 64   -> 3    -> 001000000
// 512  -> 4    -> 100000000
//
// need to start from 2^46 -> 2^48
void solve() {
    CPU cpu;
    cout << "Initial State\n";
    cpu.print_state();

    vector<int> input_vec(cpu.memory.begin(), cpu.memory.end());
    // size_t target = hash_vector_std(input_vec);

    guess_pos(cpu, input_vec, 0);
    // map<size_t, vector<int>> mp;
    // ll i = 0b111111111111111111111111111111111111111111111;
    // #pragma omp parallel for
    // // for(ll i = 0b111111111111111111111111111111111111111111111; i < (1LL << 48) + 2; i += 64) {
    // for(ll i = 0; i < 0b111111111111111111; i++) {
    //     CPU copyy = cpu;
    //     copyy.set_a(i);
    //     // copyy.print_state();
    //     vector<int> res = copyy.run();
    //     size_t hs = hash_vector_std(res);
    //     if(target == hs) {
    //         cout << i << ": " << std::bitset<19>(i) << ", ";
    //         for(auto ele : res)
    //             cout << ele << " ";
    //         cout << " -> " << res.size() << "\n";
    //         cout << "Found!!\n";
    //         cout << "i: " << i << endl;
    //     }
    // }
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
