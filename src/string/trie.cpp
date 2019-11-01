int  cnt[N];
int  nxt[N][26];
char str[12];
int  tot;

inline void init(){
    tot = 1;
    memset(cnt, 0, sizeof(cnt));
    memset(nxt[0], -1, sizeof(nxt));
}

void push(char* s){
    int p = 0;
    for(int i = 0; s[i]; i++){
        int idx = s[i] - 'a';
        if(nxt[p][idx] == -1){
            nxt[p][idx] = tot++;
        }
        cnt[nxt[p][idx]]++;
        p = nxt[p][idx];
    }
}

int query(char* s){
    int p = 0;
    for(int i = 0; s[i]; i++){
        int idx = s[i] - 'a';
        if(nxt[p][idx] == -1)   return 0;
        p = nxt[p][idx];
    }
    return cnt[p];
}
