struct LinkCutTree{
    int fa[N], ch[N][2], sum[N], val[N], lzy[N];
    int stk[N];
    int si[N];

    inline bool nRoot(int x){
        return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
    }

    void pushUp(int x){
        sum[x] = sum[lson] + sum[rson] + si[x] + 1;
    }

    void pushR(int x){
        swap(lson, rson);
        lzy[x] ^= 1;
    }

    void pushDown(int x){
        if(lzy[x]){
            if(lson)    pushR(lson);
            if(rson)    pushR(rson);
            lzy[x] = 0;
        }
    }

    void rotate(int x){
        int y = fa[x], z = fa[y];
        int p = (ch[y][1] == x), w = ch[x][p^1];
        if(nRoot(y))    ch[z][ch[z][1] == y] = x;
        ch[x][p^1] = y, ch[y][p] = w;
        if(w)   fa[w] = y;
        fa[y] = x, fa[x] = z;
        pushUp(y);
    }

    void splay(int x){
        int pstk = 0, y = x;
        for(y = x; nRoot(y); y = fa[y]){
            stk[++pstk] = y;
        }
        stk[++pstk] = y;
        while(pstk)     pushDown(stk[pstk--]);

        while(nRoot(x)){
            int y = fa[x], z = fa[y];
            if(nRoot(y))     rotate((ch[y][0] == x) ^ (ch[z][0] == y) ? x : y);
            rotate(x);
        }
        pushUp(x);
    }

    void access(int x){
        for(int y = 0; x; y = x, x = fa[x]){
            splay(x);
            si[x] += sum[rson];
            si[x] -= sum[y];
            rson = y;
            pushUp(x);
        }
    }

    void makeRoot(int x){
        access(x);
        splay(x);
        pushR(x);
    }

    int findRoot(int x){
        access(x);
        splay(x);
        while(lson){
            pushDown(x);
            x = lson;
        }
        return x;
    }

    void split(int x, int y){
        makeRoot(x);
        access(y);
        splay(y);
    }

    void link(int x, int y){
        makeRoot(x);
        if(findRoot(y) != x){
            si[y] += sum[x];
            fa[x] = y;
        }
    }

    void cut(int x, int y){
        makeRoot(x);
        if(findRoot(y) == x && fa[x] == y && !rson){
            fa[x] = ch[y][0] = 0;
            pushUp(y);
        }
    }
};
LinkCutTree lct;
