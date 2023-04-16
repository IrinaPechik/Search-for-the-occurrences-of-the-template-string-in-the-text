#include <iostream>
#include <vector>

class Pattern {
public:
    Pattern() = default;
    Pattern(std::string str) {
        pattern = str;
    }
    int getLength() {
        return pattern.length();
    }
    void setValue(int position, char value) {
        pattern[position] = value;
    }
    void setPositions(int pos) {
        positions.push_back(pos);
    }
    std::vector<int> getPositions() {
        return positions;
    }
    std::string getPattern() {
        return pattern;
    }
    ~Pattern() = default;
private:
    std::string pattern;
    std::vector<int> positions;
};
