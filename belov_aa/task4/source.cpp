#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <clocale>
#include <ios>
#include <iomanip>

using namespace std;

struct Date
{
    int day;
    int month;
    int year;
    friend ostream& operator<<(ostream& os, const Date& date)
    {
        char prev_fill = os.fill('0');

        os << setw(2) << date.day << "/";
        os << setw(2) << date.month << "/";
        os << date.year;

        os.fill(prev_fill);

        return os;
    }
};

class Contact
{
private:
    string first_name;
    string last_name;
    string middle_name;
    string phone_number;
    Date birthday;
    bool is_favorite;

public:
    Contact(string last_name, string first_name, string middle_name,
        string phone_number, Date birthday, bool is_favorite)
        : first_name(first_name)
        , last_name(last_name)
        , middle_name(middle_name)
        , phone_number(phone_number)
        , birthday(birthday)
        , is_favorite(is_favorite) {}

    Contact() : Contact("", "", "", "", { 1, 1, 1901 }, false) {}

    friend ostream& operator<<(ostream& os, const Contact& a)
    {
        os << a.last_name << ' ' << a.first_name << ' ' << a.middle_name << ' ' << a.phone_number << ' ' << a.birthday << ' ' << a.is_favorite;
        return os;
    }

    bool operator<(const Contact& other)
    {
        if (*this == other)
        {
            return false;
        }
        if (this->is_favorite != other.is_favorite)
        {
            return this->is_favorite;
        }
        if (this->last_name != other.last_name)
        {
            return this->last_name < other.last_name;
        }
        if (this->first_name != other.first_name)
        {
            return this->first_name < other.first_name;
        }
        return this->middle_name < other.middle_name;
    }

    bool operator>(const Contact& other)
    {
        return (*this != other) && !(*this < other);
    }

    bool operator==(const Contact& other)
    {
        return (this->first_name == other.first_name)
            && (this->last_name == other.last_name)
            && (this->middle_name == other.middle_name);
    }

    bool operator!=(const Contact& other)
    {
        return !(*this == other);
    }

    bool operator<=(const Contact& other)
    {
        return (*this == other) || (*this < other);
    }

    bool operator>=(const Contact& other)
    {
        return (*this == other) || (*this > other);
    }

    string get_last_name() const
    {
        return last_name;
    }

    void set_last_name(string last_name)
    {
        this->last_name = last_name;
    }

    string get_first_name() const
    {
        return first_name;
    }

    void set_first_name(string first_name)
    {
        this->first_name = first_name;
    }

    string get_middle_name() const
    {
        return middle_name;
    }

    void set_middle_name(string middle_name)
    {
        this->middle_name = middle_name;
    }

    string get_full_name() const
    {
        return last_name + " " + first_name + " " + middle_name;
    }

    string get_phone_number() const
    {
        return phone_number;
    }

    void set_phone_number(string phone_number)
    {
        this->phone_number = phone_number;
    }

    Date get_birthday() const
    {
        return birthday;
    }

    void set_birthday(Date birthday)
    {
        this->birthday = birthday;
    }

    bool get_favorite() const
    {
        return is_favorite;
    }

    void set_favorite(bool is_favorite)
    {
        this->is_favorite = is_favorite;
    }
};

class Contacts
{
private:
    vector<Contact> contacts;

public:
    Contacts() {}

    friend ofstream& operator<<(ofstream& os, const Contacts& c)
    {
        for (Contact contact : c.contacts)
            os << contact.get_full_name() << " "
            << contact.get_phone_number() << " " << contact.get_birthday().day << "/" << contact.get_birthday().month << "/" << contact.get_birthday().year << ";"
            << " " << contact.get_favorite() << endl;
        return os;
    }

    friend ostream& operator<<(ostream& os, const Contacts& c)
    {
        os << left;

        os << setw(10) << " ";
        os << setw(32) << "ФИО:";
        os << setw(16) << "Телефон:";
        os << setw(17) << "Дата рождения:";
        os << setw(10) << "Избранный?" << endl;

        for (Contact contact : c.contacts)
        {
            os << setw(40) << contact.get_full_name();
            os << setw(20) << contact.get_phone_number();

            os << right;

            os << contact.get_birthday();
            os << setw(10) << (contact.get_favorite() ? "+" : "-") << endl;

            os << left;

        }
        return os;
    }

