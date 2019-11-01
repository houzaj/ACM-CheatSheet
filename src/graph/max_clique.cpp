#include <bits/stdc++.h>
const int N = 50 + 15;

int G[N][N];
int num[N];  //维护V[i] ... v[n]的最大团

bool dfs(int adj[], int an, int cnt, int& ans) {
    if(an == 0) {
        if(cnt > ans) {
            ans = cnt;
            return true;
        }
        return false;
    }

    int tmp[N];
    for(int i = 0; i < an; i++) {
        //剪枝
        if(cnt + an - i <= ans || cnt + num[adj[i]] <= ans) {
            return false;
        }

        int k = 0;
        for(int j = i + 1; j < an; j++) {
            if(!G[adj[i]][adj[j]]) {
                continue;
            }
            tmp[k++] = adj[j];
        }

        if(dfs(tmp, k, cnt + 1, ans)) {
            return true;
        }
    }
    return false;
}

int solve(int n) {
    int adj[N];
    int ans = 0;
    //从后往前枚举，利用num[i]
    for(int i = n; i >= 1; i--) {
        int k = 0;
        for(int j = i + 1; j <= n; j++) {
            if(!G[i][j]) {
                continue;
            }
            adj[k++] = j;
        }
        dfs(adj, k, 1, ans);
        num[i] = ans;
    }
    return ans;
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
