#include <iostream>
#include <locale>
#include <string>
#include <conio.h>
#include "Header.h"
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;
SMALL_RECT window;
COORD buf;

enum KEYS {
   UP = 72, DOWN = 80, ENTER = 13, LEFT = 75
};

enum  Menu {
   Contact_list = 0, Create_new_contact = 1, Find_contact_FIO = 2, Set_number_segments = 3, All_contacts_letter = 4, Number_contacts = 5, Selected_сontacts = 6, Save_contacts_file = 7, Read_contacts_file = 8, EXIT = 9
};

enum  Menu_2 {
   Change_selected_contact = 0, Add_contact_favorites_list = 1, Delete_contact_favorites_list = 2, Delete_contact = 3, EXIT_2 = 4
};

char Menu[10][50] = {
   "Список контактов",
   "Создать новый контакт",
   "Найти контакт по ФИО",
   "Найти контакт по телефону",
   "Выдать все контакты на заданную букву",
   "Узнать текущее число контактов",
   "Выдать все избранные контакты",
   "Сохранить контакты в файл",
   "Считать контакты из файла",
   "Выход"
};

char Menu_2[5][50] = {
   "Изменить выбранный контакт",
   "Внести контакт в список избранных",
   "Удалить контакт из списка избранных",
   "Удалить контакт",
   "Выход"
};

int active_menu = 0, active_menu_2 = 0, active_menu_3 = 0;
#define SIZE 10
#define SIZE_2 5



class contacts
{
public:

   contacts()
   {
      Surname = "Surname";
      Name = "Name";
      Middle_name = "Middle_name";
      Phone = "+70000000000";
      Day = 0;
      Month = 0;
      Year = 0;
      Chosen = false;
   }

   contacts(string surname, string name, string middle_name, string phone, int day, int month, int year, bool chosen) :
      Surname(surname), Name(name), Middle_name(middle_name), Phone(phone), Day(day), Month(month), Year(year), Chosen(chosen) {}

   void set_Surname(string surname) { Surname = surname; }
   void set_Name(string name) { Name = name; }
   void set_Middle_name(string middle_name) { Middle_name = middle_name; }
   void set_Phone(string phone) { Phone = phone; }
   void set_Day(int day) { Day = day; }
   void set_Month(int month) { Month = month; }
   void set_Year(int year) { Year = year; }
   void set_Chosen(bool stat)
   {
      if (stat == true)
         Chosen = true;
      else
         Chosen = false;
   }
   void set_tChosen() { Chosen = true; }
   void set_fChosen() { Chosen = false; }
   string get_Surname() { return Surname; }
   string get_Name() { return Name; }
   string get_Middle_name() { return Middle_name; }
   string get_Phone() { return Phone; }
   int get_Day() { return Day; }
   int get_Month() { return Month; }
   int get_Year() { return Year; }
   bool get_statChosen() { return Chosen; }
   contacts& operator=(const contacts& cont) {
      if (this == &cont)
         return *this;
      Surname = cont.Surname;
      Name = cont.Name;
      Middle_name = cont.Middle_name;
      Day = cont.Day;
      Month = cont.Month;
      Year = cont.Year;
      Phone = cont.Phone;
      Chosen = cont.Chosen;
      return *this;
   }
   bool operator==(const contacts& cont) {
      if (Surname == cont.Surname && Name == cont.Name && Middle_name == cont.Middle_name)
         return true;
      else
         return false;
   }
   bool operator!=(const contacts& cont) {
      if (Surname != cont.Surname || Name != cont.Name || Middle_name != cont.Middle_name)
         return true;
      else
         return false;
   }
   bool operator<(const contacts& cont) {
      if (Surname < cont.Surname)
         return true;
      else
         if (Surname > cont.Surname)
            return false;
         else
            if (Name < cont.Name)
               return true;
            else
               if (Name > cont.Name)
                  return false;
               else
                  if (Middle_name < cont.Middle_name)
                     return true;
                  else
                     return false;
   }

