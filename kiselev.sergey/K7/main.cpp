#include <exception>
#include <iostream>
#include "beTree.hpp"
#include "iterator.hpp"

template< typename T >
std::ostream& output(std::ostream& out, kiselev::BiTree< T >* root, const std::string& text)
{
    kiselev::BiTreeIterator< T > it{ root };
  if (text == "tomax")
  {
    while (it.hasPrev())
    {
      it = it.prev();
    }
    out << it.data();
    it = it.next();
    while (it.hasNext())
    {
      out << " " << it.data();
      it = it.next();
    }
  }
  else if (text == "tomin")
  {
    while (it.hasNext())
    {
      it = it.next();
    }
    out << it.data();
    while (it.hasPrev())
    {
      out << " " << it.data();
      it = it.prev();
    }
  }
  else
  {
    throw std::logic_error("Unknown command");
  }
  return out;
}
int main()
{
  size_t length;
  std::cin >> length;
  kiselev::BiTree< int >* root = nullptr;
  try
  {
    for (size_t i = 0; i < length; ++i)
    {
      int number = 0;
      if (!std::cin >> number)
      {
        std::cerr << "Incorrect number\n";
        deleteTree(root);
        return 1;
      }
      root = pushTree(root, number);
    }
    std::string command;
    std::cin >> command;
    output(std::cout, root, command);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    deleteTree(root);
    return 1;
  }
}
