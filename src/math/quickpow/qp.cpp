inline int quickPow(int a, int b) {
    int ans = 1, base = a;
    while(b) {
        if(b & 1LL) {
            ans = (ll)ans * base % MOD;
        }
        base = (ll)base * base % MOD;
        b >>= 1LL;
    }
    return ans;
}
