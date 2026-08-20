void accumulate(int* s, const int* a, int n) {
    for (int i = 0; i < n; ++i) *s += a[i];
}

void accumulate(int* s, const char* a, int n) {
    for (int i = 0; i < n; ++i) *s += a[i];
}

void accumulate(int* s, const float* a, int n) {
    for (int i = 0; i < n; ++i) *s += static_cast<int>(a[i]);
}
