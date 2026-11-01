#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "TimSort.h"

bool isNumber(const std::string& token) {
    if (token.empty()) return false;

    int i = 0;

    if (token[i] == '-') {
        i++;
        if (i == token.size()) return false;
    }

    int dotCount = 0;
    int digitCount = 0;

    for (; i < token.size(); i++) {
        if (token[i] >= '0' && token[i] <= '9') {
            digitCount++;
        }
        else if (token[i] == '.') {
            dotCount++;

            if (dotCount > 1 || i == 0 || i == token.size() - 1) {
                return false;
            }
        }
        else {
            return false;
        }
    }

    return digitCount > 0;
}

std::string formatNumber(double value) {
    if (value == 0.0) value = 0.0;

    std::ostringstream out;
    out << std::fixed << std::setprecision(6) << value;

    std::string result = out.str();

    while (!result.empty() && result.back() == '0') {
        result.pop_back();
    }

    if (!result.empty() && result.back() == '.') {
        result.pop_back();
    }

    return result;
}

int main() {
    std::string line;
    std::getline(std::cin, line);

    DynamicArray<double> array;

    std::istringstream input(line);
    std::string token;

    while (input >> token) {
        if (!isNumber(token)) {
            std::cerr << "Unknown token: " << token << '\n';
            return 1;
        }

        array.add(array.size(), std::stod(token));
    }

    TimSort::sort(array);

    std::cout << line << "\n\n";

    for (int i = 0; i < array.size(); i++) {
        if (i > 0) std::cout << ", ";

        std::cout << formatNumber(array.get(i));
    }

    std::cout << '\n';

    return 0;
}