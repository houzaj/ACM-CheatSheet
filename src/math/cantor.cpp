// 康托展开，从末位为第1位，首位为第n位
// X = a[n]*(n-1)! + a[n - 1]*(n-2)! + ... + a[1]*0!

const int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

int cantor(int a[N]){
    int sum = 0;
    for(int i = 0; i < N; i++){
        int cnt = 0;
        for(int j = i + 1; j < N; j++){
            if(a[j] < a[i])     cnt++;     //后面的数比a[i]小的有几个
        }
        sum += cnt*fac[N - i - 1];        //sum += a[n] * (n - 1)!
    }
    return sum;
}

void inv_cantor(int num, int a[]){
    bool used[N + 1] = {0};
    for(int i = 0; i < N; i++){
        int cnt = num/fac[N - i - 1];   //比a[i]小且未用过的数有cnt个
        num %= fac[N - i - 1];
        
        int j;
        for(j = 0; j < N; j++){         //回推该位数字是几
            if(!used[j]){
                if(cnt == 0)    break;
                cnt--;
            }
        }
        a[i] = j;
        used[j] = true;
    }
}
