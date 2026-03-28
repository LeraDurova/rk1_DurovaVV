# RK_1_Durova_IU1_42B

Рубежный контроль 1, **вариант 3** (C++20).

## Сборка

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Или через CLion.

## Цели CMake

- `RK_1` — шаблон `main.cpp`
- `variant3_task1` — задача 1: склад (mutex, condition_variable, atomic)
- `variant3_task2` — задача 2: конвейер (std::binary_semaphore)

## Запуск

После сборки (пример для Debug):

- `build/variant3_task1` или `cmake-build-debug/variant3_task1.exe`
- `build/variant3_task2` или `cmake-build-debug/variant3_task2.exe`

На Windows для корректной кириллицы в консоли в начале `main` выставляется UTF-8.
