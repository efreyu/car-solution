
# Test task ![Linux build](https://github.com/efreyu/test-task/workflows/Linux%20build/badge.svg?branch=master) 

#### В самом начале вам необходимо развернуть проект
```bash
git clone git@github.com:efreyu/test-task.git test-task 
cd test-task
```

#### Сбора WebAssembly:
Для работы нужно установить компилятор emscripten
```bash
mkdir public
cd public
cmake -DBUILD_TYPE=webassembly ..
make -j$(nproc)
```

#### Сборка десктоп версии Linux/MacOS:

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
make test #Не обязательно
./Car_Example
```

#### Конфигурация докера для отладки emscripten
В сборке предусмотрено 2 контейнера, ubuntu для сборки и nginx для работы веб-сервера
```bash
chmod +x game.sh
./game.sh -b                    # Собрать контейнер
./game.sh --wasm-build          # Компиляция проекта
./game.sh --test                # Запуск тестов
./game.sh -o ubuntu bash [cmd]  # Выполнить произвольную команду в контейнере
./game.sh -d                    # Остановить контейнеры
./game.sh --help                # Для получения справки
```