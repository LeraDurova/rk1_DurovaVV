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

## Публикация на GitHub

Имя репозитория: **`RK_1_Durova_IU1_42B`**.

1. На [github.com/new](https://github.com/new) создайте репозиторий с таким именем, **без** README и .gitignore (они уже есть локально).
2. Если ваш логин на GitHub не совпадает с URL ниже, замените его:
   ```bash
   cd RK_1
   git remote set-url origin https://github.com/ВАШ_ЛОГИН/RK_1_Durova_IU1_42B.git
   ```
3. Отправьте ветку:
   ```bash
   git push -u origin main
   ```
   При запросе пароля используйте [Personal Access Token](https://github.com/settings/tokens) (классический пароль GitHub для HTTPS не подходит).

Уже настроено: `git remote add origin …` → сейчас указан `https://github.com/LeraDurova/RK_1_Durova_IU1_42B.git`. После создания пустого репозитория с этим именем на аккаунте **LeraDurova** достаточно выполнить `git push -u origin main` из папки `RK_1`.
