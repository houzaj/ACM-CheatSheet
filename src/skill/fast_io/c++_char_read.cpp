inline int read() {
    int x = 0; static char c; bool minus = false;
    for (; !(c >= '0' && c <= '9'); c = getchar()) if (c == '-') minus = true;
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = getchar()); if (minus) x = -x;
    return x;
}
