struct edge {
    int u, v, nxt;
};

edge e[N];
int head[N], tot;
bool instk[N];
int mp[N], out[N], cnt[N];
int low[N], st[N], dfn;
stack<int> stk;

inline void read(int& x) {
    scanf("%d", &x);
}

inline void addEdge(int u, int v) {
    e[tot] = edge{u, v, head[u]};
    head[u] = tot++;
}

void Tarjan(int u) {
    low[u] = st[u] = ++dfn;
    stk.push(u);
    instk[u] = true;
    for(int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(st[v] == 0) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]){
            low[u] = min(low[u], st[v]);
        }
    }
    if(low[u] == st[u]) {
        while(true) {
            int v = stk.top();
            stk.pop();
            instk[v] = false;
            mp[v] = u;
            cnt[u]++;
            if(u == v) {
                break;
            }
        }
    }
}

int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        memset(head, -1, sizeof(head));
        dfn = 0;
        for(int i = 1; i <= n; i++) {
            cnt[i] = out[i] = st[i] = 0;
        }

        while(m--){
            int u, v;
            read(u), read(v);
            addEdge(u, v);
        }

        for(int i = 1; i <= n; i++){
            if(st[i] == 0) {
                Tarjan(i);
            }
        }

        for(int i = 0; i < tot; i++){
            int u = e[i].u, v = e[i].v;
            if(mp[u] == mp[v]) {
                continue;   //在同一个连通分量的不统计出度
            }
            out[mp[u]]++;
        }

        int t = 0, ans = 0;
        for(int i = 1; i <= n; i++){
            if(mp[i] != i)  continue;
            if(out[i] == 0){
                t++;                    //出度为0的点的数量
                ans = cnt[i];
            }
        }
        printf("%d\n", t == 1 ? ans : 0);
    }
    return 0;
}
