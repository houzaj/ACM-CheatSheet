#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = (int)1e6 + 15;
const ll MOD = (ll)1e9 + 7;

const ll inv6 = 166666668;
bool isNotPrime[N];
int prime[N], tot;
int sum1[N], sum2[N], g1[N], g2[N];
ll w[N];
int idx1[N], idx2[N];
int gTot;
int sqrtN;

inline void init(int n) {
    tot = 0;
    for(int i = 2; i <= n; i++) {
        if(!isNotPrime[i]) {
            prime[++tot] = i;
            sum1[tot] = (sum1[tot - 1] + i) % MOD;
            sum2[tot] = (sum2[tot - 1] + (ll)i * i) % MOD;
        }
        for(int j = 1; i * prime[j] <= n; j++) {
            isNotPrime[i * prime[j]] = true;
            if(i % prime[j] == 0) {
                break;
            }
        }
    }
}

inline void initG(ll n) {
    // calculate g1[gTot] = 1 + 2 + 3 + ...
    // calculate g2[gTot] = 1^2 + 2^2 + 3^3 + ...
    gTot = 0;
    for(ll i = 1, r; i <= n; i = r + 1) {
        w[++gTot] = n / i;
        r = n / (n / i);
        if(n / i <= sqrtN) {
            idx1[n / i] = gTot;
        } else {
            idx2[n / (n / i)] = gTot;
        }

        ll x = w[gTot] % MOD;
        g1[gTot] = (x * (x + 1) / 2 + MOD - 1) % MOD;
        g2[gTot] = (x * (x + 1) % MOD * (2 * x + 1) % MOD * inv6 + MOD - 1) % MOD;
    }
    // enumerate j, then enumerate n
    // g(i, j - 1) can be calculated before g(n, j)
    for(int i = 1; i <= tot; i++) {
        for(int j = 1; j <= gTot && (ll)prime[i] * prime[i] <= w[j]; j++) {
            ll k = w[j] / prime[i] <= sqrtN ? idx1[w[j] / prime[i]] : idx2[n / (w[j] / prime[i])];
            g1[j] = (g1[j] - (ll)prime[i] * (g1[k] - sum1[i - 1] + MOD) % MOD + MOD) % MOD;
            g2[j] = (g2[j] - (ll)prime[i] * prime[i] % MOD * (g2[k] - sum2[i - 1] + MOD) % MOD + MOD) % MOD;
        }
    }
}

inline ll calcS(ll x, int j, ll n) {
    if(prime[j] >= x) {
        return 0;
    }
    ll k = x <= sqrtN ? idx1[x] : idx2[n / x];
    ll ans = ((ll)g2[k] - g1[k] - (sum2[j] - sum1[j]) + 2LL * MOD) % MOD;
    for(int i = j + 1; i <= tot && (ll)prime[i] * prime[i] <= x; i++) {
        for(ll e = 1, pie = prime[i]; pie <= x; pie *= prime[i], e++) {
            ll xx = pie % MOD;
            ans = (ans + xx * (xx - 1) % MOD * (calcS(x / pie, i, n) + (e != 1))) % MOD;
        }
    }
    return ans;
}

int main() {
    ll n;
    while(~scanf("%lld", &n)) {
        sqrtN = sqrt(n);
        init(sqrtN);
        initG(n);
        printf("%lld\n", (calcS(n, 0, n) + 1) % MOD);
    }
}

