const int N = 40000 + 5;
struct edge{
    int v, w, nxt;
};
edge e[N << 1];
int head[N], tot;
int dp[N << 1][21], mp[N << 1], pos[N], d[N], dfn, totDp;

inline void init(){
    memset(head, -1, sizeof(head));
    d[1] = tot = dfn = totDp = 0;
}

inline void addEdge(int u, int v, int w){
    e[tot] = edge{v, w, head[u]};
    head[u] = tot++;
}

void dfs(int u, int pre){
    int curDfn = ++dfn;
    dp[++totDp][0] = curDfn;
    mp[dfn] = u;
    pos[u] = totDp;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == pre) {
            continue;
        }
        d[v] = d[u] + e[i].w;

        dfs(v, u);

        dp[++totDp][0] = curDfn;
    }
}

void rmqInit(){
    for(int j = 1; (1 << j) <= totDp; j++){
        for(int i = 1; i + (1 << j) - 1 <= totDp; i++){
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int getLca(int u, int v){
    int l = pos[u], r = pos[v];
    if(l > r) {
        swap(l, r);
    }

    int j = (int)log2(r - l + 1);
    return mp[min(dp[l][j], dp[r - (1 << j) + 1][j])];
}
