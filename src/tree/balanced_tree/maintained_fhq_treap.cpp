int ch[N << 7][2], w[N << 7], pri[N << 7], sz[N << 7];
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
    w[x] = v;
    return x;
}

inline int copyNode(int v) {
    if(!v) {
        return 0;
    }
    int x = ++tot;
    pri[x] = pri[v];
    sz[x] = sz[v];
    w[x] = w[v];
    ch[x][0] = ch[v][0];
    ch[x][1] = ch[v][1];
    return x;
}


inline void pushUp(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
}

inline int merge(int x, int y) {
    if(!x || !y) {
        return x | y;
    }
    if(pri[x] < pri[y]) {
        ch[x][1] = merge(ch[x][1], y);
        pushUp(x);
        return x;
    } else {
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
    rt = copyNode(rt);
    if(w[rt] <= k) {
        x = rt;
        split(ch[rt][1], k, ch[x][1], y);
    } else {
        y = rt;
        split(ch[rt][0], k, x, ch[y][0]);
    }
    pushUp(rt);
}

inline int kth(int rt, int k) {
    if(sz[ch[rt][0]] + 1 == k) {
        return rt;
    } else if(sz[ch[rt][0]] >= k) {
        return kth(ch[rt][0], k);
    } else {
        return kth(ch[rt][1], k - sz[ch[rt][0]] - 1);
    }
}

int main() {
    root[0] = merge(newNode(-2147483647), newNode(2147483647));

    int m;
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        int op, v, x;
        scanf("%d%d%d", &v, &op, &x);
        if(op == 1) {
            int l, r;
            split(root[v], x, l, r);
            root[i] = merge(l, merge(newNode(x), r));
        } else if(op == 2) {
            int p, q, r;
            split(root[v], x, q, r);
            split(q, x - 1, p, q);
            q = merge(ch[q][0], ch[q][1]);
            root[i] = merge(p, merge(q, r));
        } 
		// ...
    }
    return 0;
}

