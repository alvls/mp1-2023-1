#pragma once

#include "additional.h"

// An order of storage and writing to a file: eng -> rus
class Dictionary {
private:
    std::string eng[MAX_WORDS_COUNT];
    std::string rus[MAX_WORDS_COUNT];
    int wordsCount{0};
public:
    Dictionary() = default;

    explicit Dictionary(const std::string& filePath) {
        wordsCount = ReadFromFile(filePath);
    }

    [[nodiscard]] int GetWordsCount() const {
        return wordsCount;
    }

    int ReadFromFile(const std::string& filePath) {
        std::ifstream ifs(filePath, std::ios::in);
        if (!ifs.is_open()) {
            throw std::runtime_error("File not found!");
        }
        std::string line;
        int counter = 0;
        while (!ifs.eof()) {
            if (counter == MAX_WORDS_COUNT) {
                throw std::runtime_error("The dictionary buffer is full!");
            }
            std::getline(ifs, line);
            std::stringstream ss(line);
            ss >> eng[counter];
            ss >> rus[counter];
            counter++;
        }
        return counter;
    }

    void WriteToFile(const std::string& filePath) {
        std::ofstream ofs(filePath, std::ios::out);
        for (int counter = 0; counter < wordsCount; counter++) {
            if (counter != wordsCount - 1) {
                ofs << eng[counter] << " " << rus[counter] << std::endl;
            } else {
                ofs << eng[counter] << " " << rus[counter];
            }
        }
    }

    void AddWord(const std::string& wordOriginal, const std::string& wordTranslation) {
        if (wordsCount >= MAX_WORDS_COUNT) {
            throw std::runtime_error("The dictionary buffer is full!");
        }
        if (isLatinSymbol(wordOriginal[0])) {
            eng[wordsCount] = wordOriginal;
            rus[wordsCount] = wordTranslation;
        } else {
            rus[wordsCount] = wordOriginal;
            eng[wordsCount] = wordTranslation;
        }
        wordsCount++;
    }

    std::string Translation(const std::string& word) {
        int index;
        if (isLatinSymbol(word[0])) {
            for (index = 0; index < wordsCount; index++) {
                if (word == eng[index]) {
                    return rus[index];
                }
            }
        } else {
            for (index = 0; index < wordsCount; index++) {
                if (word == rus[index]) {
                    return eng[index];
                }
            }
        }
        throw std::runtime_error("The specified word is not in the dictionary!");
    }

    void ChangeTranslation(const std::string& wordOriginal, const std::string& wordTranslation) {
        int index;
        if (isLatinSymbol(wordOriginal[0])) {
            for (index = 0; index < wordsCount; index++) {
                if (wordOriginal == eng[index]) {
                    rus[index] = wordTranslation;
                }
            }
        } else {
            for (index = 0; index < wordsCount; index++) {
                if (wordOriginal == rus[index]) {
                    eng[index] = wordTranslation;
                }
            }
        }
    }

    bool Contains(const std::string& word) {
        int index;
        if (isLatinSymbol(word[0])) {
            for (index = 0; index < wordsCount; index++) {
                if (eng[index] == word) {
                    return true;
                }
            }
            return false;
        } else {
            for (index = 0; index < wordsCount; index++) {
                if (rus[index] == word) {
                    return true;
                }
            }
            return false;
        }
    }

    ~Dictionary() = default;
};