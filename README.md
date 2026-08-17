# hft-lab

![CI](https://github.com/AlexGlotov/hft-lab/actions/workflows/ci.yml/badge.svg)


## Структура

```
hft-lab/
├── CMakeLists.txt
├── CMakePresets.json
├── cmake/            # общие CMake-модули (флаги компилятора и т.п.)
├── lib/               # переиспользуемый код (аллокаторы, обёртки типов и т.д.)
├── experiments/        # по каталогу на эксперимент: w00_sanity/, w01_type_deduction/, ...
├── bench/              # микробенчмарки
├── tests/              # модульные тесты для lib/
└── .github/workflows/ci.yml
```

## Тулчейн

- C++23, `CMAKE_CXX_EXTENSIONS OFF`
- Компиляторы: `g++-14` и `clang++-18` — оба, чтобы сверять кодогенерацию
  и предупреждения между GCC и LLVM
- CMake ≥ 3.28, генератор Ninja
- Глобально: `-Wall -Wextra -Werror -Wpedantic`

## Сборка и тесты

Пресеты в `CMakePresets.json`:

| Пресет | Компилятор | Флаги |
|---|---|---|
| `debug-asan` / `debug-asan-gcc14` / `debug-asan-clang18` | system `g++` / `g++-14` / `clang++-18` | `-fsanitize=address,undefined -fno-sanitize-recover=undefined -g` |
| `release` / `release-gcc14` / `release-clang18` | — | `-O2 -g` |
| `release-native` | system `g++` | `-O3 -march=native` |

```bash
cmake --preset debug-asan-gcc14
cmake --build --preset debug-asan-gcc14
ctest --preset debug-asan-gcc14 --output-on-failure
```

Аналогично для `debug-asan-clang18`, `release-gcc14`, `release-clang18`.

## CI

GitHub Actions прогоняет матрицу `{gcc-14, clang-18} × {debug-asan,
release}` на каждый push/PR — см. `.github/workflows/ci.yml`.

## Эксперименты

- [`experiments/w00_sanity`](experiments/w00_sanity/README.md) — доказательство,
  что ASan/UBSan реально ловят heap-buffer-overflow и signed integer
  overflow, а не просто присутствуют в флагах сборки.
- [`experiments/w01_type_deduction`](experiments/w01_type_deduction) —
  вывод типов шаблонов (T по значению / по ссылке / по forwarding-ссылке),
  зафиксированный через `static_assert`.
