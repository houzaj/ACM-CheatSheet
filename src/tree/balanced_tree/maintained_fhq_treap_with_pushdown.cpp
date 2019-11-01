int ch[N << 7][2], w[N << 7], pri[N << 7], sz[N << 7], f[N << 7];
ll sum[N << 7];
int root[N];
int tot;

inline int mrand() {
    static int seed = 123456;
    return seed = (1LL * seed * 2333 + 1234567891) % 998244353;
}

inline int newNode(int v) {
    int x = ++tot;
    pri[x] = mrand();
    sz[x] = 1;
    sum[x] = w[x] = v;
    return x;
}

inline int copyNode(int v) {
    if(!v) {
        return 0;
    }
    int x = ++tot;
    sum[x] = sum[v];
    pri[x] = pri[v];
    sz[x] = sz[v];
    w[x] = w[v];
    ch[x][0] = ch[v][0];
    ch[x][1] = ch[v][1];
    f[x] = f[v];
    return x;
}

inline void pushUp(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + w[x];
}

inline void pushDown(int x) {
    if(f[x]) {
        ch[x][0] = copyNode(ch[x][0]);
        ch[x][1] = copyNode(ch[x][1]);
        swap(ch[x][0], ch[x][1]);
        f[ch[x][0]] ^= 1;
        f[ch[x][1]] ^= 1;
        f[x] = 0;
    }
}

inline int merge(int x, int y) {
    if(!x || !y) {
        return x | y;
    }
    if(pri[x] < pri[y]) {
        pushDown(x);
        ch[x][1] = merge(ch[x][1], y);
        pushUp(x);
        return x;
    } else {
        pushDown(y);
        ch[y][0] = merge(x, ch[y][0]);
        pushUp(y);
        return y;
    }
}

inline void split(int rt, int k, int& x, int& y) {
    if(!rt) {
        x = y = 0;
        return;
    }
    pushDown(rt);
    rt = copyNode(rt);
    if(sz[ch[rt][0]] < k) {
        x = rt;
        split(ch[rt][1], k - sz[ch[rt][0]] - 1, ch[x][1], y);
    } else {
        y = rt;
        split(ch[rt][0], k, x, ch[y][0]);
    }
    pushUp(rt);
}
