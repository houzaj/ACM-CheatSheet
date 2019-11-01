const int N = 100000 + 15;

int ch[N][2], val[N], d[N], ft[N];

inline void init(int n) {
    for(int i = 1; i <= n; i++) {
        ft[i] = i;
        d[i] = 1;
        ch[i][0] = ch[i][1] = 0;
    }
}

inline int find(int x) {
    return ft[x] == x ? x : ft[x] = find(ft[x]);
}

inline int merge(int x, int y) {
    if(!x || !y) {
        return x | y;
    }
    if(val[x] < val[y]) {
        swap(x, y);
    }
    ch[x][1] = merge(ch[x][1], y);
    if(d[ch[x][0]] < d[ch[x][1]]) {
        swap(ch[x][0], ch[x][1]);
    }
    d[x] = d[ch[x][1]] + 1;
    return x;
}

int main() {
    int n, m;
    while(~scanf("%d", &n)) {
        init(n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        scanf("%d", &m);
        while(m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            u = find(u), v = find(v);
            if(u == v) {
                puts("-1");
            } else {
                for(int k = 0; k < 2; k++) {
                    val[u] >>= 1;
                    int x = merge(ch[u][0], ch[u][1]);
                    ch[u][0] = ch[u][1] = 0;
                    int y = merge(u, x);
                    ft[u] = ft[x] = y;
                    swap(u, v);
                }
                u = find(u), v = find(v);
                int x = merge(u, v);
                ft[u] = ft[v] = x;
                printf("%d\n", val[x]);
            }
        }
    }
}

