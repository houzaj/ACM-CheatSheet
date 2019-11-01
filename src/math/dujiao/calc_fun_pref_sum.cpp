#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const int N = 3e6 + 5;

bool used[1005];
bool isprime[N];
int tot;
int prime[N];
int mu[N], phi[N];
ll arr_sum_mu[N], arr_sum_phi[N];
ll mp_mu[1005], mp_phi[1005];

pii getAns(int n, int lim) {
    if(n < N)             return make_pair(arr_sum_mu[n], arr_sum_phi[n]);
    if(used[lim / n]) {
        return make_pair(mp_mu[lim / n], mp_phi[lim / n]);
    }

    used[lim / n] = true;
    mp_mu[lim / n] = 1;
    mp_phi[lim / n] = (ll)n * ((ll)n + 1) / 2;
    for(ll l = 2, r; l <= n && l > 0; l = r + 1) {
        r = n / (n / l);

        pair<ll, ll> tmp = getAns(n / l, lim);
        ll sum_g = (ll)r - l + 1;
        mp_mu[lim / n] -= sum_g * tmp.first;
        mp_phi[lim / n] -= sum_g * tmp.second;
    }
    return make_pair(mp_mu[lim / n], mp_phi[lim / n]);
}

inline void init() {
    memset(isprime, true, sizeof(isprime));
    isprime[0] = isprime[1] = false;
    mu[1] = 1, phi[1] = 1;
    arr_sum_mu[1] = 1, arr_sum_phi[1] = 1;
    tot = 0;

    for(int i = 2; i < N; i++) {
        if(isprime[i]) {
            prime[tot++] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }

        for(int j = 0; j < tot && prime[j] * i < N; j++) {
            isprime[i * prime[j]] = false;
            if(i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                mu[i * prime[j]] = 0;
                break;
            }

            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            mu[i * prime[j]] = -mu[i];
        }

        arr_sum_mu[i] = arr_sum_mu[i - 1] + mu[i];
        arr_sum_phi[i] = arr_sum_phi[i - 1] + phi[i];
    }
}

int main() {
    init();

    int t;
    scanf("%d", &t);
    while(t--) {
        memset(used, false, sizeof(used));
        int n;
        scanf("%d", &n);
        pair<ll, ll> tmp = getAns(n, n);
        printf("%lld %lld\n", tmp.second, tmp.first);
    }
}
