void tarjan(int u, int pre, int q){
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == pre)    continue;
        d[v] = d[u] + e[i].w;
        tarjan(v, u, q);
        merge(u, v);
        used[v] = true;
    }
    for(int i = qhead[u]; ~i; i = qe[i].nxt){
        int v = qe[i].v;
        if(used[v])     pa[qe[i].w] = find(v);
    }
}

