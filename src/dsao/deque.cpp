template <typename T>
struct Deque {
    int head, tail;
    T que[N << 1];

    void clear() {head = tail = N;}
    void push_back(T x) { que[tail++] = x; }
    void push_front(T x) { que[--head] = x; }
    void pop_front() { head++; }
    void pop_back() { tail--; }
    T front() { return que[head]; }
    T back() { return que[tail]; }
    bool empty() { return head == tail; }
};
