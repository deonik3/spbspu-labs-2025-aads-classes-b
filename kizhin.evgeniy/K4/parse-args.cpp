#include "parse-args.hpp"
#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>

int kizhin::parseArgs(std::ostream& out, const int argc, const char* const* const argv)
{
  constexpr std::array< const char*, 3 > values{ "0", "1", "2" };
  bool isValid = argc == 2 && argv[1][0] != '\0' && argv[1][1] == '\0';
  const auto pred = [&argv](const char* v) -> bool
  {
    return std::strcmp(v, argv[1]) == 0;
  };
  isValid = isValid && std::any_of(values.begin(), values.end(), pred);
  if (!isValid) {
    out << "Usage: " << argv[0] << " [0|1|2]\n";
    return 0;
  }
  return std::stoi(argv[1]);
}

