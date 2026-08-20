int sum(const int* a, int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) s += a[i];
    return s;
}

int call_sum(const int* a) {
    return sum(a, 8);
}
