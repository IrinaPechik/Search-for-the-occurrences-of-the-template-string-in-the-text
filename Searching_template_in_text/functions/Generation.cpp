#include <vector>
#include <string>
#include "../architecture/Pattern.cpp"

class Generation {
public:
    static std::string generate(int flag, std::vector<std::vector<Pattern>>& pattern, std::string& text) {
        if (flag == 0) {
            // Генерируем бин. алфавит, 10 тыс. символов.
            text = generateText(2, 10000);
            // Генерируем паттерн без символа подстановки.
            pattern[0] = generatePattern(0, text);
            // Генерируем паттерн с символом подстановки.
            pattern[4] = generatePattern(1, text);
        } else if (flag == 1) {
            // Генерируем бин. алфавит, 100 тыс. символов.
            text = generateText(2, 100000);
            // Генерируем паттерн без символа подстановки.
            pattern[1] = generatePattern(0, text);
            // Генерируем паттерн с символом подстановки.
            pattern[5] = generatePattern(1, text);;
        } else if (flag == 2) {
            // Генерируем 4-символьный. алфавит, 10 тыс. символов.
            text = generateText(4, 10000);
            // Генерируем паттерн без символа подстановки.
            pattern[2] = generatePattern(0, text);
            // Генерируем паттерн с символом подстановки.
            pattern[6] =generatePattern(1, text) ;
        } else if (flag == 3) {
            // Генерируем 4-символьный. алфавит, 100 тыс. символов.
            text = generateText(4, 100000);
            // Генерируем паттерн без символа подстановки.
            pattern[3] = generatePattern(0, text);
            // Генерируем паттерн с символом подстановки.
            pattern[7] = generatePattern(1, text);
        }
        return text;
    }

private:
    static std::string generateText(int alphabet, int count_of_symbols) {
        std::string result(count_of_symbols, ' ');
        if (alphabet == 2) {
            for (int i = 0; i < count_of_symbols; ++i) {
                result[i] = (rand() % 2 == 0) ? '0' : '1';
            }
        } else {
            for (int i = 0; i < count_of_symbols; ++i) {
                result[i] = "ABCD"[rand() % 4];
            }
        }
        return result;
    }

    /*
     * Генерирует паттерн из текущего текста.
     * flag - нужен ли символ подстановки.
     */
    static std::vector<Pattern> generatePattern(int flag, std::string& text) {
        // Будем генерировать 29 паттернов длины от 100 до 3000 с шагом 100.
        std::vector<Pattern> patterns(30);

        // Генерируем позицию первого символа из всей подстроки так,
        // чтобы до конца строки было минимум 3000 символа.
        int startPos = rand() % (text.size() - 3000);

        // Теперь нам последовательно нужно обрезать подстроки
        // от 100 до 3000 символов с шагом 100.
        int length = 100;
        for (int i = 0; i < 30; ++i) {
            std::string s = text.substr(startPos, length);
            patterns[i] = Pattern(s);
            length += 100;
        }
        // Смотрим, нужен ли символ подстановки.
        if (flag == 0) {
            return patterns;
        } else {
            // Генерируем количество знаков подстановки в диапазоне [1, 4].
            int count_of_wildcard_character = rand() % 4 + 1;
            // Теперь генерируем номер паттерна для текущего текста, на котором будет символ подстановки в паттерне.
            for (int i = 0; i < count_of_wildcard_character; ++i) {
                int position = rand() % 30;
                // И уже теперь генерируем позицию в строке, где будет символ подстановки
                int position_in_str = rand() % (patterns[position].getLength());
                patterns[position].setValue(position_in_str, '?');
                patterns[position].setPositions(position_in_str);
            }
            return patterns;
        }
    }
};

