int bsgs(int a, int b) {
    unordered_map<int, int> mp;
    int sqrtP = ceil(sqrt(MOD));
    for(int y = 0, sum = b; y <= sqrtP; y++, sum = 1LL * sum * a % MOD) {
        mp[sum] = y;
    }

    int z = quickPow(a, sqrtP);
    for(int x = 1, sum = z; x <= sqrtP; x++, sum = 1LL * sum * z % MOD) {
        if(mp.count(sum)) {
            return x * sqrtP - mp[sum];
        }
    }
    return -1;
}
