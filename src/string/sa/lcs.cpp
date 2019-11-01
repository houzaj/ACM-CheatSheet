#include <bits/stdc++.h>
using namespace std;
const int N = (int)200000 + 15;

int t1[N], t2[N], buc[N], sa[N], rk[N], height[N];
char s[N];

inline void buildSA(char* s, int n, int m = 128) {
    int* x = t1, *y = t2;
    memset(buc + 1, 0, m * sizeof(int));
    for(int i = 1; i <= n; i++) {
        buc[x[i] = s[i]]++;
    }
    for(int i = 1; i <= m; i++) {
        buc[i] += buc[i - 1];
    }
    for(int i = n; i >= 1; i--) {
        sa[buc[x[i]]--] = i;
    }

    for(int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for(int i = n - k + 1; i <= n; i++) {
            y[++p] = i;
        }
        for(int i = 1; i <= n; i++) {
            if(sa[i] > k) {
                y[++p] = sa[i] - k;
            }
        }
        memset(buc + 1, 0, m * sizeof(int));
        for(int i = 1; i <= n; i++) {
            buc[x[i]]++;
        }
        for(int i = 1; i <= m; i++) {
            buc[i] += buc[i - 1];
        }
        for(int i = n; i >= 1; i--) {
            sa[buc[x[y[i]]]--] = y[i];
        }
        swap(x, y);
        p = x[sa[1]] = 1;
        for(int i = 2; i <= n; i++) {
            int a = sa[i] + k > n ? -1 : y[sa[i] + k];
            int b = sa[i - 1] + k > n ? -1 : y[sa[i - 1] + k];
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && a == b) ? p : ++p;
        }
        if(p >= n) {
            break;
        }
        m = p;
    }
}

inline void getHeight(char* s, int n) {
    for(int i = 1; i <= n; i++) {
        rk[sa[i]] = i;
    }
    int k = 0;
    for(int i = 1; i <= n; i++) {
        if(rk[i] == 1) {
            continue;
        }
        if(k) {
            k--;
        }
        int j = sa[rk[i] - 1];
        while(s[i + k] == s[j + k]) {
            k++;
        }
        height[rk[i]] = k;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while(cin >> (s + 1)) {
        int pos = strlen(s + 1) + 1;
        s[pos] = '$';
        cin >> (s + 1 + pos);
        int n = strlen(s + 1);
        buildSA(s, n);
        getHeight(s, n);

        int maxx = 0;
        for(int i = 2; i <= n; i++) {
            if(maxx < height[i] && (sa[i - 1] < pos && sa[i] > pos || sa[i - 1] > pos && sa[i] < pos)) {
                maxx = height[i];
            }
        }
        cout << maxx << "\n";
    }
    cout.flush();
}

