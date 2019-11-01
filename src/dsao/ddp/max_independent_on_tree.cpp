#include<bits/stdc++.h>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
const int N = (int)1e5 + 15;
const int inf = 0x3f3f3f3f;

struct Matrix {
    int mat[2][2];

    inline Matrix operator * (const Matrix& b) const {
        Matrix ret;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                ret.mat[i][j] = 0;
                for(int k = 0; k < 2; k++) {
                    ret.mat[i][j] = max(ret.mat[i][j], mat[i][k] + b.mat[k][j]);
                }
            }
        }
        return ret;
    }
};
struct edge {
    int v, nxt;
};

int val[N];
int son[N], sz[N], dpt[N], fa[N];
int mptot, mp[N << 2], top[N << 2], belong[N << 2], ed[N];
Matrix seg[N << 2], upVal[N];
int head[N], tot;
edge e[N << 1];
int dp[N][2], ldp[N][2];

inline void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

inline void addEdge(int u, int v) {
    e[tot] = edge{v, head[u]};
    head[u] = tot++;
}

inline void dfs(int u){
    sz[u] = 1;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa[u])  continue;
        fa[v] = u;
        dpt[v] = dpt[u] + 1;
        dfs(v);
        sz[u] += sz[v];
        if(son[u] == 0 || sz[son[u]] < sz[v]) {
            son[u] = v;
        }
    }
}

inline void buildTree(int u, int rt, int n){
    mp[u] = ++mptot;
    belong[mptot] = u;
    top[u] = rt;
    ed[rt] = mptot;
    ldp[u][1] = val[u];
    if(son[u]) {
        buildTree(son[u], rt, n);
        dp[u][0] += max(dp[son[u]][0], dp[son[u]][1]);
        dp[u][1] += dp[son[u]][0];
    }

    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa[u] || v == son[u])   continue;
        buildTree(v, v, n);
        ldp[u][0] += max(dp[v][0], dp[v][1]);
        ldp[u][1] += dp[v][0];
    }
    dp[u][0] += ldp[u][0];
    dp[u][1] += ldp[u][1];
}

inline void build(int l, int r, int rt) {
    if(l == r) {
        int u = belong[l];
        upVal[u].mat[0][0] = upVal[u].mat[0][1] = ldp[u][0];
        upVal[u].mat[1][0] = ldp[u][1];
        upVal[u].mat[1][1] = -inf;
        seg[rt] = upVal[u];
        return;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    seg[rt] = seg[rt << 1] * seg[rt << 1 | 1];
}

inline void update(int pos, int l, int r, int rt) {
    if(l == r) {
        seg[rt] = upVal[belong[l]];
        return;
    }
    int m = (l + r) >> 1;
    if(pos <= m) {
        update(pos, lson);
    } else {
        update(pos, rson);
    }
    seg[rt] = seg[rt << 1] * seg[rt << 1 | 1];
}

inline Matrix query(int ql, int qr, int l, int r, int rt) {
    if(ql <= l && r <= qr) {
        return seg[rt];
    }
    int m = (l + r) >> 1;
    if(m < ql) {
        return query(ql, qr, rson);
    } else if(qr <= m) {
        return query(ql, qr, lson);
    } else {
        return query(ql, qr, lson) * query(ql, qr, rson);
    }
}

inline void change(int u, int x) {
    upVal[u].mat[1][0] += x - val[u];
    val[u] = x;
    while(u) {
        int now = top[u];
        Matrix pre = query(mp[now], ed[now], 1, mptot, 1);
        update(mp[u], 1, mptot, 1);
        Matrix cur = query(mp[now], ed[now], 1, mptot, 1);
        u = fa[now];
        upVal[u].mat[0][0] += (max(cur.mat[0][0], cur.mat[1][0]) - max(pre.mat[0][0], pre.mat[1][0]));
        upVal[u].mat[1][0] += (cur.mat[0][0] - pre.mat[0][0]);
        upVal[u].mat[0][1] = upVal[u].mat[0][0];
    }
}

int main() {
    int n, m;
    while(~scanf("%d%d", &n, &m)) {
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        for(int i = 1; i <= n - 1; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        dfs(1);
        buildTree(1, 1, n);
        build(1, mptot, 1);

        while(m--) {
            int u, x;
            scanf("%d%d", &u, &x);
            change(u, x);
            Matrix mat = query(mp[1], ed[1], 1, mptot, 1);
            printf("%d\n", max(mat.mat[0][0], mat.mat[1][0]));
        }
    }
}
