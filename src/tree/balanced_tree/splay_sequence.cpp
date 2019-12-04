// Gym 100499F: Tree again
// 给定一棵树，操作1：将点u及其子树换到点v的最后一个孩子上去；操作2：询问先序遍历第k个点

#include <bits/stdc++.h>
#define il inline
#define rd(x) scanf("%d", &x)
#define FOR(i, s, t) for(int i = s; i <= t; i++)
#define met(a, b, num) memset(a, b, (num) * sizeof(a[0]))
using namespace std;
typedef long long ll;
const int N = (int)2e5 + 15;
const int inf = 0x3f3f3f3f;

vector<int> graph[N];
int dfs_clock;
int a[N], tag[N], mp[N][2];

il void init(int n) {
    FOR(i, 1, n) {
        graph[i].clear();
    }
    dfs_clock = 0;
}

struct SplayTree{
    int ch[N][2], pre[N];
    int sum[N], val[N], key[N];
    int root, tot;

    void pushUp(int x) {
        sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
    }

    void rotate(int x, int p) {
        int y = pre[x], z = pre[y];
        ch[y][!p] = ch[x][p];
        pre[ch[x][p]] = y;
        pre[x] = z;
        if(z) {
            ch[z][ch[z][1] == y] = x;
        }
        ch[x][p] = y;
        pre[y] = x;
        pushUp(y);
        pushUp(x);
    }

    void splay(int x, int goal) {
        while(pre[x] != goal){
            if(pre[pre[x]] == goal)     rotate(x, ch[pre[x]][0] == x);
            else{
                int y = pre[x], z = pre[y];
                int p = (ch[z][0] == y);
                if(ch[y][!p] == x)     rotate(y, p), rotate(x, p);
                else                   rotate(x, !p), rotate(x, p);
            }
        }
        pushUp(goal);
    }

    int newNode(int pkey, int pval) {
        int x = ++tot;
        ch[x][0] = ch[x][1] = pre[x] = 0;
        sum[x] = val[x] = pval;
        key[x] = pkey;
        return x;
    }

    void init(){
        root = 0, tot = 0;
    }

    void build(int l, int r, int& x, int fa) {
        if(l > r) {
            return;
        }
        int m = (l + r) >> 1;
        x = newNode(a[m], tag[m]);
        mp[a[m]][tag[m]] = tot;
        pre[x] = fa;
        build(l, m - 1, ch[x][0], x);
        build(m + 1, r, ch[x][1], x);
        pushUp(x);
    }

    void setLink(int u, bool isRight, int v) {
        ch[u][isRight] = v;
        pre[v] = u;
        pushUp(u);
    }

    void cutLink(int u, bool isRight) {
        pre[ch[u][isRight]] = 0;
        ch[u][isRight] = 0;
        pushUp(u);
    }

    int merge(int x, int y) {
        splay(x, 0);
        while(ch[x][1]) {
            x = ch[x][1];
        }
        splay(x, 0);
        splay(y, 0);
        setLink(x, 1, y);
        return x;
    }

    int find(int k, int x) {
        if(val[x] && sum[ch[x][0]] + val[x] == k) {
            return key[x];
        }
        if(sum[ch[x][0]] >= k) {
            return find(k, ch[x][0]);
        } else {
            return find(k - sum[ch[x][0]] - val[x], ch[x][1]);
        }
    }
};

SplayTree spt;

il void dfs(int u, int pre) {
    a[++dfs_clock] = u;
    tag[dfs_clock] = 1;
    for(int v : graph[u]) {
        if(v == pre) {
            continue;
        }
        dfs(v, u);
    }
    a[++dfs_clock] = u;
    tag[dfs_clock] = 0;
}

int main(){
    int t;
    rd(t);
    FOR(csn, 1, t) {
        spt.init();
        int n;
        rd(n);
        init(n);
        FOR(i, 1, n - 1) {
            int u, v;
            rd(u), rd(v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        dfs(1, 0);
        spt.build(1, n << 1, spt.root, 0);
        int q;
        rd(q);
        FOR(qq, 1, q) {
            int op;
            rd(op);
            if(op == 1) {
                int u, v;
                rd(u), rd(v);
                int x = mp[u][1];
                spt.splay(x, 0);
                int t1 = spt.ch[x][0];
                spt.cutLink(x, 0);
                x = mp[u][0];
                spt.splay(x, 0);
                int t2 = spt.ch[x][1];
                spt.cutLink(x, 1);
                t1 = spt.merge(t1, t2);
                int y = mp[v][0];
                spt.splay(y, 0);
                t1 = spt.ch[y][0];
                spt.cutLink(y, 0);
                spt.root = spt.merge(spt.merge(t1, x), y);
            } else {
                int k;
                rd(k);
                printf("%d\n", spt.find(k, spt.root));
            }
        }
    }
}
