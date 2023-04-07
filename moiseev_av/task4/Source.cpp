#include <iostream>
#include <fstream>
#include <clocale>

#include "film_library.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    
//���� ������������������� ��������� ������� �������� �������//
    film_library library("films.txt");

    film_library library2;

    ifstream file;
    file.open("films.txt");

    file >> library2;

    file.close();

    film_library library3 = library + library2;
    library3 += library;

    library.get_film("����������", 1992)->year = 2000; //������ ������������� ������ ������ ������
    library.get_film("����������", 2000)->year = 1992;//C ����������� ���������� ����������� ��������� ������

    library.add_film("������ ������", "���-��", "���-�� ���", "�����", 12, 10, 1932, 1000);
    cout << library << endl << endl;

    library.save_to_file("films.txt");

    library.delete_film(library[library.get_film_index("������ ������", 1932)]);
    cout << library << endl;

    library.save_to_file("films.txt");
	
    return EXIT_SUCCESS;
}
