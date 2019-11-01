inline void pushDown(int x) {
    if (lzyAdd[x] != 0 || lzyMul[x] != 1) {
        for (int k = 0; k < 2; k++) {
            val[ch[x][k]] = lzyMul[x] * val[ch[x][k]] + lzyAdd[x];
            lzyMul[ch[x][k]] *= lzyMul[x];
            lzyAdd[ch[x][k]] = lzyMul[x] * lzyAdd[ch[x][k]] + lzyAdd[x];
        }
        lzyAdd[x] = 0;
        lzyMul[x] = 1;
    }
}

inline int merge(int x, int y) {
    if (!x || !y) {
        return x | y;
    }
    if (val[x] > val[y]) {
        swap(x, y);
    }
    pushDown(x);
    ch[x][1] = merge(ch[x][1], y);
    if (d[ch[x][0]] < d[ch[x][1]]) {
        swap(ch[x][0], ch[x][1]);
    }
    d[x] = d[ch[x][1]] + 1;
    return x;
}

inline void dfs(int u) {
    int rt = mp[u];
    for (int v : graph[u]) {
        dpt[v] = dpt[u] + 1;
        dfs(v);
        rt = merge(rt, mp[v]);
    }
    // printf("u = %d\n", u);
    while (rt && val[rt] < h[u]) {
        // printf("rt = %d, val = %lld\n", rt, val[rt]);
        cnt[u]++;
        ed[rt] = u;
        pushDown(rt);
        rt = merge(ch[rt][0], ch[rt][1]);
    }
    // printf("rt = %d, val = %lld\n", rt, val[rt]);
    mp[u] = rt;
    if (a[u] == 0) {
        val[rt] += v[u];
        lzyAdd[rt] += v[u];
    } else {
        val[rt] *= v[u];
        lzyMul[rt] *= v[u];
        lzyAdd[rt] *= v[u];
    }
}
