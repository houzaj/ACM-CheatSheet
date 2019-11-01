char str[10000 + 1];
int  pos[N];
int  nxt[N][ascii_size];
int  fail[N];
int  tot;

int  que[N];
int  head, tail;

inline void newNode(int& x){
    x = tot++;
    memset(nxt[x], -1, sizeof(nxt[x]));
    fail[x] = 0;
    pos[x] = 0;
}

inline void init(){
    head = tail = 0;
    tot = 1;
    memset(nxt[0], -1, sizeof(nxt[0]));
    fail[0] = pos[0] = 0;
}

void push(char s[], int i){
    int p = 0;
    for(int i = 0; s[i]; i++){
        int idx = s[i] - 32;
        if(nxt[p][idx] == -1){
            newNode(nxt[p][idx]);
        }
        p = nxt[p][idx];
    }
    pos[p] = i;
}

void setFail(){
    for(int idx = 0; idx < ascii_size; idx++){
        if(nxt[0][idx] != -1){
            que[head++] = nxt[0][idx];
        }else{
            nxt[0][idx] = 0;
        }
    }
    while(tail != head){
        int p = que[tail++];
        for(int idx = 0; idx < ascii_size; idx++){
            if(~nxt[p][idx]){
                fail[nxt[p][idx]] = nxt[fail[p]][idx];
                que[head++] = nxt[p][idx];
            }else{
                nxt[p][idx] = nxt[fail[p]][idx];
            }
        }
    }
}

void query(char s[]){
    int p = 0;
    for(int i = 0; s[i]; i++){
        int idx = s[i] - 32;
        p = nxt[p][idx];
        for(int q = p; q; q = fail[q]){
            if(pos[q]) {
                // DO SOMETHING
            }
        }
    }
}
