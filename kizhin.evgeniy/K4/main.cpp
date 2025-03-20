#include <iostream>
#include "forward-list.hpp"
#include "io-utils.hpp"
#include "parse-args.hpp"

int main(int argc, char** argv)
{
  kizhin::FwdList< int >* list = nullptr;
  try {
    int result = kizhin::parseArgs(std::cerr, argc, argv);
    list = kizhin::inputFwdList< int >(std::cin);
    if (!std::cin.eof() && !std::cin) {
      std::cerr << "Failed to input\n";
      clear(list);
      return 1;
    } else if (std::cin.eof() && list == nullptr) {
      std::cout << '\n';
      return 0;
    }
    if (result == 0) {
      list = reverseWithList(list);
    } else if (result == 1) {
      list = reverseCleanly(list);
    } else if (result == 2) {
      list = reverseRecursively(list);
    }
    outputFwdList(std::cout, list) << '\n';
  } catch (const std::exception& e) {
    clear(list);
    std::cerr << e.what() << '\n';
    return 1;
  }
  clear(list);
}

