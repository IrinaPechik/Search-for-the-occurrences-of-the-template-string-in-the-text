#include <iostream>
#include <fstream>
#include <chrono>
#include "algorithms/CharByCharAlgorithm.cpp"
#include "algorithms/KMP.cpp"
#include "algorithms/KMPRefinedFaces.cpp"
#include "algorithms/RabinKarp.cpp"
#include "functions/Generation.cpp"
#include "functions/BustingPatterns.cpp"
/* АиСД-2, 2023, КДЗ№2;
 * Печик Ирина Юрьевна, БПИ-217;
 * Среда разработки - Clion; Отчёт писался в google collab.
 * Сделано всё.
 * В папке "files" находятся .csv файлы, в которых содержатся полученные замеры данных.
 */
int main() {
    srand(time(nullptr));
    std::string algorithms_names[4]{"CharByCharAlgorithm", "KMP", "KMPRefinedFaces", "RabinKarp"};
    // Названия файлов.
    std::string file_names[8] {"../files/short_bin_text.csv", "../files/long_bin_text.csv",
                               "../files/short_4_text.csv", "../files/long_4_text.csv",
                               "../files/short_bin_text_with_symbol.csv", "../files/long_bin_text_with_symbol.csv",
                               "../files/short_4_text_with_symbol.csv", "../files/long_4_text_with_symbol.csv"};
    // Объявляем тип указателя на функцию псевдонимом.
    // Сначала принимаем текст, а потом паттерн.
    // Возвращаем индекс последней позиции строки, которая входила в шаблон.
    typedef int (*findPatternFunctions)(std::string text, std::string pattern);

    findPatternFunctions all_functions[4]{CharByCharAlgorithm::findPattern, KMP::findPattern,
                                          KMPRefinedFaces::findPattern, RabinKarp::findPattern};
/*  Текст для поиска шаблона.
    0 - бин. алфавит, 10 тыс. символов.
    1 - бин. алфавит, 100 тыс. символов.
    2 - 4-символьный. алфавит, 10 тыс. символов.
    3 - 4-символьный. алфавит, 100 тыс. символов.*/
    std::vector<std::string> texts(4);

/*  Шаблон.
    0 - паттерн для texts[0] без символа подстановки.
    1 - паттерн для texts[1] без символа подстановки.
    2 - паттерн для texts[2] без символа подстановки.
    3 - паттерн для texts[3] без символа подстановки.
    4 - паттерн для texts[0] с символом подстановки.
    5 - паттерн для texts[1] с символом подстановки.
    6 - паттерн для texts[2] с символом подстановки.
    7 - паттерн для texts[3] с символом подстановки.

    В каждом индексе шаблона лежат 29 шаблонов.*/

    // Генерируем все тестовые данные.
    // Тут я должна понимать на каких позициях есть знаки подстановки.
    std::vector<std::vector<Pattern>> pattern(8);
    for (int i = 0; i < 4; ++i) {
        Generation::generate(i, pattern, texts[i]);
    }

    // Результат замера в наносекундах.
    long long nanoseconds;
    // Создаём поток вывода в файл.
    std::ofstream my_file;

    // Для каждого файла выводим замеры в него.
    for (int file_counter = 0; file_counter < 8; ++file_counter) {
        // Устанавливаем алфавит.
        std::vector<std::string> alphabet;
        if (file_counter == 0 || file_counter == 1 || file_counter == 4 || file_counter == 5) {
            alphabet = {"0", "1"};
        } else {
            alphabet = {"A", "B", "C", "D"};
        }

        // Открываем очередной файл.
        my_file.open(file_names[file_counter]);

        // Делаем шапку для таблицы текущего файла.
        my_file << "size of pattern" << ',';
        // Названия алгоритмов.
        for (const auto& algorithm_name : algorithms_names) {
            my_file << algorithm_name << ',';
        }
        // Заканчиваем делать шапку.
        my_file << std::endl;

        int pattern_length = 0;
        // Проходимся по всем 30 паттернам для текущего текста.
        for (auto el : pattern[file_counter]) {
            pattern_length += 100;
            my_file << pattern_length << ',';

            // Если были знаки подстановки.
            if (!el.getPositions().empty()) {
                // Находим позиции, на которых стоят символы '?'.
                std::vector<int> positions;
                for (auto j : el.getPositions()) {
                    positions.push_back(j);
                }
                std::vector<std::string> patterns = BustingPatterns::bust(el.getPattern(), positions, alphabet);
                // Вызываем метод для каждого паттерна. Ищем сумму. Она и будет количеством всех паттернов.
                int sum = 0;
                for (int sort_type = 0; sort_type < 4; ++sort_type) {
                    // Начинаем замер времени.
                    auto start = std::chrono::high_resolution_clock::now();
                    for (auto& p : patterns) {
                        if (all_functions[sort_type](texts[file_counter % 4], p) != -1) {
                            sum++;
                        }
                    }
                    // Заканчиваем замер времени.
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
                    my_file << nanoseconds << ',';
                }
                my_file << std::endl;
            } else {
                // Вызываем простой поиск по паттерну всех алгоритмов.
                for (int sort_type = 0; sort_type < 4; ++sort_type) {
                    // Начинаем замер времени.
                    auto start = std::chrono::high_resolution_clock::now();
                    all_functions[sort_type](texts[file_counter % 4], el.getPattern());
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
                    my_file << nanoseconds << ',';
                }
                my_file << std::endl;
            }
        }
        my_file.close();
    }
    return 0;
}