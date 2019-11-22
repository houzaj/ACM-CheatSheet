#include <bits/stdc++.h>
#define FOR(i, s, t) for(int i = s; i <= t; i++)
#define rd(x) scanf("%d", &x)
#define rdl(x) scanf("%lld", &x)
#define pb(x) push_back(x)
#define il inline
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int N = (int)5e4 + 15;

struct Operate {
    int op, a, b;
    ll c;
    int idx;
};
ll seg[N << 2];
int lzy[N << 2], tot, mp[N];
Operate iop[N];
int ans[N];

il void pushUp(int rt) {
    seg[rt] = seg[rt << 1] + seg[rt << 1 | 1];
}

il void pushDown(int rt, int l, int r) {
    if(lzy[rt]) {
        int m = (l + r) >> 1;
        ll t2 = 1LL * (r - m) * lzy[rt];
        ll t1 = 1LL * (m - l + 1) * lzy[rt];
        seg[rt << 1] += t1;
        seg[rt << 1 | 1] += t2;
        lzy[rt << 1] += lzy[rt];
        lzy[rt << 1 | 1] += lzy[rt];
        lzy[rt] = 0;
    }
}

il void update(int ql, int qr, int v, int l, int r, int rt) {
    if(ql <= l && r <= qr) {
        seg[rt] += (r - l + 1) * v;
        lzy[rt] += v;
        return;
    }
    pushDown(rt, l, r);
    int m = (l + r) >> 1;
    if(ql <= m) {
        update(ql, qr, v, lson);
    }
    if(m < qr) {
        update(ql, qr, v, rson);
    }
    pushUp(rt);
}

il ll query(int ql, int qr, int l, int r, int rt) {
    if(ql <= l && r <= qr) {
        return seg[rt];
    }
    pushDown(rt, l, r);
    int m = (l + r) >> 1;
    ll ans = 0;
    if(ql <= m) {
        ans += query(ql, qr, lson);
    }
    if(m < qr) {
        ans += query(ql, qr, rson);
    }
    return ans;
}

il void solve(int l, int r, int L, int R, int n) {
    static Operate q1[N], q2[N];
    if(l > r || L > R) {
        return;
    }
    if(l == r) {
        FOR(i, L, R) {
            if(iop[i].op == 2) {
                ans[iop[i].idx] = l;
            }
        }
        return;
    }

    int m = (l + r) >> 1;
    int t1 = 0, t2 = 0;
    FOR(i, L, R) {
        if(iop[i].op == 1) {
            if(iop[i].c <= mp[m]) {
                q1[t1++] = iop[i];
                update(iop[i].a, iop[i].b, 1, 1, n, 1);
            } else {
                q2[t2++] = iop[i];
            }
        } else {
            ll t = query(iop[i].a, iop[i].b, 1, n, 1);
            if(t >= iop[i].c) {
                q1[t1++] = iop[i];
            } else {
                q2[t2] = iop[i];
                q2[t2++].c -= t;
            }
        }
    }
    FOR(i, L, R) {
        if(iop[i].op == 1 && iop[i].c <= mp[m]) {
            update(iop[i].a, iop[i].b, -1, 1, n, 1);
        }
    }
    FOR(i, 0, t1 - 1) {
        iop[L + i] = q1[i];
    }
    FOR(i, 0, t2 - 1) {
        iop[L + t1 + i] = q2[i];
    }
    solve(l, m, L, L + t1 - 1, n);
    solve(m + 1, r, L + t1, R, n);
}


int main() {
    memset(ans, -1, sizeof(ans));
    int n, m;
    rd(n), rd(m);
    int mptot = 0;
    FOR(j, 1, m) {
        int op, a, b;
        ll c;
        rd(op), rd(a), rd(b), rdl(c);
        iop[j] = Operate{op, a, b, c, j};
        if(op == 1) {
            mp[++mptot] = c;
        }
    }
    sort(mp + 1, mp + mptot + 1);
    mptot = unique(mp + 1, mp + mptot + 1) - mp - 1;
    FOR(j, 1, m) {
        if(iop[j].op == 1) {
            iop[j].c = mp[mptot - (lower_bound(mp + 1, mp + 1 + mptot, iop[j].c) - mp) + 1];
            //iop[j].c = lower_bound(mp + 1, mp + 1 + mptot, iop[j].c) - mp;
        }
    }
    solve(1, mptot, 1, m, n);
    FOR(j, 1, m) {
        if(ans[j] != -1) {
            printf("%d\n", mp[mptot - ans[j] + 1]);
        }
    }
}
