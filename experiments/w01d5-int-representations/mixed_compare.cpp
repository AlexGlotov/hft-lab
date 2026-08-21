#include <cstdio>

bool cmpUnsignedInt(int a, unsigned int b) {
    return a < b;
}

bool cmpUnsignedShort(int a, unsigned short b) {
    return a < b;
}

bool cmpUnsignedLong(int a, unsigned long b) {
    return a < b;
}

int main() {
    std::printf("cmpUnsignedInt(-1, 1u)          = %d\n", cmpUnsignedInt(-1, 1u));
    std::printf("cmpUnsignedShort(-1, (unsigned short)1) = %d\n", cmpUnsignedShort(-1, 1));
    std::printf("cmpUnsignedLong(-1, 1ul)        = %d\n", cmpUnsignedLong(-1, 1ul));
    return 0;
}