    friend ifstream& operator>>(ifstream& in, Contacts& c)
    {
        string line;

        while (getline(in, line))
        {
            vector<string> tokens;
            string token;

            for (char c : line)
            {
                if ((c == ' ') || (c == '.') || (c == '/'))
                {
                    tokens.push_back(token);
                    token.clear();
                }
                else
                {
                    token += c;
                }
            }

            tokens.push_back(token);

            if (tokens.size() == 8)
            {
                int day = stoi(tokens[4]);
                int month = stoi(tokens[5]);
                int year = stoi(tokens[6]);
                Date birthday{ day, month, year };

                bool is_favorite = stoi(tokens[7]);

                Contact contact(tokens[0], tokens[1], tokens[2], tokens[3], birthday, is_favorite);
                c.add_contact(contact);
            }
        }

        return in;
    }

    // Cоздать новый контакт
    void add_contact(Contact contact)
    {
        contacts.push_back(contact);
        sort(contacts.begin(), contacts.end());
    }

    // Изменить выбранный контакт
    void edit_contact(int index, Contact contact)
    {
        contacts[index] = contact;
        sort(contacts.begin(), contacts.end());
    }

    // Найти контакт по ФИО
    Contact* find_contact_by_name(string last_name, string first_name, string middle_name)
    {
        for (Contact& contact : contacts)
        {
            if ((contact.get_last_name() == last_name) && (contact.get_first_name() == first_name) && (contact.get_middle_name() == middle_name))
            {
                return &contact;
            }
        }
        return nullptr;
    }

    // Найти контакт по телефону
    Contact* find_contact_by_phone(string phone)
    {
        for (Contact& contact : contacts)
        {
            if (contact.get_phone_number() == phone)
            {
                return &contact;
            }
        }
        return nullptr;
    }

    // Выдать все контакты на заданную букву
    vector<Contact*> get_contacts_starting_with(char letter)
    {
        vector<Contact*> result;
        for (Contact& contact : contacts)
        {
            if (contact.get_last_name()[0] == letter || contact.get_first_name()[0] == letter || contact.get_middle_name()[0] == letter)
            {
                result.push_back(&contact);
            }
        }
        return result;
    }

    // Узнать текущее число контактов
    size_t get_number_of_contacts()
    {
        return contacts.size();
    }

    // Внести контакт в список избранных
    void add_contact_to_favorites(int index)
    {
        contacts[index].set_favorite(true);
    }

    // Удалить контакт из списка избранных
    void remove_contact_from_favorites(int index)
    {
        contacts[index].set_favorite(false);
    }

    // Выдать все избранные контакты
    vector<Contact*> favorite_contacts()
    {
        vector<Contact*> result;
        for (Contact& contact : contacts)
        {
            if (contact.get_favorite())
            {
                result.push_back(&contact);
            }
        }
        return result;
    }

    // Удалить контакт
    void delete_contact(string phone_number)
    {
        for (size_t i = 0; i < contacts.size(); i++)
        {
            if (contacts[i].get_phone_number() == phone_number)
            {
                contacts.erase(contacts.begin() + i);
            }
        }
    }
};

int main()
{
    setlocale(LC_ALL, "RU");

    // Сохранить контакты в файл
    ofstream out("outfile.txt");

    Contacts list;

    Contact c1("Коновалов", "Даниил", "Дмитриевич", "+79527475893", { 10, 12, 1997 }, 1);
    Contact c2("Яковлев", "Алексей", "Кириллович", "+79995751845", { 14, 10, 2002 }, 0);
    Contact c3("Попов", "Кирилл", "Владимирович", "+79050297351", { 9, 4, 1982 }, 0);
    Contact c4("Белов", "Артём", "Алексеевич", "+79961234567", { 6, 7, 2004 }, 1);

    list.add_contact(c1);
    list.add_contact(c2);
    list.add_contact(c3);
    list.add_contact(c4);

    out << list;
    out.close();

    cout << *list.find_contact_by_name("Коновалов", "Даниил", "Дмитриевич") << endl;
    system("PAUSE");
    system("cls");

    cout << *list.find_contact_by_phone("+79995751845") << endl;
    system("PAUSE");
    system("cls");

    for (Contact* contact : list.favorite_contacts())
        cout << *contact << endl;
    system("PAUSE");
    system("cls");

    for (Contact* contact : list.get_contacts_starting_with('К'))
        cout << *contact << endl;
    system("PAUSE");
    system("cls");

    cout << list << endl;

    // Считать контакты из файла

    ifstream file("data.txt");
    if (!file.is_open())
    {
        cerr << "Unable to open file" << endl;
        return EXIT_FAILURE;
    }

    Contacts book;

    file >> book;
    cout << book;
    file.close();

    system("PAUSE");


}