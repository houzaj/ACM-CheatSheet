char s[N];

struct Node{
    int slink, len, cnt;
    int nxt[26];
};

struct PalindromicTree{
    int  tot;
    int  cursuffix;
    Node tree[N];

    void init(){
        tree[0].slink = 0, tree[0].len = -1, tree[0].cnt = 1;
        tree[1].slink = 0, tree[1].len = 0,  tree[1].cnt = 1;
        tot = 2, cursuffix = 1;
        initNode(1);
        initNode(0);
    }

    void initNode(int o){
        memset(tree[o].nxt, -1, sizeof(tree[o].nxt));
    }

    void add(int pos){
        int idx = s[pos] - 'a';
        int cur = cursuffix;
        while(true){
            int curlen = tree[cur].len;
            if(pos - 1 - curlen >= 0 && s[pos] == s[pos - 1 - curlen])      break;
            cur = tree[cur].slink;
        }

        if(tree[cur].nxt[idx] != -1){
            cursuffix = tree[cur].nxt[idx];
            return;
        }

        int nxt = tree[cur].nxt[idx] = tot++;
        initNode(nxt);
        tree[nxt].len = tree[cur].len + 2;
        cursuffix = nxt;

        if(tree[nxt].len == 1){
            tree[nxt].cnt = 1;
            tree[nxt].slink = 1;
            return;
        }

        while(true){
            cur = tree[cur].slink;
            int curlen = tree[cur].len;
            if(pos - 1 - curlen >= 0 && s[pos] == s[pos - 1 - curlen]){
                tree[nxt].slink = tree[cur].nxt[idx];
                break;
            }
        }

        tree[nxt].cnt = tree[tree[nxt].slink].cnt + 1;
    }
};

PalindromicTree pt;
