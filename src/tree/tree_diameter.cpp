void dfs1(int u, int d, int& ansu, int& ansd) {
    if(d > ansd) {
        ansd = d;
        ansu = u;
    }
    used[u] = true;
    for(int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(used[v]) {
            continue;
        }

        dfs1(v, d + e[i].w, ansu, ansd);
    }
}

void dfs2(int u, int pre, int d, int& ansd) {
    ansd = max(ansd, d);
    used[u] = true;
    for(int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(used[v]) {
            continue;
        }

        dfs2(v, u, d + e[i].w, ansd);
    }
}
