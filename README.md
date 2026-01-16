# MathLib

Безопасные математические операции с обнаружением переполнения для C/C++.

## Что это?

Библиотека базовых математических операций с корректной обработкой переполнения:
- Сложение, вычитание, умножение, деление
- Возведение в степень
- Факториал

## Сборка

### Локально
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### FetchContent
```cmake
include(FetchContent)
FetchContent_Declare(mathlib GIT_REPOSITORY https://github.com/ananas091/mathlib.git)
FetchContent_MakeAvailable(mathlib)
target_link_libraries(myapp PRIVATE mathlib)
```
