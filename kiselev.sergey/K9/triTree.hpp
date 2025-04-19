#ifndef TRITREE_HPP
#define TRITREE_HPP
#include <functional>

namespace kiselev
{
  template< class T, class Cmp = std::less< T > >
  struct TriTree
  {
    std::pair< T, T > data;
    TriTree< T >* left;
    TriTree< T >* middle;
    TriTree< T>* right;
    TriTree< T >* parent;
  };

  template< typename T, class Cmp = std::less< T > >
  struct TriTreeIterator
  {
    using this_t = TriTreeIterator< T >;
    bool hasNext() const;
    bool hasPrev() const;

    this_t prev() const;
    this_t next() const;

    std::pair< T, T > & data();

    TriTree< T >* node;
  };
}
#endif
