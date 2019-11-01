int sum[N * 40], ls[N * 40], rs[N * 40], root[N], a[N];
int tot;

inline void build(int& x, int l, int r) {
    x = tot++;
    sum[x] = 0;
    if(l == r) {
        return;
    }
    int m = (l + r) >> 1;
    build(ls[x], lson);
    build(rs[x], rson);
}

inline void update(int& x, int pre, int pos, int l, int r) {
    x = tot++;
    ls[x] = ls[pre], rs[x] = rs[pre];
    sum[x] = sum[pre] + 1;
    if(l == r) {
        return;
    }
    int m = (l + r) >> 1;
    if(pos <= m) {
        update(ls[x], ls[pre], pos, lson);
    } else {
        update(rs[x], rs[pre], pos, rson);
    }
}

inline int querySum(int x, int pre, int pos, int l, int r) {
    if(r <= pos) {
        return sum[x] - sum[pre];
    }
    int m = (l + r) >> 1;
    int ret = querySum(ls[x], ls[pre], pos, lson);
    if(m < pos) {
        ret += querySum(rs[x], rs[pre], pos, rson);
    }
    return ret;
}

inline int findK(int x, int pre, int k, int l, int r) {
    if(l == r) {
        return l;
    }
    int tmp = sum[ls[x]] - sum[ls[pre]];
    int m = (l + r) >> 1;
    if(tmp >= k) {
        return findK(ls[x], ls[pre], k, lson);
    } else {
        return findK(rs[x], rs[pre], k - tmp, rson);
    }
}
