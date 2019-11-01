void getDfsClock(int u, int pre, int n){
    l[u] = ++dfs_clock;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == pre)    continue;
        getDfsClock(v, u, n);
    }
    r[u] = dfs_clock;
}
