#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int HIGHEST = 63;
const int N = 1e4 + 15;
typedef long long ll;

ll a[N], b[HIGHEST + 5], c[HIGHEST + 5], pp;

void build(int n) {
    for(int i = 0; i < n; i++) {
        for(int j = HIGHEST; j >= 0; j--) {
            if((a[i] >> j & 1) == 0)    continue;
            if(b[j])    a[i] ^= b[j];
            else {
                b[j] = a[i];
                for(int k = j - 1; k >= 0; k--)         if(b[k] && (b[j] >> k & 1))   b[j] ^= b[k];
                for(int k = j + 1; k <= HIGHEST; k++)   if(b[k] >> j & 1)             b[k] ^= b[j];
                break;
            }
        }
    }
}

int main() {
    int t, csn = 1;
    scanf("%d", &t);
    while(t--) {
        memset(b, 0, sizeof(b));
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)      scanf("%lld", &a[i]);
        build(n);

        pp = 0;
        for(int j = 0; j <= HIGHEST; j++) {
            if(b[j])    c[pp++] = b[j];
        }

        printf("Case #%d:\n", csn++);
        int q;
        scanf("%d", &q);
        while(q--) {
            ll k;
            scanf("%lld", &k);
            if(pp < n)      k--;
            if(k == 0) {
                puts("0");
            } else {
                ll xorsum = 0;
                for(int i = 0; i <= HIGHEST && k; i++, k >>= 1) {
                    if(i >= pp) {
                        xorsum = -1;
                        break;
                    }
                    if(k&1)     xorsum ^= c[i];
                }
                printf("%lld\n", xorsum);
            }
        }
    }
}
