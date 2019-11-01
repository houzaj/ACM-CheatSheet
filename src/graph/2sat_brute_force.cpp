int head[N * 2], tot;
bool mark[N * 2];
int stk[N * 2], pstk;

inline void addEdge(int u, int v) {
    e[tot] = edge{v, head[u]};
    head[u] = tot++;
}

inline void addClause(int x, int xval, int y, int yval) {
    x = x << 1 | xval;
    y = y << 1 | yval;
    addEdge(x^1, y);
    addEdge(y^1, x);
}

bool dfs(int x) {
    if(mark[x^1]) {
        return false;
    }
    if(mark[x]) {
        return true;
    }
    mark[x] = true;
    stk[pstk++] = x;
    for(int i = head[x]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(!dfs(v)) {
            return false;
        }
    }
    return true;
}

bool solve() {
    for(int i = 0; i < 2 * N; i += 2) {
        if(!mark[i] && !mark[i + 1]) {
            pstk = 0;
            if(!dfs(i)) {
                while(pstk > 0) {
                    mark[stk[--pstk]] = false;
                }
                if(!dfs(i + 1)) {
                    return false;
                }
            }
        }
    }
    return true;
}
