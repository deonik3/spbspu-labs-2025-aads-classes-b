#include <cstddef>
#include <exception>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>
#include <utility>
#include "triTree.hpp"

using Tree = kiselev::TriTree< int >;
using value = std::pair< int, int >;
namespace
{
  size_t countIntersects(int v1, int v2, const Tree* tree)
  {
    size_t count = 0;
    for (auto it = tree->begin(); it.node != nullptr; it = it.next())
    {
      value val = it.data();
      if (v1 <= val.second && v2 >= val.first )
      {
        ++count;
      }
    }
    return count;
  }

  size_t countCovers(int v1, int v2, const Tree* tree)
  {
    size_t count = 0;
    for (auto it = tree->begin(); it.node != nullptr; it = it.next())
    {
      value val = it.data();
      if (v1 <= val.first && v2 >= val.second)
      {
        ++count;
      }
    }
    return count;
  }

  size_t countAvoids(int v1, int v2, const Tree* tree)
  {
    size_t count = 0;
    for (auto it = tree->begin(); it.node != nullptr; it = it.next())
    {
      value val = it.data();
      if (v1 > val.second || v2 < val.first)
      {
        ++count;
      }
    }
    return count;
  }

  /*
  std::ostream& outputToMax(std::ostream& out, const Tree* tree)
  {
    Tree::Iterator it = tree->begin();
    out << it;
    it.next();
    for (; it.hasNext(); it = it.next())
    {
      out << ' ' << it;
    }
    return out;
  }

  std::ostream& outputToMin(std::ostream& out, const Tree* tree)
  {
    Tree::Iterator it = tree->rbegin();
    out << it;
    it = it.prev();
    for (; it.hasPrev(); it = it.prev())
    {
      out << ' ' << it;
    }
    return out;
  }
  */
  std::ostream& outputWithCommand(std::ostream& out, std::istream& in, Tree* tree, const std::string& command)
  {
    int v1 = 0;
    int v2 = 0;
    if (!(in >> v1 >> v2))
    {
      in.clear();
      return out << "<INVALID COMMAND>";
    }
    if (v1 > v2)
    {
      return out << "<INVALID COMMAND>";
    }
    if (command == "intersects")
    {
      out << countIntersects(v1, v2, tree);
    }
    else if (command == "covers")
    {
      out << countCovers(v1, v2, tree);
    }
    else if (command == "avoids")
    {
      out << countAvoids(v1, v2, tree);
    }
    return out;
  }
}
int main()
{
  size_t size = 0;
  std::cin >> size;
  if (!(std::cin))
  {
    std::cerr << "Incorrect size";
    return 1;
  }
  Tree* tree = new Tree{};
  try
  {
    for (size_t i = 0; i < size; ++i)
    {
      std::pair< int, int > value;
      std::cin >> value.first >> value.second;
      tree->insert(value);
    }
    std::string command = "";
    while (!(std::cin >> command).eof())
    {
      if (command != "itersects" || command != "covers" || command != "avoids")
      {
        std::cerr << "Incorrect command\n";
        tree->clear();
        delete tree;
        return 1;
      }
      outputWithCommand(std::cout, std::cin, tree, command) << "\n";
    }
    tree->clear();
    delete tree;
  }
  catch (const std::exception&)
  {
    tree->clear();
    delete tree;
    return 1;
  }
}
