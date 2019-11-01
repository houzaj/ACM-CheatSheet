void getRoot(int u, int pre, int size, int& rt){
    sum[u] = 1, maxsum[u] = 0;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(used[v] || v == pre)     continue;
        getRoot(v, u, size, rt);
        sum[u] += sum[v];
        maxsum[u] = max(maxsum[u], sum[v]);
    }
    maxsum[u] = max(maxsum[u], size - sum[u]);
    if(rt == -1 || maxsum[u] < maxsum[rt])  rt = u;
}

void getDis(int u, int pre, int w){
    d[pd++] = w;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(used[v] || v == pre)     continue;
        getDis(v, u, w + e[i].w);
    }
}

int calc(int u, int w, int k){
    pd = 0;
    getDis(u, -1, w);
    sort(d, d + pd);

    int ret = 0;
    int head = 0, tail = pd - 1;
    while(head < tail){
        while(d[head] + d[tail] >= k && head < tail){
            if(d[head] + d[tail] == k)  ret++;
            tail--;
        }
        head++;
    }
    return ret;
}

int dfs(int u, int n, int k){
    int rt = -1;
    getRoot(u, -1, n, rt);
    used[u] = true;
    int ans = calc(u, 0, k);
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(used[v])     continue;
        ans -= calc(v, e[i].w, k);
        ans += dfs(v, sum[v], k);
    }
    return ans;
}

