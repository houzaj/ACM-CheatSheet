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
const int N = (int)1e4 + 15;

struct Operate {
    char op;
    int x, y, z;
};

int seg[N * 300], ls[N * 300], rs[N * 300], tot;
int root[N];
int tree[N], a[N], mp[N * 2];
Operate iop[N];

il int lowbit(int x) {
    return x & -x;
}

il void build(int l, int r, int& x) {
    x = ++tot;
    if(l == r) {
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, ls[x]);
    build(m + 1, r, rs[x]);
}

il void updateIn(int pos, int v, int l, int r, int& x, int pre) {
    x = ++tot;
    seg[x] = seg[pre] + v;
    ls[x] = ls[pre];
    rs[x] = rs[pre];
    if(l == r) {
        return;
    }
    int m = (l + r) >> 1;
    if(pos <= m) {
        updateIn(pos, v, lson, ls[pre]);
    } else {
        updateIn(pos, v, rson, rs[pre]);
    }
}

il int queryIn(int k, int l, int r, int* vl, int tl, int* vr, int tr) {
    if(l == r) {
        return l;
    }
    int sum = 0, m = (l + r) >> 1;
    FOR(i, 0, tl - 1) {
        sum -= seg[ls[vl[i]]];
    }
    FOR(i, 0, tr - 1) {
        sum += seg[ls[vr[i]]];
    }
    FOR(i, 0, tl - 1) {
        vl[i] = (sum >= k ? ls[vl[i]] : rs[vl[i]]);
    }
    FOR(i, 0, tr - 1) {
        vr[i] = (sum >= k ? ls[vr[i]] : rs[vr[i]]);
    }
    if(sum >= k) {
        return queryIn(k, l, m, vl, tl, vr, tr);
    } else {
        return queryIn(k - sum, m + 1, r, vl, tl, vr, tr);
    }
}

il void updateOut(int x, int v, int m) {
    for(int i = x; i < N; i += lowbit(i)) {
        updateIn(a[x], -1, 1, m, tree[i], tree[i]);
    }
    a[x] = v;
    for(int i = x; i < N; i += lowbit(i)) {
        updateIn(a[x], 1, 1, m, tree[i], tree[i]);
    }
}

il int queryOut(int k, int ql, int qr, int m) {
    static int vl[N], vr[N];
    int tl = 0, tr = 0;
    vl[tl++] = root[ql - 1];
    for(int i = ql - 1; i > 0; i -= lowbit(i)) {
        vl[tl++] = tree[i];
    }
    vr[tr++] = root[qr];
    for(int i = qr; i > 0; i -= lowbit(i)) {
        vr[tr++] = tree[i];
    }
    return queryIn(k, 1, m, vl, tl, vr, tr);
}

int main() {
    int n, m, mptot = 0;
    rd(n), rd(m);
    FOR(i, 1, n) {
        rd(a[i]);
        mp[++mptot] = a[i];
    }
    FOR(i, 1, m) {
        static char tmpS[2];
        char op;
        int x = 0, y = 0, z = 0;
        scanf("%s", tmpS);
        op = tmpS[0];
        if(op == 'Q') {
            rd(x), rd(y), rd(z);
        } else {
            rd(x), rd(y);
            mp[++mptot] = y;
        }
        iop[i] = Operate{op, x, y, z};
    }
    sort(mp + 1, mp + 1 + mptot);
    mptot = unique(mp + 1, mp + 1 + mptot) - mp - 1;
    FOR(i, 1, n) {
        a[i] = lower_bound(mp + 1, mp + 1 + mptot, a[i]) - mp;
    }
    FOR(i, 1, m) {
        if(iop[i].op == 'C') {
            iop[i].y = lower_bound(mp + 1, mp + 1 + mptot, iop[i].y) - mp;
        }
    }
    build(1, mptot, root[0]);
    FOR(i, 1, n) {
        updateIn(a[i], 1, 1, mptot, root[i], root[i - 1]);
        tree[i] = root[0];
    }

    FOR(i, 1, m) {
        if(iop[i].op == 'C') {
            updateOut(iop[i].x, iop[i].y, mptot);
        } else {
            int ans = queryOut(iop[i].z, iop[i].x, iop[i].y, mptot);
            printf("%d\n", mp[ans]);
        }
    }
}

