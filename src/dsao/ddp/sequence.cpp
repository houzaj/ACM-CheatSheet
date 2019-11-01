#include<bits/stdc++.h>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int N = (int)5e4 + 15;
const int MOD = 1000000007;

struct Matrix {
    static int n;
    int mat[11][11];

    inline void init() {
        for(int i = 0; i < 11; i++) {
            mat[i][0] = 0;
        }
    }
};

int Matrix::n;
Matrix m0, seg[N << 2];
bool a[N][11];

inline void mulMatrix(const Matrix& a, const Matrix& b, Matrix& ret) {
    for(int i = 0; i < Matrix::n; i++) {
        for(int j = 0; j < Matrix::n; j++) {
            ret.mat[i][j] = 0;
            for(int k = 0; k < Matrix::n; k++) {
                ret.mat[i][j] = (ret.mat[i][j] + (ll)a.mat[i][k] * b.mat[k][j] % MOD) % MOD;
            }
        }
    }
}

inline void updateMatrix(int pos, int m, int rt) {
    for(int i = 0; i < m; i++) {
        bool ok = true;
        for(int j = i; j >= 0; j--) {
            ok &= a[pos][j];
            seg[rt].mat[i][j] = ok;
        }
        ok = true;
        for(int j = i; j < m; j++) {
            ok &= a[pos][j];
            seg[rt].mat[i][j] = ok;
        }
    }
}

inline void build(int n, int mm, int l, int r, int rt) {
    if(l == r) {
        int pos = n - l + 1;
        updateMatrix(pos, mm, rt);
        return;
    }
    int m = (l + r) >> 1;
    build(n, mm, lson);
    build(n, mm, rson);
    mulMatrix(seg[rt << 1], seg[rt << 1 | 1], seg[rt]);
}

inline void update(int pos, int y, int n, int mm, int l, int r, int rt) {
    if(l == r) {
        pos = n - pos + 1;
        a[pos][y] = !a[pos][y];
        updateMatrix(pos, mm, rt);
        return;
    }
    int m = (l + r) >> 1;
    if(pos <= m) {
        update(pos, y, n, mm, lson);
    } else {
        update(pos, y, n, mm, rson);
    }
    mulMatrix(seg[rt << 1], seg[rt << 1 | 1], seg[rt]);
}


int main() {
    int n, m, q;
    while(~scanf("%d%d%d", &n, &m, &q)) {
        Matrix::n = m;
        for(int i = 1, tmp; i <= n; i++) {
            for(int j = 0; j < m; j++) {
                scanf("%1d", &tmp);
                a[i][j] = !tmp;
            }
        }
        Matrix res;
        if(n > 1) {
            build(n, m, 1, n - 1, 1);
        }

        while(q--) {
            int op, x, y;
            scanf("%d%d%d", &op, &x, &y);
            if(op == 1) {
                if(x == 1) {
                    a[x][y - 1] = !a[x][y - 1];
                } else {
                    update(n - x + 1, y - 1, n, m, 1, n - 1, 1);
                }
            } else {
                m0.init();
                x--;
                y--;
                for(int i = x; i >= 0; i--) {
                    if(!a[1][i]) {
                        break;
                    }
                    m0.mat[i][0] = 1;
                }
                for(int i = x; i < m; i++) {
                    if(!a[1][i]) {
                        break;
                    }
                    m0.mat[i][0] = 1;
                }
                if(n > 1) {
                    mulMatrix(seg[1], m0, res);
                    printf("%d\n", res.mat[y][0]);
                } else {
                    printf("%d\n", m0.mat[y][0]);
                }
            }
        }
    }
}
