int prim(int n){
    int ans = 0;
    mincost[1] = 0;
    que.push(node(0, 1));
    while(!que.empty()){
        int u = que.top().u;
        int cost = que.top().cost;
        que.pop();

        if(used[u] || mincost[u] < cost) continue;
        used[u] = true;
        mincost[u] = cost;
        ans += cost;

        for(int v = 1; v <= n; v++){
            if(u == v)  continue;
            if(!used[v] && mincost[v] > G[u][v]){
                mincost[v] = G[u][v];
                que.push(node(G[u][v], v));
            }
        }
    }
    return ans;
}
