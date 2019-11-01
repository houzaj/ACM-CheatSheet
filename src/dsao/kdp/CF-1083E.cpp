struct Node {
    ll x, y, w;
    bool operator < (const Node& b) const {
        return x < b.x;
    }
};
 
Node a[N];
int que[N];
ll f[N];
 
inline ll calc(int i, int j) {
    return f[j] + 1LL * (a[i].x - a[j].x) * a[i].y - a[i].w;
}
 
inline double cmp(int i, int j) {
    ll dy = f[i] - f[j];
    ll dx = a[i].x - a[j].x;
    return (double)dy / dx;
}
 
int main() {
    int n;
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i++) {
            scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].w);
        }
        sort(a + 1, a + 1 + n);
 
        que[1] = 0;
        for(int i = 1, l = 1, r = 1; i <= n; i++) {
            while(l + 1 <= r && calc(i, que[l]) <= calc(i, que[l + 1])) {
                l++;
            }
            f[i] = calc(i, que[l]);
 
            while(r >= 2 && cmp(que[r - 1], que[r]) < cmp(que[r], i)) {
                r--;
            }
            l = min(r, l);
            que[++r] = i;
        }
 
        printf("%lld\n", *max_element(f + 1, f + 1 + n));
    }
}
