#include <iostream>
#include <vector>

class BustingPatterns {
public:
    // Находим всевозможные паттерны, которые можно было получить подстановкой символов алфавита на
    // места со знаками подстановки
    static std::vector<std::string> bust(std::string pattern_with_symbol, std::vector<int> positions,
                                         std::vector<std::string> alphabet) {
        std::vector<std::string> results;
        std::vector<int> indices(positions.size(), 0);

        while (true) {
            std::string new_pattern = pattern_with_symbol;
            for (int i = 0; i < positions.size(); i++) {
                int pos = positions[i];
                int idx = indices[i] % alphabet.size();
                new_pattern[pos] = alphabet[idx][0];
            }
            results.push_back(new_pattern);

            bool done = false;
            for (int i = positions.size() - 1; i >= 0; i--) {
                if (indices[i] == alphabet.size() - 1) {
                    indices[i] = 0;
                } else {
                    indices[i]++;
                    done = true;
                    break;
                }
            }
            if (!done) {
                break;
            }
        }
        return results;
    }
};