#include "Interpreter.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
  if (argc != 2)
    return 1;

  std::ifstream file_in(argv[1], std::ios::binary);
  if (!file_in)
  {
    std::cout << "Error opening " << argv[1] << std::endl;
    return 2;
  }

  std::stringstream buffer;
  buffer << file_in.rdbuf();

  Interpreter::interpret(getchar, putchar, buffer.str());

  //Code for benchmarking purposes
  /*int cnt = 0;
  auto start = std::chrono::high_resolution_clock::now();
  Interpreter::interpret([&cnt]() { return "123456789\n"[cnt++]; }, putchar, buffer.str());
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f << "s" << std::endl;*/

  return 0;
}
