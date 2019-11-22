#include <bits/stdc++.h>
#define FOR(i, s, t) for(int i = s; i <= t; i++)
#define rd(x) scanf("%d", &x)
#define rdl(x) scanf("%lld", &x)
#define pb(x) push_back(x)
#define il inline
#define lson l, m, ls[x]
#define rson m + 1, r, rs[x]
using namespace std;
typedef long long ll;
const int MOD = (int)998244353;
const int N = (int)5e4 + 15;

struct Operate {
    int op, a, b;
    ll c;
};
ll seg[N * 300];
int lzy[N * 300];
int ls[N * 300], rs[N * 300], tot;
int root[N << 2];
int mp[N];
Operate iop[N];

il void pushUp(int x) {
    seg[x] = seg[ls[x]] + seg[rs[x]];
}

il void pushDown(int x, int l, int r) {
    if(lzy[x]) {
        int m = (l + r) >> 1;
        ll t2 = 1LL * (r - m) * lzy[x];
        ll t1 = 1LL * (m - l + 1) * lzy[x];
        if(!ls[x]) {
            ls[x] = ++tot;
        }
        if(!rs[x]) {
            rs[x] = ++tot;
        }
        seg[ls[x]] += t1;
        seg[rs[x]] += t2;
        lzy[ls[x]] += lzy[x];
        lzy[rs[x]] += lzy[x];
        lzy[x] = 0;
    }
}

il void updateIn(int ql, int qr, int l, int r, int& x) {
    if(!x) {
        x = ++tot;
    }
    if(ql <= l && r <= qr) {
        seg[x] += (r - l + 1);
        lzy[x]++;
        return;
    }
    pushDown(x, l, r);
    int m = (l + r) >> 1;
    if(ql <= m) {
        updateIn(ql, qr, lson);
    }
    if(m < qr) {
        updateIn(ql, qr, rson);
    }
    pushUp(x);
}

il void updateOut(int pos, int ql, int qr, int L, int R, int l, int r, int rt) {
    updateIn(ql, qr, L, R, root[rt]);
    if(l == r) {
        return;
    }
    int m = (l + r) >> 1;
    if(pos <= m) {
        updateOut(pos, ql, qr, L, R, l, m, rt << 1);
    } else {
        updateOut(pos, ql, qr, L, R, m + 1, r, rt << 1 | 1);
    }
}

il ll queryIn(int ql, int qr, int l, int r, int x) {
    if(!x) {
        return 0;
    }
    if(ql <= l && r <= qr) {
        return seg[x];
    }
    pushDown(x, l, r);
    int m = (l + r) >> 1;
    if(m < ql) {
        return queryIn(ql, qr, rson);
    } else if(qr <= m) {
        return queryIn(ql, qr, lson);
    } else {
        return queryIn(ql, qr, lson) + queryIn(ql, qr, rson);
    }
}

il int queryOut(int ql, int qr, ll v, int L, int R, int l, int r, int rt) {
    if(l == r) {
        return l;
    }
    ll cnt = queryIn(ql, qr, L, R, root[rt << 1]);
    int m = (l + r) >> 1;
    if(cnt >= v) {
        return queryOut(ql, qr, v, L, R, l, m, rt << 1);
    } else {
        return queryOut(ql, qr, v - cnt, L, R, m + 1, r, rt << 1 | 1);
    }
}

int main() {
    int n, m;
    rd(n);
    rd(m);
    int mptot = 0;
    FOR(j, 1, m) {
        int op, a, b;
        ll c;
        rd(op), rd(a), rd(b), rdl(c);
        iop[j] = Operate{op, a, b, c};
        if(op == 1) {
            mp[++mptot] = c;
        }
    }
    sort(mp + 1, mp + mptot + 1);
    mptot = unique(mp + 1, mp + mptot + 1) - mp - 1;
    FOR(j, 1, m) {
        int op = iop[j].op, a = iop[j].a, b = iop[j].b;

        if(op == 1) {
            int c = lower_bound(mp + 1, mp + 1 + mptot, iop[j].c) - mp;
            updateOut(c, a, b, 1, n, 1, mptot, 1);
        } else {
            ll c = iop[j].c;
            ll cnt = queryIn(a, b, 1, n, root[1]);
            int p = queryOut(a, b, cnt - c + 1, 1, n, 1, mptot, 1);
            printf("%d\n", mp[p]);
        }
    }
}
