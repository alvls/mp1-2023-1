#include <iostream>
#include <fstream>
#include <clocale>

#include "film_library.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    
//Ниже продеймонстрированы различные способы создания объекта//
    film_library library("films.txt");

    film_library library2;

    ifstream file;
    file.open("films.txt");

    file >> library2;

    file.close();

    film_library library3 = library + library2;
    library3 += library;

    library.get_film("Терминатор", 1992)->year = 2000; //Пример использования метода поиска фильма
    library.get_film("Терминатор", 2000)->year = 1992;//C последующим изменением компонентов найденого фильма

    library.add_film("Пример фильма", "Кто-то", "Кто-то ещё", "Никто", 12, 10, 1932, 1000);
    cout << library << endl << endl;

    library.save_to_file("films.txt");

    library.delete_film(library[library.get_film_index("Пример фильма", 1932)]);
    cout << library << endl;

    library.save_to_file("films.txt");
	
    return EXIT_SUCCESS;
}