   void print_contact()
   {
      cout << "ФИО: " << Surname << " " << Name << " " << Middle_name << endl;
      cout << "Номер телефон: " << Phone << endl;
      cout << "Дата рождения: " << Day << "." << Month << "." << Year << endl;
      if (Chosen == true)
         cout << "Контакт находится в избранных" << "\n" << endl;
      else
         cout << "Контакт не находится в избранных" << "\n" << endl;
   }

private:

   string Surname;
   string Name;
   string Middle_name;
   string Phone;
   int Day;
   int Month;
   int Year;
   bool Chosen;

};

class retention
{
public:

   retention() {}
   size_t get_count() { return Contacts.size(); }
   bool exists(contacts& cont){
      bool exist = false;
      for (int i = 0; i < get_count(); i++)
      {
         if (cont == Contacts[i])
         {
            exist = true;
            break;
         }
      }
      return exist;
   }
   void creating_contact(contacts& cont){
      if (!exists(cont))
      {
         Contacts.push_back(cont);
         Sorting_contacts();
      }
   }
   void Sorting_contacts() {
      contacts cont;
      for (int i = 0; i < get_count() - 1; ++i)
      {
         for (int j = 0; j < get_count() - 1; ++j)
         {
            if (Contacts[j + 1] < Contacts[j])
            {
               cont = Contacts[j + 1];
               Contacts[j + 1] = Contacts[j];
               Contacts[j] = cont;
            }
         }
      }
   }
   void delete_contact(const int index) { Contacts.erase(Contacts.begin() + index); }
   void transformative_contact(string surname, string name, string middle_name, string phone, int day, int month, int year, int i){
      Contacts[i].set_Surname(surname);
      Contacts[i].set_Name(name);
      Contacts[i].set_Middle_name(middle_name);
      Contacts[i].set_Phone(phone);
      Contacts[i].set_Day(day);
      Contacts[i].set_Month(month);
      Contacts[i].set_Year(year);
      Sorting_contacts();
   }
   contacts search_name(string surname, string name, string middle_name){
      contacts tmp;
      for (int i = 0; i < Contacts.size(); i++)
         if (Contacts[i].get_Surname() == surname && Contacts[i].get_Name() == name && Contacts[i].get_Middle_name() == middle_name)
         {
            Contacts[i].print_contact();
            tmp = Contacts[i];
         }
      return tmp;
   }
   contacts search_phone(string phone) {
      contacts tmp;
      for (int i = 0; i < Contacts.size(); i++)
         if (Contacts[i].get_Phone() == phone)
         {
            Contacts[i].print_contact();
            tmp = Contacts[i];
         }
      return tmp;
   }
   vector <contacts> search_letter(char let) {
      vector <contacts> temp;
      for (int i = 0; i < Contacts.size(); i++)
         if (Contacts[i].get_Surname()[0] == let)
         {
            Contacts[i].print_contact();
            temp.push_back(Contacts[i]);
         }
      return temp;
   }
   void print_chosen() {
      for (int i = 0; i < Contacts.size(); i++)
         if (Contacts[i].get_statChosen())
            Contacts[i].print_contact();
   }
   void save_file(string path)
   {
      ofstream file;
      int i = 0;
      file.open(path);
      for (i = 0; i < Contacts.size(); i++)
      {
         file << Contacts[i].get_Surname() << " ";
         file << Contacts[i].get_Name() << " ";
         file << Contacts[i].get_Middle_name() << " ";
         file << Contacts[i].get_Day() << " ";
         file << Contacts[i].get_Month() << " ";
         file << Contacts[i].get_Year() << " ";
         file << Contacts[i].get_Phone() << " ";
         if (Contacts[i].get_statChosen())
            file << "1";
         else
            file << "0";
         file << endl;
      }
      file.close();
   }
   int reading_file(string path)
   {
      ifstream file;
      string surname, name, middle_name, phone;
      int day, month, year;
      bool chosen;
      contacts temp;
      file.open(path);
      if (!file.is_open())
      {
         return 0;
      }
      while (!file.eof())
      {
         file >> surname >> name >> middle_name >> day >> month >> year >> phone >> chosen;
         temp.set_Surname(surname);
         temp.set_Name(name);
         temp.set_Middle_name(middle_name);
         temp.set_Day(day);
         temp.set_Month(month);
         temp.set_Year(year);
         temp.set_Phone(phone);
         temp.set_Chosen(chosen);
         if (!exists(temp))
            Contacts.push_back(temp);
      }
      file.close();
      return 1;
   }
   contacts& operator[](int i) { return Contacts[i]; }
   ~retention() {}
private:

