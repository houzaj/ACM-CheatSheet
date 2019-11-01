#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 100100;
const int inf = 0x3f3f3f3f;
typedef long long ll;

struct edge{
    int v, w, nxt;
};

int head[N], rthead[N], tot, rttot;
int sum[N], par[N];
int dpt[N], d[N], fa[N][20], maxsum[N];
bool used[N];
edge e[N << 1];
edge rte[N << 1];

ll ans[N][2], val[N];

inline void init(){
    tot = rttot = 1;
}

inline int read(){
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while('0' <= ch && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}


inline void addEdge(int u, int v, int w){
    e[tot] = edge{v, w, head[u]};
    head[u] = tot++;
}

inline void addRootEdge(int u, int v, int w){
    rte[rttot] = edge{v, w, rthead[u]};
    rthead[u] = rttot++;
}

void initLCA(int u, int pre){
    fa[u][0] = pre;
    for(int j = 1; j <= 19; j++){
        if(fa[u][j - 1] == 0)   break;
        fa[u][j] = fa[fa[u][j - 1]][j - 1];
    }
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == pre)     continue;
        dpt[v] = dpt[u] + 1;
        d[v] = d[u] + e[i].w;
        initLCA(v, u);
    }
}

inline int lca(int u, int v) {
    if(dpt[u] < dpt[v])     swap(u, v);
    int tmp = dpt[u] - dpt[v];
    for(int k = 0, j = 1; j <= tmp; j <<= 1, k++){
        if(tmp & j)    u = fa[u][k];
    }
    while(u != v) {
        int j = 0;
        while(fa[u][j] != fa[v][j]) j++;
        if(j)   j--;
        u = fa[u][j], v = fa[v][j];
    }
    return u;
}

int getDist(int u, int v){
    return d[u] + d[v] - (d[lca(u, v)] << 1);
}

void getRoot(int u, int pre, int size, int& rt){
    sum[u] = 1, maxsum[u] = 0;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == pre || used[v])     continue;
        getRoot(v, u, size, rt);
        sum[u] += sum[v];
        maxsum[u] = max(maxsum[u], sum[v]);
    }
    maxsum[u] = max(maxsum[u], size - sum[u]);
    if(rt == 0 || maxsum[u] < maxsum[rt])     rt = u;
}

void initTree(int u){
    used[u] = true;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(used[v])     continue;
        int rt = 0;
        getRoot(v, u, sum[v], rt);
        par[rt] = u;
        addRootEdge(u, v, rt);
        initTree(rt);
    }
}

ll query(int u){
    ll ret = ans[u][0];
    for(int i = u; par[i]; i = par[i]){
        int d = getDist(u, par[i]);
        ret += ans[par[i]][0];
        ret -= ans[i][1];
        ret += (ll)d * (val[par[i]] - val[i]);
    }
    return ret;
}

void update(int u, int x){
    val[u] += x;
    for(int i = u; par[i]; i = par[i]){
        int d = getDist(u, par[i]);
        ans[par[i]][0] += (ll)x * d;
        ans[i][1] += (ll)x * d;
        val[par[i]] += x;
    }
}

ll work(int u){
    ll ret = query(u);
    for(int i = rthead[u]; i; i = rte[i].nxt){
        int v = rte[i].v;
        ll tmp = query(v);
        if(tmp < ret){
        	ret = min(ret, work(rte[i].w));
        }   
    }
    return ret;
}


int main(){
    int n, q;
    while(~scanf("%d%d", &n, &q)){
        init();
        for(int i = 1; i <= n - 1; i++){
            int u = read(), v = read(), w = read();
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        initLCA(1, 0);
        int rt = 0;
        getRoot(1, 0, n, rt);
        par[rt] = 0;
        initTree(rt);
        while(q--){
            int u = read(), x = read();
            update(u, x);
            printf("%lld\n", work(rt));
        }
    }
    return 0;
}
