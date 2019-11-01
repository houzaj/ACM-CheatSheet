void topoSort(int n){
    for(int i = 1; i <= n; i++){
        if(!idg[i])    que.push(i);
    }
    while(!que.empty()){
        int u = que.front();
        que.pop();
        ans.push_back(u);
        for(int i = head[u]; ~i; i = e[i].next){
            int v = e[i].v;
            if((--idg[v]) == 0)    que.push(v);
        }
    }
}
