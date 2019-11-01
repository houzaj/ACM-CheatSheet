#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 128 + 15;

int some[N][N], all[N][N], none[N][N];
int G[N][N];

int dfs(int d, int an, int sn, int nn, int sum) {
    if(!sn && !nn) {
        return sum;
    }

    int ans = 0;
    int u = some[d][0];
    for(int i = 0; i < sn; i++) {
        int v = some[d][i];
        if(G[u][v]) {
            continue;
        }

        for(int j = 0; j < an; j++) {
            all[d + 1][j] = all[d][j];
        }
        all[d + 1][an] = v;

        int tsn = 0, tnn = 0;
        for(int j = 0; j < sn; j++) {
            if(!G[v][some[d][j]]) {
                continue;
            }
            some[d + 1][tsn++] = some[d][j];
        }
        for(int j = 0; j < nn; j++) {
            if(!G[v][none[d][j]]) {
                continue;
            }
            none[d + 1][tnn++] = none[d][j];
        }

        ans = max(ans, dfs(d + 1, an + 1, tsn, tnn, sum + 1));
        some[d][i] = 0;
        none[d][nn++] = v;
    }
    return ans;
}

inline int solve(int n) {
    for(int i = 1; i <= n; i++) {
        some[0][i - 1] = i;
    }
    return dfs(0, 0, n, 0, 0);
}

int main() {
    int n;
    while(~scanf("%d", &n) && n) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &G[i][j]);
            }
        }

        printf("%d\n", solve(n));
    }
}

