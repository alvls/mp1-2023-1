#include <iostream>
#include "Menu.h"

int main()
{
  // ������� ������ ����
  Menu menu(3);

  // ������ �������� ������� ����
  menu.Set_name(0, "Option 1");
  menu.Set_name(1, "Option 2");
  menu.Set_name(2, "Option 3");

  // ��������� ����� ����� ����
  menu.AddItem("Option 4");

  // ������� ����� ����
  menu.RemoveItem(1);

  // ������������ ����� ������������
  menu.Print(5, 5, myCallback);

  return 0;
}
