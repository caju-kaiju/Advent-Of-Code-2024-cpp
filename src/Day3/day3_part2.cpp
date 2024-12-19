#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <regex>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<unsigned long, unsigned long>> parse(std::string line);

std::regex pattern{"don't\\(\\)|mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)"};

bool mul_enabled = true;
auto pair_mul = [](std::pair<unsigned long, unsigned long> p) -> unsigned long { return p.first * p.second; };

int main() {
    const std::string filename = "day3_input.txt";

    std::ifstream file;
    file.open(filename, std::ifstream::in);
    if (!file) {
        std::cout << "File failed to open";
        exit(1);
    }

    std::string line{};
    unsigned long sum{0};
    std::vector<std::pair<unsigned long, unsigned long>> numbers;
    while (std::getline(file, line)) {
        numbers = parse(std::move(line));

        auto pair_mul_view = numbers | std::ranges::views::transform(pair_mul) | std::views::common;
        sum += std::accumulate(pair_mul_view.begin(), pair_mul_view.end(), 0);
    }

    std::cout << sum;
}

std::vector<std::pair<unsigned long, unsigned long>> parse(std::string line) {
    std::smatch match;
    std::vector<std::pair<unsigned long, unsigned long>> numbers;

    std::string temp{};
    for(std::smatch sm; std::regex_search(line, sm, pattern);) {
        bool pass = false;

        if (sm.str() == "don't()") {
            mul_enabled = false;
            pass = true;
        }
        else if (sm.str() == "do()") {
            mul_enabled = true;
            pass = true;
        }

        if (mul_enabled && !pass) {
            numbers.emplace_back(std::stoul(sm[1].str()), std::stoul(sm[2].str()));
        }

        line = sm.suffix();
    }

    return numbers;
}

