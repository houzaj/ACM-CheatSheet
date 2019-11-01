#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = (int)500000 + 15;

int belong[N], st[N], ed[N], sz[N];
int a[N], pos[N], buc[N];
int f[1005][1005];
vector<int> vec[N];

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
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        buc[i] = a[i];
    }
    init(n);
    sort(buc + 1, buc + 1 + n);
    int mptot = unique(buc + 1, buc + 1 + n) - buc - 1;
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(buc + 1, buc + 1 + mptot, a[i]) - buc;
        pos[i] = vec[a[i]].size();
        vec[a[i]].push_back(i);
    }
    for(int i = 1, m = belong[n]; i <= m; i++) {
        memset(buc, 0, sizeof(buc));
        for(int j = i; j <= m; j++) {
            int& res = f[i][j];
            res = f[i][j - 1];
            for(int k = st[j]; k <= ed[j]; k++) {
                res = max(res, ++buc[a[k]]);
            }
        }
    }

    int lstAns = 0;
    while(q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l ^= lstAns;
        r ^= lstAns;
        lstAns = 0;
        int x = belong[l], y = belong[r];
        if(x == y) {
            for(int i = l; i <= r; i++) {
                while(lstAns + pos[i] < (int)vec[a[i]].size() && vec[a[i]][lstAns + pos[i]] <= r) {
                    lstAns++;
                }
            }
        } else {
            lstAns = f[x + 1][y - 1];
            for(int i = l; i <= ed[x]; i++) {
                while(lstAns + pos[i] < (int)vec[a[i]].size() && vec[a[i]][lstAns + pos[i]] <= r) {
                    lstAns++;
                }
            }
            for(int i = st[y]; i <= r; i++) {
                while(pos[i] - lstAns >= 0 && vec[a[i]][pos[i] - lstAns] >= l) {
                    lstAns++;
                }
            }
        }
        printf("%d\n", lstAns);
    }
    return 0;
}

