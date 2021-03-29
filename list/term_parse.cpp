#include <string>
#include <iostream>
#include <forward_list>
#include "fraction.h"

void trim(std::string & str) {
    auto beginning = str.find_first_not_of(" \t");
    auto ending = str.find_last_not_of(" \t");
    if (ending != std::string::npos) str = str.substr(0, ending + 1);
    if (beginning != std::string::npos) str = str.substr(beginning);
}

auto term_parse(const std::string & term_str) {
    auto term = term_str; // term_str example: " 6/5xyz^3"
    trim(term);
    // std::cout << std::format("term:\"{}\"\n", term);

    std::string numbers = "0123456789./\\()^{}";

    using expo_pair = std::pair<char, fraction>;
    std::forward_list<expo_pair> unknown_pairs;

    auto after_number_pos = term.find_first_not_of(numbers);
    auto coef_str = term.substr(0, after_number_pos);
    // double coef;
    // try { coef = std::stod(coef_str); } catch(...) { coef = 1; }
    fraction coef;
    if (coef_str.empty()) coef = 1;
    else coef = fraction(coef_str);
    // std::cout << std::format("coef: \"{}\" -> {}\n", coef_str, coef);
    unknown_pairs.push_front(expo_pair('#',coef));

    while (after_number_pos != std::string::npos) {
        term = term.substr(after_number_pos);
        // std::cout << std::format("term: \"{}\" ", term);
        auto unknown = term[0];
        after_number_pos = term.find_first_not_of(numbers, 1);
        auto expo_str = term.substr(1, after_number_pos - 1);
        trim(expo_str);
        fraction expo = 1;
        if (!expo_str.empty()) expo = fraction(expo_str);
        // std::cout << std::format("unknown: {} expo: \"{}\" -> {}\n", unknown, expo_str, expo);
        unknown_pairs.push_front(expo_pair(unknown,expo));
    }

    return unknown_pairs;
}

int main() {
    std::string in;
    while (std::cin >> in) {
        if (in == "#") break;
        auto unknown_pairs = term_parse(in);
        for (auto i : unknown_pairs) {
            auto [unknown, expo] = i;
            //std::cout << std::format("unknown: {} expo: {}\n", unknown, expo);
            std::cout << "unknown: " << unknown << " expo: " << expo << '\n';
        }        
    }
}
