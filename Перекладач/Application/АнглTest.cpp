#include "Application.h"
#include <Windows.h>

int main()
{
   // Перші дві рядки коду встановлюють кодову сторінку консолі для підтримки кирилиці.
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Application test; //Після створення об'єкта test, викликається його метод run(), який, виконує основну логіку додатку.

    test.run();

    _getch(); // Чекає, доки користувач натисне будь-яку клавішу перед закриттям консолі.
    return 0;
}