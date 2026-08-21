void opaque(int*);

void f(int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) {
        s += i;
        opaque(&s);
    }
}
