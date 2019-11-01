void build(int& o, int l, int r) {  //建立空树
    o = tot++;
    sum[o] = 0;
    if(l == r)  return;
    int m = (l + r) >> 1;
    build(ls[o], lson);
    build(rs[o], rson);
}

void update(int& o, int pre, int pos, int l, int r) {
    o = tot++;
    ls[o] = ls[pre];
    rs[o] = rs[pre];
    sum[o] = sum[pre] + 1;
    if(l == r)  return;

    int m = (l + r) >> 1;
    if(pos <= m) {
        update(ls[o], ls[pre], pos, lson);
    } else {
        update(rs[o], rs[pre], pos, rson);
    }
}

int query(int o, int qr, int l, int r) {
    if(r <= qr) {
        return sum[o];
    }
    int m = (l + r) >> 1;
    int ans = query(ls[o], qr, lson);
    if(m < qr) {
        ans += query(rs[o], qr, rson);
    }
    return ans;
}

