bool next_permutation(char* s, int len) {
    int x = -1, y = len - 1;
    for(int i = len - 1; i - 1 >= 0; i--) {
        if(s[i - 1] < s[i]) {
            x = i - 1;
            break;
        }
    }

    if(x == -1) {
        return false;
    }

    for(int i = x + 1; i < len; i++) {
        if(s[x] >= s[i]) {
            y = i - 1;
            break;
        }
    }

    swap(s[x], s[y]);
    reverse(s + x + 1, s + len);
    return true;
}
