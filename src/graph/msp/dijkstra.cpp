void dijkstra(){
    que.push(node(0, 1));
    while(!que.empty()){
        int val = que.top().val;
        int u = que.top().u;
        que.pop();

        if(d[u] < val)  continue;

        for(int i = head[u]; ~i; i = e[i].next){
            int v = e[i].v;
            if(d[v] > d[u] + e[i].val){
                d[v] = d[u] + e[i].val;
                que.push(node(d[v], v));
            }
        }
    }
}
