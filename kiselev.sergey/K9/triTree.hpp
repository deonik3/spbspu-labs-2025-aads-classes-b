#ifndef TRITREE_HPP
#define TRITREE_HPP
#include <functional>
#include "triTreeIterator.hpp"

namespace kiselev
{
  template< class T, class Cmp >
  struct TriTree
  {
    TriTree() noexcept;
    TriTree(const std::pair< T, T >&);
    ~TriTree();
    std::pair< TriTreeIterator< T >, bool >& insert(std::pair< T, T >);
    void clear() noexcept;
    TriTreeIterator< T > begin() const noexcept;
    TriTreeIterator< T > rbegin() const noexcept;
    TriTreeIterator< T > end() const noexcept;

    std::pair< T, T > data;
    TriTree< T >* left;
    TriTree< T >* middle;
    TriTree< T>* right;
    TriTree< T >* parent;
  };
}
#endif
