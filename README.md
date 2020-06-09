
# Car solution ![Linux build](https://github.com/efreyu/car-solution/workflows/Linux%20build/badge.svg?branch=master) ![Webassembly build](https://github.com/efreyu/car-solution/workflows/Webassembly%20build/badge.svg?branch=master) 
#### Описание:
##### Простая визуализация пересечения машинами перекрестка. Реализованна с использованием C++ и SDL2, совместимая с WebAssembly. Для тестирования и отладки сборки с emscripten использовалось окружение докера.
##### По [ссылке](https://efreyu.github.io/car-solution/) доступна версия для запуска прямо в браузере.

#### Управление:
По клику/тачу по экрану происходит создание 5 новых машин на карте.
В данном примере нельзя управлять движением транспорта и потоком.

#### Совместимость:
Сборка тестировалась на `Linux(Arch linux / Ubuntu)` и `macOS Catalina 10.15.4`, а также во всех последних браузерах с вертикальным и горизонтальным разрешением.

#### Установка и запуск:
#### В самом начале вам необходимо развернуть проект
```bash
git clone git@github.com:efreyu/car-solution.git car-solution 
cd car-solution
```

#### Сбора WebAssembly:
Требуется установить `emscripten`
```bash
mkdir public
cd public
cmake -DBUILD_TYPE=webassembly ..
make -j$(nproc)
```

#### Сборка десктоп версии Linux/MacOS:
Требуется `libsdl2` `libsdl2img`, для macOS все включено в cmake
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

После запуска контейнера приложение доступно по адресу `https://localhost:8080/`
```bash
chmod +x game.sh
./game.sh -b                    # Собрать контейнеры
./game.sh -b                    # Запуск контейнеров
./game.sh --wasm-build          # Компиляция проекта
./game.sh --test                # Запуск тестов
./game.sh -o ubuntu bash [cmd]  # Выполнить произвольную команду в контейнере
./game.sh -d                    # Остановить контейнеры
./game.sh --help                # Для получения справки
```

references:

[2D Urban Cars](https://looneybits.itch.io/2d-urban-cars)
