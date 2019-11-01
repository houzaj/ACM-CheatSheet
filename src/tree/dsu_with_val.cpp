int find(int x){
    if(ft[x] == x)  return x;
    int xft = ft[x];
    ft[x] = find(ft[x]);
    sum_below[x] += sum_below[xft];
    return ft[x];
}

void merge(int a, int b){
    int ra = find(a), rb = find(b);
    if(ra != rb){
        ft[rb] = ra;
        sum_below[rb] = sum_tot[ra];
        sum_tot[ra] += sum_tot[rb];
    }
}
