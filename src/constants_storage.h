#pragma once

#include <string_view>
#include <unordered_map>

namespace constants {

using namespace std::literals;

constexpr static char kDelimeter = ' ';

enum class Operations { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION};

const std::unordered_map<char, Operations> char_to_operations{
    {'+', Operations::ADDITION},
    {'-', Operations::SUBTRACTION},
    {'*', Operations::MULTIPLICATION},
    {'/', Operations::DIVISION},
};

}  // namespace constants