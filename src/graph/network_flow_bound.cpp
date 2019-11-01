int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        init();
        int tt = n + m + 2, ss = n + m + 3;
        int s = 0, t = n + m + 1;
        int sum = 0;
        for(int i = 1; i <= m; i++){
            int val;
            scanf("%d", &val);
            addEdge(n + i, tt, val);
            addEdge(ss, t, val);
            addEdge(n + i, t, inf);
            sum += val;
        }
        for(int i = 1; i <= n; i++){
            int k, val;
            scanf("%d%d", &k, &val);
            addEdge(s, i, val);
            while(k--){
                int idx, l, r;
                scanf("%d%d%d", &idx, &l, &r);
                addEdge(i, tt, l);
                anse[pans++] = tot - 2;
                addEdge(ss, n + 1 + idx, l);
                addEdge(i, n + 1 + idx, r - l);
                anse[pans++] = tot - 2;
                sum += l;
            }
        }
        addEdge(t, s, inf);

        int ans = ISAP(ss, tt, n + m + 4);
        if(sum <= ans){
            //不用 += 是因为上一次的结果贮存在t到s这条边中，再跑一次最大流会利用这个结果
            ans = ISAP(s, t, n + m + 4);
            printf("%d\n", ans);
            for(int i = 0; i < pans; i += 2){
                printf("%d\n", e[anse[i]].val + e[anse[i + 1]].val);
            }
        }else{
            puts("-1");
        }
        puts("");
    }
}

