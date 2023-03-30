#include <iostream>
#include "Menu.h"
#include "ConsoleUtils.h"

COORD menu_area = { 0, 0 };
COORD work_area = { 20, 5 };

using namespace std;

void wk_print(const char* str)
{
	gotoxy(work_area.X, work_area.Y);
	std::cout << str << std::endl;
}

void handler_opt1()
{
	wk_print("��������� ��������� �����: 1");
}
void handler_opt2()
{
	wk_print("��������� ��������� �����: 2");
}
void handler_opt3()
{
	wk_print("��������� ��������� �����: 3");
}
void handler_opt4()
{
	wk_print("��������� ��������� �����: 4");
}
void handler_opt5()
{
	wk_print("��������� ��������� �����: 5");
}

int main()
{
	setlocale(LC_ALL, "Russian");

	Menu menu(3, menu_area, work_area);

	menu.get_item(0).title = "������� 1";
	menu.get_item(0).handler = &handler_opt1;

	menu.get_item(1).title = "������� 2";
	menu.get_item(1).handler = &handler_opt2;

	menu.get_item(2).title = "������� 3";
	menu.get_item(2).handler = &handler_opt3;

	menu.listen();

	menu.set_size(4);
	menu.get_item(3).title = "������� 4 (������ ����� ����� ������ � �������� ����� �� ������)";
	menu.get_item(3).handler = &handler_opt4;

	menu.listen();

	menu.add_item({ "������� 5 (�������� ����� �����)", &handler_opt5 });
	menu.listen();

	cout << endl;
	system("pause");

}