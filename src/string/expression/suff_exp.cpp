void getSuffixExp(char s[]){
    pp = 0;
    stack<char> stk;
    for(int i = 0; s[i]; ){
        if(s[i] == ' '){
            i++;
            continue;
        }

        if(isdigit(s[i])){
            sscanf(s + i, "%d", &suffix_exp[pp].data);
            suffix_exp[pp++].type = 0;
            while(isdigit(s[i]))    i++;
        }else{
            while(!stk.empty() && getPriority(stk.top()) >= getPriority(s[i])){
                suffix_exp[pp++] = Data{stk.top(), 1};
                stk.pop();
            }

            stk.push(s[i]);
            i++;
        }
    }
    while(!stk.empty()){
        suffix_exp[pp++] = Data{stk.top(), 1};
        stk.pop();
    }
}

double solve(){
    stack<double> ans;
    for(int i = 0; i < pp; i++){
        if(suffix_exp[i].type == 0)     ans.push(suffix_exp[i].data);
        else{
            double t2 = ans.top();
            ans.pop();
            double t1 = ans.top();
            ans.pop();

            if(suffix_exp[i].data == '+')        ans.push(t1 + t2);
            else if(suffix_exp[i].data == '-')   ans.push(t1 - t2);
            else if(suffix_exp[i].data == '*')   ans.push(t1 * t2);
            else if(suffix_exp[i].data == '/')   ans.push(t1 / t2);
        }
    }
    return ans.top();
}

