#include <cstddef>
#include <iostream>
#include <istream>
#include <new>
#include <utility>
#include "triTree.hpp"

using Tree = kiselev::TriTree< int >;
namespace
{
}
int main()
{
  size_t size = 0;
  std::cin >> size;
  if (size == 0)
  {
    std::cerr << "The sequence is empty\n";
    return 1;
  }
  Tree* tree = nullptr;
  try
  {
    for (size_t i = 0; i < size; ++i)
    {
      std::pair< int, int > value;
      std::cin >> value.first >> value.second;
      tree->insert(value);
    }
  }
  catch (...)
  {
    tree->clear();
    return 1;
  }
}
