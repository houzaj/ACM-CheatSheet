bool spfa(int src, int des){
    memset(d, 0x3f, sizeof(d));
    memset(inq, false, sizeof(inq));
    d[src] = 0, pre[src] = src;
    que.push(src);
    inq[src] = true;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        inq[u] = false;
        for(int i = head[u]; ~i; i = e[i].next){
            int v = e[i].v;
            if(d[v] > d[u] + e[i].cost && e[i].val){
                d[v] = d[u] + e[i].cost;
                pre[v] = u;
                cur[v] = i;
                if(!inq[v]){
                    que.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return d[des] != inf;
}

int solve(int src, int des){
    int ans = 0;
    while(spfa(src, des)){
        int aug = inf;
        for(int v = des; v != src; v = pre[v])     aug = min(aug, e[cur[v]].val);
        for(int v = des; v != src; v = pre[v]){
            e[cur[v]].val -= aug;
            e[cur[v]^1].val += aug;
        }
        ans += d[des] * aug;
    }
    return ans;
}
