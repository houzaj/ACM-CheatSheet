int getSrc(int n){
    for(int i = 1; i <= n; i++){
        if(dg[i]&1){
            return i;
        }
    }
    return 1;
}

void dfs(int u){
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(used[i])    continue;
        used[i] = used[i^1] = true;
        dfs(v);
    }
    ans[pp++] = u;
}
