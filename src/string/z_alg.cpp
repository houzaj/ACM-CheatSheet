char s[N];
int z[N];

inline void zFunc(char* s, int n) {
    z[1] = 0;
    for(int i = 2, l = 1, r = 1; i <= n; i++) {
        z[i] = 0;
        if(i <= r) {
            z[i] = min(z[i - l + 1], r - i + 1);
        }
        while(i + z[i] <= n && s[1 + z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}
