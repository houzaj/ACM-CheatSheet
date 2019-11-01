for(int i = 0; i < n; i++){
    while(stk1.top().val >= a[i])    stk1.pop();
    l[i] = stk1.top().idx + 1;
    stk1.push(Node(a[i], i));
}

for(int i = n - 1; i >= 0; i--){
    while(stk2.top().val >= a[i])    stk2.pop();
    r[i] = stk2.top().idx - 1;
    stk2.push(Node(a[i], i));
}
