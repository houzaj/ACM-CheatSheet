inline bool Guass(int n) {
    bool flag = 0;
    for(int i = 1; i <= n; i++) {
        if(G[i][i] == 0) {
            return false;
        }
        
        for(int k = i + 1; k <= n; k++) {
            while(G[k][i]) {
                int r = G[i][i] / G[k][i];
                for(int j = i; j <= n; j++) {
                    G[i][j] = addMod(G[i][j], MOD - 1LL * G[k][j] * r % MOD);
                }
                swap(G[k], G[i]);
                flag ^= 1;
            }
        }
    }
    return flag;
}

