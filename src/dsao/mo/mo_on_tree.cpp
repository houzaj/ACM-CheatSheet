#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
typedef long long ll;

struct squery{
    int u, v, tim, idx;
};
struct supdate{
    int u, val, preval;
};
struct edge{
    int v, next;
};
squery  query[N];
supdate update[N];
int  w[N], v[N], c[N];
edge e[N << 1];
int  head[N], tot;
int  belong[N];
int  stk[N], pstk;
int  fa[N][18];
int  dpt[N];
bool used[N];
int  cnt[N];
ll   ans[N];
int  BLOCK_SIZE;

bool cmp(const squery& a, const squery& b){
    if(belong[a.u] != belong[b.u])          return belong[a.u] < belong[b.u];
    else if(belong[a.v] != belong[b.v])     return belong[a.v] < belong[b.v];
    else                                    return a.tim/BLOCK_SIZE < b.tim/BLOCK_SIZE;
}

inline void init(){
    memset(head, -1, sizeof(head));
    memset(fa, -1, sizeof(fa));
    memset(cnt, 0, sizeof(cnt));
    memset(used, 0, sizeof(used));
    tot = 0;
}

inline void addEdge(int u, int v){
    e[tot] = edge{v, head[u]};
    head[u] = tot++;
}

void dfs(int u, int pre, int depth){
    int bottom = pstk;
    dpt[u] = depth;
    for(int i = head[u]; ~i; i = e[i].next){
        int v = e[i].v;
        if(v == pre)    continue;
        fa[v][0] = u;
        dfs(v, u, depth + 1);
        if(pstk - bottom >= BLOCK_SIZE){
            while(pstk != bottom){
                belong[stk[pstk--]] = u;
            }
        }
    }
    stk[++pstk] = u;
}

void initLCA(int n){
    for(int j = 1; j <= 17; j++){
        for(int u = 1; u <= n; u++){
            if(fa[u][j - 1] == -1)  continue;
            fa[u][j] = fa[fa[u][j - 1]][j - 1];
        }
    }
}

void initBlockAndLCA(int n){
    BLOCK_SIZE = (int)pow(n, 2.0/3);
    pstk = 0;
    dfs(1, -1, 0);
    while(pstk >= 1){
        belong[stk[pstk--]] = 1;
    }
    initLCA(n);
}

int getFa(int u, int v){
    if(dpt[u] > dpt[v])     swap(u, v);
    for(int j = 17; j >= 0; j--){
        if(fa[v][j] == -1 || dpt[fa[v][j]] < dpt[u])    continue;
        v = fa[v][j];
    }
    if(u == v)  return u;
    for(int j = 17; j >= 0; j--){
        if(fa[v][j] == -1 || fa[u][j] == -1 || fa[u][j] == fa[v][j])    continue;
        u = fa[u][j], v = fa[v][j];
    }
    return fa[u][0];
}

void reverse(int u, ll& ans){
    if(used[u]){
        ans -= (ll)v[c[u]] * w[cnt[c[u]]];
        cnt[c[u]]--;
    }else{
        cnt[c[u]]++;
        ans += (ll)v[c[u]] * w[cnt[c[u]]];
    }
    used[u] ^= 1;
}

void change(int u, int val, ll& ans){
    if(used[u]){
        reverse(u, ans);
        c[u] = val;
        reverse(u, ans);
    }else{
        c[u] = val;
    }
}

void moveTimeForward(int tim, ll& ans){
    int u = update[tim].u;
    update[tim].preval = c[u];
    change(u, update[tim].val, ans);
}

void moveTimeBack(int tim, ll& ans){
    int u = update[tim].u;
    change(u, update[tim].preval, ans);
}

void moveNode(int u, int v, ll& ans){
    while(u != v){
        if(dpt[u] < dpt[v]){
            reverse(v, ans);
            v = fa[v][0];
        }else{
            reverse(u, ans);
            u = fa[u][0];
        }
    }
}

int main(){
    int n, m, q;
    while(~scanf("%d%d%d", &n, &m, &q)){
        init();
        for(int i = 1; i <= m; i++)     scanf("%d", &v[i]);
        for(int i = 1; i <= n; i++)     scanf("%d", &w[i]);
        for(int i = 1; i <= n - 1; i++){
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        for(int i = 1; i <= n; i++)     scanf("%d", &c[i]);
        initBlockAndLCA(n);

        int pp = 0, pq = 0;
        while(q--){
            int type, x, y;
            scanf("%d%d%d", &type, &x, &y);
            if(type == 0){
                update[++pq] = supdate{x, y, -1};
            }else{
                query[pp] = squery{x, y, pq, pp};
                pp++;
            }
        }
        sort(query, query + pp, cmp);

        int u = query[0].u, v = query[0].v, tim = 0;
        ll curans = 0;
        while(tim < query[0].tim)   moveTimeForward(++tim, curans);
        moveNode(u, v, curans);
        reverse(getFa(u, v), curans);
        ans[query[0].idx] = curans;
        reverse(getFa(u, v), curans);
        for(int i = 1; i < pp; i++){
            while(tim < query[i].tim)       moveTimeForward(++tim, curans);
            while(tim > query[i].tim)       moveTimeBack(tim--, curans);
            int nu = query[i].u, nv = query[i].v;
            moveNode(u, nu, curans);
            moveNode(v, nv, curans);
            int lca = getFa(nu, nv);
            reverse(lca, curans);
            ans[query[i].idx] = curans;
            reverse(lca, curans);
            u = nu, v = nv;
        }
        for(int i = 0; i < pp; i++){
            printf("%lld\n", ans[i]);
        }
    }
}
