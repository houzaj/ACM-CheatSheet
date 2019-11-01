int maxx[2];
char G[N][N];
int l[N][N], r[N][N], up[N][N];
bool used[N][N];
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
    for(int i=1; i<=n; i++) {
        scanf("%s", G[i] + 1);
        for(int j = 1; j <= m; j++) {
            G[i][j] = (G[i][j] == '1');
        }
    }
 
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(G[i][j])
                up[i][j]=1,r[i][j]=l[i][j]=j;
    for(int i=1; i<=n; i++)
        for(int j=2; j<=m; j++)
            if(G[i][j]==1&&G[i][j-1]==1)
                l[i][j]=l[i][j-1];
    for(int i=1; i<=n; i++)
        for(int j=m-1; j>0; j--)
            if(G[i][j]==1&&G[i][j+1]==1)
                r[i][j]=r[i][j+1];
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(i>1&&G[i][j]==1&&G[i-1][j]==1) {
                r[i][j]=min(r[i][j],r[i-1][j]);
                l[i][j]=max(l[i][j],l[i-1][j]);
                up[i][j]=up[i-1][j]+1;
            }
        }
    }
 
    stack<pair<int, int> > stk;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(!G[i][j]) {
                continue;
            }
            if(used[l[i][j]][r[i][j]]) {
                continue;
            }
            used[l[i][j]][r[i][j]] = true;
            stk.push(make_pair(l[i][j], r[i][j]));
 
            int res;
            res = (r[i][j]-l[i][j]+1)*up[i][j];
            if(res > maxx[0]) {
                maxx[1] = maxx[0];
                maxx[0] = res;
            } else if(res > maxx[1]) {
                maxx[1] = res;
            }
 
            res = max(0, (r[i][j]-l[i][j])*up[i][j]);
            if(res > maxx[0]) {
                maxx[1] = maxx[0];
                maxx[0] = res;
            } else if(res > maxx[1]) {
                maxx[1] = res;
            }
 
            res = max(0, (r[i][j]-l[i][j])*(up[i][j]-1));
            if(res > maxx[0]) {
                maxx[1] = maxx[0];
                maxx[0] = res;
            } else if(res > maxx[1]) {
                maxx[1] = res;
            }
        }
        while(!stk.empty()) {
            pair<int, int> pr = stk.top();
            stk.pop();
            used[pr.first][pr.second] = false;
        }
    }
    printf("%d\n", maxx[1]);
}
