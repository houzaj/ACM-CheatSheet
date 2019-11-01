const int N = (int)400 + 15;
const ll inf = 1LL << 60;

bool vx[N], vy[N];
ll lx[N], ly[N], slack[N], w[N][N];
int ml[N], mr[N], pre[N];
int que[N];

inline void setCrossRoad(int& v) {
    for(; v; swap(v, mr[pre[v]])) {
        ml[v] = pre[v];
    }
}

inline void bfs(int u, int n) {
    int head = 0, tail = 0;
    que[tail++] = u;
    vx[u] = true;
    while(true) {
        while(head != tail) {
            int u = que[head++];
            for(int v = 1; v <= n; v++) {
                if(vy[v]) {
                    continue;
                }
                ll d = lx[u] + ly[v] - w[u][v];
                if(d > slack[v]) {
                    continue;
                }
                pre[v] = u;
                if(d == 0) {
                    if(!ml[v]) {
                        setCrossRoad(v);
                        return;
                    }
                    vy[v] = vx[ml[v]] = true;
                    que[tail++] = ml[v];
                } else {
                    slack[v] = d;
                }
            }
        }
        ll d = inf;
        int to = 1;
        for(int v = 1; v <= n; v++) {
            if(!vy[v] && d > slack[v]) {
                d = slack[v];
                to = v;
            }
        }
        for(int i = 1; i <= n; i++) {
            if(vx[i]) {
                lx[i] -= d;
            }
            if(vy[i]) {
                ly[i] += d;
            } else {
                slack[i] -= d;
            }
        }
        if(!ml[to]) {
            setCrossRoad(to);
            return;
        }
        head = tail = 0;
        que[tail++] = ml[to];
        vx[ml[to]] = vy[to] = true;
    }
}

inline ll KM(int n) {
    for(int i = 1; i <= n; i++) {
        ly[i] = 0;
        ml[i] = mr[i] = 0;
        lx[i] = *max_element(w[i] + 1, w[i] + 1 + n);
    }
    for(int i = 1; i <= n; i++) {
        fill(vx, vx + 1 + n, false);
        fill(vy, vy + 1 + n, false);
        fill(slack, slack + 1 + n, inf);
        bfs(i, n);
    }
    return accumulate(lx + 1, lx + 1 + n, 0LL) + accumulate(ly + 1, ly + 1 + n, 0LL);
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    while(k--) {
        int u, v, val;
        scanf("%d%d%d", &u, &v, &val);
        w[u][v] = val;
    }
    ll ans = KM(max(n, m));
}
