#ifndef DS_PROJECT_UTILS_HPP
#define DS_PROJECT_UTILS_HPP

#include <string>
#include <vector>

inline std::string trimmed(std::string const& str) {
    auto beginning = str.find_first_not_of(" \t");
    auto ending = str.find_last_not_of(" \t");

    if (beginning == std::string::npos) { beginning = 0; }

    if (ending == std::string::npos) {
        return str.substr(beginning);
    } else {
        return str.substr(beginning, ending - beginning + 1);
    }
}

inline auto split(std::string const & s) {
    std::vector<std::string> result(1);
    for (auto const& t : s) {
        if (t != ' ') {
            result.back().push_back(t);
        } else if (!result.back().empty()) {
            result.emplace_back();
        }
    }
    if (result.back().empty()) result.pop_back();
    return result;
}

inline auto split(std::string const & s, char c) {
    std::vector<std::string> result(1);
    for (auto const& t : s) {
        if (t == c) {
            result.emplace_back();
        } else {
            result.back().push_back(t);
        }
    }
    return result;
}

#endif
