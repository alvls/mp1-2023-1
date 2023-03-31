#include <iostream>
#include "Menu.h"

int main()
{
  // Создаем объект меню
  Menu menu(3);

  // Задаем названия пунктам меню
  menu.Set_name(0, "Option 1");
  menu.Set_name(1, "Option 2");
  menu.Set_name(2, "Option 3");

  // Добавляем новый пункт меню
  menu.AddItem("Option 4");

  // Удаляем пункт меню
  menu.RemoveItem(1);

  // Обрабатываем выбор пользователя
  menu.Print(5, 5, myCallback);

  return 0;
}
