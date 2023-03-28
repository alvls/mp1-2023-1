#include "dictionary.h"
#include "additional.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    std::cout << "Let's create an instance of the class \"Dictionary\"" << std::endl;
    Dictionary dict{};
    std::cout << R"(Now let's add some words)" << std::endl;
       
    dict.AddWord("array", "массив");
    dict.AddWord("function", "функция");
    dict.AddWord("string", "строка");
    dict.AddWord("bug", "жук");
    dict.AddWord("variable", "переменная");
    dict.AddWord("компилятор", "compiler"); // we can add words in any order

    std::cout << "Check if the word \"bug\" is in the dictionary: ";
    if (dict.Contains("bug")) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Let's find a translation of this word: ";
    std::cout << dict.Translation("bug") << std::endl;
    std::cout << "Something is wrong here... Let's change the translation" << std::endl;
    dict.ChangeTranslation("bug", "ошибка");

    std::cout << "Count of words in the dictionary now: " << dict.GetWordsCount() << std::endl;

    std::string path;
    std::cout << "\nLet's write the changes to the file" << std::endl;
    std::cout << "Enter the path to save the dictionary: ";
    std::getline(std::cin, path);

    dict.WriteToFile(path);

    system("pause");
    return EXIT_SUCCESS;
}