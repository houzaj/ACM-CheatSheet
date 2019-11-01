void dfs(int depth, ull cnt, ull num, ull& upper, ull& max_num, ull& ans){  //传入的n作为上界
    if(cnt > max_num || (cnt == max_num && ans > num)){   //因子数大于 或 因子数相同但值小则更新
        ans = num;
        max_num = cnt;
    }
    for(ull i = 1; i <= prime_nums[depth - 1]; i++){
        if(num > upper/prime[depth])     break;
        prime_nums[depth] = i;
        num*=prime[depth];
        dfs(depth + 1, cnt*(i + 1), num, upper, max_num, ans);
    }
    prime_nums[depth] = 0;
}

