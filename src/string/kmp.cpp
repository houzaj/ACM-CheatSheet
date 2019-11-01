int knxt[N];

void getNext(char* p){
    knxt[0] = -1;
    int k = -1, j = 0;
    while(p[j]){
        if(k == -1 || p[k] == p[j]){
            j++;
            k++;
            knxt[j] = (p[k] != p[j] ? k : knxt[k]);
            // knxt[j] = k; //未优化版本，可求循环节
        }else{
            k = knxt[k];
        }
    }
}

int kmpSearch(char* s, char* p){
    getNext(p);
    int i = 0, j = 0;
    int cnt = 0;
    while(s[i]){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }else{
            j = knxt[j];
        }

        if(j>=0&&!p[j]){      
            cnt++;
            j = 0; 
        }
    }
    return cnt;
}
