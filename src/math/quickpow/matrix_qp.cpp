struct Matrix {
    int met[metSize][metSize];

    inline void initZero() {
        memset(met, 0, sizeof(met));
    }

    inline void initI() {
        for(int i = 0; i < metSize; i++) {
            for(int j = 0; j < metSize; j++) {
                met[i][j] = (i == j);
            }
        }
    }

    Matrix operator * (const Matrix& b) const {
        Matrix ret;
        for(int i = 0; i < metSize; i++) {
            for(int j = 0; j < metSize; j++) {
                ret.met[i][j] = 0;
                for(int k = 0; k < metSize; k++) {
                    ret.met[i][j] = (ret.met[i][j] + (ll)met[i][k] * b.met[k][j]) % (MOD - 1);
                }
            }
        }
        return ret;
    }
};

inline Matrix quickPow(Matrix a, ll b) {
    Matrix ans;
    ans.initI();
    Matrix base = a;
    while(b) {
        if(b & 1) {
            ans = ans * base;
        }
        base = base * base;
        b >>= 1;
    }
    return ans;
}
