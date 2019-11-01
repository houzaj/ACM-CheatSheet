const int N = (int)1e5 + 15;

char tmp[N], s[2 * N];
int d[2 * N];

inline void manacher(char* s, int n) {
    for(int i = 1, l = 0, r = -1; i <= n; i++) {
        int k = (i > r ? 1 : min(d[l + r - i], r - i + 1));
        while(i - k >= 1 && i + k <= n && s[i - k] == s[i + k]) {
            k++;
        }
        d[i] = k;
        if(i + k - 1 > r) {
            r = i + k - 1;
            l = i - k + 1;
        }
    }
}

int main() {
    while(~scanf("%s", tmp + 1)) {
        int n = 0, m = 0;
        s[++n] = '#';
        for(int i = 1; tmp[i]; i++) {
            s[++n] = tmp[i];
            s[++n] = '#';
            ++m;
        }
        s[n + 1] = 0;
        manacher(s, n);
        //...
    }
}
