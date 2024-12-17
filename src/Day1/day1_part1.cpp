#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

std::pair<std::vector<unsigned int>, std::vector<unsigned int>> parse(const std::string& filename);
std::regex pattern{"(\\d+)\\s+(\\d+)"};

int main() {
    const std::string filename = "day1_input.txt";
    auto input_pair = parse(filename);

    std::vector left = std::move(input_pair.first);
    std::vector right = std::move(input_pair.second);

    if (left.size() != right.size()) {
        std:: cout << "Left, Right vector sizes do not match";
        exit(1);
    }

    std::ranges::sort(left, std::greater<unsigned int>());
    std::ranges::sort(right, std::greater<unsigned int>());

    auto distance = [](unsigned int a, unsigned int b) { if (a > b) return a - b; else return b - a; };
    unsigned int sum{0};
    for (size_t i = 0U; i < left.size(); ++i) {
        unsigned int d = distance(left.at(i), right.at(i));
        sum = sum + d;
    }

    std::cout << sum;

    return 0;
}

std::pair<std::vector<unsigned int>, std::vector<unsigned int>> parse(const std::string& filename) {
    std::ifstream file;
    file.open(filename, std::ifstream::in);
    if (!file) {
        std::cout << "File failed to open";
        exit(1);
    }

    std::vector<unsigned int> left_list{};
    std::vector<unsigned int> right_list{};

    std::string line{""};
    std::smatch match;
    std::string number1{""};
    std::string number2{""};
    while (std::getline(file, line)) {
        std::regex_search(line, match, pattern);
        if (!match.empty()) {
            left_list.push_back(std::stoul(match[1].str()));
            right_list.push_back(std::stoul(match[2].str()));
        }
    }

    return std::pair(std::move(left_list), std::move(right_list));
}

