const int N = (int)500 + 3;
const int M = (int)124750 + 3;
const int inf = 1LL << 30;

struct edge {
    int v, nxt;
};

edge e[M << 1];
int head[N], tot;
int match[N], pre[N], type[N];
int que[N], qhead, qtail;
int ft[N];

inline void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

inline void addEdge(int u, int v) {
    e[tot] = edge{v, head[u]};
    head[u] = tot++;
}

inline int find(int x) {
    return ft[x] == x ? x : ft[x] = find(ft[x]);
}

inline int getLca(int u, int v) {
    static int ss[N], tim;
    tim++;
    while(ss[u] != tim) {
        if(u) {
            ss[u] = tim;
            u = find(pre[match[u]]);
        }
        swap(u, v);
    }
    return u;
}

inline void flower(int x, int y, int p) {
    while(find(x) != p) {
        pre[x] = y;
        y = match[x];
        ft[x] = ft[y] = p;
        if(type[y] == 1) {
            que[qtail++] = y;
            type[y] = 2;
        }
        x = pre[y];
    }
}

inline bool blossom(int u, int n) {
    qhead = qtail = 0;
    for(int i = 1; i <= n; i++) {
        type[i] = 0;
        ft[i] = i;
    }
    que[qtail++] = u;
    type[u] = 2;
    while(qhead != qtail) {
        u = que[qhead++];
        for(int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if(type[v] == 0) {
                type[v] = 1;
                pre[v] = u;
                if(!match[v]) {
                    while(u) {
                        u = match[pre[v]];
                        match[v] = pre[v];
                        match[match[v]] = v;
                        v = u;
                    }
                    return true;
                } else {
                    que[qtail++] = match[v];
                    type[match[v]] = 2;
                }
            } else if(type[v] == 2 && find(u) != find(v)) {
                int p = getLca(u, v);
                flower(u, v, p);
                flower(v, u, p);
            }
        }
    }
    return false;
}

int main() {
    init();
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
        if(!match[u] && !match[v]) {
            match[v] = u;
            match[u] = v;
            ans++;

        }
    }
    for(int i = 1; i <= n; i++) {
        if(!match[i] && blossom(i, n)) {
            ans++;
        }
    }
    printf("%d\n", ans);
    for(int i = 1; i <= n; i++) {
        printf("%d ", match[i]);
    }
    puts("");
}
