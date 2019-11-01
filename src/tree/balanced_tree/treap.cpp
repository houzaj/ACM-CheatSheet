struct Treap{
    int key[N], weight[N], sz[N], pre[N], ch[N][2];
    int tot, root;

    void newNode(int& x, int pkey){
        x = ++tot;
        key[x]    = pkey;
        weight[x] = rand();
        ch[x][0] = ch[x][1] = pre[x] = 0;
        sz[x] = 1;
    }

    void pushUp(int x){ 
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1; 
    }

    void rotate(int x, int p){
        int y = pre[x], z = pre[y];
        ch[y][p^1] = ch[x][p];  
        pre[ch[x][p]] = y;
        pre[x] = z;             
        if(z)   ch[z][ch[z][1] == y] = x;
        else    root = x; 
        ch[x][p] = y;       
        pre[y] = x;
        pushUp(y);            
        pushUp(x);
    }

    void insert(int x, int pkey, int fa = 0){
        if(x == 0){
            newNode(x, pkey);
            if(fa)  ch[fa][!(pkey < key[fa])] = x;  
            pre[x] = fa;
            return;
        }
        insert(ch[x][!(pkey < key[x])], pkey, x);
        pushUp(x);
        int y = ch[x][!(pkey < key[x])];
        if(weight[y] > weight[x])  rotate(y, (key[y] < key[x]));
    }

    void init(){
        tot = 0, root = 1;
        insert(0, inf);
        insert(root, -inf);
    }

    void query(int x, int pkey, int& ans){
        if(x == 0)     return;
        if(key[x] <= pkey){
            ans = max(ans, key[x]);
            query(ch[x][1], pkey, ans);
        }else{
            query(ch[x][0], pkey, ans);
        }
    }
};

Treap tp;

