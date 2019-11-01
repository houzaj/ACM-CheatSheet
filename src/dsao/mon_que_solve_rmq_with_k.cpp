while(!que.empty())     que.pop_back();
for(int i = 0; i < n; i++){
    while(!que.empty() && que.back().val > a[i])   que.pop_back();
    que.push_back(Node(a[i], i));
    if(i + 1 - k >= 0){
        while(!que.empty() && que.front().idx < i + 1 - k)  que.pop_front();
        ansmin[i + 1 - k] = que.front().val;
    }
}
