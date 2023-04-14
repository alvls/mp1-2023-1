#include "Header.h"

Cinema session_list;
//TicketOffice manager;
void create_sessions();

int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");
	int day, month, hr, min, number, place_count, index;
	string name;
	bool purchase, find_pur, get_ticket, vip_ticket;
	int menu_main, menu_find, vip_status, save_menu;
	TicketOffice manager;
	MyDate t_day;
	MyDate s_day;
	MyTime t_time;
	MyTime s_time;
	Film chose, empty;
	create_sessions();
	hello();
	string functions[] = { "\t\tВыберите необходмую функцию", "> показать доступные сеансы", 
		"> перейти к выбору сеанса", "> поиск сеансов", "> сменить дату и время", "> выход из программы"};
	string find[] = { "\t\tВыберите критерий поиска", "> поиск по названию",
		"> поиск по залу", "> вернуться назад", };
	string vip[] = { "\t\tЖелаете ли Вы найти VIP-места?", "> да", "> нет" };
	string save[] = { "Желаете ли вы оплатить билеты?", "> да", "> отменить бронь" };
	manager.set_new_list(session_list);
	while (1)
	{
		system("cls");
		purchase = true;
		cout << "Введите дату и месяц покупки в числовом формате" << endl;
		cin >> day;
		cin >> month;
		system("cls");
		cout << "Введите время покупки (часы и минуты)" << endl;
		cin >> hr;
		cin >> min;
		t_day.set_day(day);
		t_day.set_month(month);
		t_time.set_hours(hr);
		t_time.set_minutes(min);
		manager.set_purchase_date(t_day);
		manager.set_purchase_time(t_time);
		while (purchase)
		{
			manager.null_cost();
			menu_main = menu_mode(functions, 6);
			switch (menu_main)
			{
			case 1:
				system("cls");
				cout << "\t\tДоступно для покупки" << endl;
				manager.print_enable_sessions();
				system("pause");
				break;
			case 2:
				chose = manager.find_session(t_day, t_time);
				system("cls");
				if (chose.film_name != "fail")
				{
					get_ticket = true;
					index = manager.return_session_index(chose);
					manager.set_chosen_session(session_list[index]);
					while (get_ticket)
					{
						system("cls");
						vip_status = menu_mode(vip, 3);
						if (vip_status == 1)
							vip_ticket = true;
						else
							vip_ticket = false;
						cout << "Введите желаемое количество мест: ";
						cin >> place_count;
						system("cls");
						if (manager.check_free_place(vip_ticket, index)<place_count)
						{
							system("cls");
							cout << "К сожалению, на этот сеанс осталось всего " << manager.check_free_place(vip_ticket, index) << " мест." << endl;
							system("pause");
							get_ticket = false;
						}
						else
						{
							manager.print_tickets(place_count,vip_ticket,index);
							system("pause");
							save_menu = menu_mode(save, 3);
							switch (save_menu)
							{
							case 1:
								get_ticket = false;
;								break;
							case 2:
								get_ticket = false;
								manager.list_plus_place(vip_ticket, index, place_count);
								break;
							}
						}
					}
					chose = empty;
				}
				else
				{
					system("cls");
					cout << "По вашему запросу ничего не найдено" << endl;
					system("pause");
				}
				break;
			case 3:
				find_pur = true;
				while (find_pur)
				{
					menu_find = menu_mode(find, 4);
					switch (menu_find)
					{
					case 1:
						system("cls");
						cout << "Введите название интересующего Вас фильма: ";
						cin.ignore();
						getline(cin,name);
						manager.sessions_by_name(name);
						cin.putback('\n');
						system("pause");
						find_pur = false;
						break;
					case 2:
						system("cls");
						cout << "Введите номер интересующего Вас зала: ";
						cin >> number;
						manager.print_sessions_by_hall(number);
						system("pause");
						find_pur = false;
						break;
					case 3:
						find_pur = false;
						break;
					}
				}
				break;
			case 4:
				purchase = false;
				break;
			case 5:
				exit_prog();
				break;
			}
		}
	}
	system("pause");
	return 0;
}

void create_sessions()
{
	MyDate dates_for_first(3,3);
	MyDate dates_for_second(1, 3);
	MyDate dates_for_third(4, 3);
	MyTime time;
	Hall hallA(1, 10, 15, 3, 6, 250);
	Hall hallB(2, 7, 10, 4, 4, 150);
	Hall hallC(3, 9, 10, 5, 8, 300);
	Hall hallD(4, 4, 10, 3, 5, 400);
	int i = dates_for_first.return_day();
	int j = dates_for_second.return_day();
	int k = dates_for_third.return_day();
	int a = i + 31;
	string name = "Спящий программист";
	for (i; i<a;i++)
	{
		if (i % 2 == 0)
		{
			time.set_hours(20);
			time.set_minutes(30);
			session_list.create_new_session(name, dates_for_first, time, hallA);
		}
		else
		{
			time.set_hours(14);
			time.set_minutes(15);
			session_list.create_new_session(name, dates_for_first, time, hallB);
		}
		dates_for_first.set_day(dates_for_first.return_day() + 1);
	}
	name = "Последний студент";
	for (j; j < a; j++)
	{
		if (j % 2 == 0)
		{
			time.set_hours(11);
			time.set_minutes(15);
			session_list.create_new_session(name, dates_for_second, time, hallC);
		}
		else
		{
			time.set_hours(18);
			time.set_minutes(40);
			session_list.create_new_session(name, dates_for_second, time, hallD);
		}
		dates_for_second.set_day(dates_for_second.return_day() + 1);
	}
	name = "Отчисленный вчера";
	for (k; k < a; k++)
	{
		if (k % 2 == 0)
		{
			time.set_hours(13);
			time.set_minutes(30);
			session_list.create_new_session(name, dates_for_third, time, hallD);
		}
		else
		{
			time.set_hours(9);
			time.set_minutes(5);
			session_list.create_new_session(name, dates_for_third, time, hallA);
		}
		dates_for_third.set_day(dates_for_third.return_day() + 1);
	}
}