#pragma once
#include <windows.h>
#include <iostream>
#include <locale>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
using namespace std;
enum TColor {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};
COORD wherexy(void);
void clrscr(void);
void gotoxy(int x, int y);
void textcolor(int color);
void hidecursor(void);

class Contacts
{
    string name;
    string surname;
    string patronymic;
    string phone;
    int day;
    int month;
    int year;
    bool favourite;
public: 
    Contacts();
    Contacts(string _name, string _surname, string _patronymic, string _phone, int _day, int _month, int _year, bool _favourite);
    string get_name();
    string get_surname();
    string get_patronymic();
    string get_phone();
    int get_day();
    int get_month();
    int get_year();
    bool favourite_contact();
    void set_name(string _name);
    void set_surname(string _surname);
    void set_patronymic(string _patronymic);
    void set_phone(string _phone);
    void set_day(int _day);
    void set_month(int _month);
    void set_year(int _year);
    void set_favourite_true();
    void set_favourite_false();
    void set_favourite(bool status);
    void print_contact();
    void print_contact_lite();
    Contacts& operator=(const Contacts& c);
    bool operator!=(const Contacts& c);
    bool operator==(const Contacts& c);
    bool operator<(const Contacts& c);
};

class Storage
{
    vector <Contacts> contacts;
public:
    Storage() {}
    Contacts contacts_by_name(string _name, string _surname, string _patronymic);
    Contacts contacts_by_phone(string _phone);
    vector <Contacts> contacts_by_letter(char _letter);
    Contacts& operator[](int i);
    size_t get_index(Contacts& c);
    size_t get_contacts_count();
    void sort_contacts();
    void create_contact(Contacts& c);
    void delete_storage();
    void delete_contact(const int index);
    void print_favourite_contacts();
    int load_file(string way);
    void save_file(string way);
    void print_storage();
    bool is_exist(Contacts& contact);
    void change_contact(string _name, string _surname, string _patronymic, string _phone, int day, int month, int year, bool favourite, int ind);
    ~Storage() {}
};
int menu_mode_clear(string* arr, int size);
int menu_mode_contact(string* arr, int size, Contacts& contact);
int menu_mode_list(Storage& list);
void exit_prog();
void hello();
void create_new_contact(Contacts& contact, Storage& list);
string get_way();