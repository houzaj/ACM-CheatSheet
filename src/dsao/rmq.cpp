void build(int n){
    for(int j = 1; (1 << j) <= n; j++){
        for(int i = 1; i + (1 << j) - 1 <= n; i++){
            arr_max[i][j] = max(arr_max[i][j - 1], arr_max[i + (1 << (j - 1))][j - 1]);
            arr_min[i][j] = min(arr_min[i][j - 1], arr_min[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r, int p){
    int k = log(r - l + 1)/log(2);
    if(p == 0)  return max(arr_max[l][k], arr_max[r - (1 << k) + 1][k]);
    else        return min(arr_min[l][k], arr_min[r - (1 << k) + 1][k]);
}
