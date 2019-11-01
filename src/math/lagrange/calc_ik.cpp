#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MOD = 1000000007;
const int N = 50000 + 15;

int inv[N];
int prime[N], tot;
int fi[N];
int ans[N];

inline int quickPow(int a, int b) {
    int ans = 1, base = a;
    while(b) {
        if(b & 1) {
            ans = (ll)ans * base % MOD;
        }
        base = (ll)base * base % MOD;
        b >>= 1;
    }
    return ans;
}

inline void initInv() {
    inv[1] = 1;
    for(int i = 2; i < N; i++) {
        inv[i] = ((-(ll)(MOD / i) * inv[MOD % i]) % MOD + MOD) % MOD;
    }
}

inline void initFi(int k) {
    memset(fi, 0, sizeof(fi));
    tot = 0;
    fi[1] = 1;
    for(int i = 2; i <= k + 1; i++) {
        if(!fi[i]) {
            fi[i] = quickPow(i, k);
            prime[tot++] = i;
            for(int j = 0; i * prime[j] < N; j++) {
                fi[i * prime[j]] = (ll)fi[i] * fi[prime[j]] % MOD;
                if(i % prime[j] == 0) {
                    break;
                }
            }
        }
    }
    for(int i = 2; i <= k + 1; i++) {
        fi[i] = (fi[i] + fi[i - 1]) % MOD;
    }
}

inline void Lagrange(ll n, int k) {
    int p = 1;
    for(int i = 1; i <= k + 1; i++) {
        ans[i] = (i + k + 1) & 1 ? MOD - fi[i] : fi[i];
        p = (ll)p * ((n - i + 1) % MOD) % MOD * inv[i] % MOD;
        ans[i] = (ll)ans[i] * p % MOD;
    }
    p = 1;
    for(int i = k; i >= 1; i--) {
        p = (ll)p * ((n - i - 1) % MOD) % MOD * inv[k + 1 - i] % MOD;
        ans[i] = (ll)ans[i] * p % MOD;
    }
}

int main() {
    initInv();

    int t;
    scanf("%d", &t);
    while(t--) {
        ll n;
        int k;
        scanf("%lld%d", &n, &k);
        initFi(k);
        Lagrange(n, k);
        int res = accumulate(ans, ans + k + 2, 0, [] (int a, int b) -> int { return (a + b) % MOD; });
        printf("%d\n", res);
    }
}
