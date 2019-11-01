#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = (int)100000 + 3;

int belong[N], st[N], ed[N], sz[N];
int a[N], buc[N];
int f[320][320], cnt[320][N];

inline void init(int n) {
    int num = sqrt(n);

    for(int i = 1, m = n / num; i <= num; i++) {
        st[i] = m * (i - 1) + 1;
        ed[i] = m * i;
        sz[i] = m;
    }
    ed[num] = n;
    sz[num] = n - st[num] + 1;
    for(int i = 1; i <= num; i++) {
        for(int j = st[i]; j <= ed[i]; j++) {
            belong[j] = i;
        }
    }
}

int main() {
    int n, c, m;
    scanf("%d%d%d", &n, &c, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    init(n);
    for(int i = 1, m = belong[n]; i <= m; i++) {
        memset(buc + 1, 0, c * sizeof(int));
        for(int j = 1; j <= c; j++) {
            cnt[i][j] = cnt[i - 1][j];
        }
        for(int k = st[i]; k <= ed[i]; k++) {
            cnt[i][a[k]]++;
        }
        for(int j = i; j <= m; j++) {
            int& res = f[i][j];
            res = f[i][j - 1];
            for(int k = st[j]; k <= ed[j]; k++) {
                res += (buc[a[k]] == 0 ? 0 : (buc[a[k]] & 1 ? 1 : -1));
                buc[a[k]]++;
            }
        }
    }

    int ans = 0;
    while(m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if(l > r) {
            swap(l, r);
        }
        int x = belong[l], y = belong[r];
        ans = 0;
        if(y - x <= 1) {
            for(int i = l; i <= r; i++) {
                buc[a[i]] = 0;
            }
            for(int i = l; i <= r; i++) {
                ans += (buc[a[i]] == 0 ? 0 : (buc[a[i]] & 1 ? 1 : -1));
                buc[a[i]]++;
            }
        } else {
            ans = f[x + 1][y - 1];
            for(int i = l; i <= ed[x]; i++) {
                buc[a[i]] = 0;
            }
            for(int i = st[y]; i <= r; i++) {
                buc[a[i]] = 0;
            }
            for(int i = l; i <= ed[x]; i++) {
                int tmp = buc[a[i]] + cnt[y - 1][a[i]] - cnt[x][a[i]];
                ans += (tmp == 0 ? 0 : (tmp & 1 ? 1 : -1));
                buc[a[i]]++;
            }
            for(int i = st[y]; i <= r; i++) {
                int tmp = buc[a[i]] + cnt[y - 1][a[i]] - cnt[x][a[i]];
                ans += (tmp == 0 ? 0 : (tmp & 1 ? 1 : -1));
                buc[a[i]]++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
