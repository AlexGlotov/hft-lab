int main(int argc, char**) {
    // argc >= 1, но конкретное значение компилятору на этапе компиляции
    // неизвестно — size не сворачивается в константу, поэтому
    // -Warray-bounds не поймает переполнение статически.
    int size = 9 + argc;  // при обычном запуске (argc == 1) size == 10
    char* buffer = new char[size];

    buffer[size] = 0;  // запись 1 байта за пределом буфера — heap-buffer-overflow

    delete[] buffer;
    return 0;
}
