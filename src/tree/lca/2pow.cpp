void dfs(int u, int pre){
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == pre)    continue;
        dpt[v] = d[u] + 1;
        d[v] = d[u] + e[i].w;
        fa[v][0] = u;
        dfs(v, u);
    }
}

void getFa(int n){
    for(int j = 1; j <= BASE; j++){
        for(int i = 1; i <= n; i++){

            if(fa[i][j - 1] == -1)  continue;
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
}

int getLca(int u, int v){
    if(dpt[u] > dpt[v])     swap(u, v);
    for(int j = BASE; j >= 0; j--){
        if(fa[v][j] == -1 || dpt[fa[v][j]] < dpt[u])    continue;
        v = fa[v][j];
    }
    if(u == v)  return u;
    for(int j = BASE; j >= 0; j--){
        if(fa[u][j] == -1 || fa[v][j] == -1 || fa[u][j] == fa[v][j])    continue;
        u = fa[u][j], v = fa[v][j];
    }
    return fa[u][0];
}

