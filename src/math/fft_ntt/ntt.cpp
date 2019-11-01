inline int addMod(int a, int b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}

inline int quickPow(int a, int b) {
    int ans = 1, base = a;
    while(b) {
        if(b & 1) {
            ans = (ll)ans * base % MOD;
        }
        base = (ll)base * base % MOD;
        b >>= 1;
    }
    return ans;
}

void change(vector<int>& y, int len) {
    for(int i = 1, j = len / 2; i < len - 1; i++) {
        if(i < j) {
            swap(y[i], y[j]);
        }
        int k = len / 2;
        while(j >= k) {
            j = j - k;
            k = k / 2;
        }
        if(j < k) {
            j += k;
        }
    }
}

void ntt(vector<int>& y, int len, int on) {
    change(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        int gn = quickPow(3, (MOD - 1) / h);
        for (int j = 0; j < len; j += h) {
            int g = 1;
            for (int k = j; k < j + h / 2; k++) {
                int u = y[k];
                int t = (ll)g * y[k + h / 2] % MOD;
                y[k] = addMod(u, t);
                y[k + h / 2] = addMod(u, MOD - t);
                g = (ll)g * gn % MOD;
            }
        }
    }
    if(on == -1) {
        reverse(y.begin() + 1, y.begin() + len);
        for(int i = 0, inv = quickPow(len, MOD - 2); i < len; i++) {
            y[i] = (ll)y[i] * inv % MOD;
        }
    }
}

inline void mul(vector<int> a, vector<int> b, vector<int>& res, int alen, int blen) {
    int len = rpow2[alen + blen];
    ntt(a, len, 1);
    ntt(b, len, 1);
    for(int i = 0; i < len; i++) {
        res[i] = (ll)a[i] * b[i] % MOD;
    }
    ntt(res, len, -1);
}

