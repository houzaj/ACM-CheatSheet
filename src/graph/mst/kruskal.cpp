int Kruskal(int m){
    int ans = 0;
    sort(e, e + m);
    for(int i = 0; i < m; i++){
        int p = find(e[i].u), q = find(e[i].v);
        if(p != q){
            ans += e[i].val;
            merge(p, q);
        }
    }
    return ans;
}
