#include "Interpreter.hpp"
#include "Tape.hpp"

#include <map>
#include <sstream>
#include <stack>
#include <vector>

void Interpreter::interpret(const CinFunction& cin_function,
                            const CoutFunction& cout_function,
                            const std::string& code)
{
  //Preprocessing: Remove all non-code characters
  std::stringstream d;
  for (const auto& c : code)
  {
    switch (c)
    {
      case '>':
      case '<':
      case '+':
      case '-':
      case '.':
      case ',':
      case '[':
      case ']':
        d << c;
    }
  }
  std::string code_stripped = d.str();

  //Create jump table for fast calls to [ and ]
  std::map<char*, char*> jump_table;
  {
    std::stack<char*> opening_brackets;
    auto end = code_stripped.data() + code_stripped.size();
    for (auto it = code_stripped.data(); it != end; it++)
    {
      switch (*it)
      {
        case '[':
          opening_brackets.push(it);
          break;
        case ']':
          jump_table[it] = opening_brackets.top();
          jump_table[opening_brackets.top()] = it;
          opening_brackets.pop();
          break;
      }
    }
  }

  Tape tape;
  auto ip = code_stripped.data();
  const char* ip_end = code_stripped.data() + code_stripped.size();

  //Interpret code until finished
  while (ip != ip_end)
  {
    switch (*ip)
    {
      case '>': //increment tape position
        ++tape;
        break;
      case '<': //decrement tape position
        --tape;
        break;
      case '+': //increment value at current tape position
        ++*tape;
        break;
      case '-': //decrement value at current tape position
        --*tape;
        break;
      case '.': //output value at current tape position
        cout_function(*tape);
        break;
      case ',': //store value at current tape position
        *tape = cin_function();
        break;
      case '[': //loop start
        if (*tape == 0)
          ip = jump_table[ip]; //jump to loop end
        break;                 //do nothing
      case ']': //loop end
        if (*tape != 0)
          ip = jump_table[ip]; //jump to loop start
        break;                 //do nothing
    }
    ip++;
  }
}
