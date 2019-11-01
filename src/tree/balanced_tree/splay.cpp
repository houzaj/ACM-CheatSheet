struct SplayTree{
    int ch[N][2], pre[N];
    ll  sum[N], lzy[N], key[N], val[N], sz[N];
    int root, tot;

    void color(int o, ll delta){
        lzy[o] += delta;
        sum[o] += sz[o] * delta;
        val[o] += delta;
    }

    void pushUp(int o){
        sz[o] = 1, sum[o] = val[o];
        if(~ch[o][0]){
            sz[o] += sz[ch[o][0]];
            sum[o] += sum[ch[o][0]];
        }
        if(~ch[o][1]){
            sz[o] += sz[ch[o][1]];
            sum[o] += sum[ch[o][1]];
        }
    }

    void pushDown(int o){
        if(lzy[o]){
            if(~ch[o][0])    color(ch[o][0], lzy[o]);
            if(~ch[o][1])    color(ch[o][1], lzy[o]);
            lzy[o] = 0;
        }
    }

    void rotate(int x, int p){
        int y = pre[x], z = pre[y];
        pushDown(y), pushDown(x);
        ch[y][p^1] = ch[x][p];
        pre[ch[x][p]] = y;
        pre[x] = z;
        if(~z)   ch[z][ch[z][1] == y] = x;
        ch[x][p] = y;
        pre[y] = x;
        pushUp(y), pushUp(x);
    }

    void splay(int x, int goal){
        while(pre[x] != goal){
            if(pre[pre[x]] == goal)     rotate(x, ch[pre[x]][0] == x);
            else{
                int y = pre[x], z = pre[y];
                int p = (ch[z][0] == y);
                if(ch[y][p^1] == x)     rotate(y, p), rotate(x, p);
                else                    rotate(x, p^1), rotate(x, p);
            }
        }

        if(goal == -1)       root = x;
        else                 pushUp(goal);
    }

    void newNode(int& o, int pkey, ll pval){
        o = tot++;
        ch[o][0] = ch[o][1] = pre[o] = -1;
        lzy[o] = 0;
        key[o] = pkey;
        sum[o] = val[o] = pval;
        sz[o] = 1;
    }

    void insert(int& o, int pkey, ll pval, int fa){
        if(o == -1){
            newNode(o, pkey, pval);
            pre[o] = fa;
            splay(o, -1);
            return;
        }
        if(key[o] == pkey){
            pushDown(o);
            splay(o, -1);
            return;
        }

        pushDown(o);
        if(pkey < key[o])    insert(ch[o][0], pkey, pval, o);
        else                 insert(ch[o][1], pkey, pval, o);
    }

    void init(){
        root = -1, tot = 0;
        insert(root, inf, 0, -1);
        insert(root, -inf, 0, -1);
    }

    int findPrev(int o, int pkey){
        if(o == -1)  return -1;
        if(key[o] < pkey){
            int ret = findPrev(ch[o][1], pkey);
            return ret == -1 ? o : ret;
        }else{
            return findPrev(ch[o][0], pkey);
        }
    }

    int findSucc(int o, int pkey){
        if(o == -1)  return -1;
        if(key[o] > pkey){
            int ret = findSucc(ch[o][0], pkey);
            return ret == -1 ? o : ret;
        }else{
            return findSucc(ch[o][1], pkey);
        }
    }

    void splayLR(int lkey, int rkey){
        int l = findPrev(root, lkey), r = findSucc(root, rkey);
        splay(l, -1);
        splay(r, root);
    }

    ll query(int lkey, int rkey){
        splayLR(lkey, rkey);
        return sum[ch[ch[root][1]][0]];
    }

    void changeInterval(int lkey, int rkey, ll pval){
        splayLR(lkey, rkey);
        color(ch[ch[root][1]][0], pval);
    }

    void delInterval(int lkey, int rkey){
        splayLR(lkey, rkey);
        ch[ch[root][1]][0] = -1;
        pushUp(ch[root][1]);
    }
};

SplayTree spt;
