// 有无数种硬币，为2, 4, 8, 16, ... 各两个，问组成n的方案数
// (1 + x^2 + x^4)(1 + x^4 + x^8)...
void solve(){
    int lim = 2;
    memset(c1, 0, sizeof(c1));
    memset(c2, 0, sizeof(c2));
    c1[0] = c1[1] = c1[2] = 1;

    for(int i = 2; i < N; i <<= 1){
        for(int k = 0; k <= (i << 1); k += i){
            for(int j = 0; j <= lim && j + k < N; j++){
                c2[j + k] += c1[j];
            }
            lim += k;
        }
        for(int j = 0; j <= lim && j < N; j++){
            c1[j] = c2[j];
            c2[j] = 0;
        }
    }
}
