char s[N];

struct SuffixAutomaton {
    int slink[N], len[N], trans[N][SIZE], cnt[N], buc[N], vec[N];
    ll dp[N];
    int lst, tot;

    inline void init() {
        tot = 0;
        lst = newNode();
        slink[lst] = len[lst] = 0;
    }

    inline int newNode() {
        int x = ++tot;
        memset(trans[x], 0, sizeof(trans[x]));
        dp[x] = idg[x] = cnt[x] = 0;
        return x;
    }

    inline void push(int val) {
        int p = lst, np = newNode();
        len[np] = len[p] + 1;
        cnt[np] = 1;

        for(; p && trans[p][val] == 0; p = slink[p]) {
            trans[p][val] = np;
        }

        if(p == 0) {
            slink[np] = 1;
        } else {
            int q = trans[p][val];
            if(len[q] == len[p] + 1) {
                slink[np] = q;
            } else {
                int nq = ++tot;
                cnt[nq] = dp[nq] = 0;
                slink[nq] = slink[q];
                len[nq] = len[p] + 1;
                memcpy(trans[nq], trans[q], sizeof(trans[q]));
                slink[np] = slink[q] = nq;
                for(; p && trans[p][val] == q; p = slink[p]) {
                    trans[p][val] = nq;
                }
            }
        }
        lst = np;
    }

    inline void getCnt() {
        memset(buc, 0, (tot + 1) * sizeof(int));
        for(int i = 2; i <= tot; i++) {
            buc[len[i]]++;
        }
        for(int i = 2; i <= tot; i++) {
            buc[i] += buc[i - 1];
        }
        for(int i = tot; i >= 2; i--) {
            vec[buc[len[i]]--] = i;
        }

        for(int i = tot - 1; i >= 1; i--) {
            int u = vec[i];
            cnt[slink[u]] += cnt[u];
        }
        cnt[1] = 0;
    }
};

SuffixAutomaton sam;
