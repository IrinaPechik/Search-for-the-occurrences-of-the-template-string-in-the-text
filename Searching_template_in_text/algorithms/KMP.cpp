#include <string>
#include <vector>

class KMP {
private:
    // Функция подсчёта массива наибольших граней.
    static std::vector<int> prefixFunc(const std::string &p) {
        // Длина подстроки.
        int m = static_cast<int>(p.length());
        // Массив граней.
        std::vector<int> br(m);
        // База. Грань строки длины 1 - 0.
        br[0] = 0;

        for (int i = 1; i < m; ++i) {
            int j = br[i - 1];
            while (j > 0 && p[j] != p[i]) {
                j = br[j - 1];
            }
            if (p[j] == p[i]) {
                j++;
            }
            br[i] = j;
        }
        return br;
    }

public:
    static int findPattern(std::string text, std::string pattern) {
        int n = static_cast<int>(text.length());
        int m = static_cast<int> (pattern.length());

        int kol = 0;
        int index = -1;
        std::vector<int> brs = prefixFunc(pattern);
        std::vector<int> output;
        for (int i = 0; i < n; ++i) {
            while (kol > 0 && pattern[kol] != text[i]) {
                kol = brs[kol - 1];
            }
            if (pattern[kol] == text[i]) {
                kol++;
            }
            if (kol == m) {
                kol = brs[kol - 1];
                index = i - m + 1;
            }
        }
        return index;
    }
};