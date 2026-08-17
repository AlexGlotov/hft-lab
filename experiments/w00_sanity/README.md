# w00_sanity — доказательство, что санитайзеры реально работают

Флаг `-fsanitize=address,undefined` в `CMakePresets.json` ничего не
доказывает сам по себе — «я добавил флаг» и «санитайзер срабатывает» это
разные состояния мира. Здесь — два намеренно ломающихся бинарника и
реальный вывод ASan/UBSan, полученный их прямым запуском.

## Файлы

- `heap_overflow.cpp` — запись 1 байта за границей `new char[size]`.
  `size` намеренно не constant-foldable (`size = 9 + argc`), чтобы
  `-Warray-bounds`/оптимизатор не поймали баг ещё на этапе компиляции.
- `signed_overflow.cpp` — то же самое для `INT_MAX + 1` через `argc`,
  чтобы обмануть constant folding.

Оба собираются только в `debug-asan`-пресетах (гейт
`HFT_LAB_SANITIZERS_ENABLED` в `experiments/CMakeLists.txt`) и
зарегистрированы в ctest с `WILL_FAIL TRUE` — падение процесса это
ожидаемый и единственно правильный исход.

## Реальный вывод — g++-14 (`debug-asan-gcc14`)

`w00_heap_overflow`, exit code 1:
```
==33490==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x50200000001a at pc 0x5ca3359eb344 bp 0x7fffa95c3ce0 sp 0x7fffa95c3cd0
WRITE of size 1 at 0x50200000001a thread T0
    #0 0x5ca3359eb343 in main /home/gloto/hft-lab/experiments/w00_sanity/heap_overflow.cpp:8
    #1 0x7ab48562a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #2 0x7ab48562a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #3 0x5ca3359eb1a4 in _start (.../w00_heap_overflow+0x11a4)

0x50200000001a is located 0 bytes after 10-byte region [0x502000000010,0x50200000001a)
allocated by thread T0 here:
    #0 0x7ab4866fe6c8 in operator new[](unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:98
    #1 0x5ca3359eb2af in main /home/gloto/hft-lab/experiments/w00_sanity/heap_overflow.cpp:6

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/gloto/hft-lab/experiments/w00_sanity/heap_overflow.cpp:8 in main
==33490==ABORTING
```
(shadow-byte карта и легенда опущены для краткости — есть в полном выводе при запуске локально)

`w00_signed_overflow`, exit code 1:
```
/home/gloto/hft-lab/experiments/w00_sanity/signed_overflow.cpp:7:9: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
```

## Реальный вывод — clang++-18 (`debug-asan-clang18`)

`w00_heap_overflow`, exit code 1:
```
==33634==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x50200000001a at pc 0x653ba00a9c6d bp 0x7ffca1e28ac0 sp 0x7ffca1e28ab8
WRITE of size 1 at 0x50200000001a thread T0
    #0 0x653ba00a9c6c in main /home/gloto/hft-lab/experiments/w00_sanity/heap_overflow.cpp:8:18
    #1 0x73cf9042a1c9 in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #2 0x73cf9042a28a in __libc_start_main csu/../csu/libc-start.c:360:3
    #3 0x653b9ffce344 in _start (.../w00_heap_overflow+0x2c344)

0x50200000001a is located 0 bytes after 10-byte region [0x502000000010,0x50200000001a)
allocated by thread T0 here:
    #0 0x653ba00a78d1 in operator new[](unsigned long) (.../w00_heap_overflow+0x1058d1)
    #1 0x653ba00a9b8d in main /home/gloto/hft-lab/experiments/w00_sanity/heap_overflow.cpp:6:20

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/gloto/hft-lab/experiments/w00_sanity/heap_overflow.cpp:8:18 in main
==33634==ABORTING
```

`w00_signed_overflow`, exit code 1:
```
/home/gloto/hft-lab/experiments/w00_sanity/signed_overflow.cpp:7:28: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior /home/gloto/hft-lab/experiments/w00_sanity/signed_overflow.cpp:7:28
```

Разница между компиляторами чисто стилистическая: clang дополнительно
печатает `SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior` для
UBSan-срабатываний, gcc — нет. Суть диагностики (файл, строка, характер
ошибки) идентична на обоих тулчейнах.

## Как воспроизвести

```bash
cmake --build --preset debug-asan-gcc14
./build/debug-asan-gcc14/experiments/w00_sanity/w00_heap_overflow
./build/debug-asan-gcc14/experiments/w00_sanity/w00_signed_overflow
```
