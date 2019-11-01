#include <bits/stdc++.h>
using namespace std;
const int N = (int)5e4 + 15;

struct info {
    int h, v, idx, dp;
    double cnt;
};
struct Tree {
    int len;
    double sum;
    Tree(): len(0), sum(0) {}
    Tree(int len, double sum): len(len), sum(sum) {}
};
info a[N], b[N];
int mph[N], mpv[N];
Tree tree[N];

inline bool cmp(const info& a, const info& b) {
    return a.idx < b.idx;
}
inline bool cmp1 (const info& a, const info& b) {
    return a.h != b.h ? a.h < b.h : a.v < b.v;
}

inline int lowbit(int x) {
    return x & -x;
}

inline void update(int x, int len, double sum) {
    for(; x < N; x += lowbit(x)) {
        if(tree[x].len < len) {
            tree[x] = Tree{len, sum};
        } else if(tree[x].len == len) {
            tree[x].sum += sum;
        }
    }
}

inline Tree getSum(int x) {
    Tree ret;
    for(; x > 0; x -= lowbit(x)) {
        if(tree[x].len > ret.len) {
            ret = tree[x];
        } else if(tree[x].len == ret.len) {
            ret.sum += tree[x].sum;
        }
    }
    return ret;
}

inline void clearTree(int x) {
    for(; x < N; x += lowbit(x)) {
        tree[x] = Tree{0, 0};
    }
}

inline void cdq(int l, int r, info* a) {
    if(r <= l) {
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid, a);

    sort(a + l, a + mid + 1, cmp1);
    sort(a + mid + 1, a + r + 1, cmp1);
    int st = l;
    for(int i = mid + 1; i <= r; i++) {
        while(a[st].h <= a[i].h && st <= mid) {
            update(a[st].v, a[st].dp, a[st].cnt);
            st++;
        }
        Tree res = getSum(a[i].v);
        if(res.len == 0) {
            continue;
        }
        if(res.len + 1 > a[i].dp) {
            a[i].dp = res.len + 1;
            a[i].cnt = res.sum;
        } else if(res.len + 1 == a[i].dp) {
            a[i].cnt += res.sum;
        }
    }

    for(int i = l; i < st; i++) {
        clearTree(a[i].v);
    }

    sort(a + mid + 1, a + r + 1, cmp);

    cdq(mid + 1, r, a);
}

int main() {
    int n;
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i].h, &a[i].v);
            a[i].idx = i, b[i].idx = n - i + 1;
            a[i].dp = b[i].dp = 1;
            a[i].cnt = b[i].cnt = 1;
            mph[i] = a[i].h;
            mpv[i] = a[i].v;
        }
        sort(mph + 1, mph + n + 1);
        sort(mpv + 1, mpv + n + 1);
        int toth = unique(mph + 1, mph + n + 1) - mph - 1;
        int totv = unique(mpv + 1, mpv + n + 1) - mpv - 1;
        for(int i = 1; i <= n; i++) {
            a[i].h = lower_bound(mph + 1, mph + toth + 1, a[i].h) - mph;
            a[i].v = lower_bound(mpv + 1, mpv + totv + 1, a[i].v) - mpv;
        }

        for(int i = 1; i <= n; i++) {
            b[i].h = a[i].h;
            b[i].v = a[i].v;
            a[i].h = toth - a[i].h + 1;
            a[i].v = totv - a[i].v + 1;
        }
        reverse(b + 1, b + n + 1);

        cdq(1, n, a);
        sort(a + 1, a + n + 1, cmp);

        int maxLen = 0;
        for(int i = 1; i <= n; i++) {
            maxLen = max(maxLen, a[i].dp);
        }
        double sumCnt = 0;
        for(int i = 1; i <= n; i++) {
            if(a[i].dp == maxLen) {
                sumCnt += a[i].cnt;
            }
        }

        cdq(1, n, b);
        sort(b + 1, b + n + 1, cmp);

        printf("%d\n", maxLen);
        for(int i = 1; i <= n; i++) {
            if(a[i].dp + b[n - i + 1].dp - 1 == maxLen) {
                printf("%.5f ", a[i].cnt * b[n - i + 1].cnt / sumCnt);
            } else {
                printf("0.00000 ");
            }
        }
        puts("");
    }
}
