#include "BrainfuckInterpreter.hpp"

#include <map>
#include <sstream>
#include <stack>
#include <vector>

void BrainfuckInterpreter::interpret(const CinFunction& cin_function,
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
  std::map<const char*, const char*> jump_table;
  {
    std::stack<const char*> opening_brackets;
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

  std::vector<char> memory(5000, 0); //TODO: change to on-demand memory?
  auto ip = code_stripped.data();
  const char* ip_end = code_stripped.data() + code_stripped.size();
  auto dp = memory.data();

  //Interpret code until finished
  while (ip != ip_end)
  {
    switch (*ip)
    {
      case '>': //increment current byte address
        ++dp;
        break;
      case '<': //decrement current byte address
        --dp;
        break;
      case '+': //increment current byte value
        ++*dp;
        break;
      case '-': //decrement current byte value
        --*dp;
        break;
      case '.': //output current byte
        cout_function(*dp);
        break;
      case ',': //read to current byte
        *dp = cin_function();
        break;
      case '[': //loop start
        if (*dp == 0)
          ip = jump_table[ip]; //jump to loop end
        break;                 //do nothing
      case ']': //loop end
        if (*dp != 0)
          ip = jump_table[ip]; //jump to loop start
        break;                 //do nothing
    }
    ip++;
  }
}
