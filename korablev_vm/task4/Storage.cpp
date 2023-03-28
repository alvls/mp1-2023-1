//класс, отвечающий за хранение контактов
#include "header.h"


size_t Storage::get_contacts_count() { return contacts.size(); }

void Storage::delete_storage() { contacts.clear(); }

Contacts& Storage::operator[](int i) { return contacts[i]; }

void Storage::delete_contact(const int ind) { contacts.erase(contacts.begin() + ind); }

void Storage::print_favourite_contacts()
{
    for (int i = 0; i < contacts.size(); i++)
        if (contacts[i].favourite_contact())
            contacts[i].print_contact();
}

size_t Storage::get_index(Contacts& contact)
{
    int i = 0;
    for (i = 0; i < contacts.size(); i++)
        if (contact.get_phone() == contacts[i].get_phone())
            return i;
}

void Storage::print_storage()
{
    int i = 0;
    for (i = 0; i < contacts.size(); i++)
    {
        contacts[i].print_contact();
        cout << endl;
    }
}

void Storage::create_contact(Contacts& contact)
{
    bool new_c = true;
    for (int i = 0; i < get_contacts_count(); i++)
    {
        if (contact == contacts[i])
        {
            new_c = false;
            break;
        }
    }
    if (new_c = true)
    {
        contacts.push_back(contact);
        sort_contacts();
    }
}

void Storage::change_contact(string _name, string _surname, string _patronymic, string _phone, int _day, int _month, int _year, bool _favourite, int i)
{
    contacts[i].set_name(_name);
    contacts[i].set_surname(_surname);
    contacts[i].set_patronymic(_patronymic);
    contacts[i].set_phone(_phone);
    contacts[i].set_day(_day);
    contacts[i].set_month(_month);
    contacts[i].set_year(_year);
    contacts[i].set_favourite(_favourite);
    sort_contacts();
}

void Storage::sort_contacts()
{
    Contacts tmp;
    size_t size = get_contacts_count();
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if (contacts[j + 1] < contacts[j])
            {
                tmp = contacts[j + 1];
                contacts[j + 1] = contacts[j];
                contacts[j] = tmp;
            }
        }
    }
}

Contacts Storage::contacts_by_name(string _name, string _surname, string _patronymic)
{
    int i = 0;
    bool check = false;
    Contacts Empty;
    for (i = 0; i < contacts.size(); i++)
        if (contacts[i].get_name() == _name && contacts[i].get_surname() == _surname && contacts[i].get_patronymic() == _patronymic)
        {
            check = true;
            contacts[i].print_contact();
            return contacts[i];
        }
    if (!check)
    {
        cout << "ѕо вашему запросу ничего не найдено!" << endl;
        return Empty;
    }
}

Contacts Storage::contacts_by_phone(string _phone)
{
    int i = 0;
    bool indicator = false;
    Contacts Empty;
    for (i = 0; i < contacts.size(); i++)
        if (contacts[i].get_phone() == _phone)
        {
            indicator = 1;
            contacts[i].print_contact();
            return contacts[i];
        }
    if (!indicator)
    {
        cout << "ѕо вашему запросу ничего не найдено!" << endl;
        return Empty;
    }
}

vector <Contacts> Storage::contacts_by_letter(char _letter)
{
    int i = 0;
    bool indicator = false;
    vector <Contacts> temp_list;
    for (i = 0; i < contacts.size(); i++)
        if (contacts[i].get_surname()[0] == _letter)
        {
            contacts[i].print_contact_lite();
            temp_list.push_back(contacts[i]);
        }
    if (temp_list.size())
        indicator = 1;
    return temp_list;
}

int Storage::load_file(string way)
{
    ifstream in;
    string name, surname, patronymic, phone;
    int day, month, year;
    bool favourite;
    Contacts temp_contact;
    in.open(way);
    if (!in.is_open())
    {
        cout << "ѕо вашему запросу ничего не найдено!" << endl;
        system("pause");
        return 0;
    }
    while (!in.eof())
    {
        in >> surname >> name >> patronymic >> day >> month >> year >> phone >> favourite;
        temp_contact.set_name(name);
        temp_contact.set_surname(surname);
        temp_contact.set_patronymic(patronymic);
        temp_contact.set_day(day);
        temp_contact.set_month(month);
        temp_contact.set_year(year);
        temp_contact.set_phone(phone);
        temp_contact.set_favourite(favourite);
        contacts.push_back(temp_contact);
    }
    contacts.pop_back();
    in.close();
    return 1;
}

void Storage::save_file(string way)
{
    ofstream fileout;
    int i = 0;
    fileout.open(way);
    for (i = 0; i < contacts.size(); i++)
    {
        fileout << contacts[i].get_surname() << " ";
        fileout << contacts[i].get_name() << " ";
        fileout << contacts[i].get_patronymic() << " ";
        fileout << contacts[i].get_day() << " ";
        fileout << contacts[i].get_month() << " ";
        fileout << contacts[i].get_year() << " ";
        fileout << contacts[i].get_phone() << " ";
        if (contacts[i].favourite_contact())
            fileout << "1";
        else
            fileout << "0";
        fileout << endl;
    }
    fileout.close();
}
