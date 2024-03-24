#pragma once

#include <string_view>
#include <unordered_map>

namespace constants {

using namespace std::literals;

enum class Operations { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION };

const std::unordered_map<std::string_view, Operations> char_to_operations{
    {"+"sv, Operations::ADDITION},
    {"-"sv, Operations::SUBTRACTION},
    {"*"sv, Operations::MULTIPLICATION},
    {"/"sv, Operations::DIVISION},
};

}  // namespace constants