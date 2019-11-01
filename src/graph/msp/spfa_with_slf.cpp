void spfa(int src){
    que.push_back(src);
    inque[src] = true;
    while(!que.empty()){
        int u = que.front();
        inque[u] = false;
        que.pop_front();
        for(int i = head[u]; ~i; i = e[i].next){
            int v = e[i].v;
            if(d[v] > d[u] + e[i].val){
                d[v] = d[u] + e[i].val;
                if(!inque[v]){
                    inque[v] = true;
                    if(!que.empty() && d[v] <= d[que.front()]) {
                        que.push_front(v);
                    } else {
                        que.push_back(v);
                    }
                }
            }
        }
    }
}
