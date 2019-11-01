#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 10000 + 5;
const int M = 1e6 + 5;

struct QQuery{
    int l, r, tim, idx;
};
struct QModify{
    int pos, val, pre;
};
int BLOCK_SIZE;
int ans[N];
int cnt[M];
int a[N];
QQuery  queq[N];
QModify queu[N];

bool cmp(const QQuery& a, const QQuery& b){
    if(a.l/BLOCK_SIZE != b.l/BLOCK_SIZE)         return a.l < b.l;
    else if(a.r/BLOCK_SIZE != b.r/BLOCK_SIZE)    return a.r < b.r;
    return a.tim/BLOCK_SIZE < b.tim/BLOCK_SIZE;
}

void moveTimeForward(int tim, int l, int r, int& ans){
    QModify& qcur = queu[tim];
    qcur.pre = a[qcur.pos];
    a[qcur.pos] = qcur.val;
    if(l <= qcur.pos && qcur.pos <= r){
        if((--cnt[qcur.pre]) == 0)  ans--;
        if((++cnt[qcur.val]) == 1)  ans++;
    }
}

void moveTimeBack(int tim, int l, int r, int& ans){
    QModify& qcur = queu[tim];
    a[qcur.pos] = qcur.pre;
    if(l <= qcur.pos && qcur.pos <= r){
        if((--cnt[qcur.val]) == 0)  ans--;
        if((++cnt[qcur.pre]) == 1)  ans++;
    }
}

void add(int pos, int& ans){
    if((++cnt[a[pos]]) == 1)    ans++;
}

void del(int pos, int& ans){
    if((--cnt[a[pos]]) == 0)    ans--;
}

int main(){
    int n, q;
    while(~scanf("%d%d", &n, &q)){
        memset(cnt, 0, sizeof(cnt));
        BLOCK_SIZE = (int)pow(n, 2.0/3);
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }

        int ppq = 0, ppu = 0;
        while(q--){
            char s[2];
            int x, y;
            scanf("%s%d%d", s, &x, &y);
            if(s[0] == 'Q'){
                queq[ppq] = QQuery{x, y, ppu, ppq};
                ppq++;
            }else{
                queu[++ppu] = QModify{x, y, 0};
            }
        }
        sort(queq, queq + ppq, cmp);

        int r = -1, l = 0, tim = 0, curans = 0;
        for(int i = 0; i < ppq; i++){
            QQuery& q = queq[i];
            while(tim < q.tim)     moveTimeForward(++tim, l, r, curans);
            while(tim > q.tim)     moveTimeBack(tim--, l, r, curans);
            while(l < q.l)         del(l++, curans);
            while(l > q.l)         add(--l, curans);
            while(r < q.r)         add(++r, curans);
            while(r > q.r)         del(r--, curans);
            ans[q.idx] = curans;
        }

        for(int i = 0; i < ppq; i++){
            printf("%d\n", ans[i]);
        }
    }
}