   vector <contacts> Contacts;

};


void main()
{
   setlocale(LC_ALL, "Russian");
   system("chcp 1251");
   SetConsoleTitle("Контакты");
   setwindow(170, 70);
   SMALL_RECT window;
   COORD buf;
   getwindow(&window, &buf);

   int variable_x;
   char ch;
   clrscr();
   variable_x = (window.Left + window.Right) / 30;
   textcolor(MAGENTA);
   gotoxy(variable_x + 45, wherey() + 5);
   cout << "Добро пожаловать в Контакты\n\n" << endl;
   gotoxy(variable_x + 25, wherey() + 1);
   cout << "Здесь вы сможете создавать, изменять контакты, производить поиск, а также \n\n" << endl;
   gotoxy(variable_x + 39, wherey());
   cout << "считывать их из файла и сохранять в файл\n\n" << endl;
   gotoxy(variable_x + 27, wherey());
   cout << "Для выхода из списка контактов нажмите на клавиатуре \"стрелку влево\"\n\n" << endl;
   gotoxy(variable_x + 37, wherey());
   system("pause");

   int day, month, year, flag = 0, ind, flag_1;
   string path, surname, name, middle_name, phone;
   size_t size;
   contacts cont;
   retention ret;
   char let;

   textcolor(MAGENTA);
   system("cls");
   while (1) {
      hidecursor();
      system("cls");
      for (int i = 0; i < SIZE; i++) {
         if (i == active_menu)
            textcolor(GREEN);
         else
            textcolor(YELLOW);
         cout << Menu[i] << "\n";
      }
      ch = _getch();
      if (ch == -32)
         ch = _getch();

      switch (ch)
      {
      case UP:
         if (active_menu > 0)
            active_menu--;
         break;
      case DOWN:
         if (active_menu < SIZE - 1)
            active_menu++;
         break;
      case ENTER:
         system("cls");
         switch (active_menu)
         {
         case Contact_list:
            flag = 1;
            while (flag) {
               system("cls");
               size = ret.get_count();
               if (size > 0) {
                  for (int i = 0; i < size; i++) {
                     if (i == active_menu_2)
                        textcolor(GREEN);
                     else
                        textcolor(YELLOW);
                     cout << i + 1 << ")\n";
                     ret[i].print_contact();
                  }
                  ch = _getch();
                  if (ch == -32)
                     ch = _getch();

                  switch (ch)
                  {
                  case UP:
                     if (active_menu_2 > 0)
                        active_menu_2--;
                     break;
                  case DOWN:
                     if (active_menu_2 < size - 1)
                        active_menu_2++;
                     break;
                  case LEFT:
                     flag = 0;
                     break;
                  case ENTER:
                     ind = active_menu_2;
                     flag_1 = 1;
                     while (flag_1) {
                        system("cls");
                        for (int i = 0; i < SIZE_2; i++) {
                           if (i == active_menu_3)
                              textcolor(GREEN);
                           else
                              textcolor(YELLOW);
                           cout << Menu_2[i] << "\n";
                        }
                        ch = _getch();
                        if (ch == -32)
                           ch = _getch();

                        switch (ch)
                        {
                        case UP:
                           if (active_menu_3 > 0)
                              active_menu_3--;
                           break;
                        case DOWN:
                           if (active_menu_3 < SIZE_2 - 1)
                              active_menu_3++;
                           break;
                        case LEFT:
                           flag = 0;
                           break;
                        case ENTER:
                           switch (active_menu_3)
                           {
                           case Change_selected_contact:
                              cout << "Введите ФИО контакта:" << endl;
                              cin >> surname;
                              cin >> name;
                              cin >> middle_name;
                              cout << "Введите номер телефона в формате +79999999999" << endl;
                              cin >> phone;
                              cout << "Введите дату рождения(день, месяц, год) через пробел:" << endl;
                              cin >> day;
                              cin >> month;
                              cin >> year;
                              ret.transformative_contact(surname, name, middle_name, phone, day, month, year, ind);
                              break;

                           case Add_contact_favorites_list:
                              ret[ind].set_tChosen();
                              break;

                           case Delete_contact_favorites_list:
                              ret[ind].set_fChosen();
                              break;

                           case Delete_contact:
                              ret.delete_contact(ind);
                              break;

                           case EXIT_2:
                              flag = 0;
                              break;

                           }
                           flag_1 = 0;
                        }
                     }
                     break;
                  }
               }
               else
               {
                  textcolor(RED);
                  gotoxy(variable_x + 45, wherey() + 7);
                  cout << "Список контактов пуст" << endl;
                  gotoxy(variable_x + 37, wherey() + 1);
                  system("pause");
                  textcolor(MAGENTA);
                  flag = 0;
               }
            }
            break;


         case Create_new_contact:
            cout << "Введите ФИО контакта:" << endl;
            cin >> surname;
            cin >> name;
            cin >> middle_name;
            cout << "Введите номер телефона в формате +79999999999" << endl;
            cin >> phone;
            cout << "Введите дату рождения(день, месяц, год) через пробел:" << endl;
            cin >> day;
            cin >> month;
            cin >> year;
            cont.set_Surname(surname);
            cont.set_Name(name);
            cont.set_Middle_name(middle_name);
            cont.set_Phone(phone);
            cont.set_Day(day);
            cont.set_Month(month);
            cont.set_Year(year);
            if (ret.exists(cont))
            {
               textcolor(RED);
               system("cls");
               gotoxy(variable_x + 40, wherey() + 7);
               cout << "Этот человек уже есть в ваших контактах" << endl;
               gotoxy(variable_x + 38, wherey() + 1);
               system("pause");
               textcolor(MAGENTA);
               break;
            }
            ret.creating_contact(cont);
            break;

         case Find_contact_FIO:
            cout << "Введите ФИО контакта:" << endl;
            cin >> surname;
            cin >> name;
            cin >> middle_name;
            system("cls");
            ret.search_name(surname, name, middle_name);
            system("pause");
            break;

         case Set_number_segments:
            cout << "Введите номер телефона в формате +79999999999" << endl;
            cin >> phone;
            system("cls");
            ret.search_phone(phone);
            system("pause");
            break;

         case All_contacts_letter:
            cout << "Введите букву для поиска контактов" << endl;
            cin >> let;
            system("cls");
            ret.search_letter(let);
            system("pause");
            break;

         case Number_contacts:
            cout << "Текущее число контактов: " << ret.get_count() << endl;
            system("pause");
            break;
         case Selected_сontacts:
            ret.print_chosen();
            system("pause");
            break;

         case Save_contacts_file:
            cout << "Введите путь к файлу(d:/Contacts.txt/): ";
            cin >> path;
            ret.save_file(path);
            cout << "Сохранение завершено\n";
            system("pause");
            break;

         case Read_contacts_file:
            cout << "Введите путь к файлу(d:/Contacts.txt/): ";
            cin >> path;
            ret.reading_file(path);
            cout << "Считывание завершено\n";
            system("pause");
            break;

         case EXIT:
            exit(0);
            break;

         }
      }
   }
}