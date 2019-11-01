inline void pushUp(int rt){
    seg[rt] = max(seg[rt << 1], seg[rt << 1 | 1]);
}

void update(int pos, int val, int l, int r, int rt){
    if(l == r){
        seg[rt] = val;
        return;
    }
    int m = (l + r) >> 1;
    if(pos <= m)    update(pos, val, lson);
    else            update(pos, val, rson);
    pushUp(rt);
}

int query(int ql, int qr, int l, int r, int rt){
    if(ql <= l && r <= qr){
        return seg[rt];
    }
    int ans = 0, m = (l + r) >> 1;
    if(ql <= m)     ans = max(ans, query(ql, qr, lson));
    if(m < qr)      ans = max(ans, query(ql, qr, rson));
    return ans;
}

void dfs(int u){
    son[u] = -1, sz[u] = 1;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa[u])  continue;
        fa[v] = u;
        preew[v] = e[i].w;
        dpt[v] = dpt[u] + 1;
        dfs(v);
        sz[u] += sz[v];
        if(son[u] == -1 || sz[son[u]] < sz[v])  son[u] = v;
    }
}

void buildTree(int u, int rt, int n){
    mp[u] = ++mptot, top[u] = rt;
    update(mp[u], preew[u], 1, n, 1);
    if(~son[u])     buildTree(son[u], rt, n);
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa[u] || v == son[u])   continue;
        buildTree(v, v, n);
    }
}

void solveUpdate(int idx, int val){
    int v = dpt[input[idx][0]] > dpt[input[idx][1]] ? input[idx][0] : input[idx][1];
    update(mp[v], val, 1, mptot, 1);
}

int solveQuery(int u, int v, int n){
    int fu = top[u], fv = top[v], ret = 0;
    while(fu != fv){
        if(dpt[fu] < dpt[fv]){
            swap(fu, fv);
            swap(u, v);
        }

        ret = max(ret, query(mp[fu], mp[u], 1, n, 1));
        u = fa[fu], fu = top[u];
    }
    if(u == v)  return ret;
    if(dpt[u] > dpt[v])     swap(u, v);
	// 最后是mp[u] + 1而不是mp[u]是因为维护的是父边，故mp[u]不在(u,v)路径上
    return max(ret, query(mp[u] + 1, mp[v], 1, n, 1));
}
