#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MOD = 998244353;
const int N = 2000 + 15;

int x[N], y[N];

int quickPow(int a, int b, int MOD) {
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

inline int calc(int k, int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        int cur = y[i];
        for(int j = 1; j <= n; j++) {
            if(i == j) {
                continue;
            }
            cur = (ll)cur * (k - x[j] + MOD) % MOD * quickPow((x[i] - x[j] + MOD) % MOD, MOD - 2, MOD) % MOD;
        }
        sum = (sum + cur) % MOD;
    }
    return sum;
}

int main() {
    int n, k;
    while(~scanf("%d%d", &n, &k)) {
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &x[i], &y[i]);
        }
        printf("%d\n", calc(k, n));
    }
}

