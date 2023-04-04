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

void Storage::print_storage()
{
    int i = 0;
    for (i = 0; i < contacts.size(); i++)
    {
        contacts[i].print_contact();
        cout << endl;
    }
}

bool Storage::is_exist(Contacts& contact)
{
    bool ex_c = false;
    for (int i = 0; i < get_contacts_count(); i++)
    {
        if (contact == contacts[i])
        {
            ex_c = true;
            break;
        }
    }
    return ex_c;
}

void Storage::create_contact(Contacts& contact)
{
    if (!is_exist(contact))
    {
        contacts.push_back(contact);
        sort_contacts();
    }
}

void Storage::change_contact(string _name, string _surname, string _patronymic, string _phone, int _day, int _month, int _year, bool _favourite, int i)
{
    Contacts temp;
    temp.set_name(_name);
    temp.set_surname(_surname);
    temp.set_patronymic(_patronymic);
    temp.set_phone(_phone);
    temp.set_day(_day);
    temp.set_month(_month);
    temp.set_year(_year);
    temp.set_favourite(_favourite);
    if (!is_exist(temp))
    {
        contacts[i]=temp;
        sort_contacts();
    }
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
    Contacts answer;
    for (i = 0; i < contacts.size(); i++)
        if (contacts[i].get_name() == _name && contacts[i].get_surname() == _surname && contacts[i].get_patronymic() == _patronymic)
        {
            contacts[i].print_contact();
            answer = contacts[i];
        }
    return answer;
}

Contacts Storage::contacts_by_phone(string _phone)
{
    int i = 0;
    Contacts answer;
    for (i = 0; i < contacts.size(); i++)
        if (contacts[i].get_phone() == _phone)
        {
            contacts[i].print_contact();
            answer = contacts[i];
        }
    return answer;
}

vector <Contacts> Storage::contacts_by_letter(char _letter)
{
    int i = 0;
    vector <Contacts> temp_list;
    for (i = 0; i < contacts.size(); i++)
        if (contacts[i].get_surname()[0] == _letter)
        {
            contacts[i].print_contact_lite();
            temp_list.push_back(contacts[i]);
        }
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
        if (!is_exist(temp_contact))
            contacts.push_back(temp_contact);
    }
    in.close();
    sort_contacts();
    return 1;
}

void Storage::save_file(string way)
{
    ofstream out;
    int i = 0;
    out.open(way);
    for (i = 0; i < contacts.size(); i++)
    {
        out << contacts[i].get_surname() << " ";
        out << contacts[i].get_name() << " ";
        out << contacts[i].get_patronymic() << " ";
        out << contacts[i].get_day() << " ";
        out << contacts[i].get_month() << " ";
        out << contacts[i].get_year() << " ";
        out << contacts[i].get_phone() << " ";
        if (contacts[i].favourite_contact())
            out << "1";
        else
            out << "0";
        out << endl;
    }
    out.close();
}
