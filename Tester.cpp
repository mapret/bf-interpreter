#include "Interpreter.hpp"
#include "Tester.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>


namespace fs = std::filesystem;
using Clock = std::chrono::high_resolution_clock;

int Tester::test(bool simple)
{
  std::set<std::string> long_testcases = {
      "Collatz",
      "Counter",
      "EasyOpt",
      "Factor",
      "Hanoi",
      "Life",
      "Mandelbrot",
      "Mandelbrot-tiny"
  };

  std::vector<std::string> tests;
  for (const auto& direntry : fs::directory_iterator("test"))
  {
    const auto& path = direntry.path();
    if (path.extension() == ".b" && (!simple || long_testcases.find(path.stem()) == long_testcases.end()))
      tests.push_back(path.stem());
  }
  std::sort(tests.begin(), tests.end());

  int num_correct = 0;
  int num_wrong = 0;

  auto start_time = Clock::now();
  for (const auto& test : tests)
  {
    std::ifstream file_in("test/" + test + ".b", std::ios::binary);
    if (!file_in)
      throw std::runtime_error("Failed to open " + test + ".b");
    std::stringstream buffer;
    buffer << file_in.rdbuf();

    std::stringstream input;
    if (fs::exists("test/" + test + ".in"))
    {
      std::ifstream input_in("test/" + test + ".in", std::ios::binary);
      input << input_in.rdbuf();
    }
    std::stringstream output;
    printf("Testing %-50s", test.c_str());
    std::cout.flush();
    auto test_start_time = Clock::now();
    Interpreter::interpret([&](){return input.get();}, [&](char c){output << c;}, buffer.str());
    std::chrono::duration<float> ts = Clock::now() - test_start_time;

    std::string reference = "OK\n";
    {
      std::ifstream reference_in("test/" + test + ".out");
      if (reference_in)
        reference = std::string((std::istreambuf_iterator<char>(reference_in)), std::istreambuf_iterator<char>());
    }
    if (reference == output.str())
    {
      std::cout << " [OK]    ";
      num_correct++;
    }
    else
    {
      std::cout << " [ERROR] ";
      num_wrong++;
    }
    printf("(%.2fs)\n", ts.count());
  }
  std::chrono::duration<float> time = Clock::now() - start_time;
  std::cout << std::string(80, '-') << std::endl;
  const char* correct_string = num_wrong == 0 ? "[OK]" : "[ERROR]";
  int num_written;
  printf("Total correct/wrong: %d/%d%n", num_correct, num_wrong, &num_written);
  printf("%s%s     %.2f\n", std::string(size_t(59 - num_written), ' ').c_str(), correct_string, time.count());

  return num_wrong;
}
