inline bool Guass(int n) {
    for(int i = 1; i <= n; i++) {
        int r = i;
        for(int k = i + 1; k <= n; k++) {
            if(fabs(G[r][i]) < fabs(G[k][i])) {
                r = k;
            }
        }
        swap(G[i], G[r]);

        if(fabs(G[i][i]) < 1e-4) {
            return false;
        }

        for(int k = i + 1; k <= n; k++) {
            for(int j = n + 1; j >= i; j--) {
                G[k][j] -= G[i][j] / G[i][i] * G[k][i];
            }
        }
    }

    for(int i = n; i >= 1; i--) {
        for(int j = i - 1; j >= 1; j--) {
            G[j][n + 1] -= G[i][n + 1] / G[i][i] * G[j][i];
            G[j][i] = 0;
        }
    }
    return true;
}
