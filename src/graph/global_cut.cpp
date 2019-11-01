const ll inf = 0x3f3f3f3f3f3f3f3fLL;
const int N = 300 + 5;

bool used[N];
int v[N];
ll dis[N], G[N][N];


ll storeWagner(int n) {
    ll res = inf;
    for(int i = 0; i < n; i++) {
        v[i] = i;
    }
    while(n > 1) {
        used[v[0]] = 1 ;
        for(int i = 1; i < n; i++) {
            used[v[i]] = 0 ;
            dis[v[i]] = G[v[0]][v[i]];
        }
        int last = 0;
        for(int i = 1; i < n; i++) {
            int maxs = -1;
            for(int j = 1; j < n; j++) {
                if(used[v[j]] == false && (maxs == -1 || dis[v[j]] > dis[v[maxs]])) {
                    maxs = j;
                }
            }
            used[v[maxs]] = 1;
            if(i == n - 1) {
                res = min(res, dis[v[maxs]]);
                for(int j = 0 ; j < n; j++) {
                    G[v[last]][v[j]] += G[v[maxs]][v[j]];
                    G[v[j]][v[last]] += G[v[j]][v[maxs]];
                }
                v[maxs] = v[--n];
                break;
            }
            last = maxs;
            for(int j = 1; j < n; j++) {
                if(used[v[j]] == false) {
                    dis[v[j]] += G[v[maxs]][v[j]];
                }
            }
        }
    }
    return res;
}

int main() {
    int n, m, s;
    while(~scanf("%d%d%d", &n, &m, &s) && (n && m && s)) {
        memset(G, 0, sizeof(G));
    
        while(m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            G[u - 1][v - 1] += w;
            G[v - 1][u - 1] += w;
        }
        printf("%lld\n", storeWagner(n));
    }
}
