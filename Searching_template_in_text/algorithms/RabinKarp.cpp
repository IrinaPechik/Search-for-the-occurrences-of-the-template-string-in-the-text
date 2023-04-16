#include <string>

class RabinKarp {
private:

    static int get_hash(std::string text, int m) {
        int res = 0;
        for (int i = 0; i < m; ++i) {
            res = (256 * res + text[i]) % 13;
        }
        return res;
    }
public:
    static int findPattern(std::string text, std::string pattern) {
        int n = static_cast<int>(text.length());
        int m = static_cast<int>(pattern.length());
        int multiply = 1;
        int j;
        int index = -1;

        for (int i = 0; i < m - 1; i++) {
            multiply = (multiply * 256) % 13;
        }
        int pat_hash = get_hash(pattern, m);
        int text_hash = get_hash(text, m);
        for (int i = 0; i <= n - m; i++) {
            if (pat_hash == text_hash) {
                for (j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        break;
                    }
                }
                if (j == m) {
                    index = i;
                }
            }
            if (i < n - m) {
                text_hash = (256 * (text_hash - text[i] * multiply) + text[i + m]) % 13;
                if (text_hash < 0) {
                    text_hash = (text_hash + 13);
                }
            }
        }
        return index;
    }
};

