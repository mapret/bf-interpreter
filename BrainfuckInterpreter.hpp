#pragma once

#include <functional>

using CinFunction = std::function<char()>;
using CoutFunction = std::function<void(char)>;

class BrainfuckInterpreter
{
  public:
    static void interpret(const CinFunction& cin_function,
                          const CoutFunction& cout_function,
                          const std::string& code);
};
