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

std::vector<std::pair<int, int>> parse(std::string line);

std::regex pattern{"mul\\((\\d+),(\\d+)\\)"};

auto printv = [](std::vector<std::pair<int, int>>& v){
    for (const auto& p : v) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
};

auto pair_mul = [](std::pair<int, int> p) -> int { return p.first * p.second; };

int main() {
    const std::string filename = "day3_input_example.txt";

    std::ifstream file;
    file.open(filename, std::ifstream::in);
    if (!file) {
        std::cout << "File failed to open";
        exit(1);
    }

    std::string line{};
    int sum{0};
    std::vector<std::pair<int, int>> numbers;
    while (std::getline(file, line)) {
        numbers = parse(std::move(line));
        // printv(numbers);

        auto pair_mul_view = numbers | std::ranges::views::transform(pair_mul) | std::views::common;
        sum += std::accumulate(pair_mul_view.begin(), pair_mul_view.end(), 0);
    }

    std::cout << sum;
}

std::vector<std::pair<int, int>> parse(std::string line) {
    std::smatch match;
    std::vector<std::pair<int, int>> numbers;

    for(std::smatch sm; std::regex_search(line, sm, pattern);) {
        numbers.emplace_back(std::stoul(sm[1].str()), std::stoul(sm[2].str()));
        line = sm.suffix();
    }

    return numbers;
}

