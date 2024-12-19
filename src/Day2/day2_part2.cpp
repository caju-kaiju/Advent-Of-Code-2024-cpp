#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

std::vector<unsigned int> parse(std::string line);

enum class Direction {
    Increasing,
    Decreasing,
    Neither
};

int main() {
    const std::string filename = "day2_input.txt";

    std::ifstream file;
    file.open(filename, std::ifstream::in);
    if (!file) {
        std::cout << "File failed to open";
        exit(1);
    }

    auto is_valid_difference = [](unsigned int a, unsigned int b) { 
        int difference = a - b;
        difference = std::abs(difference);

        if ( (difference < 1) || (difference > 3) ) return false;
        return true;
    };

    auto get_direction = [](unsigned int a, unsigned int b) {
        int difference = a - b;
        if (difference < 0) return Direction::Increasing;
        else if (difference > 0) return Direction::Decreasing;
        else return Direction::Neither;
    };

    auto is_safe = [get_direction, is_valid_difference]
                   (Direction target_direction, unsigned int a, unsigned int b) {
        return (get_direction(a, b) == target_direction) && is_valid_difference(a, b);
    };

    std::string line{};
    std::vector<unsigned int> levels;
    unsigned int safe_count{0};
    while (std::getline(file, line)) {
        levels = parse(std::move(line));
        bool safe = false;
        int dampener{-1};

        for (size_t index{0}; index < levels.size() + 1; ++index) {
            std::vector<unsigned int> levels_modified = levels;
            if (dampener >= 0)
                levels_modified.erase(levels_modified.begin() + dampener);

            Direction target_direction = get_direction(levels_modified.at(0), levels_modified.at(1));
            unsigned int previous_num = levels_modified.at(0);

            for (auto num : std::views::all(levels_modified) | std::views::drop(1)) {
                safe = is_safe(target_direction, previous_num, num);

                previous_num = num;
                if (!safe) {
                    dampener++;
                    break;
                }
            }

            if (safe) break;
        }

        if (safe) safe_count++;
    }

    std::cout << safe_count;
}

std::vector<unsigned int> parse(std::string line) {
    std::stringstream stream(line);
    std::string temp;
    std::vector<unsigned int> tokens;

    while (std::getline(stream, temp, ' ')) {
        tokens.push_back(std::stoul(temp.c_str()));
    }

    return tokens;
}

