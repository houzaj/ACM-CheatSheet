bool cmp(const node& a, const node& b){
    if(a.l/block_size == b.l/block_size){
        return a.r < b.r;
    }else{
        return a.l/block_size < b.l/block_size;
    }
}

int l = 0, r = -1;
int answer = 0;
for(int i = 0; i < q; i++){
    while(que[i].l < l) { add(--l, answer); }
    while(l < que[i].l) { del(l++, answer); }
    while(que[i].r < r) { del(r--, answer); }
    while(r < que[i].r) { add(++r, answer); }
    ans[que[i].id] = answer;
}
