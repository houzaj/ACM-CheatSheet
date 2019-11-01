int getPriority(char ch){
    if(ch == '*' || ch == '/')          return 2;
    else if(ch == '+' || ch == '-')     return 1;
    else                                return 0;
}

bool isOperation(char ch){
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')');
}

void getSuffixExp(char s[]){
    stack<char> stk;
    pp = 0;
    for(int i = 0; s[i]; i++){
        if(isOperation(s[i])){
            if(s[i] == ')'){
                while(!stk.empty() && stk.top() != '('){
                    suffix_exp[pp++] = make_pair(stk.top(), 1);
                    stk.pop();
                }
                stk.pop();
            }else{
                while(s[i] != '(' && !stk.empty() && getPriority(stk.top()) >= getPriority(s[i])){   //)
                    suffix_exp[pp++] = make_pair(stk.top(), 1);
                    stk.pop();
                }
                stk.push(s[i]);
            }
        }else{
            suffix_exp[pp++] = make_pair(s[i], 0);
        }
    }
    while(!stk.empty()){
        suffix_exp[pp++] = make_pair(stk.top(), 1);
        stk.pop();
    }
}

void newNode(int rt, char val){
    tree[rt].ch[0] = tree[rt].ch[1] = 0;
    tree[rt].data = val;
}

int buildTree(){
    int rt = 0;
    stack<int> stk;
    for(int i = 0; i < pp; i++){
        if(suffix_exp[i].second == 0){
            newNode(++rt, suffix_exp[i].first);
            stk.push(rt);
        }else{
            int t2 = stk.top();
            stk.pop();
            int t1 = stk.top();
            stk.pop();

            newNode(++rt, suffix_exp[i].first);
            tree[rt].ch[0] = t1;
            tree[rt].ch[1] = t2;
            stk.push(rt);
        }
    }
    return rt;
}

void dfs(int u, int pre, bool is_left){
    if(!isOperation(tree[u].data)){
        putchar(tree[u].data);
        return;
    }

    bool flag = false;
    if(pre != -1 && is_left && getPriority(tree[u].data) < getPriority(tree[pre].data))                 flag = true;
    if(pre != -1 && !is_left){
        if(getPriority(tree[u].data) < getPriority(tree[pre].data))                                     flag = true;
        else if(getPriority(tree[u].data) == getPriority(tree[pre].data) && (tree[pre].data == '-' || tree[pre].data == '/'))       flag = true;
    }

    if(flag)    putchar('(');
    dfs(tree[u].ch[0], u, true);
    putchar(tree[u].data);
    dfs(tree[u].ch[1], u, false);
    if(flag)    putchar(')');
}
