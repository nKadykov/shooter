# Shooter

Игра Shooter, написанная на С++ с использованием библиотеки SFML.

Меню
![screenshot](Screenshots/Menu.jpg)

Игра
![screenshot](Screenshots/Game.jpg)

Game Over
![screenshot](Screenshots/GameOver.jpg)

# Управление

Меню

- Нажмите кнопку Start Game, чтобы запуститься игру.
- Нажмите кнопку Close, чтобы выйти.

Игра

- Нажмите и удерживайте клавишу W для перемещения вверх.
- Нажмите и удерживайте клавишу S для перемещения вниз.
- Нажмите клавишу Space, чтобы выстрелить.
- Нажмите клавишу Tab для выхода в меню.
- Стреляйте по движущимся целям. Если противник достигнет левой границы, количество здоровья уменьшится.
- По окончании здоровья появится окно Game Over.

Game Over
- Нажмите кнопку Start New Game для перезапуска игры.
- Нажмите клавишу Tab для выхода в меню.


# Требования
# Проект с использованием CMAKE и библиотеки SFML
Проект с использованием CMake и vcpkg с библиотекой SFML.

# Требования
1. Скачать и установить vcpkg:</br>
git clone https://github.com/microsoft/vcpkg.git </br>
cd vcpkg </br>
bootstrap-vcpkg.bat </br>
vcpkg integrate install

2. Скачать и установить CMake

3. Скачать SFML:</br>
vcpkg install sfml:x64-windows

4. Клонировать репозиторий:</br>
git clone https://github.com/nKadykov/shooter_project.git

5. Создать папку с проектом:</br>
mkdir build</br>
cd build

6. Собрать проект:</br>
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake</br>
Заменить C:/path/to/vcpkg на путь к vcpkg</br>
cmake --build
